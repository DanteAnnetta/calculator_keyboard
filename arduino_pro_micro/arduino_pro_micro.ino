#include <Wire.h>
#include <Keyboard.h>
#include <Keypad.h>
#include <Mouse.h>

const byte I2C_ADDRESS = 8;
char caracterBuffer;
String buffer;

const byte ROWS = 4;
const byte COLS = 10;

char keys[ROWS][COLS] = {
  {'x' , 'S' , 'Y' , '7' , '8' , '9'  , '(' , ')' ,  'C' , 'h' },
  {'l' , 'O' , 'k' , '4' , '5' , '6'  , '*' , '/' ,  'A' , 'f' },
  {'g' , 'T' , 'n' , '1' , '2' , '3'  , '+' , '-' , '\t' , 'B' },
  {'i' , 'P' , 'v' , '0' , '.' , 'p'  , 'a' , 'e' ,  'R' , 'L' }
};

byte rowPins[ROWS] = {1 , 0 , 4 , 5};
byte colPins[COLS] = {7 , 8 , 6 , 9 , 10 , 16 , 14 , 15 , 18 , 19};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void decodeAndProcessMessage(String message) {
    message.replace("_", ""); // Eliminar los '_'
    if (message.length() == 0) return;

    char firstChar = message.charAt(0);
    if (firstChar != '|') {
        Keyboard.press(firstChar);
        delay(5);
        Keyboard.release(firstChar);
    }

    for (int i = 1; i < message.length(); i++) {
        if (message.charAt(i) == '1') {
            switch (i) {
                case 1: Keyboard.press(KEY_RETURN); delay(5); Keyboard.release(KEY_RETURN); break;
                case 2: Keyboard.press(KEY_UP_ARROW); delay(5); Keyboard.release(KEY_UP_ARROW); break;
                case 3: Keyboard.press(KEY_LEFT_ARROW); delay(5); Keyboard.release(KEY_LEFT_ARROW); break;
                case 4: Keyboard.press(KEY_RIGHT_ARROW); delay(5); Keyboard.release(KEY_RIGHT_ARROW); break;
                case 5: Keyboard.press(KEY_DOWN_ARROW); delay(5); Keyboard.release(KEY_DOWN_ARROW); break;
            }
        }
    }
}

void receiveEvent(int howMany) {
    buffer = "";
    while (Wire.available()) {
        caracterBuffer = Wire.read();
        buffer += caracterBuffer;
    }
    decodeAndProcessMessage(buffer);
}

void setup() {
    Wire.begin(I2C_ADDRESS);
    Wire.onReceive(receiveEvent);
    Keyboard.begin();
}

void processKey(char key) {
    switch (key) {
        case 'S': Keyboard.print("sin("); break;
        case 'O': Keyboard.print("cos("); break;
        case 'T': Keyboard.print("tan("); break;
        case 'P': Keyboard.print("\u03C0"); break; // Pi
        case 'x': Keyboard.print("e^x"); break;
        case 'l': Keyboard.print("ln("); break;
        case 'g': Keyboard.print("log("); break;
        case 'i': Keyboard.press('i'); break;
        case 'Y': Keyboard.press(KEY_LEFT_SHIFT); break;
        case 'k': Keyboard.press(KEY_LEFT_ALT); delay(200); Keyboard.release(KEY_LEFT_ALT); break;
        case 'v': Keyboard.press(KEY_LEFT_ALT); Keyboard.press('v'); delay(5); Keyboard.releaseAll(); break;
        case 'C': Keyboard.press(KEY_LEFT_CTRL); break;
        case 'A': Keyboard.press(KEY_LEFT_ALT); delay(200); Keyboard.release(KEY_LEFT_ALT); break;
        case 'B': case 'h': Keyboard.press(KEY_ESC); break;
        case 'L': Mouse.press(MOUSE_LEFT); delay(5); Mouse.release(MOUSE_LEFT); break;
        case 'R': Mouse.press(MOUSE_RIGHT); delay(5); Mouse.release(MOUSE_RIGHT); break;
        default: Keyboard.press(key); break;
    }
    delay(5);
    Keyboard.release(key);
}

void loop() {
    char key = keypad.getKey();
    if (key) {
        processKey(key);
    }
}
