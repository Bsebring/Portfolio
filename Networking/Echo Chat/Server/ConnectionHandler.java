/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Server;

import java.io.EOFException;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.regex.Pattern;

/**
 *
 * @author BSebring
 */
public class ConnectionHandler implements Runnable
{
    private final Socket socket;
    public final long socketID;
    //private DataInputStream streamIn;
    //private DataOutputStream streamOut;
    private ObjectInputStream objStreamIn;
    private ObjectOutputStream objStreamOut;
    private static final int MAX_LOGINS = 5;
    
    
    
    ConnectionHandler(Socket clientSocket, long socketID) 
    {
        this.socket = clientSocket;
        this.socketID = socketID;
    }
    
    
    //
    @Override
    public void run()
    {
        //Accept connections
        //Create a new Data stream with this accepted connection
        try{ this.open(); } catch(IOException ex1){ System.out.println("Error Opening Data Streams"); }
        
        EchoServerMessageBuilder messageBuilder = new EchoServerMessageBuilder();
        
        //if(loginProcedure())
        //{
        //If login succeeds chat
        //LOGGED IN
        boolean loggedIn = false;
        EchoClientMessage inputClientMessage = null;
        int loginAttempts = 0;

        try
        {

            while((inputClientMessage = (EchoClientMessage) objStreamIn.readObject()) != null)
            {
                if(!loggedIn && loginAttempts < MAX_LOGINS)
                {
                    loginAttempts++;
                    loggedIn = loginProcedure(inputClientMessage);
                }
                else
                {
                    loginAttempts = 0;
                    String inputMessage = inputClientMessage.getMessage();
                    EchoServerMessage serverResponseMessage;
                    MessageType responseType = processMessage(inputClientMessage);

                    //enum messageType {Login, Setup, Message, Error, Command};
                    if(responseType == MessageType.ChatMessage)
                    {
                        
                        messageBuilder.setAsDefaultMessage();
                        String username = EchoServer.userLookup(this.socketID);
                        messageBuilder.setUsername(username);
                        AccountType userType = EchoServer.userTypeLookup(username);
                        messageBuilder.setUserType(userType);
                        messageBuilder.setMessage(inputMessage);
                        EchoServerMessage output;
                        
                        if(EchoServer.isSubMode() && (userType == AccountType.User))
                        {
                            messageBuilder.setStatus(false);
                            output = messageBuilder.buildMessage();
                            this.pushServerMessage(output);
                            continue;
                        }
                        output = messageBuilder.buildMessage();
                        EchoServer.pushBroadcastMessage(output);

                    }
                    else if(responseType == MessageType.DirectMessage)
                    {
                        messageBuilder.setAsDefaultMessage();

                        //Check if logged in
                        String username = EchoServer.userLookup(this.socketID);

                        messageBuilder.setUsername(username);
                        AccountType userType = EchoServer.userTypeLookup(username);
                        messageBuilder.setUserType(userType);

                        String[] messageTokens = inputMessage.split(" ");
                        String destUser = (messageTokens[0]).substring(1);
                        messageBuilder.setDestUsername(destUser);
                        String totalMessage = "";
                        for(int i = 1; i < messageTokens.length; i++)
                        {
                            totalMessage += messageTokens[i];
                            totalMessage += " ";
                        }
                        messageBuilder.setMessage(totalMessage);


                        serverResponseMessage = messageBuilder.buildMessage();
                        EchoServer.pushDirectMessage(serverResponseMessage);
                        messageBuilder.setDestUsername(username);
                        serverResponseMessage = messageBuilder.buildMessage();
                        EchoServer.pushDirectMessage(serverResponseMessage);

                        //Acknowledgement Response or Error Response
                        //serverResponseMessage = messageBuilder.buildMessage();
                        //objStreamOut.writeObject(serverResponseMessage);
                    }
                    else if(responseType == MessageType.Command)
                    {
                        String username = EchoServer.userLookup(this.socketID);
                        AccountType userType = EchoServer.userTypeLookup(username);
                        //clean up the command first and trim
                        String command = inputMessage.substring(1);
                        boolean commandResult = EchoServer.processCommand(command, username, userType);

                        messageBuilder.setAsDefaultMessage();
                        messageBuilder.setUserType(userType);
                        messageBuilder.setMessageType(MessageType.Command);
                        messageBuilder.setMessage(inputMessage);
                        messageBuilder.setUsername(username);
                        messageBuilder.setStatus(commandResult);
                        EchoServerMessage output = messageBuilder.buildMessage();
                        pushServerMessage(output);
                    }
                    else if(responseType == MessageType.Logout)
                    {
                        EchoServer.logout(socketID);
                        loggedIn = false;
                    }
                        //Otherwise the message is dropped
                }
            }
        }
        catch(EOFException eof)
        {
            System.out.println("Client Closed (Server)");
        }
        catch (IOException ioe) {
            System.out.println("Error Receiving Message (Server)");
        }
        catch (ClassNotFoundException cnfe) {
            System.out.println("Error Class Not Found Message (Server)");
        }
        //}
        
        //When chat is done close and exit
        try{ this.close(); }  catch(Exception ex2){ }
    }
    
