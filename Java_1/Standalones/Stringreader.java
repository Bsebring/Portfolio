
/**
 * This program reads the length of a string, Transposes a string, identifies the first, middle, and last
 * character of a string, and prints the string in all upper case.
 * @author (Benjamin Sebring) 
 * @version (9/15/2015)
 */
import java.util.*;
import java.io.*;
public class Stringreader
{
 public static void main(String args[])
 {
   System.out.println("Please input a string, no spaces please."); // asking for input.
   Scanner scanObj = new Scanner(System.in);
   String name = scanObj.next();// waiting for user input.
   int stringLength = name.length(); //finding the length of the string.
   char start = name.charAt(0); // identifying the first character and storing it.
   char last = name.charAt(stringLength - 1);  // identifying the last character and storing it.
   int midStringLength = (stringLength)/2; // identifying the middle of the string and storing it.
   char middle = name.charAt(midStringLength); // identifying the middle character and storing it.
   String fHalf = name.substring(0,midStringLength); // identifying the first half of string and storing it.
   String sHalf = name.substring(midStringLength, stringLength); // identifying the second half of string and storing it.
   System.out.println("Your string is " + stringLength + " characters long."); // data output
   System.out.println("The First Character is: " + start); // data output
   System.out.println("The Last Character is: " + last); // data output
   System.out.println("The Middle Character at position " + midStringLength + " is: " + middle); // data output
   System.out.println("Transpose: " + sHalf + fHalf); // Transposed string
   System.out.print("Upper Case: ");  // text output
   System.out.println(name.substring(0, stringLength).toUpperCase()); // outputting the string in upper case.
 }
}
