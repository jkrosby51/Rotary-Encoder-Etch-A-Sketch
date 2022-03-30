import processing.serial.*;

/*
 * Johnny Krosby
 * 3/30/2022
 * 
 * Gathers data from Arduino etchInput.ino through the Serial Port.
 * Creates a window to be used as a canvas
 * Uses Arduino data from etchInput.ino to control the visuals shown on the canvas.
 * 
 * 
 * Sending Data between Processing and Arduino:
 *  https://learn.sparkfun.com/tutorials/connecting-arduino-to-processing/all
 * Processing Reference:
 *  https://processing.org/reference
 * 
 */

 
Serial myPort;
String val = "";     // Data received from the serial port

int xCoor = 0; // Stored X Coordinates
int yCoor = 0; // Stored Y Coordinates
int cHeight = 500; // canvas height
int cWidth = 500; // canvas width
int tempX = 0;
int tempY = 0;
boolean drawing = true;

int circleDistance = 2;
   
void setup() {
  size(500, 500);
  noStroke();
  background(0);
  
  String portName = "COM6"; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 9600);
}

void draw() { 
  
  if(drawing == true) // Only draws when drawing is toggled
    circle(xCoor, yCoor, 2);
  
  if ( myPort.available() > 0){
    val = myPort.readString();  // Storing data from etchInput.ino through Serial Port.
    println(val);
  } 
  if(val.contains("X+")){
    //RIGHT
    if(xCoor <= cWidth - circleDistance)
      xCoor += circleDistance;
  }
  if(val.contains("X-")){
    //LEFT
    if(xCoor >= circleDistance)
      xCoor -= circleDistance;
  }
  if(val.contains("Y+")){
    //DOWN
    if(yCoor >= circleDistance)
      yCoor -= circleDistance;
  }
  if(val.contains("Y-")){
    //UP
    if(yCoor <= cHeight - circleDistance)
      yCoor += circleDistance;
    }
  if(val.contains("btnB"))   // Clears Canvas
    background(0);
  if(val.contains("btnA")){  // Toggles drawing
    if(drawing == true)
      drawing = false;
    else
      drawing = true;
  }
  val = "";
    

}
