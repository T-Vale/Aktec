#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <Ethernet.h>

#include "ChronoSettings.h"
#include "SensorSettings.h"
#include "NetworkSettings.h"
#include "FileSettings.h"

const int chipSelect = 4;

void setup()
{
  pinMode(47,OUTPUT);
  digitalWrite(47,LOW);
  delay(500);
  digitalWrite(47,HIGH);
  Serial.begin(9600);
  Serial.println("Setup Start");
  Serial.println();
  pinMode(dataPin, INPUT);
  pinMode(recordingPin, INPUT);
  pinMode(recordingButton, INPUT_PULLUP); //ALTERADO
  pinMode(beepPin, OUTPUT);
  //ALTERADO
  digitalWrite(beepPin, LOW);
  beepbeep(1, 1000);
  Serial.println("Initializing SD card...");
  if (!SD.begin(chipSelect))
  {
    return;
  }

  Serial.println("Reading parameters from SD card...");
  config_networkParameters(networkConfigFileName); //passes the file name !!!!!!!
  config_dataNumberParameters(dataNumberFileName);
  Serial.println("Parameters read");
  
  delay(1000);
  Ethernet.begin(macAddress_, ipAddress_);
  server.begin();
  debug_setupprinter();
  Serial.println("Setup End");
  Serial.println();
}

void loop()
{
  Serial.print("Recording Pin: ");
  Serial.println(analogRead(recordingPin));

  html_interface();
  if(recordingButtonStatus())
  {
    if(recordingPinStatus())
    {
      Serial.println("Record order received");
      Serial.println(dataFilesNumber);
      if(!recordData())
      {
        Serial.print(String(MAXIMUMNUMBEROFDATAFILES));
        Serial.println(" files limit reached");
        beepbeep(10, 200);
      }
      else
      {
        Serial.println("Finish record");
        beepbeep(3, 150);
      }
    }
  }
}

boolean recordData()
{
  if(dataFilesNumber < MAXIMUMNUMBEROFDATAFILES)
  {
    beepbeep(2, 150);
    startingMillis = millis();
    data_write();
    delay(1000);
    while(recordingPinStatus() && recordingButtonStatus())
    {
      data_write();
      delay(1000);
    }
    dataFilesNumber++;
    card_removeFile(dataNumberFileName);
    String toWrite = "datafilesnumber=" + String(dataFilesNumber) + ";";
    card_writeFile(dataNumberFileName, toWrite);
    return true;
  }
  else
  {
   return false; 
  }
}

boolean recordingPinStatus() //ALTERADO
{
  if(analogRead(recordingPin) > 800) // > 3V, a maquina esta a gravar
  {
    return true;
  }
  else
  {
    return false;
  }
}

boolean recordingButtonStatus() //ALTERADO
{
  if(digitalRead(recordingButton)) //ALTERADO
  {
    return true;
  }
  else
  {
    return false;
  }
}

void beepbeep(int cycles, int delayt)
{
  for(int f = 0; f < cycles; f++)
  {
    delay(delayt);
    digitalWrite(beepPin, HIGH);
    delay(delayt);
    digitalWrite(beepPin, LOW);
  }
}

