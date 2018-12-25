/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Client;

import java.io.*;
import java.net.*;
import Server.MessageType;
import Server.EchoServerMessage;
import Server.EchoClientMessage;

/**
 *
 * @author BSebring
 */
public class EchoClient implements Runnable
{

    private Socket socket;
    private DataInputStream console;
    //private DataInputStream streamIn;
    //private DataOutputStream streamOut;
    private ObjectInputStream objStreamIn;
    private ObjectOutputStream objStreamOut;
    private boolean loggedIn = false;

    /*
        serverName is localhost etc
        serverPort is some port, 62828 for example
    */
    public EchoClient(String serverName, int serverPort){
        
        System.out.println("Establishing connection. Please wait ...");
        try 
        {
            socket = new Socket(serverName, serverPort);
            System.out.println("Connected: " + socket);
        } 
        catch (UnknownHostException uhe) 
        {
            System.out.println("Host unknown: " + uhe.getMessage());
        } 
        catch (IOException ioe) 
        {
            System.out.println("Unexpected exception: " + ioe.getMessage());
        }
    }

    @Override
    public void run()
    {
        try{ this.start(); }  catch(Exception ex2){ }
    
        //Accept connections
        //Create a new Data stream with this accepted connection
        EchoServerMessage inputServerMessage = null;
        
        try{
        
            while((inputServerMessage = (EchoServerMessage) objStreamIn.readObject()) != null)
            {
                String inputMessage = inputServerMessage.message;
                MessageType responseType = inputServerMessage.messageType;

                //enum messageType {Login, Setup, Message, Error, Command};
                if(responseType == MessageType.ChatMessage)
                {
                    ClientDriver.appendToChat(inputServerMessage);
                }
                else if(responseType == MessageType.DirectMessage)
                {
                    ClientDriver.appendToChat(inputServerMessage);
                }
                else if(responseType == MessageType.Command)
                {
                    ClientDriver.appendToChat(inputServerMessage);
                }
                else if(responseType == MessageType.Login)
                {
                    if(inputServerMessage.status)
                    {
                        loggedIn = true;
                        ClientDriver.switchToChat();
                        String successMessage = "Logged In As: " + inputServerMessage.sourceUsername;
                        ClientDriver.appendStringToChat(successMessage);
                    }
                    else
                    {
                        System.out.println("Login Failed");
                    }
                }
                else if(responseType == MessageType.Logout)
                {
                    loggedIn = false;
                    ClientDriver.switchToMain();
                }
                else if(responseType == MessageType.Setup)
                {
                    if(inputServerMessage.status)
                    {
                        ClientDriver.switchToMain();
                    }
                    else
                    {
                        ClientDriver.clearSetupText();
                    }
                }
            }
        }
        catch(EOFException eof)
        {
            ClientDriver.appendStringToChat("Server Closed");
        }
        catch (IOException ioe) {
            System.out.println("Error Reading Message (Client)");
        }
        catch (ClassNotFoundException cnfe) 
        {
            System.out.println("Error Reading Message (Client)");
        }
        //When chat is done close and exit
        try{ this.stop(); }  catch(Exception ex2){ }
    }
    
    
    //create the data streams
    public void start() throws IOException 
    {
        console = new DataInputStream(System.in);
        //streamIn = new DataInputStream(socket.getInputStream());
        //streamOut = new DataOutputStream(socket.getOutputStream());
        objStreamOut = new ObjectOutputStream(socket.getOutputStream());
        objStreamIn = new ObjectInputStream(socket.getInputStream());
    }

    //close the socket and data streams
    public void stop() 
    {
        try 
        {
            if (console != null) {
                console.close();
            }
            if (objStreamIn != null) {
                objStreamIn.close();
            }
            if (objStreamOut != null) {
                objStreamOut.close();
            }
            /*if (streamIn != null) {
                streamOut.close();
            }
            if (streamOut != null) {
                streamOut.close();
            }*/
            if (socket != null) {
                socket.close();
            }
        } 
        catch (IOException ioe) 
        {
            System.out.println("Error closing ...");
        }
    }

    public void pushClientMessage(EchoClientMessage outputMessage) 
    {
        try
        {
        objStreamOut.writeObject(outputMessage);
        objStreamOut.flush();
        }
        catch(Exception ex)
        {
            System.out.println("Error Pushing Message (Client)");
        }
    }

    public boolean isLoggedIn() {
        return loggedIn;
    }
    
    
    
    
}


