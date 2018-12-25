
/**
 * Extension of class Employee and uses 
 * wage and hours worked to determine salary
 * 
 * @author (Ben Sebring) 
 * @version (3/23/16)
 */
import java.text.*;
public class PartTimeEmployee extends Employee
{
    // instance variables - replace the example below with your own
    private double wagePerHour, hoursWorked;

    // constructor taking 5 inputs
    public PartTimeEmployee(String first, String last, String ssn, double hoursWorked, double wagePerHour)
    {
        // calling the super method to obtain the first three bits of info
        super(first, last, ssn);
        this.wagePerHour = wagePerHour;
        this.hoursWorked = hoursWorked;
    }

    // getter method
    public double getWagePerHour() {
        return wagePerHour;
    }
    
    public double getHoursWorked() {
        return hoursWorked;
    }
    
    // setter methods
    public void setHoursWorked (double hoursWorked) {
    
        this.hoursWorked = hoursWorked;
    }
    
    public void setWagePerHour ( double wagePerHour) {
    
        this.wagePerHour = wagePerHour;
    }
    
    // overriding the abstract methos from super class
    public double earnings(){
        
        // calculating the weekly salary for a part-time employee
        if (hoursWorked > 40 )
        {
            double overtime = hoursWorked - 40;
            hoursWorked -= overtime;
            double timeAndHalf = overtime * 1.5;
            hoursWorked += timeAndHalf;
        }
        return wagePerHour * hoursWorked;
    }
    // To string method
    public String toString () {

        return super.toString() + String.format("\t$%1$7.2f", earnings());
    
    }
}
