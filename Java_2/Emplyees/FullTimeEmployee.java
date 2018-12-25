
/**
 * Extension of class Employee 
 * and uses salary for weekly salary
 * 
 * @author (Ben Sebring) 
 * @version (3/23/16)
 */
import java.text.*;
public class FullTimeEmployee extends Employee
{
    private double weeklySalary;
    
    //constructor mathod taking four inputs
    public FullTimeEmployee (String first, String last, String ssn, double salary) {
        // calling the super class to get the first three bits of info
        super(first, last, ssn);
        weeklySalary = salary;
    }
    
    // getter method
    public double getWeeklySalary() {
        return weeklySalary;
    }
    
    // setter method
    public void setWeeklySalary (double salary) {
    
        this.weeklySalary = salary;
    }
    
    // overriding the abstract methos from super class
    public double earnings(){
        // setting the earnings method to retrive the weekly salary for a full-time employee
        return weeklySalary;
    }
    
    // To string method
    public String toString () {
        DecimalFormat formatter = new DecimalFormat("#,###.00");
        return super.toString() + String.format("\t$%1$7.2f", earnings());
    
    }
    
}
