/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Client;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.concurrent.CopyOnWriteArraySet;
import javax.swing.WindowConstants;
import Server.AccountType;
import Server.MessageType;
import Server.EchoServerMessage;
import Server.EchoClientMessage;

/**
 *
 * @author BSebring
 */
public class ClientDriver 
{
    
    private static EchoChat_Main main;
    private static EchoChat_Login login;
    private static EchoChat_SignUp signUp;
    private static EchoChat_Chat chat;
    private static EchoClient client;
    private static CopyOnWriteArraySet<String> wordBlackList;
    private static final String[] bannedWords = {"fuck","shit","dick","cunt","asshole","bitch","bastard"};

    public static void main(String[] args) 
    {
        if(args.length < 2)
        {
            System.out.println("Usage: java EchoClient IP-Address Port-Number");
            System.exit(1);
        }
        
        client = new EchoClient(args[0], Integer.parseInt(args[1]));
        
        ArrayList<String> tempList = new ArrayList<>(Arrays.asList(bannedWords));
        wordBlackList = new CopyOnWriteArraySet<>(tempList);
        
        
        main = new EchoChat_Main();
        login = new EchoChat_Login(client);
        signUp = new EchoChat_SignUp(client);
        chat = new EchoChat_Chat(client);
        
        
        //Prepare GUI's
        main.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        main.pack();
        main.setVisible(true);

        login.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        login.pack();
        login.setVisible(false);

        signUp.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        signUp.pack();
        signUp.setVisible(false);

        chat.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        chat.pack();
        chat.setVisible(false);
        new Thread(client).start();
        
        
        /*
        if (args.length != 2))
        {
            System.out.println("Usage: java ChatClient host port");
        } 
        else 
        {
            client = new EchoClient("localhost", 62828);
        }
        */
    }
    public static void closeOperation()
    {
        if(client.isLoggedIn())
        {
            client.pushClientMessage(new EchoClientMessage("#logout"));
        }
        
        System.exit(0);
        
    }
    
    public static void switchToLogin() {
        chat.setVisible(false);
        signUp.setVisible(false);
        main.setVisible(false);
        login.setVisible(true);
    }

    public static void switchToChat() {
        login.setVisible(false);
        signUp.setVisible(false);
        main.setVisible(false);
        chat.setVisible(true);
    }

    public static void switchToSignUp() {
        chat.setVisible(false);
        login.setVisible(false);
        main.setVisible(false);
        signUp.setVisible(true);
    }

    public static void switchToMain() {
        chat.setVisible(false);
        login.setVisible(false);
        signUp.setVisible(false);
        main.setVisible(true);
    }

    public static void appendToChat(EchoServerMessage inputMessage) 
    {
        
        String message = filterMessage(inputMessage);
        
        if(inputMessage.messageType == MessageType.ChatMessage)
        {
            chat.appendToChatWindow(inputMessage,message);
        }
        else if(inputMessage.messageType == MessageType.DirectMessage)
        {
            chat.appendToChatWindow(inputMessage,message);
        }
        else if(inputMessage.messageType == MessageType.Command)
        {
            chat.appendCommandToChatWindow(inputMessage,message);
        }
        else
        {
            //Do Nothing
        }
        
    }

    public static String parseUserType(AccountType userType) 
    {
        if(userType == AccountType.Streamer)
        {
            return "Streamer";
        }
        else if(userType == AccountType.Mod)
        {
            return "Mod";
        }
        else if(userType == AccountType.Sub)
        {
            return "Sub";
        }
        else
        {
            return "User";
        }
    }

    public static void appendStringToChat(String message) 
    {
        chat.appendStringToChatWindow(message);
    }

    public static void clearSetupText() 
    {
        signUp.clearText();
    }

    private static String filterMessage(EchoServerMessage inputMessage) 
    {
        String message = inputMessage.message;
        int starCount = 0;
        String starMessage = "";
        for(String badWord : wordBlackList)
        {
            if(message.contains(badWord))
            {
                starCount = badWord.length();
                for(int i = 0; i < starCount; i++)
                {
                    starMessage += "*";
                }
                message = message.replace(badWord, starMessage);
            }
        }
        return message;
    }

}
