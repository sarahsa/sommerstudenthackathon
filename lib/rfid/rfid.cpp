#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 5 // Configurable, see typical pin layout above
#define SS_PIN 10 // Configurable, see typical pin layout above

#define GREEN_LED 9 //Output pin on arduino board
#define RED_LED 8 //Output pin on arduino board

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

void rfidSetup(){
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  SPI.begin(); // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522
}


bool isRfidActivated(){
  // Reset the loop if no new card present on the sensor/reader.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    digitalWrite(RED_LED, LOW); 
    digitalWrite(GREEN_LED, LOW); 
    return false;
  }
  
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    digitalWrite(RED_LED, LOW); 
    digitalWrite(GREEN_LED, LOW); 
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
 
  if ( RFIDtag.substring(1) == "42 89 B1 14" )//Change to your UID card number that you want to give access 
  {
    Serial.println("Access is granted");
    digitalWrite(RED_LED, LOW); 
    digitalWrite(GREEN_LED, HIGH); 
    return true;
  }
 
  else {
    Serial.println("Access is denied");
    Serial.println("Please put your card on the RFID reader..");
    digitalWrite(RED_LED, HIGH); 
    digitalWrite(GREEN_LED, LOW); 
    return false;
  }
}