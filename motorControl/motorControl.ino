#include <Servo.h> // Servo object class

#define numOfValsRec 5  // motors being used
#define digitsPerVal 1 //we are only getting single digit values, for analog it would be 4 since analog goes from 0 to 1000

//Initializing each servo to a finger using the Servo.h class
Servo servoThumb;
Servo servoIndex;
Servo servoMiddle;
Servo servoRing;
Servo servoPinky;

int valsRec[numOfValsRec]; //an array for the number of values received, which would be 5 for 5 motors

//$00000
int stringLen = numOfValsRec * digitsPerVal + 1; //The +1 is to account for the $
int counter = 0; //counts the number of iterations
bool counterStart = false; // whenever we recieve the $, the counter becomes True and we will do counter ++
String recievedString; // we will take the recieved string and break it down into multiple substrings (which will be stored into the valsRec array

void setup() {
  Serial.begin(9600);  //Just standard initialization, I've seen and done this in other codes
  //Routing each servo to a digital pin
  servoThumb.attach(7);
  servoIndex.attach(8);
  servoMiddle.attach(9);
  servoRing.attach(10);
  servoPinky.attach(11);
  }

void recievedData() {
  while(Serial.available()){
    char c = Serial.read(); // looking for $
    if (c == '$') {    // begin once the character read is $
      counterStart = true;
    }

    if (counterStart) {
      if (counter < stringLen) {
        recievedString = String(recievedString + c); // adding the new character to the string
        counter++;
      }
      if (counter >= stringLen) {
        for (int i = 0; i < numOfValsRec ; i++) {
          int num = (i * digitsPerVal) + 1;
          valsRec[i] = recievedString.substring(num, num + digitsPerVal).toInt();
          }
          // RESETS
          recievedString = "";
          counter = 0;
          counterStart = false;
        }
      }
    }
}

void loop() {

  recievedData();
  if (valsRec[0] == 1) {servoThumb.write(180); }else{ servoThumb.write(0);}
  if (valsRec[0] == 1) {servoIndex.write(180); }else{ servoIndex.write(0);}
  if (valsRec[0] == 1) {servoMiddle.write(180); }else{ servoMiddle.write(0);}
  if (valsRec[0] == 1) {servoRing.write(180); }else{ servoRing.write(0);}
  if (valsRec[0] == 1) {servoPinky.write(180); }else{ servoPinky.write(0);}
  }
