/*
The code below is used to control the RFID reader and two LEDs. When scanning RFID tags, the accepted tags turn on a yellow LED briefly, and the non-accepted tags turns on a red LED briefly.

- The first thing the code does is include the SPI and MFRC522 libraries. These libraries are necessary for the code to work.
- After that, the code initializes the MFRC522 module and sets the SDA and RST pins.
- In the setup function, the code begins the serial communication and starts the SPI communication. It also initializes the MFRC522 module.
- In the loop function, the code looks for new cards. If a new card is present, it reads the card's UID.
- The code then checks if the UID of the card is one of the accepted UIDs. If it is, the code turns on the yellow LED for 1.5 seconds.
- If the UID of the card is not registered, the code turns on the red LED for 1.5 seconds.
- After the code has been executed, it halts the PICC and stops the encryption on the PCD.
*/

#include <SPI.h>                                        //communication with the Arduino microcontroller
#include <MFRC522.h>                                    //MFRC522 is the RFID reader we are using 

#define SDApin 10                                       //SDA from the reader is connected to pin 10
#define RSTpin 9                                        //RST from the reader is connected to pin 9
#define redLED 5                                        //red LED is connected to pin 5
#define yellowLED 6                                     //yellow LED is connected to pin 6

MFRC522 mfrc522(SDApin, RSTpin);

void setup() 
{
SPI.begin();                                            //starts the SPI
Serial.begin(9600);                                     //allows us to monitor the reader using the serial moniter function
mfrc522.PCD_Init();                                     //function in the library to initialize the mfrc522

pinMode(5, OUTPUT);
pinMode(6, OUTPUT);                                     //starts pins for red and yellow LEDs                       

//Serial.println("Please scan your tag...\n");            //Prompts the user to scan tag
//Serial.println();                                       //empty line to appear in the serial monitor

}

void loop()
{
if(!mfrc522.PICC_IsNewCardPresent())                    //reader is searching for tags to scan
  {  
    return;
  }

if(!mfrc522.PICC_ReadCardSerial())                      //correct tag is presented
  {
    return;
  }    
  
//Serial.println();
//Serial.println("Tag UID is:");
String tag = "";
for(byte i = 0; i < mfrc522.uid.size; i++)              //prints the UID of the tag to the serial monitor
  {
    //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    //Serial.print(mfrc522.uid.uidByte[i], HEX);
    tag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    tag.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
//Serial.println();

tag.toUpperCase();                                      //puts the tag number in upper case

if(tag.substring(1) == "21 F8 7C 26")                     //checks user credentials
  {
    //Serial.println();
    //Serial.println("Your credentials are correct. Check for second step of authentication.");
    //Serial.println();
    String tag = "";
    for(byte i = 0; i < mfrc522.uid.size; i++)              //prints the UID of the tag to the serial monitor
      {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        tag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        tag.concat(String(mfrc522.uid.uidByte[i], HEX));
      }
    Serial.println();

    tag.toUpperCase();
    
        digitalWrite(yellowLED, HIGH);
        delay(1500);
        digitalWrite(yellowLED, LOW);
        //delay(4000)
      }
else if(tag.substring(1) == "D3 99 12 2E")
  {
    //Serial.println();
    //Serial.println("Your credentials are correct. Check for second step of authentication.");
    //Serial.println();
    String tag = "";
    for(byte i = 0; i < mfrc522.uid.size; i++)              //prints the UID of the tag to the serial monitor
      {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        tag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        tag.concat(String(mfrc522.uid.uidByte[i], HEX));
      }
    Serial.println();

    tag.toUpperCase();
    
        digitalWrite(yellowLED, HIGH);
        delay(1500);
        digitalWrite(yellowLED, LOW);
        //delay(4000)
      }
else  
  {                                                                      //denies access to any unauthorized user
    //Serial.println();
    //Serial.println("Your credentials are incorrect. Please try again.");
    digitalWrite(redLED, HIGH);
    delay(1500);
    digitalWrite(redLED, LOW);
    
  } 

mfrc522.PICC_HaltA();                                                 //halts the PICC session then stops the encryption session
mfrc522.PCD_StopCrypto1();                                            //stops communications to the PICC (the RFID tag)
}
