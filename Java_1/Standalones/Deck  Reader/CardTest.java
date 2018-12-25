
/**
 * This program accepts user input for an input and output file. if the file is not found, it returns
 * the appropriate error message and handles the exception. The program decodes the input file into the appropriate 
 * card and value. this program will tell if the deck is full, and also if the deck has any repeats. the class 
 * is named CardTest due to instructor request.
 * 
 * @author (Benjamin Sebring) 
 * @version (Due Date 12/5/15 @ 11:59PM Version 1.0) 
 */
import java.io.*;
import java.util.*;
import java. lang.*;
import javax.swing.JOptionPane;
public class CardTest
{
    public static String inputFileName;
    public static String outputFileName;
    public static String output;
    public static Scanner keyboard = new Scanner(System.in);
    public static String value = "";
    public static String reader = "";
    public static String exCredOut = "";
    public static int rank;
    public static String suit = "";
    public static String goodSuit = "";
    public static String goodRank = "";
    public static String goodVal = "";
    public static String exCred = "";
    public static String delimiter = "";
    public static String goodCard = "";
    public static int delimError, suitError, rankError, multipleErrors; 
    public static String path = "";
    public static boolean done = false;
    public static int goodCardCount, badCardCount, cardCount, attempts;
    public static int extraTwoClubs,extraTwoHearts,extraTwoSpades,extraTwoDiamonds,extraThreeClubs,extraThreeHearts,extraThreeSpades,extraThreeDiamonds,extraFourClubs,extraFourHearts,extraFourSpades,extraFourDiamonds,extraFiveClubs,extraFiveHearts,extraFiveSpades, extraFiveDiamonds,extraSixClubs,extraSixHearts,extraSixSpades,extraSixDiamonds,extraSevenClubs,extraSevenHearts,extraSevenSpades,extraSevenDiamonds,extraEightClubs,extraEightHearts,extraEightSpades,extraEightDiamonds,extraNineClubs,extraNineHearts,extraNineSpades,extraNineDiamonds,extraTenClubs,extraTenHearts,extraTenSpades,extraTenDiamonds,extraJackClubs,extraJackHearts,extraJackSpades,extraJackDiamonds,extraQueenClubs,extraQueenHearts,extraQueenSpades,extraQueenDiamonds,extraKingClubs,extraKingHearts,extraKingSpades,extraKingDiamonds,extraAceClubs,extraAceHearts,extraAceSpades,extraAceDiamonds;
    public static int twoClubs,twoHearts,twoSpades,twoDiamonds,threeClubs,threeHearts,threeSpades,threeDiamonds,fourClubs,fourHearts,fourSpades,fourDiamonds,fiveClubs,fiveHearts,fiveSpades,fiveDiamonds,sixClubs,sixHearts,sixSpades,sixDiamonds,sevenClubs,sevenHearts,sevenSpades,sevenDiamonds,eightClubs,eightHearts,eightSpades,eightDiamonds,nineClubs,nineHearts,nineSpades,nineDiamonds,tenClubs,tenHearts,tenSpades,tenDiamonds,jackClubs,jackHearts,jackSpades,jackDiamonds,queenClubs,queenHearts,queenSpades,queenDiamonds,kingClubs,kingHearts,kingSpades,kingDiamonds,aceClubs,aceHearts,aceSpades,aceDiamonds;
    public static void main(String[] args)
    {
        while(!done)
        {
          if(attempts > 0)
          {
              inputFileName = JOptionPane.showInputDialog("Enter File Name...");
              outputFileName = JOptionPane.showInputDialog("Enter Output File Name...");
              readFile();
              attempts = 0;
              done = true;
          }
            else
          {
            System.out.println("Enter File Name...");

            inputFileName = keyboard.next();
            System.out.println("Enter Output File Name...");
            outputFileName = keyboard.next();
            readFile();
          }
        }
    

    }

