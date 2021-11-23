import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * Program to display earthquake details from a USGS data feed.
 */
public class QuakeInfo {
  public static void main(String[] args) {
    //new Main().testFeed();

    if (args.length != 2) { // If any arguments provided
      System.out.println("Invalid arguments provided.");
      System.exit(1);
    }

    if( Arrays.asList("significant","4.5","1.5","1.0","all").contains(args[0])){}
    else {
      System.out.println("Invalid severity level provided.");
      System.out.println("Please insert one of the following values: significant, 4.5, 1.5, 1.0 or all.");
      System.exit(1);
    }

    if( Arrays.asList("hour","day","week","month").contains(args[1])){}
    else {
      System.out.println("Invalid time period provided.");
      System.out.println("Please insert one of the following values: hour, day, week or month.");
      System.exit(1);
    }


    QuakeFeed quakeFeed = new QuakeFeed(args[0], args[1]);

    try{
        quakeFeed.Update();
    }
    catch(IOException ex){
        System.out.println (ex.toString());
        System.out.println("Could not find file ");
    }
    quakeFeed.print();

    System.out.println("\nShallowest : "+quakeFeed.getShallowest().toString());
    System.out.println("Deepest    : "+quakeFeed.getDeepest().toString());
    System.out.println("Strongest  : "+quakeFeed.getStrongest().toString());
    System.out.println("Weakest    : "+quakeFeed.getWeakest().toString());
  }

  public void testFeed(){
    QuakeFeed quakeFeed = new QuakeFeed("all", "hour");
    try{
        quakeFeed.Update();
    }
    catch(IOException ex){
        System.out.println (ex.toString());
        System.out.println("Could not find file ");
    }
    quakeFeed.print();
    System.out.println("\nShallowest : "+quakeFeed.getShallowest().toString());
    System.out.println("Deepest    : "+quakeFeed.getDeepest().toString());
    System.out.println("Strongest  : "+quakeFeed.getStrongest().toString());
    System.out.println("Weakest    : "+quakeFeed.getWeakest().toString());
  }

  public void testStub(){
    Quake quake = new Quake("2018-04-27T10:54:58.520Z,-4.1006,102.7375,103.14,4.8,mb,,84,2.291,1.05,us,us1000dt9m,2018-04-27T11:21:41.040Z,\"59km W of Pagaralam, Indonesia\",earthquake,8,7.4,0.082,46,reviewed,us,us");
    System.out.println(quake.toString());
  }
}
