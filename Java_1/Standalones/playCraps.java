
/**
 * Plays craps.
 * 
 * @author (Benjamin Sebring) 
 * @version (Version 1.0)
 */
import java.util.*;
import javax.swing.JOptionPane;
import java.text.DecimalFormat;
public class playCraps
{
    public static double gameCount = 0;
    public static double gamesWon = 0;
    public static double gamesLost = 0;
    public static boolean invalidBalance = true;
    public static boolean invalidBet = true;
    public static boolean playAgain = true;
    public static int d1,d2;
    public static Scanner in = new Scanner(System.in);
    public static double startingBalance = 0;
    public static double bet, badYON = 0;
    public static double balance = 0;
    public static String endBalance = "Your current account balance is: ";
    public static String lose = ">>>You Lose ;( <<<";
    public static String win = ">>>You Win!<<<";
    public static String youRolled = "You Rolled a(n): ";
    public static String pointIs = "You must roll a(n) ";
    public static String sorry = "Sorry, but your balance has reached zero, Please come back when you have more money to lose!";
    public static void main (String args[])
    {
        double initialBalance = menu();
        boolean craps = isCraps(); 
        System.out.println();

    }

    public static double menu()
    {
        System.out.println("\nWelcome to Craps!");
        while(invalidBalance)
        {

            System.out.print("Please input a starting balance >>  $");

            if(in.hasNextDouble())
            {
                startingBalance = in.nextDouble();
                if (startingBalance < 1)
                {
                    System.out.println("\nError, Balance must be atleast $1.");
                    continue;

                }
                else 
                {
                    balance = startingBalance;
                    invalidBalance = false;
                }
            }
            else
            {
                System.out.println("\nError, Balance must be a double value.");
                String invalid = in.next();
            }
        }
        return startingBalance;
    }
    
    public static int roll ()
    {
        d1 =  (int) (6.0*Math.random() + 1);
        d2 =  (int) (6.0*Math.random() + 1);
        return d1 + d2;
    }

    public static boolean isCraps() 
    { 
        while(playAgain)
        {
            gameCount++;
            while(invalidBet)
            {
                System.out.print("Please place a bet >>  $");
                if(in.hasNextDouble())
                {
                    bet = in.nextDouble();
                    if (bet < 1)
                    {
                        System.out.println("\nError, bet must be atleast $1.");

                    }
                    else if (bet > balance)
                    {
                        System.out.println("\nError, bet cannot exceed your balance of: " + balance);

                    }
                    else
                    {
                        invalidBet = false;
                    }
                }
                else
                {
                    String invalid = in.next();
                    System.out.println("\nError, please enter a number");
                }
            }
            System.out.println("\nGame # " + (gameCount) + " with a starting bet of: $" + bet);

            // checking the first roll to see if player wins 
            int firstRoll = roll(); 
            System.out.printf("%15s\t%3d\n", youRolled, firstRoll); 

            while (true)
            { 
                if (firstRoll == 7 || firstRoll == 11)
                { 
                    System.out.printf("\n%15s\n", win); 
                    balance = balance + bet;
                    System.out.printf("\n%15s %10.2f\n", endBalance, balance); 
                    gamesWon++;
                    break;
                } 
                // Player doesn't win then checking if player looses 
                else if (firstRoll == 2 || firstRoll == 3 || firstRoll == 12)
                { 
                    System.out.printf("\n%15s\n", lose); 
                    balance = balance - bet;
                    System.out.printf("\n%15s %10.2f\n", endBalance, balance); 
                    gamesLost++;
                    break;
                } 
                // If player doesn't win or loose on first roll then check to see if earns 
                // points; then rolls the dice again 
                else 
                { 

                    int pointCount = firstRoll; 
                    int subsequentRoll; 

                    System.out.printf("%15s\t%3d again \n", pointIs, pointCount);
                    // rolling the dice again 
                    subsequentRoll = roll(); 

                    System.out.printf("%15s\t%3d\n", youRolled, subsequentRoll);

                    // Checking to see if subsequent roll equals 7, if so player looses 

                    if (subsequentRoll == 7)
                    { 
                        System.out.printf("\n%15s\n", lose);
                        balance = balance - bet;
                        System.out.printf("\n%15s %10.2f\n", endBalance, balance); 
                        gamesLost++;
                        break;
                    } 

                    // Checking if first roll and subsequent roll are the same then 
                    //player wins 
                    else if(subsequentRoll == firstRoll)
                    { 
                        System.out.printf("\n%15s\n", win);
                        balance = balance + bet;
                        System.out.printf("\n%15s %10.2f\n", endBalance, balance); 
                        gamesWon++;
                        break;
                    } 
                } 
            }
            if (balance <= 0)
            {
                System.out.printf("\n\n%15s\n", sorry);
                playAgain = false;
                break;
            }
            System.out.print("\nWould you like to play again? enter 'y' or 'n' for yes or no >>");
            if (in.hasNext())
            {
                String again = in.next();
                if (again.equals("y")||again.equals("Y"))
                {
                    invalidBet = true;
                    continue;
                }
                else if (again.equals("n")||again.equals("N"))
                {
                    System.out.println("See ya, play again soon!");
                    invalidBet = true;
                    playAgain = false;
                }
                else
                {
                    System.out.println("You entered a number, this will be treated like you wished to not play anymore, goodbye! play again soon!");
                    invalidBet = true;
                    playAgain = false;
                }
            }
            else
            {
                playAgain = false;

            }

        }
        DecimalFormat single = new DecimalFormat("#");
        DecimalFormat two = new DecimalFormat("#.##");
        double winPercent = (gamesWon/gameCount)*100;
        double lossPercent = (gamesLost/gameCount)*100;
        double difference = 0;
        double diffPer = 0;
        
        String output = "You won " + (single.format(gamesWon)) + " games, and lost " + (single.format(gamesLost)) + " games with and ending balance of: $" 
        + (two.format(balance)) + "\n\nYour win percentage is: " + (two.format(winPercent)) + "%\nYour loss percentage is: " + (two.format(lossPercent)) + "%\n";
        if(balance > startingBalance)
        {
            difference = balance - startingBalance;
            diffPer = (difference/startingBalance)*100;
            output = output + "You won $" + (two.format(difference)) + " increasing your account by "
            + (two.format(diffPer)) + "%!";
        }
        else
        {
            difference = startingBalance - balance;
            diffPer = (difference/startingBalance)*100;
            output = output + "You lost $" + (two.format(difference)) + " decreasing your account by "
            + (two.format(diffPer)) + "%!";
        }
        
        
        JOptionPane.showMessageDialog(null, output);
        
        return true;
    }
}

