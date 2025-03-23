#include <Keypad.h>
#include <Wire.h>

// TODO: CAMBIAR SÍMBOLOS DE LA MATRIZ

const byte ROWS = 2;
const byte COLS = 3;

char key;
String message;

// Mapeo de teclas
char keys[ROWS][COLS] = {
  {'\t', 127, ','},  // '\t' para TAB, 127 para DELETE
  {'{', 'r', 'q'}
};

byte rowPins[ROWS] = {7, 8};
byte colPins[COLS] = {9, 10, 11};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
    Wire.begin();  // Inicializa I2C como maestro
    //Serial.begin(9600);
    
    // Configuración de pines del trackpad
    for (byte i = 2; i <= 6; i++) {
        pinMode(i, INPUT_PULLUP);
    }
}

String encodeTrackpad() {
    String pins = "";
    for (byte i = 2; i <= 6; i++) {
        pins += String(not(digitalRead(i)));
        if (i < 6) pins += "_";  // Separador
    }
    return pins;
}

void sendI2CMessage(String msg) {
    Wire.beginTransmission(8);  // Dirección del esclavo I2C
    Wire.write(msg.c_str(), msg.length());
    Wire.endTransmission();
}

void loop() {
    key = keypad.getKey();
    
    if (key) { // Solo enviar si hay una tecla presionada
        message = String(key) + "_" + encodeTrackpad();
        sendI2CMessage(message);
        //Serial.println(message); // Para depuración
    } 
    else {  // En caso de que no se esté pulsando ninguna tecla del keypad
        message = String('|') + "_" + encodeTrackpad();  // CARACTER NULO 
        sendI2CMessage(message);
        //Serial.println(message); // Para depuración
    }

    delay(100);
}
