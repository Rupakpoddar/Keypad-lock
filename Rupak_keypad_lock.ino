/*
Written by Rupak Poddar
www.youtube.com/RupakPoddar


  '*' is to validate the password 
  '#' is to reset attempt
  
*/

#include <Keypad.h>  //https://github.com/Chris--A/Keypad
//PASSWORD LIBRARY IS NO MORE REQUIRED FOR THIS PROJECT

String password = "1234"; //change the password from here
String input = "";

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns

// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = { 9,8,7,6 };// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte colPins[COLS] = { 5,4,3,2 };// Connect keypad COL0, COL1, COL2 and COL3 to these Arduino pins.


// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int door_lock = 12; //connect the door lock to pin 12.
int lock_delay = 1500; //change the delay from here.

void setup(){

  Serial.begin(9600);
  keypad.addEventListener(keypadEvent);
  pinMode(door_lock, OUTPUT);
}

void loop(){
  keypad.getKey();
}

void keypadEvent(KeypadEvent eKey){
  switch (keypad.getState()){
    case PRESSED:
 Serial.print("Pressed: ");
 Serial.println(eKey);
 switch (eKey){
   case '*': checkPassword(); break;
   case '#': input = ""; break;
   default: input+=eKey;
     }
  }
}

void checkPassword(){
  if (password == input){
    Serial.println("Success");
    digitalWrite(door_lock, HIGH);
    delay(lock_delay);
    digitalWrite(door_lock, LOW);
    input = "";
  }else{
    Serial.println("Wrong");
  }
}
