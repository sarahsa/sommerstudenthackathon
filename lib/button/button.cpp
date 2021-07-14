#include <Arduino.h>

bool buttonPressed(){
    int BUTTON = 4;
    bool buttonPressed = digitalRead(BUTTON);
    return !buttonPressed;
}