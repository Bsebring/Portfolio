
/**
 * Write a description of class bugTester here.
 * 
 * @author (Ben Sebring) 
 * @version (a version number or a date)
 */
import java.util.*;
import java.io.*;
public class bugTester
{
    //test all methods of class bug
    public static void main(){
        // initializing additional variables
        boolean done = false;

        // printing the header
        System.out.println("************************************");
        System.out.println("*****Welcome to the Bug's World*****");
        System.out.println("************************************");

        //initializing the scanner
        Scanner in = new Scanner(System.in);

        // initializing the bug using default constructor and printing the current position
        Bug bug1 = new Bug();
        bug1.turn(bug1.getDirection());
        System.out.println("Bug's initial position: ");
        bug1.printCurrentPosition();        

        // using while loop to continue until the user no longer wishes to.
        while(!done){
            int d,m = 0;
            // using try/catch for exception handling
            try {
                // asking for input and storing it
                System.out.print("\n\nPlease enter the direction (0-N, 1-E, 2-S, 3-W) for the bug to turn: ");
                d = in.nextInt();
                bug1.turn(d);
                System.out.print("\nPlease enter the number of units for the bug to move: ");
                m = in.nextInt();
                bug1.move(m);
                System.out.println("Bug's current position:");
                bug1.printCurrentPosition();        
                System.out.println("////////////////////////////////////////////////////");
                System.out.print("Turn and move the bug again (1 or 0)? (1-Yes, 0-No): ");
                int answer = in.nextInt();

                // checking if user wants to continue or not.
                if(answer == 0){
                    done = true;
                }
                else if (answer > 1)
                {
                    System.out.println("please use 1 or 0 to make your choice (1-Yes, 0-No): ");
                    answer = in.nextInt();
                }

            }catch (ArrayIndexOutOfBoundsException e) {
                System.out.println(e.getMessage());
                bug1.printCurrentPosition();

                // checking if user wants to continue or not.
                System.out.println("////////////////////////////////////////////////////");
                System.out.print("Turn and move the bug again (1 or 0)? (1-Yes, 0-No): ");
                int answer = in.nextInt();

                if(answer == 0){
                    done = true;
                }
                else if (answer > 1)
                {
                    System.out.println("please use 1 or 0 to make your choice (1-Yes, 0-No): ");
                    answer = in.nextInt();
                }

            }catch (InputMismatchException e) {
                System.out.println("Please use the choices provided");
                String error = in.next();
            }
            catch(IllegalArgumentException f){
                System.out.println(f.getMessage());
            }

        }

    }
}
