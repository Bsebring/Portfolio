
/**
 * Write a description of class bug here.
 * 
 * @author (Ben Sebring) 
 * @version (3/1/16)
 */
import java.io.*;
import java.util.InputMismatchException;
public class Bug
{
    // private variable declaration
    private int row;
    private int column;
    private int direction;
    private String [][] bugSpot = {
            {".", ".", ".", ".", ".",".", ".",".",".","."}, {".",".",".",".",".",".", ".",".",".","."},
            {".", ".",".",".",".", ".", ".",".",".","."} ,{".", ".",".",".",".", ".", ".",".",".","."}, 
            {".", ".",".",".",".", ".", ".",".",".","."}
        };

    // default constructor
    public Bug() {
        row = 0;
        column = 0;
        direction = 0;
    }

    // Constructor with parameters
    public Bug(int row, int column, int direction) {
        this.row = row;
        this.column = column;
        this.direction = direction;
    }

    // Accessor or getter methods
    public int getRow(){
        return row;
    }

    public int getColumn(){
        return column;
    }

    public int getDirection(){
        return direction;
    }

    // mutator methods
    public int turn (int d) 
    {
        // update the direction based on user choice
        String directionLetter = "";
        if (d == 0) {
            directionLetter = "N";
        }
        else if (d == 1) {
            directionLetter = "E";
        }
        else if (d == 2) {
            directionLetter = "S";
        }
        else if (d == 3) {
            directionLetter = "W";
        }
        else 
        {
            throw new IllegalArgumentException("Please enter a number 0-3 for the direction");   
        }
        // setting the bugs position to the corresponding letter
        bugSpot [row][column] = directionLetter;
        direction = d;
        return d;
    }
    // mutator method to reset the variables
    public void reset() {
        row = 0;
        column = 0;
        direction = 0;
    }

    public void move(int num) throws ArrayIndexOutOfBoundsException { 
        String directionLetter = "";

        // checking to see if row and column are within their boundaries
        if ((row >= 0 && row <= 5) && (column >=  0 && column <= 10)){
            if (direction == 0) {
                row -= num;
                directionLetter =  "N";
            }
            else if (direction == 1) {
                column += num;
                directionLetter = "E";
            }
            else if (direction == 2) {
                row += num;
                directionLetter = "S";
            }
            else if (direction == 3) {
                column -= num;
                directionLetter = "W";
            }
            

            //using nested for loop to set the bugs position
            for (int i = 0; i <= 4; i++) {
                for (int j = 0; j <= 9; j++){
                    bugSpot [i] [j] = ".";
                    if (i == row && j == column){
                        bugSpot [i][j] = directionLetter;
                    }
                    else 
                    {
                        bugSpot [i] [j] = ".";
                    }
                }
            }
        }

        // checking to see if the bug hits a boundary or not
        if (direction == 2 && row  > 5) {
            row = 4;
            column = column;
            bugSpot [row] [column] = directionLetter;
            throw new ArrayIndexOutOfBoundsException("Hit the wall on the South boundary");

        }
        else if (direction == 0 && row  < 0){
            row = 0;
            column = column;
            bugSpot [row] [column] = directionLetter;
            throw new ArrayIndexOutOfBoundsException("Hit the wall on the North boundary");

        }
        else if (direction == 3 && column  < 0){
            column = 0;
            row = row;
            bugSpot [row] [column] = directionLetter;
            throw new ArrayIndexOutOfBoundsException("Hit the wall on the West boundary");

        }
        else if (direction == 1 && column  > 10){
            column = 9;
            row = row;
            bugSpot [row] [column] = directionLetter;
            throw new ArrayIndexOutOfBoundsException("Hit the wall on the East boundary");

        }
    }

    public void printCurrentPosition() {
        // printing out the current position using a nested for loop
        for (int i = 0; i < 5; i++) {
            System.out.println();
            for (int j = 0; j < 10; j++){

                System.out.print(bugSpot [i] [j]);
            }
        }
        System.out.println("\n\n");
    }
}
