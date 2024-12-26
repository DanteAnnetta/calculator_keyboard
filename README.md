# calculator_keyboard

## About the keyboard
In order to implement the keyboard, we decided to use the keyboard emulation library (Keyboard.h) provided by Arduino, using an Arduino Pro Micro as host.
However, since the number of buttons used is greater than the number of pins provided by this microcontroller, we decided to install a second Arduino (a UNO R3 model in this case).
This device is responsible for reading a matrix of buttons on its own and sending the keystrokes to the main one using the I2c protocol.

This repository contains the firmware for each of the microcontrollers, as well as a schematic of the connections used.

calculator_keyboard ------ arduino_uno.ino
                      |--- arduino_pro_micro.ino
                      |--- schematics
