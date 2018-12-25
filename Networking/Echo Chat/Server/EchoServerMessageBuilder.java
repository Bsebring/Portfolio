/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Server;

/**
 *
 * @author BSebring
 */
public class EchoServerMessageBuilder 
{
    private EchoServerMessage resultMessage;
    private String username;
    private AccountType userType;
    private String message;
    private MessageType messageType;
    private boolean status;
    private String destUsername;
    
    public EchoServerMessageBuilder()
    {
    }
    
    public void setAsDefaultMessage()
    {
        username = "";
        userType = AccountType.User;
        message = "";
        messageType = MessageType.ChatMessage;
        status = true;
        destUsername = "";
        
    }
    
    public void setAsLoginMessage()
    {
        username = "";
        userType = AccountType.User;
        message = "";
        messageType = MessageType.Login;
        status = false;
        destUsername = "";
        
    }
    
    
    
    //Bleeps out banned words
    //If users get strikes against their account it must be stored in
    //AccountInfo and updated on login/logout
    private void validateMessage() 
    {
        /*
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
    
    public EchoServerMessage buildMessage()
    {
        validateMessage();
        resultMessage = new EchoServerMessage(username,userType,message,messageType,status,destUsername);
        return resultMessage;
    }

    
    //Generated Getters and Setters

    public EchoServerMessage getResultMessage() {
        return resultMessage;
    }

    public void setResultMessage(EchoServerMessage resultMessage) {
        this.resultMessage = resultMessage;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public AccountType getUserType() {
        return userType;
    }

    public void setUserType(AccountType userType) {
        this.userType = userType;
    }

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    public MessageType getMessageType() {
        return messageType;
    }

    public void setMessageType(MessageType messageType) {
        this.messageType = messageType;
    }

    public boolean isStatus() {
        return status;
    }

    public void setStatus(boolean status) {
        this.status = status;
    }

    public String getDestUsername() {
        return destUsername;
    }

    public void setDestUsername(String destUsername) {
        this.destUsername = destUsername;
    }
    
    

    

    
    
    
    
    
}