    public static void readFile()
    { 

        try
        {
            File file = new File(inputFileName);
            Scanner in = new Scanner(file);
            path = "path : " + file.getAbsolutePath();
            in.useDelimiter("\\s");
            System.out.println("Reading File...");
            PrintWriter out = new PrintWriter(outputFileName);

            System.out.println("Decoding to output file...");
            System.out.println("Done.");

            while(in.hasNext())
            {
                reader = in.next();
                if(reader.equals("")){continue;}
                suit = "";
                value = "";
                int length = (reader.length());
                goodSuit = "";
                goodRank = "";
                goodVal = "";
                exCred = "";
                delimiter = "";
                goodCard = "";
                //for(int i = 0; i <= length; i++)
                //{
                //char ch = reader.charAt(i);
                char lastThree;
                char lastFour;
                if( length == 3)
                {
                    lastThree = reader.charAt(2);
                    value = value + reader.charAt(0);
                    delimiter = delimiter + reader.charAt(1);
                    suit = suit + reader.charAt(2);
                    goodRank = rankCheck(value);
                    goodSuit = suitCheck(suit,goodRank);
                    goodVal = numVal(rank,value);
                    goodCard = delimiterCheck(delimiter, goodRank, goodSuit);
                    exCred = extraCredit(rank, delimiter, suit, value);
                }
                else if (length == 4)
                {
                    suit = suit + reader.charAt(3);
                    value = value + reader.charAt(0);
                    value = value + reader.charAt(1);
                    delimiter = delimiter + reader.charAt(2);
                    lastFour = reader.charAt(3);
                    goodRank = rankCheck(value);
                    goodSuit = suitCheck(suit,goodRank);
                    goodVal = numVal(rank,value);
                    goodCard = delimiterCheck(delimiter, goodRank, goodSuit);
                    exCred = extraCredit(rank, delimiter, suit, value);
                }
                else if (length >4)
                {
                    suit = suit + reader.charAt(3);
                    value = value + reader.charAt(0);
                    lastFour = reader.charAt(3);
                    delimiter = delimiter + reader.charAt(2);
                    goodSuit = suitCheck(suit,goodRank);
                    goodVal = numVal(rank,value);
                    goodRank = rankCheck(value);
                    goodCard = delimiterCheck(delimiter, goodRank, goodSuit);
                    exCred = extraCredit(rank, delimiter, suit, value);
                }
                else
                {
                    //say there are multiple errors
                    //goodSuit = "Multiple errors in " + reader;
                    suit = suit + reader.charAt(0);
                    value = value + reader.charAt(0);
                    goodSuit = suitCheck(suit,goodRank);
                    goodVal = numVal(rank,value);
                    goodRank = rankCheck(value);
                    goodCard = delimiterCheck(delimiter, goodRank, goodSuit);
                    exCred = extraCredit(rank, delimiter, suit, value);
                }
                out.println(goodCard);
                cardCount++;
                
                
            }
            String deckCheck = missCheck();
            String sumBorder = "-------Summary-------";
            String ecBorder = "-------Extra-Credit-------";
            String sum = summary(badCardCount, goodCardCount, cardCount, multipleErrors, delimError, suitError, rankError, path);
            out.println(sumBorder);
            out.println(path);
            out.println(sum);
            out.println(ecBorder);
            out.println(deckCheck);
            out.println(exCred);
            in.close();
            out.close();
            attempts = 0;
            done = true;
        } 
        catch(FileNotFoundException exception)
        {
            System.out.println("File Not Found...");
            attempts++;

        }
        catch(NumberFormatException exception)
        {

            System.out.println("invalid rank in " + reader);
            attempts++;
        }
    }

    public static String rankCheck(String value) 
    {
        String correctRank = "";
        char first = value.charAt(0);
        if(Character.isDigit(first))
        {
            rank = Integer.parseInt(value);

            if( rank >= 2 && rank <= 10)
            {
                if (rank == 2){correctRank = "Two of";}
                else if (rank == 3){correctRank = "Three of";}
                else if (rank == 4){correctRank = "Four of";}
                else if (rank == 5){correctRank = "Five of";}
                else if (rank == 6){correctRank = "Six of";}
                else if (rank == 7){correctRank = "Seven of";}
                else if (rank == 8){correctRank = "Eight of";}
                else if (rank == 9){correctRank = "Nine of";}
                else if (rank == 10){correctRank = "Ten of";}
                else{correctRank = "Invalid rank in: " + reader;}

            }
            else{correctRank = "Invalid rank in: " + reader;}

        }
        else if(Character.isLetter(first))
        {
            if( value.equals( "a" ) || value.equals( "A" )){correctRank = "Ace of";rank = 11;}
            else if(value.equals( "j" ) || value.equals( "J" )){correctRank = "Jack of";rank = 10;}
            else if(value.equals( "k" ) || value.equals( "K" )){correctRank = "King of";rank = 10;}
            else if(value.equals( "q" ) || value.equals( "Q" )){correctRank = "Queen of";rank = 10;}
            else{correctRank = "Invalid rank in: " + reader;}
        }
        else{correctRank = "Invalid rank in: " + reader;}
        return correctRank;

    }

