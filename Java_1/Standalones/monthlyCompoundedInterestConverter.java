
/**
 * will compute the monthly compund interest.
 * 
 * @author (Ben Sebring) 
 * @version (version 1.0 10/30/2015)
 */
import java.util.*;
public class monthlyCompoundedInterestConverter
{
    public static void main(String args[])
    {
        Scanner input = new Scanner(System.in);
        double interest = 0;
        double newInterest = 0;
        double interestRate = 0;
        double initialInvestment = 0;
        double newBalance = 0;
        double time = 0;
        String category = "hi";
        String notValid;
        String notValid2;
        String notValid3;
        String invalidCategory;
        String month = "Month:";
        String printInterest = "Interest:";
        String principal = "Principal:";
        String lastPrincipal = "Final Account Balance";
        String start = "Starting Balance";
        String total = "Total Interest Paid";
        double numberOfMonths = 0;
        boolean invalidInput = true;

        System.out.println("Welcome to the Account Interest Calculator \n\n");
        System.out.print("Please input the following:  principal, interest rate, term >> ");

        while (invalidInput)
        {

            
            if (input.hasNextDouble())
            {
                initialInvestment = input.nextDouble();

            }
            else
            {
                System.out.println("\nInvalid Principal amount!\n");
                notValid = input.next();
                continue;
            }
            if (input.hasNextDouble())
            {
                interestRate = input.nextDouble();
                
            }
            else
            {
                System.out.println("\nInvalid interest rate!\n");
                notValid2 = input.next();
                continue;
            }
            if (input.hasNextDouble())
            {
                time = input.nextDouble();
                
            }
            else
            {
                System.out.println("\nInvalid Term!\n");
                notValid3 = input.next();
                continue;
            }
            if (input.hasNext())
            {
                category = input.next();
                if(category.equals("months")||category.equals("Months")||category.equals("MONTHS"))
                {
                    numberOfMonths = time;
                    invalidInput = false;
                    category = "months";
                }
                else if (category.equals("years")||category.equals("Years")||category.equals("YEARS"))
                {
                    numberOfMonths = time * 12;
                    invalidInput = false;
                    category = "years";
                }
                else
                {
                     System.out.println("\nInvalid choice of months or years!\n");
                     invalidCategory = input.next();
                     continue;
                }
                
            }
        }
        double n = 12;
        double balance = initialInvestment;
        double numberOfYears = numberOfMonths/12;
      
        int i = 1;
        System.out.printf("\n\n%5s\t %8s\t %8s\n", month, printInterest, principal);
        for (i = 1; i <= numberOfMonths; i++)
        {
           newBalance = balance * Math.pow((1+ (interestRate/n)/100), (n/12));
           interest = newBalance - balance;
           balance = newBalance;
           System.out.printf("%5d\t $%7.2f\t $%8.2f\n", i, interest, balance);
            
            
        }
        double interestPaid = balance - initialInvestment;
        System.out.printf("\n\n%-25s= $%8.2f \n%-25s= $%8.2f\n%-25s= $%8.2f\n", start, initialInvestment, lastPrincipal, balance, total, interestPaid);
        System.out.println("\nThankyou for using the Account Interest Calculator!");
    }
}

