#include <Keypad.h>
#include <Wire.h>

// TODO: ACTUALIZAR PARA LEER ÚNICAMENTE UNA MATRIZ DE 2X3 Y EL TRACKPAD, PARA ENVIAR DICHA INFORMACIÓN AL ARDUINO PRO MICRO


const byte ROWS = 3;
const byte COLS = 6;

const byte ROWS_2 = 2;
const byte COLS_2 = 4;


char key;



// Mapeo de teclas (ajustar según necesidad)
char keys[ROWS][COLS] = {
  {'h', 'a', 'x', 'v', '\t', 127},  // '\t' para TAB, 127 para DELETE
  {'x', 'n', 'l', 'i', ',', '{'},
  {'s', 'c', 't', 'p', 'r', 'q'}
};

byte rowPins[ROWS] = {0, 2, 3};
byte colPins[COLS] = {4, 5, 6, 7, 8, 9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
    Wire.begin();
    Serial.begin(9600);
}

void loop() {
    key = keypad.getKey();
    
    if (key) { // Solo enviar si hay una tecla presionada
        Wire.beginTransmission(8); // Dirección del esclavo I2C
        Wire.write(key);
        Wire.endTransmission();
        Serial.println(key); // Para depuración
    }
}
