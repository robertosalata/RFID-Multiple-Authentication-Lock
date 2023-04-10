#include <SPI.h>
#include <MFRC522.h>
#include <SD.h> // Add SD library

#define SDApin 10
#define RSTpin 9
#define redLED 5
#define yellowLED 6
#define SSpin 4 // Add SS pin for SD card

MFRC522 mfrc522(SDApin, RSTpin);
File userTagsFile; // Add File variable for the text file

void setup()
{
  SPI.begin();
  Serial.begin(9600);
  mfrc522.PCD_Init();

  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  pinMode(SSpin, OUTPUT); // Set SS pin as OUTPUT
  SD.begin(SSpin);        // Initialize SD card
}

bool isTagAccepted(String tag)
{
  userTagsFile = SD.open("user_ids.txt"); // Open the text file

  if (userTagsFile)
  {
    while (userTagsFile.available())
    {
      String line = userTagsFile.readStringUntil('\n');
      int separatorIndex = line.indexOf(',');
      String tagId = line.substring(0, separatorIndex);

      if (tagId.equals(tag))
      {
        userTagsFile.close();
        return true;
      }
    }

    userTagsFile.close();
  }

  return false;
}

void loop()
{
  // Other code

  if (isTagAccepted(tag.substring(1)))
  {
    // Code for the accepted tag
  }
  else
  {
    // Code for the rejected tag
  }

  // Other code
}

