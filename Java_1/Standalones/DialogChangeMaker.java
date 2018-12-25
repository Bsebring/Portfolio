
/**
 * This change maker distibutes optimal coins for change.
 * This is a demo run with the JOptionPane.
 * 
 * @author (Benjamin Sebring) 
 * @version 1.2.0 (JOptionPane)
 */
import java.util.*;
import javax.swing.JOptionPane;
public class DialogChangeMaker
{
  public static void main(String args[])
   {
     String input = JOptionPane.showInputDialog("How much does your item cost, (in cents)?");
     double price = Double.parseDouble(input);
     int cost = (int) price;
     int total = 100;
     int change = (total - cost);
     int quarter = (change/25);
     int remainchange = (change%25);
     int dime = (remainchange/10);
     int remainchange2 = (remainchange%10);
     int nickle = (remainchange2/5);
     int penny = (remainchange2%5);
     String output = "Your change is: " + change + " cents." + "\n" +"Quarter (s): "+ quarter +"\n" +"Dime (s): "+ dime + "\n" +"Nickle (s): " + nickle  +"\n"+"Penny (s): "+ penny +"\n";
     JOptionPane.showMessageDialog(null, output);
    }  
}