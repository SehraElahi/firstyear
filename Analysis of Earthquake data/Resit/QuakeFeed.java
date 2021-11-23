import java.io.InputStream;
import java.net.URL;
import java.util.Scanner;
import java.io.IOException;
/**
 * An earthquake dataset obtained from the USGS web feed.
 */
public class QuakeFeed {

  private static final String WEB_TEMPLATE =
   "https://earthquake.usgs.gov/earthquakes/feed/v1.0/summary/%s_%s.csv";

  String severityLevel;
  String timePeriode;
  int counter;

  Quake[] quakeObject = new Quake[100000];

  public QuakeFeed(String level, String periode){
    severityLevel = level;
    timePeriode = periode;
  }

  public boolean Update() throws IOException{
    boolean updateData = false;
    String webFeed = String.format(WEB_TEMPLATE, severityLevel, timePeriode);
    Scanner scanner = new Scanner(new URL(webFeed).openStream());
    counter = 0;

    //Disregard first line;
    scanner.nextLine();

    while (scanner.hasNextLine()) {
      //
      quakeObject[counter] = new Quake(scanner.nextLine());
      //System.out.println("counter "+counter+" : "+quakeObject[counter].toString());

      //Atleast one quakeObject is filled
      updateData = true;
      counter++;
    }

    //Check on updated data
    //System.out.println("Data has been updated: "+updateData);

    // close the scanner
    scanner.close();

    //return whether data was updated
    return updateData;
  }

  public int getSize(){
    return counter;
  }

  public Quake get(int q){
    return quakeObject[q];
  }

  public Quake getWeakest(){
    double lowestMag = 0;
    int q = 0;
    for(int i = 0; i < counter; i++){
      if(i==0){
        lowestMag = quakeObject[i].getMagnitude();
        q = i;
      }
      if(quakeObject[i].getMagnitude() < lowestMag){
        lowestMag = quakeObject[i].getMagnitude();
        q = i;
      }
    }
    return get(q);
  }

  public Quake getStrongest(){
    double highestMag = 0;
    int q = 0;
    for(int i = 0; i < counter; i++){
      if(i==0){
        highestMag = quakeObject[i].getMagnitude();
        q = i;
      }
      if(quakeObject[i].getMagnitude() > highestMag){
        highestMag = quakeObject[i].getMagnitude();
        q = i;
      }
    }
    return get(q);
  }

  public Quake getShallowest(){
    double lowestDepth = 0;
    int q = 0;
    for(int i = 0; i < counter; i++){
      if(i==0){
        lowestDepth = quakeObject[i].getDepth();
        q = i;
      }
      if(quakeObject[i].getDepth() < lowestDepth){
        lowestDepth = quakeObject[i].getDepth();
        q = i;
      }
    }
    return get(q);
  }


  public Quake getDeepest(){
    double highestDepth = 0;
    int q = 0;
    for(int i = 0; i < counter; i++){
      if(i==0){
        highestDepth = quakeObject[i].getDepth();
        q = i;
      }
      if(quakeObject[i].getDepth() > highestDepth){
        highestDepth = quakeObject[i].getDepth();
        q = i;
      }
    }
    return get(q);
  }


  public boolean print(){
    for(int i=0; i<counter; i++){
      System.out.println(quakeObject[i].toString());
    }
    return true;
  }
}
