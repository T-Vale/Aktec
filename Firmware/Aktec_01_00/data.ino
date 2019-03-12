boolean data_write()
{
  //read_value();
  int reading = analogRead(dataPin);

  String dataToWrite = String((round(millis() - startingMillis)/1000)) + "\t" + String(reading) + newLine;

  String fileLocation = String(dataFilesNumber);

  char charFileLocation[fileLocation.length() + 1]; //it only accepts character arrays
  fileLocation.toCharArray(charFileLocation, sizeof(charFileLocation));

  if (SD.exists(charFileLocation))
  {
      return false;
  }
  fileLocation = fileLocation + ".TXT";

  if (!card_writeFile(fileLocation, dataToWrite))
  {
    return false;
  }
  return true;
}



