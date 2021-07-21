#include <Arduino.h>
#include <../lib/button/button.h>
#include <../lib/distancemeter/distancemeter.h>
#include <../lib/rfid/rfid.h>

int BUTTON = 4;
int RXLED = 17;
int RELAY = 2;

// the setup function runs once when you press reset or power the board
void setup() {
  distanceMeterSetup();
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
  rfidSetup();
}
 
// the loop function runs over and over again forever
void loop() {
  bool dispence = isButtonPressed() || isRfidActivated();
  digitalWrite(RXLED, !dispence);
  digitalWrite(RELAY, dispence);
}