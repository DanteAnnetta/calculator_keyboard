#include <Keypad.h>
#include <Wire.h>

const int rows = 3;
const int columns = 6;
char key;


// TODO: change E for (x,n,t)'s key

// b = "TAB" , ¿ = "DELETE" 
char keys [rows][columns] = {
  {'h', 'a', 'E', 'v', 'b', '¿'},
  {'x', 'n', 'l', 'i', ',', '{'},
  {'s', 'c', 't', 'p', 'r', 'q'}
};
  

byte rowPins[rows] = {0 , 3 , 2};
byte columnPins[columns] = {4 , 5 , 6 , 7 , 8 , 9};

Keypad keys = Keypad(makeKeymap(keys ) , rowPins , columnPins , rows , columns);

void setup() {
  Wire.begin();
  //Serial.begin(9600);
  

}

void loop() {
  

  key = keys.getKey();
  if(key != 0){
    Wire.beginTransmission(8);
    Wire.write(key);
    Wire.endTransmission();
    //Serial.println(key);
  }
  delay(10);
}
