#include <Arduino.h>
#include <../lib/button/button.h>
#include <../lib/distancemeter/distancemeter.h>
#include <../lib/rfid/rfid.h>

int BUTTON = 4;
int RXLED = 17;
int RELAY = 2;

// the setup function runs once when you press reset or power the board
void setup() {
  setupDistanceMeter();
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(RXLED, OUTPUT);
  pinMode(RELAY, OUTPUT);
  Serial.begin(9600);
  rfidSetup();
}
 
// the loop function runs over and over again forever
void loop() {

 bool dispence = buttonPressed() || rfidActivated();
  Serial.print("Dispence: ");
  Serial.println(dispence);
  digitalWrite(RXLED, !dispence);
  digitalWrite(RELAY, dispence);
}