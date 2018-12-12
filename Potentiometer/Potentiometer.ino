/* This code uses a potentiometer and four single colour LEDs. Turning the potentiometer will result in the LEDS 
 *  
 * See attached Fritzing Diagram to set up the circuit and then follow the comments
  in the body of the code for a breakdown on each section of code.
 *  
 *  Wesley Slade 2018 - IXDA Arduino Workshop - Sheridan College
 *  all /* comments are by Wesley Slade
*/

void setup() {
  /* Turns on serial communcations and allows the Arduino to detect the potentiometer's input */
  Serial.begin(9600);

/* pinMode allows us to tell the Arduino pins what mode to be in. In this tutorial
 *  we want to set four pins to output, so each pin can power a seperate LED. 
*/  
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
}

void loop() {
  /* We're setting up a variable called Knob to detect our potentiometer's input from the A0 Analog Pin on the Arduino.
   *  While doing that, we're also using the map function to scale it down to a lower number for convenience. 
   *  Normally the potentiometer's input is between 0-1000~ and we're scaling it down to between 0-4 with the map function.
  */ 
 int Knob = map(analogRead(A0), 0, 1000, 0, 4);

 /* Serial.Print is a way for you to view your variables values while the code is running.
  *  Opening the Serial Monitor from the Tools menu will show our variable's values as the code runs
  *  The difference between Serial.print and Serial.println is that println will print on a new
  *  line each time the command runs. 
 */
Serial.println(Knob);

/* We're written 4 if/else statements that turn on the LED based on how high the potentiometer's input is.
 *  Since we've used the map function to change the input range, we only have to put 1, 2, 3, 4 as the 
 *  threshholds for our values.
 *  
 *  The digitalWrite function powering the digital pin listed as a number in the function 
 *  at 5V when it is declared as HIGH, and shutting off power to the pin when it is declared LOW.
 *  
 *  We've chosen Arduin Digital Pins 4, 5, 6 and 7 as the pins the LEDs are powered from.
*/
  if (Knob >= 1) {            
    digitalWrite(7,HIGH);
  } else {digitalWrite(7,LOW);}

    if (Knob >= 2) {            
    digitalWrite(6,HIGH);
  } else {digitalWrite(6,LOW);}

    if (Knob >= 3) {            
    digitalWrite(5,HIGH);
  } else {digitalWrite(5,LOW);}

    if (Knob >= 4) {            
    digitalWrite(4,HIGH);
  } else {digitalWrite(4,LOW);}
}
