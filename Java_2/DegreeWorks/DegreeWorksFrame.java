
/**
 * Creates a Graphic User Interface that accepts and 
 * displays course information, as well as calculating the GPA
 * 
 * @author (Ben Sebring) 
 * @version (April 6, 2016)
 */
import javax.swing.*;
import java.awt.event.*;
import java.util.*;

public class DegreeWorksFrame extends JFrame
{
    // declring the four buttons
    private JButton addCourseButton;
    private JButton calculateGPAButton;
    private JButton resetInputButton;
    private JButton resetOutputButton;
    
    // declaring the four labels
    private JLabel codeLabel;
    private JLabel nameLabel;
    private JLabel creditLabel;
    private JLabel gradeLabel;
    
    // declaring the four text fields
    private JTextField codeTextField;
    private JTextField nameTextField;
    private JTextField creditTextField;
    private JTextField gradeTextField;

    // declaring the JTextArea and JScrollPane
    private JTextArea result;
    private JScrollPane output;
    
    //initializing the ArrayList
    private ArrayList<Course> courseList = new ArrayList<Course>(); 

    // setting the FRAME_WIDTH and FRAME_HEIGHT variables
    private static final int FRAME_WIDTH = 500;
    private static final int FRAME_HEIGHT = 500;
    
    // defining the heading string for the output area
    private String heading = String.format("%7s\t%7s\t%7s\t%7s", 
        "Code", "Name", "Credits", "Grade");
    
    // default frame constructor
    public DegreeWorksFrame()
    {
        // implementing the createComponents and setSize methods
        createComponents();
        setSize(FRAME_WIDTH, FRAME_HEIGHT);
    }

    // helper method to create the frame components
    public void createComponents()
    {
        // initializing the panel
        JPanel panel = new JPanel();
        
        // initializing and setting the text to display on the buttons
        addCourseButton = new JButton ("Add Course");
        calculateGPAButton = new JButton ("Calculate GPA");
        resetInputButton = new JButton ("Reset Input");
        resetOutputButton = new JButton ("Reset Output");

        // initializing and setting the text for the labels to display
        codeLabel = new JLabel ("Course Code:");
        nameLabel = new JLabel ("Course Name:");
        creditLabel = new JLabel ("Course Credit:");
        gradeLabel = new JLabel ("Course Grade:");
        
        // initializing and setting the text fields' size
        codeTextField = new JTextField(30);
        nameTextField = new JTextField(30);
        creditTextField = new JTextField(30);
        gradeTextField = new JTextField(30);

        // initializing the text area's dimensions 
        result = new JTextArea (10, 35);
        
        
        result.append(heading);
        
        //adding the text area to the JScrollPane
        output = new JScrollPane(result);
        
        
        // initializing the four action listeners
        ActionListener addCourseListener = new AddCourseListener();
        addCourseButton.addActionListener(addCourseListener);

        ActionListener calculateGPAListener = new CalGPAListener();
        calculateGPAButton.addActionListener(calculateGPAListener);

        ActionListener resetInputListener = new ResetInputListener();
        resetInputButton.addActionListener(resetInputListener);

        ActionListener resetOutputListener = new ResetOutputListener();
        resetOutputButton.addActionListener(resetOutputListener);
        
        // adding all the items to the panel
        panel.add(codeLabel);
        panel.add(codeTextField);
        panel.add(nameLabel);
        panel.add(nameTextField);
        panel.add(creditLabel);
        panel.add(creditTextField);
        panel.add(gradeLabel);
        panel.add(gradeTextField);
        panel.add(addCourseButton);
        panel.add(calculateGPAButton);
        panel.add(resetInputButton);
        panel.add(resetOutputButton);
        panel.add(output);
        
        // adding the panel to the frame
        this.add(panel);

    }
    
    // add course listener
    class AddCourseListener implements ActionListener
    {
        public void actionPerformed(ActionEvent event) {
            // stroing the information in the text areas
            String code = codeTextField.getText();
            String name = nameTextField.getText();
            int credits = Integer.parseInt(creditTextField.getText());
            String grade = gradeTextField.getText();
            
            // using the stored information as inputs for constructor from
            // class Course
            Course course = new Course(code, name, credits, grade);
            
            // add course to the ArrayList
            courseList.add(course); 
            
            // display the class in the text area
            result.append("\n" + course.toString());
        }
    }
    
    // GPA calculator listener
    class CalGPAListener implements ActionListener
    {
        public void actionPerformed(ActionEvent event) {
            // declaring some variables used in the GPA calculation
            int credits, totalCredits = 0;
            double grade = 0;
            double gradeCredits = 0;
            double totalGradeCredits = 0;
            double GPA = 0;
            String letterGrade = "";
            
            // looping through the courseList and collect the grade and credits
            for(int i = 0; i < courseList.size(); i++){
                // retrieving the "i" th element 
                Course newCourse = courseList.get(i);
                credits = newCourse.getCredit();
                
                // updating total credits
                totalCredits += credits;
                
                // invoking the getCredit() method
                letterGrade = newCourse.getGrade();
                
                // checking to see what the letter grade is and setting
                // a number value to it
                if (letterGrade.equals("A")||letterGrade.equals("a"))
                {
                    grade = 4.0;
                }
                else if (letterGrade.equals("B")||letterGrade.equals("b"))
                {
                    grade = 3.0;
                }
                else if (letterGrade.equals("C")||letterGrade.equals("c"))
                {
                    grade = 2.0;
                }
                else if (letterGrade.equals("D")||letterGrade.equals("d"))
                {
                    grade = 1.0;
                }
                else if (letterGrade.equals("E")||letterGrade.equals("e"))
                {
                    grade = 0;
                }
                // setting a variable equal to grade times credits
                gradeCredits = grade * credits;
                
                // updating total for grade * credits
                totalGradeCredits += gradeCredits;
                
                // calculating GPA
                GPA = totalGradeCredits / totalCredits;
            }
            result.append(String.format("\n\n%7s%.1f", "GPA: ", GPA));
        }
    }

    // reset input listener
    class ResetInputListener implements ActionListener
    {
        // resetting the input fields to null or empty
        public void actionPerformed(ActionEvent event) {
            codeTextField.setText(null);
            nameTextField.setText(null);
            creditTextField.setText(null);
            gradeTextField.setText(null);

        }
    }

    // reset output listener
    class ResetOutputListener implements ActionListener
    {
        public void actionPerformed(ActionEvent event) {
            // clearing all but thr output heading and the courseList
            result.setText(heading);
            courseList.clear();
        }
    }
}