    public static String extraCredit(int rank, String delimiter, String suit, String value)
    {
      //Made for extra credit.  
        if (rank == 2)
         {
            if((suit.equals ("s")||suit.equals("S"))&& delimiter.equals("-")){twoSpades++; if(twoSpades > 1 ){extraTwoSpades = twoSpades - 1; exCredOut = exCredOut + "Extra Two Of Spades ";}}        
            else if((suit.equals ("c")||suit.equals("C"))&& delimiter.equals("-")){twoClubs++; if(twoClubs > 1 ){extraTwoClubs = twoClubs - 1;exCredOut = exCredOut + "Extra Two Of Clubs ";}}        
            else if((suit.equals ("d")||suit.equals("D"))&& delimiter.equals("-")){twoDiamonds++;if(twoDiamonds > 1 ){extraTwoDiamonds = twoDiamonds - 1;exCredOut = exCredOut + "Extra Two Of Diamonds ";}}        
            else if((suit.equals ("h")||suit.equals("H"))&& delimiter.equals("-")){twoHearts++;if(twoHearts > 1 ){extraTwoHearts = twoHearts - 1;exCredOut = exCredOut + "Extra Two Of Hearts ";}}        
            else{}
        }
        else if (rank == 3)
        {
            if((suit.equals ("s")||suit.equals("S"))&& delimiter.equals("-")){threeSpades++; if(threeSpades > 1 ){extraThreeSpades = threeSpades - 1;exCredOut = exCredOut + "Extra Three Of Spades ";}}        
            else if((suit.equals ("c")||suit.equals("C"))&& delimiter.equals("-")){threeClubs++; if(threeClubs > 1 ){extraThreeClubs = threeClubs - 1;exCredOut = exCredOut + "Extra Three Of Clubs ";}}        
            else if((suit.equals ("d")||suit.equals("D"))&& delimiter.equals("-")){threeDiamonds++;if(threeDiamonds > 1 ){extraThreeDiamonds = threeDiamonds - 1;exCredOut = exCredOut + "Extra Three Of Diamonds ";}}        
            else if((suit.equals ("h")||suit.equals("H"))&& delimiter.equals("-")){threeHearts++;if(threeHearts > 1 ){extraThreeHearts = threeHearts - 1;exCredOut = exCredOut + "Extra Three Of Hearts ";}}        
            else{}
        }
        else if (rank == 4)
        {
            if((suit.equals ("s")||suit.equals("S"))&& delimiter.equals("-")){fourSpades++; if(fourSpades > 1 ){extraFourSpades = fourSpades - 1;exCredOut = exCredOut + "Extra Four Of Spades ";}}        
            else if((suit.equals ("c")||suit.equals("C"))&& delimiter.equals("-")){fourClubs++; if(fourClubs > 1 ){extraFourClubs = fourClubs - 1;exCredOut = exCredOut + "Extra Four Of Clubs ";}}        
            else if((suit.equals ("d")||suit.equals("D"))&& delimiter.equals("-")){fourDiamonds++;if(fourDiamonds > 1 ){extraFourDiamonds = fourDiamonds - 1;exCredOut = exCredOut + "Extra Four Of Diamonds ";}}        
            else if((suit.equals ("h")||suit.equals("H"))&& delimiter.equals("-")){fourHearts++;if(fourHearts > 1 ){extraFourHearts = fourHearts - 1;exCredOut = exCredOut + "Extra Four Of Hearts ";}}        
            else{}
        }
        else if (rank == 5)
        {
            if((suit.equals ("s")||suit.equals("S"))&& delimiter.equals("-")){fiveSpades++; if(fiveSpades > 1 ){extraFiveSpades = fiveSpades - 1;exCredOut = exCredOut + "Extra Five Of Spades ";}}        
            else if((suit.equals ("c")||suit.equals("C"))&& delimiter.equals("-")){fiveClubs++; if(fiveClubs > 1 ){extraFiveClubs = fiveClubs - 1;exCredOut = exCredOut + "Extra Five Of Clubs ";}}        
            else if((suit.equals ("d")||suit.equals("D"))&& delimiter.equals("-")){fiveDiamonds++;if(fiveDiamonds > 1 ){extraFiveDiamonds = fiveDiamonds - 1;exCredOut = exCredOut + "Extra Five Of Diamonds ";}}        
            else if((suit.equals ("h")||suit.equals("H"))&& delimiter.equals("-")){fiveHearts++;if(fiveHearts > 1 ){extraFiveHearts = fiveHearts - 1;exCredOut = exCredOut + "Extra Five Of Hearts ";}}        
            else{}
        }
        else if (rank == 6)
        {
          if((suit.equals ("s")||suit.equals("S"))&& delimiter.equals("-")){sixSpades++; if(sixSpades > 1 ){extraSixSpades = sixSpades - 1;exCredOut = exCredOut + "Extra Six Of Spades ";}}        
            else if((suit.equals ("c")||suit.equals("C"))&& delimiter.equals("-")){sixClubs++; if(sixClubs > 1 ){extraSixClubs = sixClubs - 1;exCredOut = exCredOut + "Extra Six Of Clubs ";}}        
            else if((suit.equals ("d")||suit.equals("D"))&& delimiter.equals("-")){sixDiamonds++;if(sixDiamonds > 1 ){extraSixDiamonds = sixDiamonds - 1;exCredOut = exCredOut + "Extra Six Of Diamonds ";}}        
            else if((suit.equals ("h")||suit.equals("H"))&& delimiter.equals("-")){sixHearts++;if(sixHearts > 1 ){extraSixHearts = sixHearts - 1;exCredOut = exCredOut + "Extra Six Of Hearts ";}}        
            else{}
        }
        else if (rank == 7)
        {
            if((suit.equals ("s")||suit.equals("S"))&& delimiter.equals("-")){sevenSpades++; if(sevenSpades > 1 ){extraSevenSpades = sevenSpades - 1;exCredOut = exCredOut + "Extra Seven Of Spades ";}}        
            else if((suit.equals ("c")||suit.equals("C"))&& delimiter.equals("-")){sevenClubs++; if(sevenClubs > 1 ){extraSevenClubs = sevenClubs - 1;exCredOut = exCredOut + "Extra Seven Of Clubs ";}}        
            else if((suit.equals ("d")||suit.equals("D"))&& delimiter.equals("-")){sevenDiamonds++;if(sevenDiamonds > 1 ){extraSevenDiamonds = sevenDiamonds - 1;exCredOut = exCredOut + "Extra Seven Of Diamonds ";}}        
            else if((suit.equals ("h")||suit.equals("H"))&& delimiter.equals("-")){sevenHearts++;if(sevenHearts > 1 ){extraSevenHearts = sevenHearts - 1;exCredOut = exCredOut + "Extra Seven Of Hearts ";}}        
            else{}
        }
        else if (rank == 8)
         {
            if((suit.equals ("s")||suit.equals("S"))&& delimiter.equals("-")){eightSpades++; if(eightSpades > 1 ){extraEightSpades = eightSpades - 1;exCredOut = exCredOut + "Extra Eight Of Spades ";}}        
            else if((suit.equals ("c")||suit.equals("C"))&& delimiter.equals("-")){eightClubs++; if(eightClubs > 1 ){extraEightClubs = eightClubs - 1;exCredOut = exCredOut + "Extra Eight Of Clubs ";}}        
            else if((suit.equals ("d")||suit.equals("D"))&& delimiter.equals("-")){eightDiamonds++;if(eightDiamonds > 1 ){extraEightDiamonds = eightDiamonds - 1;exCredOut = exCredOut + "Extra Eight Of Diamonds ";}}        
            else if((suit.equals ("h")||suit.equals("H"))&& delimiter.equals("-")){eightHearts++;if(eightHearts > 1 ){extraEightHearts = eightHearts - 1;exCredOut = exCredOut + "Extra Eight Of Hearts ";}}        
            else{}
        }
        else if (rank == 9)
          {
            if((suit.equals ("s")||suit.equals("S"))&& delimiter.equals("-")){nineSpades++; if(nineSpades > 1 ){extraNineSpades = nineSpades - 1;exCredOut = exCredOut + "Extra Nine Of Spades ";}}        
            else if((suit.equals ("c")||suit.equals("C"))&& delimiter.equals("-")){nineClubs++; if(nineClubs > 1 ){extraNineClubs = nineClubs - 1;exCredOut = exCredOut + "Extra Nine Of Clubs ";}}        
            else if((suit.equals ("d")||suit.equals("D"))&& delimiter.equals("-")){nineDiamonds++;if(nineDiamonds > 1 ){extraNineDiamonds = nineDiamonds - 1;exCredOut = exCredOut + "Extra Nine Of Diamonds ";}}        
            else if((suit.equals ("h")||suit.equals("H"))&& delimiter.equals("-")){nineHearts++;if(nineHearts > 1 ){extraNineHearts = nineHearts - 1;exCredOut = exCredOut + "Extra Nine Of Hearts ";}}       
            else{}
        }
        else if (rank == 10&& (value.equals( "j" ) || value.equals( "J"  )))
          {
            if((suit.equals ("s")||suit.equals("S"))&& delimiter.equals("-")){jackSpades++; if(jackSpades > 1 ){extraJackSpades = jackSpades - 1;exCredOut = exCredOut + "Extra Jack Of Spades ";}}        
            else if((suit.equals ("c")||suit.equals("C"))&& delimiter.equals("-")){jackClubs++; if(jackClubs > 1 ){extraJackClubs = jackClubs - 1;exCredOut = exCredOut + "Extra Jack Of Clubs ";}}        
            else if((suit.equals ("d")||suit.equals("D"))&& delimiter.equals("-")){jackDiamonds++;if(jackDiamonds > 1 ){extraJackDiamonds = jackDiamonds - 1;exCredOut = exCredOut + "Extra Jack Of Diamonds ";}}        
            else if((suit.equals ("h")||suit.equals("H"))&& delimiter.equals("-")){jackHearts++;if(jackHearts > 1 ){extraJackHearts = jackHearts - 1;exCredOut = exCredOut + "Extra Jack Of Hearts ";}}        
            else{}
        }
        else if (rank == 10&& (value.equals( "q" ) || value.equals( "Q"  )))
         {
            if((suit.equals ("s")||suit.equals("S"))&& delimiter.equals("-")){queenSpades++; if(queenSpades > 1 ){extraQueenSpades = queenSpades - 1;exCredOut = exCredOut + "Extra Queen Of Spades ";}}        
            else if((suit.equals ("c")||suit.equals("C"))&& delimiter.equals("-")){queenClubs++; if(queenClubs > 1 ){extraQueenClubs = queenClubs - 1;exCredOut = exCredOut + "Extra Queen Of Clubs ";}}        
            else if((suit.equals ("d")||suit.equals("D"))&& delimiter.equals("-")){queenDiamonds++;if(queenDiamonds > 1 ){extraQueenDiamonds = queenDiamonds - 1;exCredOut = exCredOut + "Extra Queen Of Diamonds ";}}        
            else if((suit.equals ("h")||suit.equals("H"))&& delimiter.equals("-")){queenHearts++;if(queenHearts > 1 ){extraQueenHearts = queenHearts - 1;exCredOut = exCredOut + "Extra Queen Of Hearts ";}}        
            else{}
        }
        else if (rank == 10&& (value.equals( "k" ) || value.equals( "K"  )))
        {
            if((suit.equals ("s")||suit.equals("S"))&& delimiter.equals("-")){kingSpades++; if(kingSpades > 1 ){extraKingSpades = kingSpades - 1;exCredOut = exCredOut + "Extra King Of Spades ";}}        
            else if((suit.equals ("c")||suit.equals("C"))&& delimiter.equals("-")){kingClubs++; if(kingClubs > 1 ){extraKingClubs = kingClubs - 1;exCredOut = exCredOut + "Extra King Of Clubs ";}}        
            else if((suit.equals ("d")||suit.equals("D"))&& delimiter.equals("-")){kingDiamonds++;if(kingDiamonds > 1 ){extraKingDiamonds = kingDiamonds - 1;exCredOut = exCredOut + "Extra King Of Diamonds ";}}        
            else if((suit.equals ("h")||suit.equals("H"))&& delimiter.equals("-")){kingHearts++;if(kingHearts > 1 ){extraKingHearts = kingHearts - 1;exCredOut = exCredOut + "Extra King Of Hearts ";}}        
            else{}
        }
        else if (rank == 10)
        {
            if((suit.equals ("s")||suit.equals("S"))&& delimiter.equals("-")){tenSpades++; if(tenSpades > 1 ){extraTenSpades = tenSpades - 1;exCredOut = exCredOut + "Extra Ten Of Spades ";}}        
            else if((suit.equals ("c")||suit.equals("C"))&& delimiter.equals("-")){tenClubs++; if(tenClubs > 1 ){extraTenClubs = tenClubs - 1;exCredOut = exCredOut + "Extra Ten Of Clubs ";}}        
            else if((suit.equals ("d")||suit.equals("D"))&& delimiter.equals("-")){tenDiamonds++;if(tenDiamonds > 1 ){extraTenDiamonds = tenDiamonds - 1;exCredOut = exCredOut + "Extra Ten Of Diamonds ";}}        
            else if((suit.equals ("h")||suit.equals("H"))&& delimiter.equals("-")){tenHearts++;if(tenHearts > 1 ){extraTenHearts = tenHearts - 1;exCredOut = exCredOut + "Extra Ten Of Hearts ";}}        
            else{}
        }
        else if (value.equals( "a" ) || value.equals( "A"  )&&rank == 11)
      {
            if((suit.equals ("s")||suit.equals("S"))&& delimiter.equals("-")){aceSpades++; if(aceSpades > 1 ){extraAceSpades = aceSpades -1; exCredOut = exCredOut + "Extra Ace Of Spades " ;}}        
            else if((suit.equals ("c")||suit.equals("C"))&& delimiter.equals("-")){aceClubs++; if(aceClubs > 1 ){extraAceClubs = aceClubs - 1;exCredOut = exCredOut + "Extra Ace Of Clubs ";}}        
            else if((suit.equals ("d")||suit.equals("D"))&& delimiter.equals("-")){aceDiamonds++;if(aceDiamonds > 1 ){extraAceDiamonds = aceDiamonds - 1;exCredOut = exCredOut + "Extra Ace Of Diamonds " ;}}        
            else if((suit.equals ("h")||suit.equals("H"))&& delimiter.equals("-")){aceHearts++;if(aceHearts > 1 ){extraAceHearts = aceHearts - 1;exCredOut = exCredOut + "Extra Ace Of Hearts " ;}}        
            else{}
        }
        else
        {

        }
        return exCredOut;
    }

