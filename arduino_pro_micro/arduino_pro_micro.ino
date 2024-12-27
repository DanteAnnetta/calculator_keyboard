//#include <Keypad.h>
#include <Wire.h>
//#include "Keyboard.h"

char key;
/*
const byte rows = 4;
const byte columns = 5;


char keys [filas][columnas] = {
  {'7' , '8' , '9', '(', ')'},
  {'4', '5', '6', '*', '/'},
  {'1', '2', '3', '+', '-'},
  {'0', '.', 'p', 'a', 'e'}
};

byte rowPins[rows] = {10 , 16 , 14 , 15};
byte columnPins[columns] = {5 , 6 , 7 , 8 , 9};

Keypad keypad = Keypad(makeKeymap(keys ) , rowPins , columnPins , rows , columns);
*/


void setup() {
  Serial.begin(9600);
  Wire.begin(8); 
  //Keyboard.begin();


}

void loop() {

  Wire.requestFrom(8, 1); 
  while (Wire.available()) { // If received data is detected,

    // Keys captured by the keyboard physically connected to the arduino pro mini
  /*
    key = keypad.getKey();
    if(key != 0){
      //Serial.println(key);
      Keyboard.write(key);

    }
    */
    // Keys captured by the keyboard connected by i2c

    key = Wire.read(); 
    if(key != 0){
      //Keyboard.write(key);
      Serial.println(key);
    }

    delay(10);
  }
}
