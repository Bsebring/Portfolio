/**
 * Creates a sorted list form couses read from a file 
 * removes and replaces failed course, also creates a 
 * list of courses with grade "A"
 * 
 * @author(Ben Sebring)
 * @version(4/27/2016)
*/
import java.io.*;
import java.util.*;
import java.lang.*;

public class LinkedListCourse
{
    public static LinkedList<Course> courseList = new LinkedList<Course>();
    /**
     * Test the methods that you are going to implement. Your task will include the following:
     * 1) Create a sorted linked list of course by invoking the method "readItemsSortedOrder";
     * 2) Remove all failed courses from the lise by invoking the method "removeFailedCourse";
     * 3) Add two retaken courses into the list by invoking the method "addCourseIntoSortedList";
     *    You have to call the method to add one at a time:
     *    a) The first one to be added ["Math140", "Calculus I", 4, "C"]
     *    b) The second one to be added ["CPSC140", "Computer_Organization", 3, "B"]
     * 4) Find the courses with "A" from the list by invoking the method "searchACourses".
     * After each step, you need to print the linked list by  invoking the method "printListWithSeparator".
     */ 
    public static void main(String[] args) //throws FileNotFoundException
    {
        try{
            // read the file , store the courses in a licked list, and print out the list
            readItemsSortedOrder("courses.txt");
            System.out.println("A Sorted List Of The Classes Taken So Far)(imported from a file): ");
            printListWithSeparator(courseList);

            // removing the failed courses form the list
            System.out.println("\n A Sorted List After Removing Failed Courses: ");
            removeFailedCourse(courseList);
            printListWithSeparator(courseList);

            // adding retaken courses
            Course course1 = new Course("Math140", "Calculus I", 4, "C");
            addCourseIntoSortedList( courseList, course1);

            Course course2 = new Course("CPSC140", "Computer_Organization", 3, "B");
            addCourseIntoSortedList( courseList, course2);

            // printing the list after adding retaken courses
            System.out.println("\n A Sorted List After Adding Retaken Courses: ");
            printListWithSeparator(courseList);
            
            // printing the results of the searchACourses method
            System.out.println("\n A Sorted List Of Courses With Grade 'A': ");
            printListWithSeparator(searchACourses(courseList));

        }
        catch (FileNotFoundException e) {
            // error message
            System.out.println("Error, File not Found");
        }
    }

    /**
     * Method that reads an input file (containing a list of courses) into a sorted linked list 
     * (the course list is sorted on course code alphabetically)
     * 
     * @param fileName: the input file that is scanned
     * @return a linked list of courses (sorted) from the file
     */    
    public static LinkedList<Course> readItemsSortedOrder(String fileName) throws FileNotFoundException
    {
        // Hint: you may create a linkedList<Course> object first, and then for each line you read 
        //       (i.e., each course) call the method addCourseIntoSortedList (to be implemented below) 
        //       to add one course at a time when reading one line from the file
        File inputFile = new File(fileName);
        Scanner fileScan = new Scanner(inputFile);

        while(fileScan.hasNext()){
            // storing the data from the file 
            String code = fileScan.next();
            String name = fileScan.next();
            int credit = fileScan.nextInt();
            String grade = fileScan.next();
            
            // creating a Couse wit the stored data
            Course c = new Course(code, name, credit, grade);

            // adding the course into the sorted list
            addCourseIntoSortedList(courseList, c);
        }
        return courseList;
    }

    /**
     * Method that adds a courses into a sorted linked list 
     * (the course list is sorted on course code alphabetically)
     * 
     * @param l: a sorted linked list of course
     * @param c: a course to be added into a sorted linked list
     */
    public static void addCourseIntoSortedList(LinkedList<Course> l, Course c){
        // Important: You are NOT allowed to use available sorting method to make 
        //            the list sorted. You can only use ListIterator to find a 
        //            suitable position to add a course into the list. You may use 
        //            "compareTo" to compare two course codes.
        //
        // Hint: You may add the course node in the following scenarios:
        // Case 1: No node in the list, add it directly in the list
        // Case 2: The new node to be added will be smaller than the first node 
        //         in the list, add it at the begining in the list
        // Case 3: The new node to be added will be in somewhere in the list, move
        //         the iterator the right position, and add it in the list
        // Case 4: The new node to be added will be larger than the last node 
        //         in the list, add it at the end in the list
        ListIterator<Course> iterator = l.listIterator();

        // checking to see if the list is empty
        if (l.size() == 0){
            l.add(c);
        }
        // checking to see if the code comes before the first course in aplphabetical order
        else if (c.getCode().compareTo(l.peekFirst().getCode()) < 0) {
            // adding the course to the front of the list
            l.addFirst(c);
        }
        // checking to see if the code comes after the last course in aplphabetical order
        else if (c.getCode().compareTo(l.peekLast().getCode()) > 0) {
            // adding the course to the end of the list
            l.addLast(c);
        }
        else {
            String code = c.getCode();
            Course current = iterator.next();
            
            // searching for position to add the course
            while(iterator.hasNext() && code.compareTo(current.getCode()) > 0) {
                current = iterator.next();
            }
            // once the String code no longer comes after  the current course's code move to the
            // previous node to add the course into the correct position
            current = iterator.previous();
            iterator.add(c);
        }
    }

    /**
     * Method that removes the failed courses from the  linked list 
     * The failed course is defined as the course with the grade of "D" or "E"
     * 
     * @param l: a linked list of courses
     */    
    public static void removeFailedCourse(LinkedList<Course> l)
    {
        ListIterator<Course> iterator = l.listIterator();
        
        // using the iterator to check if a failing grade is detected and removing the failing couses
        while(iterator.hasNext()) {

            Course course = iterator.next();

            if (course.getGrade().equals("E")||course.getGrade().equals("D")) {
                iterator.remove();
            }
        }
    }

    /**
     * Method that searches the "A" courses from the  linked list, and save it a new linked List 
     * 
     * @param l: a sorted linked list of courses
     * @return a sorted linked list of "A" courses 
     */    
    public static LinkedList<Course> searchACourses(LinkedList<Course> l){
        ListIterator<Course> iterator = l.listIterator();
        LinkedList<Course> listOfACourses = new LinkedList<Course> ();

        while(iterator.hasNext()) {
            Course course = iterator.next();
            // if a grade of "A" is detected invoke the addCourseIntoSortedList method to add into the 
            // "A" list courses
            if (course.getGrade().equals("A")) {
                addCourseIntoSortedList(listOfACourses, course);
            }

        }
        return listOfACourses;
    }

    /**
     * Method that prints a linked list of courses, each course will be printed as follows:  
     *  ->  coureCode courseName courseCredit courseGrade
     *  
     * @param l: a sorted linked list of courses
     */
    public static void printListWithSeparator(LinkedList<Course> l)
    {
        // using the iterator to print the list
        ListIterator<Course> iterator = l.listIterator();
        while(iterator.hasNext()) {
            String val = iterator.next().toString();
            System.out.println(" ->" +val);

        }
    }


}
