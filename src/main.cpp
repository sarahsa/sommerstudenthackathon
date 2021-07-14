#include <Arduino.h>
#include <../lib/button/button.h>
#include <../lib/distancemeter/distancemeter.h>
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
MFRC522::MIFARE_Key key;

volatile bool bNewInt = false;
byte regVal = 0x7F;
void activateRec(MFRC522 mfrc522);
void clearInt(MFRC522 mfrc522);


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
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
}
 
// the loop function runs over and over again forever
void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    Serial.println("No card!");
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    Serial.println("no card!");
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "BD 31 15 2B") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(3000);
  }
 
 else   {
    Serial.println(" Access denied");
    delay(3000);
  }
  bool dispence = distanceMeterActivated(10) || buttonPressed();
  digitalWrite(RXLED, dispence);
  digitalWrite(RELAY, dispence);
}