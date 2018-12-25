/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Server;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.CopyOnWriteArraySet;

/**
 *
 * @author BSebring
 */
public class EchoServer {

    private ServerSocket server = null;
    
    //Needs to be syncronized
    private static ConcurrentHashMap<String,AccountInfo> userData; //Setup
    private static ConcurrentHashMap<String,ConnectionHandler> userConnection;  //Login  //Sending Messages
    private static ConcurrentHashMap<Long,String> loginTable; //Login  //Finding Username
    private static CopyOnWriteArraySet<String> bannedList;
    private static CopyOnWriteArraySet<String> registeredCommands;
    private static CopyOnWriteArraySet<String> registeredUsers;
    //private static CopyOnWriteArraySet<ConnectionHandler> registeredConnections;
    
    
    private static final String filename = "userData.dat";
    private static final int MAX_MODS = 5;
    private static final int SUB_COST = 5;
    private static boolean subMode = false;

    public EchoServer(int port) {
        userData = new ConcurrentHashMap<>();
        userConnection = new ConcurrentHashMap<>();
        loginTable = new ConcurrentHashMap<>();
        bannedList = new CopyOnWriteArraySet<>();
        registeredCommands = new CopyOnWriteArraySet<>();
        registeredCommands.add("quit");
        registeredUsers = new CopyOnWriteArraySet<>();
        //registeredConnections = new CopyOnWriteArraySet<>();
        
        
        try {
            System.out.println("Binding to port " + port + ", please wait  ...");
            //Create a server listening on 'port' port
            server = new ServerSocket(port);
            System.out.println("Server started: " + server);
            System.out.println("Waiting for a clients ...");
            
        } 
        catch (IOException ioe) {
            System.out.println(ioe);
        }
    }
    
    //Pass the socket returned from the ServerSocket up to the ServerDriver
    public Socket accept()
    {
        try
        {
            return server.accept();
        }
        catch(Exception ex)
        {
            
        }
        return new Socket();
    }
    
    //Used to determine if a login is successful and to update the list of 
    //logged in users based on userData (aka AccountInfo)
    public static boolean authenticate(String username, String password, ConnectionHandler socketObject) 
    {
        if( !registeredUsers.contains(username))
        {
            return false;
        }
        
        AccountInfo tempUser = userData.get(username);
        
        if( tempUser.isLoggedIn() )
        {
            return false;
        }
        else if( (tempUser.getPassword()).equals(password) )
        {
            tempUser.setLoggedIn(true);
            loginTable.put(socketObject.socketID, username);
            userConnection.put(username,socketObject);
            //registeredConnections.add(socketObject);
            return true;
        }
        
        return false;
    }
    
    //Adds a new user to userData - Should it login as well
    public static boolean setup(String username, String password)
    {
        if(isUserRegistered(username))
        {
            return false;
        }
        else
        {
            userData.put(username, new AccountInfo(username,password));
            registeredUsers.add(username);
            return true;
        }
    }
    
    public static void pushBroadcastMessage(EchoServerMessage serverResponseMessage) 
    {
        //if !subMode this
        //else pushSubBroadcaseMessage
        ConnectionHandler tempHandler;
        for(String user : userConnection.keySet())
        {
            tempHandler = userConnection.get(user);
            tempHandler.pushServerMessage(serverResponseMessage);
        }
    }
    
    private static void pushSubBroadcastMessage(EchoServerMessage inputMessage) 
    {
        ConnectionHandler tempHandler;
        
        for(String user : userConnection.keySet())
        {
            if(userTypeLookup(user) != AccountType.User)
            {
                tempHandler = userConnection.get(user);
                tempHandler.pushServerMessage(inputMessage);
            }
        }
    }
    
    public static void pushDirectMessage(EchoServerMessage serverResponseMessage) 
    {
        (userConnection.get(serverResponseMessage.destUsername)).pushServerMessage(serverResponseMessage);
    }
    
