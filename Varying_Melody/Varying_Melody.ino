/*
  Melody

  Plays a melody

  circuit:
  - 8 ohm speaker on digital pin 8

  created 21 Jan 2010
  modified 30
  Aug 2011
  by Tom Igoe
  
  modified Nov 2018
  by Wesley Slade

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Tone
*/



/* This is the modified version of the Tone_Melody tutorial available in the examples section
  of the Arduino Software.

  This code uses an ultrasonic sensor to detect the present and distance of an object placed
  in front of the sensor, and based on the object's distance it will play a different tone through
  a simple two wire speaker.

  See attached Fritzing Diagram to set up the circuit and then follow the comments
  in the body of the code for a breakdown on each section of code.

    Wesley Slade 2018 - IXDA Arduino Workshop - Sheridan College
    all /* comments are by Wesley Slade
    all // comments are by Tom Igoe - the original "Tone" tutorial creator

*/


/* These variables declare a variable equal to the digital pin 
 *  we are plugging the sensor into, whenever we reference our trigger or echo
 *  pin we can write this variable instead. If you want to change which
 *  digital pin you're using simply change the number to the pin you want to use.
*/
int trigPin = 11;
int echoPin = 12;

/* This variable is slightly different from an int variable. We are using 
 *  it in this case because a long variable type lets the variable have a decimal point. 
 *  An int variable cannot have a decimal point.
*/
long duration, inches;


/* The variable "user" creates a boolean variable that has two states: true and false. 
 *  Further down in the code we will create an If Statement to change this variable to true
 *  if a object is detected.
 *  We will also create a second If Statement to change this variable back
 *  to false if an object is not detected.
*/
bool object = false;


/* This line just includes a file located in the folder where the Arduino Sketch is created */
#include "pitches.h"
/* These two variables contain notes from pitches.h
 *  You can reference that file to find notes and easily
 *  add them to the variable by either replacing a current
 *  note or adding a comma to the last note and putting the new one after
*/

/* Just like the ultrasonic sensor pins, here we're assigning our speaker a digital pin  */
int MelodyPin = 8;

/* melodyLong has 7 notes and melodyShort has 3 */

int MelodyLong[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, NOTE_B3, NOTE_C4
};
int MelodyShort[] = {
  NOTE_G3, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 8, 4, 4
};

void setup() {
  /* Starts monitoring the serial port for information coming into the Arduino.
   *  In this case we will be using the data the Ultrasonic Sensor is sending to
   *  determine how far an object is away from the sensor.

  */
  Serial.begin (9600);
  /* pinMode allows us to tell the Arduino pins what mode to be in.
   *  Our Trigger pin is set to OUTPUT because we want it to send out a pulse.
   *  Our Echo pin is set to INPUT because we want it to listen for the echo of the pulse
   *  we sent out in trigger
  */
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop() {

  /* This code is for the ultrasonic sensor*/
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // Convert the time into a distance
  inches = (duration / 2) / 74; // Divide by 74 or multiply by 0.0135
  Serial.print(inches);
  Serial.println();


  /* This is just a simple if/else statemant that detects whether an object
   *  is within 5 inches of the sensor. If it is, the variable "object"
   *  will be set to true.
   *  && adds an additional check, only making an object true if it is between 1-10 inches.
  */
  if (inches >= 1 && inches < 10) {
    object = true;
  }
  else {
    object = false;
  }

  /* If statement that checks if there is a user nearby. */

  if (object == true) {

    /* This is a for loop that plays a melody depending on if there is
     * an object is detected
    */

    for (int thisNote = 0; thisNote < 7; thisNote++) {
      // to calculate the note duration, take one second divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / noteDurations[thisNote];
      /* Tone is the function that plays a note and it has 3 arguments (the information between the () )
       *  MelodyPin = The digital pin you've assigned the MelodyPin variable, could also just be declared as '8'
       *  melodyLong[thisNote] =  What variable to get the notes from

      */
      tone(MelodyPin, MelodyLong[thisNote], noteDuration);
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(200);
    }
    /* tiny delay to break up the notes for clarity */
    delay(1000);
  }

  if (object == false) {

    for (int thisNote = 0; thisNote < 3; thisNote++) {
      // to calculate the note duration, take one second divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / noteDurations[thisNote];
      /*Tone is the function that plays a note and it has 3 arguments (the information between the () )
       * MelodyPin = The digital pin you've assigned the MelodyPin variable, could also just be declared as '8'
       * MelodyLong[thisNote= =  What variable to get the notes from

      */
      tone(MelodyPin, MelodyShort[thisNote], noteDuration);
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(200);
    }
    /* Small delay to break up the notes if a user isn't detected */
    delay(2000);
  }

}
