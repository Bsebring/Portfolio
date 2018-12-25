package Server;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.net.Socket;
import java.util.concurrent.atomic.AtomicLong;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author BSebring
 */
public class ServerDriver {

    public static void main(String[] args) {
        
        EchoServer server = null;
        
        if (args.length != 1) 
        {
            System.out.println("Usage: java EchoServer port");
            System.exit(1);
        } 
        else
        {
            server = new EchoServer(Integer.parseInt(args[0]));
        }
        
        //Create a server on port 62828
        
        //Load the server data from file
        try{ EchoServer.loadServer(); }
        catch(ClassNotFoundException ex1){ System.out.println("Conversion Error"); }
        catch(FileNotFoundException ex2)
        { 
            EchoServer.clearUserData();
            System.out.println("File Error"); 
        }
        catch(IOException ex3)
        { 
           System.out.println("General IO Error");
           EchoServer.clearUserData();
        }
        finally{ System.out.println("Load Complete"); }
        
        //Accept connections and send to a new ConnectionHandler Thread
        //Until Server is closed
        Socket clientSocket;
        Runnable connectionHandler;
        AtomicLong socketID = new AtomicLong();
        
        boolean flag = true;
        while(flag)
        {
            //Accept all connections
            clientSocket = server.accept();
            System.out.println("Accepted Client: " + clientSocket.toString());
            //Create a handler for each
            connectionHandler = new ConnectionHandler(clientSocket, socketID.incrementAndGet());
            //Create a new thread to run the handler on
            new Thread(connectionHandler).start();
        }
        
        
        /*
        if (args.length != 1) 
        {
            System.out.println("Usage: java EchoServer port");
        } 
        else
        {
            server = new EchoServer(Integer.parseInt(args[0]));
        }
        */
    }

    

    

}