    public static String numVal(int rank, String value)
    {
        String worth = "";
        if (rank == 2){worth = " (value = 2).";}
        else if (rank == 3){worth = " (value = 3).";}
        else if (rank == 4){worth = " (value = 4).";}
        else if (rank == 5){worth = " (value = 5).";}
        else if (rank == 6){worth = " (value = 6).";}
        else if (rank == 7){worth = " (value = 7).";}
        else if (rank == 8){worth = " (value = 8).";}
        else if (rank == 9){worth = " (value = 9).";}
        else if (rank == 10){worth = " (value = 10).";}
        else if ((value.equals( "a" ) || value.equals( "A"  ))&&rank == 11){worth = " (value = 1 or value = 11).";}
        else {worth = "";}
        return worth;
    }

    public static String suitCheck(String suit ,String goodRank)
    {
        String correctSuit = "";
       if (!goodRank.equals("invalid")&&!goodRank.equals("")&&!goodRank.equals(" "))
        {
        if ((rank>=2&&rank<=10)||(value.equals("a")||value.equals("A"))){
        if(suit.equals ("s")||suit.equals("S")){ correctSuit = " Spades.";}        
        else if(suit.equals ("c")||suit.equals("C")){ correctSuit = " Clubs.";}        
        else if(suit.equals ("d")||suit.equals("D")){ correctSuit = " Diamonds.";}        
        else if(suit.equals ("h")||suit.equals("H")){ correctSuit = " Hearts.";}        
        else{ correctSuit = "invalid";}
       }
    }
    
        return correctSuit;
    }

