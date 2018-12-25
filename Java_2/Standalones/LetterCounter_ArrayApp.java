
/**
 * Write a description of class countLetters here.
 * 
 * @author (Benjamin Sebring) 
 * @version (2/8/16)
 */
import java.util.*;
public class LetterCounter_ArrayApp
{
    // Defining the alphabet as an array.
    final public static String [] ALPHABET = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", 
            "k", "l","m", "n", "o", "p", "q", "r","s","t", "u", "v", "w", "x", "y", "z"};
    // Definining the countArray to store 26 integers.
    public static int [] countArray = new int [26];

    public static int [] countLetters(String str)
    {
        // using a for loop to search through the string.
        for (int h = 0; h < str.length(); h++)
        {
            // initializing and resetting string check.
            String check = "";
            // storing the character in question in string check.
            check += str.charAt(h);
            for (int j = 0; j < ALPHABET.length; j++)
            {
                // Checking to see if string check matches any letter in the alphabet.
                if (check.equals(ALPHABET [j]))
                {
                    // adding 1 to the same position of countArray.
                    countArray [j] += 1;
                    break;
                }
            } 
        }
        return countArray;
    }

    public static void printLetterFreq(int [] countArray)
    {
        for (int k = 0; k < countArray.length; k++)
        {
            // Making sure that the frequency is not zero.
            if (countArray[k] > 0)
            {
                // printing out each letter, and its' frequency.
                System.out.print(ALPHABET [k]);
                System.out.printf("%-1s%2d%3s", "(", countArray [k], "): ");
                // storing the value at k into num
                int num = countArray[k];
                // calling the numToStar method and printing it out.
                String starFreq = numToStar(num);
                System.out.println(starFreq);
            }
        }
    }

    public static String numToStar(int num)
    {
        String star = "";
        // Adding "*" until it is equal to the currency.
        for (int k = 0; k < num; k++) 
        {
            star += "*";
        }
        return star;
    }

    public static char mostFreqLetter(int [] countArray)
    {
        // initializing variables.
        int freqLett = 0;
        String highestOccurence = "";
        char highestOccurChar= 'a';
        for (int k = 0; k < countArray.length; k++)
        {
            // checking every value to see which letter has the highest frequency
            if (countArray [k] > freqLett)
            {
                // setting the current value to the highest if it is larger.
                freqLett = countArray [k];
                // finding the letter that matches the highest value and storing it in highestOccurChar.
                highestOccurence = ALPHABET [k];
                highestOccurChar = highestOccurence.charAt(0);
            }
            // resetting the value to zero for the next string to be evaluated.
            countArray [k] = 0;
        }
        return highestOccurChar;
    }

    public static void main() 
    {
        // Initializing the strings and converting them to lowercase.
        String str0 = "counting the frequencies of letters";
        String str1 = "Computer programming II is fun";
        String lowerCase1 = str1.toLowerCase();
        String str2 = "After a fairly tame season so far -- especially compared to the last one -- a monster storm loomed Friday over the Carolinas north \nto New England, spurring people to hunker down with their shovels, coffee and ideally firewood, given real fears that powerful winds and heavy snow and \nice could knock out power. Roughly 75 million people total are in the path, 30 million of whom are under blizzard watches or warnings.";
        String lowerCase2 = str2.toLowerCase();
        String str3 = "Our department boasts an employment rate for graduates of nearly 100% in the field. Graduating students have recently been placed \nin a wide variety of organizations, including: Cisco Systems, Hershey Foods, IBM, Lockheed Martin, Merck, New York Life, National Security Agency (NSA), \nPocono Medical Center, Proteus Technologies, Sanofi-Pasteur, Situational Awareness Systems, Space and Naval Warfare Systems (SPAWAR), US Army R&D Center at \nPicatinny Arsenal, NJ, Vanguard Investments, Verizon, and Vonage.";
        String lowerCase3 = str3.toLowerCase();

        // calling the methods using str0
        int [] test = countLetters(str0);
        System.out.println("Letter Frequency: " + str0); 
        // Calling the printLetterFreq with the Array countArray as the input
        printLetterFreq(countArray);
        char frequent = mostFreqLetter(countArray);
        System.out.println("The most Frequent letter is: " + frequent + "\n");

        // calling the methods using str1
        int [] test2 = countLetters(lowerCase1);
        System.out.println("Letter Frequency: " + str1);
        // Calling the printLetterFreq with the Array countArray as the input
        printLetterFreq(countArray);
        char frequent2 = mostFreqLetter(countArray);
        System.out.println("The most Frequent letter is: " + frequent2 + "\n");

        // calling the methods using str0
        int [] test3 = countLetters(lowerCase2);
        System.out.println("Letter Frequency: " + str2);
        // Calling the printLetterFreq with the Array countArray as the input
        printLetterFreq(countArray);
        char frequent3 = mostFreqLetter(countArray);
        System.out.println("The most Frequent letter is: " + frequent3 + "\n");

        // calling the methods using str0
        int [] test4 = countLetters(lowerCase3);
        System.out.println("Letter Frequency: " + str3);
        // Calling the printLetterFreq with the Array countArray as the input
        printLetterFreq(countArray);
        char frequent4 = mostFreqLetter(countArray);
        System.out.println("The most Frequent letter is: " + frequent4 + "\n");
    }
}
