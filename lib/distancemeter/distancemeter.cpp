#include <Arduino.h>

int TRIGGER = 14;
int ECHO = 16;

void distanceMeterSetup(){
    pinMode(TRIGGER, OUTPUT);
    pinMode(ECHO, INPUT);
}
bool distanceMeterActivated(int distanceThreshold){
    digitalWrite(TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    long duration = pulseIn(ECHO, HIGH);
    // Calculating the distance
    int distance = duration * 0.034 / 2; 

    bool dispense = distance < distanceThreshold;
    return dispense;
}