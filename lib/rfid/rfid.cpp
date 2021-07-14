#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9 // Configurable, see typical pin layout above
#define SS_PIN 10 // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

void rfidSetup(){
  SPI.begin(); // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522
}


bool rfidActivated(){
    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
 if ( ! mfrc522.PICC_IsNewCardPresent()) {
 return false;
 }
 
 // Select one of the cards
 if ( ! mfrc522.PICC_ReadCardSerial()) {
 return false;
 }
 
 //Show UID on serial monitor
 Serial.print("UID tag :");
 String RFIDtag = "";
 for (byte i = 0; i < mfrc522.uid.size; i++)
 {
 Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
 Serial.print(mfrc522.uid.uidByte[i], HEX);
 RFIDtag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
 RFIDtag.concat(String(mfrc522.uid.uidByte[i], HEX));
 }
 Serial.println();
 Serial.print("Message : ");
 RFIDtag.toUpperCase();
 
 if ( RFIDtag.substring(1) == "97 85 73 26" )//Change to your UID card number that you want to give access 
 {
 Serial.println("Access is granted");
 return true;
 }
 
 else {
 Serial.println("Access is denied");
 delay(1000);
 Serial.println("Please put your card on the RFID reader..");
 }
}