    private boolean loginProcedure(EchoClientMessage inputClientLogin)
    {
        EchoServerMessageBuilder messageBuilder = new EchoServerMessageBuilder();
        messageBuilder.setAsLoginMessage();
        
        
        try
        {

            MessageType loginType = processMessage(inputClientLogin);
            String inputLoginMessage = inputClientLogin.getMessage();

            if(loginType == MessageType.Login)
            {
                String credentials = inputLoginMessage.substring(7);
                String username = credentials.split(":")[0];
                String password = credentials.split(":")[1];
                boolean loginResult = EchoServer.authenticate(username,password,this);


                //send confirm message
                messageBuilder.setAsLoginMessage();
                messageBuilder.setUsername(username);
                messageBuilder.setMessageType(MessageType.Login);
                messageBuilder.setStatus(loginResult);
                EchoServerMessage output = messageBuilder.buildMessage();
                pushServerMessage(output);
                return loginResult;
            }
            else if(loginType == MessageType.Setup)
            {
                String credentials = inputLoginMessage.substring(7);
                String username = credentials.split(":")[0];
                String password = credentials.split(":")[1];
                boolean setupResult = EchoServer.setup(username,password);


                //send confirm message
                messageBuilder.setAsLoginMessage();
                messageBuilder.setUsername(username);
                messageBuilder.setMessageType(MessageType.Setup);
                messageBuilder.setStatus(setupResult);

                EchoServerMessage output = messageBuilder.buildMessage();
                pushServerMessage(output);
                return false;
            }
        }
        catch(Exception ex)
        {
            System.out.println("Error Receiving Message (Server)");
        }
        
        return false;
    }
    
    //Used in Connection Handler for chat messages only
    private static MessageType processMessage(EchoClientMessage message) 
    {
        //
        if(Pattern.matches("^#logout$", message.getMessage()))
        {
            return MessageType.Logout;
        }
        else if(Pattern.matches("^#login .*:.*$", message.getMessage()))
        {
            return MessageType.Login;
        }
        else if(Pattern.matches("^#setup .*:.*$", message.getMessage()))
        {
            return MessageType.Setup;
        }
        else if(Pattern.matches("^!.+$", message.getMessage()))
        {
            return MessageType.Command;
        }
        else if(Pattern.matches("^@.* .+", message.getMessage()))
        {
            return MessageType.DirectMessage;
        }
        else
        {
            return MessageType.ChatMessage;
        }
        
    }
    
    public void pushServerMessage(EchoServerMessage serverResponseMessage) 
    {
        try
        {
        objStreamOut.writeObject(serverResponseMessage);
        objStreamOut.flush();
        }
        catch(Exception ex)
        {
            System.out.println("Error Sending Message (Server)");
        }
    }
    
    
    public void open() throws IOException {
        //streamIn = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
        //streamOut = new DataOutputStream(new BufferedOutputStream(socket.getOutputStream()));
        objStreamIn = new ObjectInputStream(socket.getInputStream());
        objStreamOut = new ObjectOutputStream(socket.getOutputStream());
    }

    public void close() throws IOException {
        if (socket != null) {
            socket.close();
        }
        if (objStreamIn != null) {
            objStreamIn.close();
        }
        if (objStreamOut != null) {
            objStreamOut.close();
        }
        /*if (streamIn != null) {
            streamIn.close();
        }
        if (streamOut != null) {
            streamIn.close();
        }*/
    }

    
}
