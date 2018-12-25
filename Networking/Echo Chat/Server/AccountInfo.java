/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Server;

import java.io.Serializable;

/**
 *
 * @author BSebring
 */




class AccountInfo implements Serializable
{
    private static final long serialVersionUID = 7526472295622776110L;
    private String username;
    private String password;
    private AccountType accountType;
    private int balance;
    private boolean loggedIn;
    private static final int MAX_DEPOSIT = 100;

    public AccountInfo(String username, String password) {
        this.username = username;
        this.password = password;
        this.accountType = AccountType.User;
        this.balance = 0;
        this.loggedIn = false;
    }
    
    //Generated Code

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public AccountType getAccountType() {
        return accountType;
    }

    public void setAccountType(AccountType accountType) {
        this.accountType = accountType;
    }


    public int getBalance() {
        return balance;
    }

    public void setBalance(int balance) {
        if(balance > 65000)
        {
            this.balance = 65000;
        }
        else
        {
            this.balance = balance;
        }
    }
    
    public void addToBalance(int deposit)
    {
        if(deposit > MAX_DEPOSIT)
        {
            deposit = MAX_DEPOSIT;
        }
        this.setBalance(this.balance + deposit);
    }

    public boolean isLoggedIn() {
        return loggedIn;
    }

    public void setLoggedIn(boolean loggedIn) {
        this.loggedIn = loggedIn;
    }

    public void removeFromBalance(int amount) 
    {
        if(this.balance - amount >= 0)
        {
            this.setBalance(this.balance - amount);
        }
    }
    
    
    
    
    
}
