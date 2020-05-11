//Written by Rupak Poddar
//www.youtube.com/RupakPoddar

/*
  * is to validate the password 
  # is to reset attempt
*/

#include <Password.h> //http://www.arduino.cc/playground/uploads/Code/Password.zip
#include <Keypad.h> //http://www.arduino.cc/playground/uploads/Code/Keypad.zip

Password password = Password( "1234" ); //change password from here

const byte ROWS = 4; // Four rows
const byte COLS = 4; //  columns
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

int lock = 12;

void setup(){

  Serial.begin(9600);
  keypad.addEventListener(keypadEvent);
  pinMode(12, OUTPUT);
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
   case '#': password.reset(); break;
   default: password.append(eKey);
     }
  }
}

void checkPassword(){
  if (password.evaluate()){
    Serial.println("Success");
    digitalWrite(12, HIGH);
    delay(1000);
    digitalWrite(12, LOW);
    password.reset();
  }else{
    Serial.println("Wrong");
  }
}
