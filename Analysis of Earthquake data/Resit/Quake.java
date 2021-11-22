/**
 * Details of a single earthquake.
 */

public class Quake {

  private double latitude;
  private double longitude;
  private double depth;
  private double magnitude;

  public Quake(String line) {
      String[] split = line.split(",");
      latitude = Double.parseDouble(split[1]);
      longitude = Double.parseDouble(split[2]);
      depth = Double.parseDouble(split[3]);
      magnitude = Double.parseDouble(split[4]);
  }

  public double getLatitude() throws QuakeException{
    return latitude;
  }

  public double getLongitude() throws QuakeException{
    return longitude;
  }

  public double getDepth() throws QuakeException{
    return depth;
  }

  public double getMagnitude() throws QuakeException{
    return magnitude;
  }

  //toString prints out the values exactly instead of memmory address (rubbish)
  public String toString() {
    //System.out.println(String.format ("M%0.1f, %3.2f km, (%2.4f\u00b0, %3.4f\u00b0)" getmagnitude(),getdepth(),getlatitude(), getlongitude()));
    return String.format ("M%.1f, %3.2f km, (%2.4f\u00b0, %3.4f\u00b0)", getMagnitude(),getDepth(),getLatitude(), getLongitude());
  }
}
