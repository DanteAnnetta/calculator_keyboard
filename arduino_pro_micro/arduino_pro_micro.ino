#include <Wire.h>
#include <Keyboard.h>
#include <Keypad.h>
#include <Mouse.h>

const byte I2C_ADDRESS = 8;
char receivedKey;

const byte ROWS = 4;
const byte COLS = 10;

/* TODOs: 
- agregar funciones de movimiento del mouse (decodificado de los datos del arduino uno)
- implementar tecla de fn
- implementar tecla X, N, T
- implementar combinaciones de teclas
*/


/*
 == TECLAS DE LAS ÚLTIMAS COLUMNAS: ==

- Teclas panel intermedio (salvo las seis del arduino uno)
S => sin
O => cos
T => tan
P => pi
x => e^x
l => ln
g => log
i => i
Y => Shift
k => alpha
n => x,n,t
v => var


- Teclas panel superior

c => ctrl 
h => home (esc)
A => alt   
f => fn* SOLO FUNCIONA PARA COMBINACIONES DE TECLADO
\t => TAB (ya implementado) 
B => BACK (esc)
R => right click 
L=> left click
*/

char keys[ROWS][COLS] = {
  {'7' , '8' , '9' , '(' , ')' , 'S'  , 'x' , 'Y' , 'C'  , 'h' },
  {'4' , '5' , '6' , '*' , '/' , 'O'  , 'l' , 'k' ,'A'   , 'f' },
  {'1' , '2' , '3' , '+' , '-' , 'T'  , 'g' , 'n' , '\t' , 'B' },
  {'0' , '.' , 'p' , 'a' , 'e' , 'P'  , 'i' , 'v' , 'R'  , 'L' }
};

byte rowPins[ROWS] = {14 , 15 , 18 , 19};
byte colPins[COLS] = {1 , 0 , 4 , 5 , 6 , 7 , 8 , 9 , 10 , 16};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void receiveEvent(int howMany) {
    while (Wire.available()) {
        receivedKey = Wire.read();
        Keyboard.press(receivedKey);
        delay(5); // Pequeña pausa para simular la pulsación
        Keyboard.release(receivedKey);
    }
}

void setup() {
    Wire.begin(I2C_ADDRESS);
    Wire.onReceive(receiveEvent);
    Keyboard.begin();
}

void processKey(char key) {
    switch (key) {

        case 'S':
            Keyboard.write("sin(");
            delay(5);
            break;
        
        case 'O':
            Keyboard.write("cos(");
            delay(5);
            break;

        case 'T':
            Keyboard.write("tan(");
            delay(5);
            break;

        case 'P':
            Keyboard.write("π");
            delay(5);
            break;
            
        case 'x':
            Keyboard.write("e^x");
            delay(5);
            break;
        
        case 'l':
            Keyboard.write("ln(");
            delay(5);
            break;

        case 'g':
            Keyboard.write("log(");
            delay(5);
            break;

        case 'i':
            Keyboard.press('i');
            delay(5);
            Keyboard.release('i');
            break;

        case 'Y':
            Keyboard.press(KEY_SHIFT);
            delay(5);
            Keyboard.release(KEY_SHIFT);
        
        case 'k': // Alt     // CUMPLE LA MISMA FUNCIÓN QUE LA TECLA DE ALT, PERO SE MANTIENE POR CUESTIONES DE DISEÑO
            Keyboard.press(KEY_LEFT_ALT);
            delay(200);   // ALT TIENE UNA MAYOR DEMORA, DEBIDO A QUE SE USA EN COMBINACIÓN DE TECLAS
            Keyboard.release(KEY_LEFT_ALT);
            break;

        case 'n':   // TODO: implementar X, N, T
            // placeholder
            break;

        case 'v':
            Keyboard.press(KEY_LEFT_ALT);
            Keyboard.press('v');
            delay(5);
            Keyboard.press(KEY_LEFT_ALT);
            Keyboard.release('v');
        
        case 'C': // Ctrl
            Keyboard.press(KEY_LEFT_CTRL);
            delay(5);
            Keyboard.release(KEY_LEFT_CTRL);
            break;

        case 'A': // Alt
            Keyboard.press(KEY_LEFT_ALT);
            delay(200);   // ALT TIENE UNA MAYOR DEMORA, DEBIDO A QUE SE USA EN COMBINACIÓN DE TECLAS
            Keyboard.release(KEY_LEFT_ALT);
            break;

        case 'B': // Back (Escape)
            Keyboard.press(KEY_ESC);
            delay(5);
            Keyboard.release(KEY_ESC);
            break;

        case 'h': // Home (Escape)
            Keyboard.press(KEY_ESC);
            delay(5);
            Keyboard.release(KEY_ESC);
            break;

        case 'L': // Botón izquierdo del mouse
            Mouse.press(MOUSE_LEFT);
            delay(5);
            Mouse.release(MOUSE_LEFT);
            break;

        case 'R': // Botón derecho del mouse
            Mouse.press(MOUSE_RIGHT);
            delay(5);
            Mouse.release(MOUSE_RIGHT);
            break;

        case 'f':  // TODO: codificar tecla de [fn]
            continue;
            break;

        default: // Teclas normales
            Keyboard.press(key);
            delay(5);
            Keyboard.release(key);
            break;
    }
}

void loop() {
    char key = keypad.getKey();
    if (key) {
        processKey(key);
    }
}
