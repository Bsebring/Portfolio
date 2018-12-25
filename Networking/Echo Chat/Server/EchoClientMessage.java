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
public class EchoClientMessage implements java.io.Serializable
{
    private static final long serialVersionUID = 7526472295622776140L;
    private String message = "";
    
    public EchoClientMessage(String message)
    {
        setMessage(message);
    }
    
    public EchoClientMessage()
    {
        setMessage("Test Message");
    }
    

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        validateMessage(message);
        this.message = message;
    }
    
    public void validateMessage(String message)
    {
        /* how to censor curse words
        int starCount = 0;
        String stars = "";
        for(String token : bannedList)
        {
            if(this.message.contains(""))
            {
                for(starCount = token.length(); starCount > 0; starCount--)
                {
                    stars += "*";
                }
                this.message = (this.message).replace(token, stars);
                starCount = 0;
                stars = "";
            }
        }
        */
    }
    
    public void validateState()
    {
        validateMessage(this.message);
    }
    
    /*
     * Always treat de-serialization as a full-blown constructor, by validating
     * the final state of the de-serialized object.
     */
    private void readObject(ObjectInputStream aInputStream) throws ClassNotFoundException, IOException 
    {
        //always perform the default de-serialization first
        aInputStream.defaultReadObject();

        //ensure that object state has not been corrupted or tampered with maliciously
        validateState();
    }

    /*
     * This is the default implementation of writeObject. Customize if
     * necessary.
     */
    private void writeObject(ObjectOutputStream aOutputStream) throws IOException
    {
        //perform the default serialization for all non-transient, non-static fields
        aOutputStream.defaultWriteObject();
    }
    
}
