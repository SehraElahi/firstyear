/**
* Exception class for use with the earthquakes application.
*/
public class QuakeException extends RuntimeException {

 private static final long serialVersionUID = 1L;

 public QuakeException(String message) {
   super(message);
 }
}
