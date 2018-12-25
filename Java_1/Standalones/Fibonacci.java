
/**
 * Will detect if a number is a fibonacci number or not.
 * 
 * @author (Benjamin Sebring) 
 * @version (version 1.0 10/30/2015)
 */
import java.util.Scanner;

public class Fibonacci
{

    public static void main(String args[])
    {

        Scanner input = new Scanner(System.in);
        boolean quit = false;

        System.out.println("Welcome to Fibonacci Sequence Dectector\n\n");
        while(!false)
        {
            int fibAbove = 1;
            int fibBelow = 0;
            int counter = 1;
            int fibNext = 0;
            int evalNumber = 0;
            String exit;
            System.out.print("\nPlease input a number for analysis >> ");
            if(input.hasNextInt())
            {
                evalNumber = input.nextInt();
            }
            else
            {
                System.out.print("\n\nThank you for using the Fibonacci Sequence Detector\n\n"); 
                exit = input.next();
                break;
            }

            if(evalNumber < 0)
            {
                System.out.println("\n  Error, Please enter a positive number!\n ");
                continue;

            }
            while(fibNext < evalNumber)
            {
                fibNext = fibAbove + fibBelow;
                fibBelow = fibAbove;
                fibAbove = fibNext;
                counter++;
                
            }
            if(fibNext == evalNumber && evalNumber == 1)
            {
                System.out.println(evalNumber + " is a fibonacci number whose order in the sequence is both " + counter + " and " + (counter + 1));

            }
            else if(fibNext == evalNumber && evalNumber == 0)
            {
                System.out.println(evalNumber + " is a fibonacci number whose order in the sequence is  " + (counter));

            }
            else if(fibNext == evalNumber)
            {
                System.out.println(evalNumber + " is a fibonacci number whose order in the sequence is " + (counter + 1));

            }
            else if(fibNext != evalNumber) 
            {
                System.out.println("\n" + evalNumber + " is not a fibonacci number \nHowever, it lies between the Fibonacci numbers " + fibBelow + " (order:" + (counter) + ") and " + fibAbove + " (order:" + (counter +1) + ")");
            }
            
        }
    }
}