    //command does not contain the !
    //Username and type are of the source user
    public static boolean processCommand(String command, String username, AccountType userType)
    {
        EchoServerMessageBuilder messageBuilder = new EchoServerMessageBuilder();
        if(command.equals("quit"))
        {
            if(userType == AccountType.Mod || userType == AccountType.Streamer)
            {
                try{ quitServer(); }
                catch(Exception ex){}
                return true;
            }
            else
            {
                return false;
            }
        }
        else if(command.equals("submodeon"))
        {
            if(userType == AccountType.Streamer)
            {
                subMode = true;
                return true;
            }
            else
            {
                return false;
            }
            
        }
        else if(command.equals("submodeoff"))
        {
            if(userType == AccountType.Streamer)
            {
                subMode = false;
                return true;
            }
            else
            {
                return false;
            }
        }
        else if(command.equals("balance"))
        {
            AccountInfo user = userData.get(username);
            if(user == null)
            {
                return false;
            }
            
            if(registeredUsers.contains(username))
            {
                messageBuilder.setAsDefaultMessage();
                messageBuilder.setMessage("balance: " + user.getBalance());
                messageBuilder.setUsername(username);
                messageBuilder.setDestUsername(username);
                messageBuilder.setUserType(userTypeLookup(username));
                messageBuilder.setMessageType(MessageType.DirectMessage);
                pushDirectMessage(messageBuilder.buildMessage());
                return true;
            }
            else
            {
                return false;
            }
        }
        else if(command.equals("sub"))
        {
            AccountInfo user = userData.get(username);
            if(user == null)
            {
                return false;
            }
            else if(registeredUsers.contains(username))
            {
                if(user.getAccountType() != AccountType.User)
                {
                    return false;
                }
                else if(user.getBalance() >= SUB_COST)
                {
                    user.removeFromBalance(SUB_COST);
                    user.setAccountType(AccountType.Sub);
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else if(command.equals("emote"))
        {
            if(userType != AccountType.User)
            {
                messageBuilder.setAsDefaultMessage();
                messageBuilder.setMessage(":)");
                messageBuilder.setUsername(username);
                messageBuilder.setUserType(userType);
                pushBroadcastMessage(messageBuilder.buildMessage());
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            String[] testLength = command.split(" ");
            if(testLength.length <= 1)
            {
                return false;
            }
            String resultCommand = command.split(" ")[0];
            String resultParams = command.substring(resultCommand.length()+1);
            return processCommandWithTarget(resultCommand, resultParams, username, userType);
        }
    }
    
    public static boolean processCommandWithTarget(String command, String parameters, String username, AccountType userType)
    {
        EchoServerMessageBuilder messageBuilder = new EchoServerMessageBuilder();
        messageBuilder.setAsDefaultMessage();
        if(command.equals("kick") && (userType == AccountType.Mod || userType == AccountType.Streamer))
        {
            AccountInfo user = userData.get(parameters);
            if(user == null)
            {
                return false;
            }
            else if(user.isLoggedIn())
            {
                
                //send message
                ConnectionHandler userHandle = userConnection.get(parameters);
                long userID = userHandle.socketID;
                logout(userID);
                return true;
            }
            else
            {
                return false;
            }
        }
        else if(command.equals("submessage") && (userType == AccountType.Mod || userType == AccountType.Streamer))
        {
            messageBuilder.setAsDefaultMessage();
            messageBuilder.setUserType(userType);
            messageBuilder.setUsername(username);
            messageBuilder.setMessage(parameters);
            pushSubBroadcastMessage(messageBuilder.buildMessage());
            return true;
        }
        else if(command.equals("ban") && (userType == AccountType.Mod || userType == AccountType.Streamer))
        {
            AccountInfo user = userData.get(parameters);
            if(user == null)
            {
                return false;
            }

            if(user.isLoggedIn())
            {
                
                //send message
                ConnectionHandler userHandle = userConnection.get(parameters);
                long userID = userHandle.socketID;
                logout(userID);
            }
            
            if(isUserRegistered(parameters))
            {
                userData.remove(parameters);
                return true;
            }
            else
            {
                return false;
            }
        }
        else if(command.equals("upgrade") && (userType == AccountType.Mod || userType == AccountType.Streamer))
        {
            AccountInfo user = userData.get(parameters);
            AccountType targetType = user.getAccountType();
            if(user == null)
            {
                return false;
            }
            else if(registeredUsers.contains(parameters))
            {
                if(targetType == AccountType.User)
                {
                    user.setAccountType(AccountType.Sub);
                    return true;
                }
                else if(targetType == AccountType.Sub)
                {
                    if(!allowNewMod())
                    {
                        return false;
                    }
                    else
                    {
                        user.setAccountType(AccountType.Mod);
                        return true;
                        
                    }
                }
                else if(targetType == AccountType.Mod)
                {
                    if(!doesStreamerExist())
                    {
                        user.setAccountType(AccountType.Streamer);
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else if(command.equals("downgrade") && (userType == AccountType.Mod || userType == AccountType.Streamer))
        {
            AccountInfo user = userData.get(parameters);
            AccountType targetType = user.getAccountType();
            if(user == null)
            {
                return false;
            }
            else if(registeredUsers.contains(parameters))
            {
                if(targetType == AccountType.Streamer)
                {
                    user.setAccountType(AccountType.Mod);
                    return true;
                }
                else if(targetType == AccountType.Mod)
                {
                    user.setAccountType(AccountType.Sub);
                    return true;
                }
                else if(targetType == AccountType.Sub)
                {
                    user.setAccountType(AccountType.User);
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else if(command.equals("newpassword"))
        {
            //usage !newpassword oldpassword newpassword
            //parameters = "mburns coolpassword"
            String oldPassword = parameters.split(" ")[0];
            String newPassword = parameters.split(" ")[1];
            AccountInfo user = userData.get(username);
            if(user == null)
            {
                return false;
            }
            else if(registeredUsers.contains(username))
            {
                if(oldPassword.equals(user.getPassword()))
                {
                    user.setPassword(newPassword);
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else if(command.equals("cheer") && (userType != AccountType.Streamer))
        {
            AccountInfo user = userData.get(username);
            int amount;
            try{amount = Integer.parseInt(parameters);}
            catch(NumberFormatException ife){ amount = 0; }
            
            if(user == null)
            {
                return false;
            }
            else if(registeredUsers.contains(username))
            {
                if(user.getBalance() >= amount)
                {
                    AccountInfo streamer = findStreamer();
                    if(streamer != null)
                    {
                        user.removeFromBalance(amount);
                        streamer.addToBalance(amount);
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else if(command.equals("addbalance") && (userType != AccountType.Streamer))
        {
            AccountInfo user = userData.get(username);
            if(user == null)
            {
                return false;
            }
            else if(registeredUsers.contains(username))
            {
                int deposit = Integer.parseInt(parameters);
                user.addToBalance(deposit);
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    
    //Does the user exist?
    public static boolean isUserRegistered(String username)
    {
        return registeredUsers.contains(username);
    }
    
    //Who am I? ConnectionHandler asks Server
    public static String userLookup(long socketID)
    {
        String result = loginTable.get(socketID);
        if(result == null)
        {
            result = "error";
        }
        return result;
    }
    
    public static AccountType userTypeLookup(String username) {
        return (userData.get(username)).getAccountType();
    }

    public static boolean isSubMode() {
        return subMode;
    }

    public static void setSubMode(boolean subMode) {
        EchoServer.subMode = subMode;
    }
    
    //doesStreamerExist
    private static boolean doesStreamerExist() 
    {
        //no one is a streamer
        if(findStreamer() != null)
        {
            return true;
        }
        return false;
    }
    
    private static AccountInfo findStreamer() 
    {
        for(AccountInfo user : userData.values())
        {
            if(user.getAccountType() == AccountType.Streamer)
            {
                //we found one streamer
                return user;
            }
        }
        //no streamers found
        return null;
    }
    
    //allowMods
    private static boolean allowNewMod() 
    {
        //no one is a streamer
        boolean result = false;
        int numMods = 0;
        for(AccountInfo user : userData.values())
        {
            if(user.getAccountType() == AccountType.Mod)
            {
                //we found one streamer
                numMods++;
            }
        }
        if(numMods < MAX_MODS)
        {
            //allow a new mod
            result = true;
        }
        //otherwise there are the max allowed mods
        return result;
    }
    //update userData and loginTable
    public static void logout(long socketID) 
    {
        EchoServerMessageBuilder messageBuilder = new EchoServerMessageBuilder();
        messageBuilder.setAsDefaultMessage();
        
        String username = loginTable.get(socketID);
        ConnectionHandler userHandle = userConnection.get(username);
        
        messageBuilder.setMessageType(MessageType.Logout);
        messageBuilder.setUsername(username);
        messageBuilder.setStatus(true);
        EchoServerMessage output = messageBuilder.buildMessage();
        userHandle.pushServerMessage(output);
        loginTable.remove(socketID);
        userConnection.remove(username);
        (userData.get(username)).setLoggedIn(false);
    }
    
    //Attempts to deserialize the userData object from file of filename E://Documents/NetbeansProjects/EchoChat/
    public static void loadServer() throws FileNotFoundException, IOException, ClassNotFoundException
    {
        FileInputStream streamIn = new FileInputStream(filename);
        ObjectInputStream ois = new ObjectInputStream(streamIn);
        userData = (ConcurrentHashMap<String,AccountInfo>) ois.readObject();
        //userData.put("mburns", new AccountInfo("mburns","anchor"));
        //userData.put("rafael", new AccountInfo("rafael","light"));
        registeredCommands.clear();
        registeredCommands.add("quit");
        registeredUsers.clear();
        registeredUsers.addAll(userData.keySet());
        int counter = 1;
        for(String user : registeredUsers)
        {
            System.out.println("user " + counter + ": " + user);
            counter++;
        }
    }
    
    //Attempts to serialize the userData object to file of filename E://Documents/NetbeansProjects/EchoChat/
    public static void quitServer() throws FileNotFoundException, IOException
    {
        FileOutputStream fout = new FileOutputStream(filename);
        ObjectOutputStream oos = new ObjectOutputStream(fout);
        
        for(AccountInfo users : userData.values())
        {
            users.setLoggedIn(false);
        }
        for(Long userID : loginTable.keySet())
        {
            logout(userID);
        }
        
        oos.writeObject(userData);
        
        //System.exit(0);
    }
    
    public static void clearUserData()
    {
        userData = new ConcurrentHashMap<>();
        registeredUsers.clear();
        registeredCommands.clear();
        registeredCommands.add("quit");
    }
    

    
}
