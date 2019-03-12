boolean card_readFile(String fileName, String &fileContent, byte maxStringSize) //reads a specified file and fills the passed string until it reachs the maxStringSize or its end
{
  fileContent = "";
  File openedFile = SD.open(fileName, FILE_READ);
  if (!openedFile)
  {
    openedFile.close();
    return false;
  }
  byte cNumber = 0;
  while (openedFile.available() && cNumber < maxStringSize) //limits the size, protecting the memory used
  {
    char c = openedFile.read();
    fileContent = fileContent + c;
    cNumber++;
  }
  openedFile.flush();
  openedFile.close();
  return true;
}

boolean card_writeFile(String fileName, String dataContent)
{
  Serial.println(fileName);
  Serial.println(dataContent);
  File dataFile = SD.open(fileName, FILE_WRITE);
  if (dataFile)
  {
    dataFile.print(dataContent);
    dataFile.close();
    return true;
  }
  else
  {
    dataFile.close();
    return false;
  }
}

boolean card_removeFile(String location)
{
  char charlocation[location.length() + 1]; //it only accepts character arrays
  location.toCharArray(charlocation, sizeof(charlocation));
  if (SD.remove(charlocation))
  {
    return true;
  }
  else
  {
    return false;
  }
}



