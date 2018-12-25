/**
 * Tests class DegreeWorksFrame
 * 
 * @author (Ben Sebring) 
 * @version (April 6, 2016)
 */
import javax.swing.JFrame;

public class DegreeWorksFrameViewer
{
   public static void main(String[] args)
   {
      DegreeWorksFrame frame = new DegreeWorksFrame();
      frame.setTitle("My DegreeWorks Frame");
      frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      frame.setVisible(true);
   }
}