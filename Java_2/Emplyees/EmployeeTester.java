
/**
 * Tests the Employee class and its' subclasses
 * 
 * @author (Ben Sebring) 
 * @version (3/23/16)
 */
import java.util.*;
import java.io.*;
public class EmployeeTester 
{
    public static void main(){
        // creating an array of size 6 to store the employee data
        Employee [] em = new Employee [6];
        
        try{
            // Scanning the file 
            File inputFile = new File("data.txt");
            Scanner fileScan = new Scanner(inputFile);

            while (fileScan.hasNextLine()){
                
                // once another line is detected, processing the data
                for(int i = 0; i < em.length; i++){
                    
                    // breaking the file down line by line
                    String read = fileScan.nextLine();
                    Scanner lineReader = new Scanner(read);
                    
                    while(lineReader.hasNext()){
                        // storing the dat in appropriate variables
                        int status = lineReader.nextInt();
                        String first = lineReader.next();
                        String last = lineReader.next();                    
                        String ssn = lineReader.next();
                        
                        // checking to see if it is a full or part-time employee
                        if(status == 1){
                            double salary = lineReader.nextDouble();
                            //creating instance of a full-time employee with specific data read from file
                            em[i] = new FullTimeEmployee(first, last, ssn, salary);

                        }
                        else if(status == 2) {
                            double hours = lineReader.nextDouble();                        
                            double wage = lineReader.nextDouble();
                            //creating instance of a part-time employee with specific data read from file
                            em[i] = new PartTimeEmployee(first, last, ssn, hours, wage);

                        }
                    }

                }
            }
            // closing the file that is read
            fileScan.close();
            
            // catching a file not found exception
        }catch (FileNotFoundException e ){
            System.out.println(e.getMessage());
        }
        
        // printing out the formatted information
        System.out.println("----------------------------------------------");
        System.out.println("A List of Employees and Their Weekly Salaries:");
        System.out.println("----------------------------------------------");
        
        for (Employee e : em){

            System.out.println(e.toString());
        }
        
        System.out.println("\n\n---------------------");
        System.out.println("Employee Information:");
        System.out.println("---------------------");
        
        for (int j = 0; j < em.length; j++){

            System.out.println("Employee "+ (j+1) + " is a " + em[j].getClass().getName() + ".");

        }

    }
}

