/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Server;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

/**
 *
 * @author BSebring
 */


public class EchoServerMessage implements java.io.Serializable
{
    private static final long serialVersionUID = 7526472295622776150L;
    public final String sourceUsername;
    public final AccountType userType;
    public final String message;
    public final MessageType messageType;
    public final boolean status;
    public final String destUsername;
    
    //Always created by the Builder class object in the Connention Handler
    // or Server
    public EchoServerMessage(String username, AccountType userType, String message, MessageType messageType, boolean statusSuccess, String destUsername) {
        this.sourceUsername = username;
        this.userType = userType;
        this.message = message;
        this.messageType = messageType;
        this.status = statusSuccess;
        this.destUsername = destUsername;
    }

    //Prevent corruption of data passes over the wire - that would lead to
    //an unsafe state
    public void validateState()
    {
    }
    
    /**
     * Always treat de-serialization as a full-blown constructor, by validating
     * the final state of the de-serialized object.
     */
    private void readObject(ObjectInputStream aInputStream) throws ClassNotFoundException, IOException 
    {
        //always perform the default de-serialization first
        aInputStream.defaultReadObject();

        //ensure that object state has not been corrupted or tampered with maliciously
        //validateState();
    }

    /**
     * This is the default implementation of writeObject. Customize if
     * necessary.
     */
    private void writeObject(ObjectOutputStream aOutputStream) throws IOException
    {
        //perform the default serialization for all non-transient, non-static fields
        aOutputStream.defaultWriteObject();
    }
}
