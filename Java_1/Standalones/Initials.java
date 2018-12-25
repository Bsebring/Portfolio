
/**
 * Write a description of class initials here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
import java.util.*;
public class Initials
{
   public static void main (String[] args)
   {
      // Display prompts for all three names
      System.out.println("Please enter first name, middle name, last name: ");

      // Read names
      Scanner in = new Scanner(System.in);
      String fName = in.next();
      String mName = in.next();
      String lName = in.next();

      // Print out the initials 

      char first = fName.charAt(0);
      char middle = mName.charAt(0);
      char last = lName.charAt(0);
      System.out.println(first);
      System.out.println(middle);
      System.out.println(last);
   }
}


