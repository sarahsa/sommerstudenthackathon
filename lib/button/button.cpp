#include <Arduino.h>

bool isButtonPressed(){
    int BUTTON = 4;
    bool buttonPressed = digitalRead(BUTTON);
    return !buttonPressed;
}