    public static String delimiterCheck(String delimiter, String goodRank, String goodSuit)
    {
        String correctDelimiter = "";
        
        if((!goodRank.equals("invalid")||!goodRank.equals("")||!goodRank.equals(" ")) && (!goodSuit.equals("invalid")||!goodSuit.equals("")||!goodSuit.equals(" ")))
        {

            if(delimiter.equals("-")){correctDelimiter = goodRank + goodSuit + goodVal; goodCardCount++;
            }
            else
            {
                correctDelimiter = "Invalid Delimiter in: " + reader; badCardCount++;delimError++;
            }

        }
        else if((goodRank.equals("invalid")||goodRank.equals("")||goodRank.equals(" ")) && !goodSuit.equals("invalid"))
        {
            if(delimiter.equals("-")){correctDelimiter = "Invalid Rank in: " + reader; badCardCount++;rankError++;}
            else
            {
                correctDelimiter = "Multiple Errors in: " + reader; badCardCount++; multipleErrors++;
            }
        }
        else if(!goodRank.equals("invalid") && (goodSuit.equals("invalid")||goodSuit.equals("")||goodSuit.equals(" ")))
        {
            if(delimiter.equals("-")){correctDelimiter = "Invalid Suit in: " + reader; badCardCount++;suitError++;}
            else
            {
                correctDelimiter = "Multiple Errors in: " + reader; badCardCount++; multipleErrors++;
            }
        }
        else
        {
             correctDelimiter = "Multiple Errors in: " + reader; badCardCount++; multipleErrors++;  
        }
        return correctDelimiter;
    }
    public static String summary (int badCardCount,int goodCardCount, int cardCount,int multipleErrors,  int delimError, int suitError, int rankError, String path)
    {
        String sumOut = "";
        sumOut = "Valid Cards: " + goodCardCount + " Invalid Cards: " + badCardCount + " Total Cards: " + cardCount +
        " Rank Errors: " + rankError + "\nDelimiter Errors: " + delimError + " Suit Errors: " + suitError + 
        " Multiple Errors: " + multipleErrors ;
        return sumOut;
    }
    public static String missCheck()
    {
        //Checks for missing cards.
        String missing = "";
        if(twoClubs == 0) 
         {if(!missing.contains("Missing Two of Clubs"))
             {missing = missing + "Missing Two of Clubs" ;}}
        if(twoSpades == 0)
         {if(!missing.contains("Missing Two of Spades"))
             {missing = missing + "Missing Two of Spades" ;}}
        if(twoDiamonds == 0)
         {if(!missing.contains("Missing Two of Diamonds"))
             {missing = missing + "Missing Two of Diamonds" ;}}
        if(twoHearts == 0)
         {if(!missing.contains("Missing Two of Hearts"))
             {missing = missing + "Missing Two of Hearts" ;}}
        if(threeClubs == 0)
         {if(!missing.contains("Missing Three of Clubs"))
             {missing = missing + "Missing Three of Clubs" ;}}
        if(threeSpades == 0)
         {if(!missing.contains("Missing Three of Spades"))
             {missing = missing + "Missing Three of Spades" ;}}
        if(threeDiamonds == 0)
         {if(!missing.contains("Missing Three of Diamonds"))
            {missing = missing + "Missing Three of Diamonds" ;}}
        if(threeHearts == 0)
         {if(!missing.contains("Missing Three of Hearts"))
            {missing = missing + "Missing Three of Hearts" ;}}
        if(fourClubs == 0)
         {if(!missing.contains("Missing Four of Clubs")){missing = missing + "Missing Four of Clubs" ;}}
        if(fourSpades == 0)
         {if(!missing.contains("Missing Four of Spades"))
            {missing = missing + "Missing Four of Spades" ;}}
        if(fourDiamonds == 0)
         {if(!missing.contains("Missing Four of Diamonds"))
            {missing = missing + "Missing Four of Diamonds" ;}}
        if(fourHearts == 0)
         {if(!missing.contains("Missing Four of Hearts"))
            {missing = missing + "Missing Four of Hearts" ;}}
        if(fiveClubs == 0)
         {if(!missing.contains("Missing Five of Clubs"))
            {missing = missing + "Missing Five of Clubs" ;}}
        if(fiveSpades == 0)
         {if(!missing.contains("Missing Five of Spades"))
            {missing = missing + "Missing Five of Spades" ;}}
        if(fiveDiamonds == 0)
         {if(!missing.contains("Missing Five of Diamonds"))
            {missing = missing + "Missing Five of Diamonds" ;}}
        if(fiveHearts == 0)
         {if(!missing.contains("Missing Five of Hearts"))
            {missing = missing + "Missing Five of Hearts" ;}}
        if(sixClubs == 0)
         {if(!missing.contains("Missing Six of Clubs"))
            {missing = missing + "Missing Six of Clubs" ;}}
        if(sixSpades == 0)
         {if(!missing.contains("Missing Six of Spades"))
            {missing = missing + "Missing Six of Spades" ;}}
        if(sixDiamonds == 0)
         {if(!missing.contains("Missing Six of Diamonds"))
            {missing = missing + "Missing Six of Diamonds" ;}}
        if(sixHearts == 0)
         {if(!missing.contains("Missing Six of Hearts"))
            {missing = missing + "Missing Six of Hearts" ;}}
        if(sevenClubs == 0)
         {if(!missing.contains("Missing Seven of Clubs"))
            {missing = missing + "Missing Seven of Clubs" ;}}
        if(sevenSpades == 0)
         {if(!missing.contains("Missing Seven of Spades"))
            {missing = missing + "Missing Seven of Spades" ;}}
        if(sevenDiamonds == 0)
         {if(!missing.contains("Missing Seven of Diamonds"))
            {missing = missing + "Missing Seven of Diamonds" ;}}
        if(sevenHearts == 0)
         {if(!missing.contains("Missing Seven of Hearts"))
            {missing = missing + "Missing Seven of Hearts" ;}}
        if(eightClubs == 0)
         {if(!missing.contains("Missing Eight of Clubs"))
            {missing = missing + "Missing Eight of Clubs" ;}}
        if(eightSpades == 0)
         {if(!missing.contains("Missing Eight of Spades"))
            {missing = missing + "Missing Eight of Spades" ;}}
        if(eightDiamonds == 0)
         {if(!missing.contains("Missing Eight of Diamonds"))
            {missing = missing + "Missing Eight of Diamonds" ;}}
        if(eightHearts == 0)
         {if(!missing.contains("Missing Eight of Hearts"))
            {missing = missing + "Missing Eight of Hearts" ;}}
        if(nineClubs == 0)
         {if(!missing.contains("Missing Nine of Clubs"))
            {missing = missing + "Missing Nine of Clubs" ;}}
        if(nineSpades == 0)
         {if(!missing.contains("Missing Nine of Spades"))
            {missing = missing + "Missing Nine of Spades" ;}}
        if(nineDiamonds == 0)
         {if(!missing.contains("Missing Nine of Diamonds"))
            {missing = missing + "Missing Nine of Diamonds" ;}}
        if(nineHearts == 0)
         {if(!missing.contains("Missing Nine of Hearts"))
            {missing = missing + "Missing Nine of Hearts" ;}}
        if(tenClubs == 0)
         {if(!missing.contains("Missing Ten of Clubs"))
            {missing = missing + "Missing Ten of Clubs" ;}}
        if(tenSpades == 0)
         {if(!missing.contains("Missing Ten of Spades"))
            {missing = missing + "Missing Ten of Spades" ;}}
        if(tenDiamonds == 0)
         {if(!missing.contains("Missing Ten of Diamonds"))
            {missing = missing + "Missing Ten of Diamonds" ;}}
        if(tenHearts == 0)
         {if(!missing.contains("Missing Ten of Hearts"))
            {missing = missing + "Missing Ten of Hearts" ;}}
        if(jackClubs == 0)
         {if(!missing.contains("Missing Jack of Clubs"))
            {missing = missing + "Missing Jack of Clubs" ;}}
        if(jackSpades == 0)
         {if(!missing.contains("Missing Jack of Spades"))
            {missing = missing + "Missing Jack of Spades" ;}}
        if(jackDiamonds == 0)
         {if(!missing.contains("Missing Jack of Diamonds"))
            {missing = missing + "Missing Jack of Diamonds" ;}}
        if(jackHearts == 0)
         {if(!missing.contains("Missing Jack of Hearts"))
            {missing = missing + "Missing Jack of Hearts" ;}}
        if(queenClubs == 0)
         {if(!missing.contains("Missing Queen of Clubs"))
            {missing = missing + "Missing Queen of Clubs" ;}}
        if(queenSpades == 0)
         {if(!missing.contains("Missing Queen of Spades"))
            {missing = missing + "Missing Queen of Spades" ;}}
        if(queenDiamonds == 0)
         {if(!missing.contains("Missing Queen of Diamonds"))
            {missing = missing + "Missing Queen of Diamonds" ;}}
        if(queenHearts == 0)
         {if(!missing.contains("Missing Queen of Hearts"))
            {missing = missing + "Missing Queen of Hearts" ;}}
        if(kingClubs == 0)
         {if(!missing.contains("Missing King of Clubs"))
            {missing = missing + "Missing King of Clubs" ;}}
        if(kingSpades == 0)
         {if(!missing.contains("Missing King of Spades"))
            {missing = missing + "Missing King of Spades" ;}}
        if(kingDiamonds == 0)
         {if(!missing.contains("Missing King of Diamonds"))
            {missing = missing + "Missing King of Diamonds" ;}}
        if(kingHearts == 0)
         {if(!missing.contains("Missing King of Hearts"))
            {missing = missing + "Missing King of Hearts" ;}}
        if(aceClubs == 0)
         {if(!missing.contains("Missing Ace of Clubs"))
            {missing = missing + "Missing Ace of Clubs" ;}}
        if(aceSpades == 0)
         {if(!missing.contains("Missing Ace of Spades"))
            {missing = missing + "Missing Ace of Spades" ;}}
        if(aceDiamonds == 0)
         {if(!missing.contains("Missing Ace of Diamonds"))
            {missing = missing + "Missing Ace of Diamonds" ;}}
        if(aceHearts == 0)
         {if(!missing.contains("Missing Ace of Hearts"))
            {missing = missing + "Missing Ace of Hearts" ;}}
        if(twoClubs >= 1 && twoHearts >= 1 && twoSpades >= 1 && twoDiamonds >= 1 && threeClubs >= 1 && threeHearts >= 1 && threeSpades >= 1 && threeDiamonds >= 1 && fourClubs >= 1 && fourHearts >= 1 && fourSpades >= 1 && fourDiamonds >= 1 && fiveClubs >= 1 && fiveHearts >= 1 && fiveSpades >= 1 && fiveDiamonds >= 1 && sixClubs >= 1 && sixHearts >= 1 && sixSpades >= 1 && sixDiamonds >= 1 && sevenClubs >= 1 && sevenHearts >= 1 && sevenSpades >= 1 && sevenDiamonds >= 1 && eightClubs >= 1 && eightHearts >= 1 && eightSpades >= 1 && eightDiamonds >= 1 && nineClubs >= 1 && nineHearts >= 1 && nineSpades >= 1 && nineDiamonds >= 1 && tenClubs >= 1 && tenHearts >= 1 && tenSpades >= 1 && tenDiamonds >= 1 && jackClubs >= 1 && jackHearts >= 1 && jackSpades >= 1 && jackDiamonds >= 1 && queenClubs >= 1 && queenHearts >= 1 && queenSpades >= 1 && queenDiamonds >= 1 && kingClubs >= 1 && kingHearts >= 1 && kingSpades >= 1 && kingDiamonds >= 1 && aceClubs >= 1 && aceHearts >= 1 && aceSpades >= 1 && aceDiamonds >= 1 && goodCardCount == 52){missing = "This is a complete deck!";}
        return missing;
    }
}
