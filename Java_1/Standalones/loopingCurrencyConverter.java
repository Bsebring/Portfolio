/**
 * Benjamin Sebring
 * 
 * This program converts currency between Us dollars, British Pounds, The Euro, and Yen.
 * 
 * The conversion rates used in this program were updated on October 14, 2015 from www.xe.com/ucc/ , the
 * website given to us on the word document from this assignments' drop box.
 * 
 *  version ( 2.0 ) while loop converter
 *  
 *  date (10/14/2015)
 */

import java.util.Scanner;
public class loopingCurrencyConverter
{
    public static void main(String[] args)
    {
        
        Scanner in = new Scanner(System.in);
        boolean invalid3 = true;
        boolean invalidChoice1 = true;
        boolean invalidChoice2 = true;
        boolean invalidTotal = true;
        boolean invalid1 = true;
        boolean invalid2 = true;
        String choiceA;
        String choiceB;
        String choiceC;
        
        int choice1 = -1;
        int choice2 = -1;
        int total = 0;
        final double eurosToDollars = 1.14410;
        final double eurosToPounds = 0.74057;
        final double eurosToYen = 136.338;
        final double poundsToDollars = 1.54486;
        final double poundsToEuros = 1.35035;
        final double poundsToYen = 184.106;
        final double yenToDollars = 0.00839;
        final double yenToEuros = 0.00733;
        final double yenToPounds = 0.00543;
        final double dollarsToEuros = 0.87405;
        final double dollarsToPounds = 0.64733;
        final double dollarsToYen = 119.171;

        double convertedTotal = 0;
        String outputDTE = (" US Dollars at a conversion rate of " + dollarsToEuros + " Dollars to Euros = € ");
        String outputDTP = (" US Dollars at a conversion rate of " + dollarsToPounds + " Dollars to Pounds = £ ");
        String outputDTY = (" US Dollars at a conversion rate of " + dollarsToYen + " Dollars to Yen = ¥ ");
        String outputETD = (" Euros at a conversion rate of " + eurosToDollars + " Euros to Dollars = $ ");
        String outputETP = (" Euros at a conversion rate of " + eurosToPounds + " Euros to Pounds = £ ");
        String outputETY = (" Euros at a conversion rate of " + eurosToYen + " Euros to Yen = ¥ ");
        String outputPTD = (" British Pounds at a conversion rate of " + poundsToDollars + " Pounds to Dollars = $ ");
        String outputPTE = (" British Pounds at a conversion rate of " + poundsToEuros + " Pounds to Euros = € ");
        String outputPTY = (" British Pounds at a conversion rate of " + poundsToYen + " Pounds to Yen = ¥ ");
        String outputYTD = (" Yen at a conversion rate of " + yenToDollars + " Yen to Dollars = $ " );
        String outputYTE = (" Yen at a conversion rate of " + yenToEuros + " Yen to Euros = € " );
        String outputYTP = (" Yen at a conversion rate of " + yenToPounds + " Yen to Pounds = £ ");String welcome = "Welcome to the Currency Converter program.\n \nUse the following codes to input your currency choices:\n\n";
        
        // Prompt for input with looping validation.

        System.out.printf("%-10s",welcome);    
        System.out.println("1 - Dollars. ($)");
        System.out.println("2 - Euros. (€)");
        System.out.println("3 - Pounds. (£)");
        System.out.println("4 - Yen. (¥)\n\n");
        System.out.println("Please choose the input currency >>");

        // Wait for user inputand check for validity.

        

        while (invalid1)
        {
            if (in.hasNextInt())
            {
                invalid1 = false;
                choice1 = in.nextInt();
                // Validation.

            }
            else
            {
                System.out.println("Invalid input, please enter an integer >>.");
                choiceA = in.next();

            }
        }
        while (invalidChoice1)
        {
            if (choice1 > 0 && choice1 < 5)
            {
                invalidChoice1 = false;
                System.out.println("\nPlease choose the currency to convert to >>.");

            }
            else
            {
                System.out.println("Please input a choice from the provided options >>.");
                choice1 = in.nextInt();
            }
        }
        while (invalid2)
        {
            if (in.hasNextInt())
            {
                invalid2 = false;
                choice2 = in.nextInt();
                // Validation.

            }
            else
            {
                System.out.println("Invalid input, please enter an integer >>.");
                choiceB = in.next();
            }
        }
        while (invalidChoice2)  
        {
            if (choice2 > 0 && choice2 < 5)
            {
                
                System.out.println("\nPlease enter the amount of currency you would like to convert >>.");
                invalidChoice2 = false;
            }
            else
            {
                System.out.println("Please input a valid choice from the provided options >>.");
                choice2 = in.nextInt();
            }
        }
        while (invalid3)
        {
            if(in.hasNextInt())
            {
                invalid3 = false;
                total = in.nextInt();
            }
            else
            {
                System.out.println("Please input an integer, not a string >>.");
                choiceC = in.next();
            }
        }
        while (invalidTotal)
        {
            if (total > 0)
            {
                invalidTotal = false;
                System.out.println("Calculating the conversion Now...\n\n");
            }
            else
            {
                System.out.println("Please input a positive value! >>");
                total = in.nextInt();
            }
        }
        if (choice1 == choice2 )
        {
            System.out.println("There is not conversion needed, as both the input and output currency were the Same.");
            System.out.println("You Inputted " + total + "\n\n");
        }
        else if (choice1 == 1 && choice2 == 2)
        {
            convertedTotal = total * dollarsToEuros;
            System.out.print(total + outputDTE);
            System.out.printf("%.2f\n\n", convertedTotal);
        }
        else if (choice1 == 1 && choice2 == 3)
        {
            convertedTotal = total * dollarsToPounds;
            System.out.println(total + outputDTP);
            System.out.printf("%.2f\n\n", convertedTotal);
        }
        else if (choice1 == 1 && choice2 == 4)
        {
            convertedTotal = total * dollarsToYen;
            System.out.println(total + outputDTY);
            System.out.printf("%.2f\n\n", convertedTotal);
        }
        else if (choice1 == 2 && choice2 == 1)
        {
            convertedTotal = total * eurosToDollars;
            System.out.print(total + outputETD);
            System.out.printf("%.2f\n\n", convertedTotal);
        }

        else if (choice1 == 2 && choice2 == 3)
        {
            convertedTotal = total * eurosToPounds;
            System.out.print(total + outputETP);
            System.out.printf("%.2f\n\n", convertedTotal);
        }
        else if (choice1 == 2 && choice2 == 4)
        {
            convertedTotal = total * eurosToYen;
            System.out.print(total + outputETY);
            System.out.printf("%.2f\n\n", convertedTotal);
        }
        else if (choice1 == 3 && choice2 == 1)
        {
            convertedTotal = total * poundsToDollars;
            System.out.print(total + outputPTD );
            System.out.printf("%.2f\n\n", convertedTotal);
        }
        else if (choice1 == 3 && choice2 == 2)
        {

            convertedTotal = total * poundsToEuros;
            System.out.print(total + outputPTE);
            System.out.printf("%.2f\n\n", convertedTotal);

        }

        else if (choice1 == 3 && choice2 == 4)
        {
            convertedTotal = total * poundsToYen;
            System.out.print(total + outputPTY);
            System.out.printf("%.2f\n\n", convertedTotal);
        }
        else if (choice1 == 4 && choice2 == 1)
        {
            convertedTotal = total * poundsToDollars;
            System.out.print(total + outputYTD);
            System.out.printf("%.2f\n\n", convertedTotal);
        }
        else if (choice1 == 4 && choice2 == 2)
        {

            convertedTotal = total * poundsToEuros;
            System.out.print(total + outputYTE);
            System.out.printf("%.2f\n\n", convertedTotal);

        }
        else if (choice1 == 4 && choice2 == 3)
        {
            convertedTotal = total * poundsToYen;
            System.out.print(total + outputYTP);
            System.out.printf("%.2f\n\n", convertedTotal);
        }
        System.out.println("\nThank you for using the Currency Converter Program!");

    }
}

