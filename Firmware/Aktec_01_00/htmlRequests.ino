boolean htmlRequest_delaySetting(String receivedLine, String endChar)
{
}

/*boolean htmlRequest_adcPost(String receivedLine, String endChar)
{
  String strBuff = "";
  int numBuff;

  boolean adcReadValidation = true;
  int adcSensorAssigned_[MAXIMUMNUMBEROFADCS];

  for (int adc = 0; adc < MAXIMUMNUMBEROFADCS; adc++)
  {
    if (parse_parameterReader(receivedLine, "adc" + String(adc) + "=", strBuff, endChar)) //buff is always reset in the parse function
    {
      numBuff = strBuff.toInt();
      if (numBuff >= -1 && numBuff < sensorNumber)
      {
        adcSensorAssigned_[adc] = numBuff;
      }
      else
      {
        adcReadValidation = false;
        break;
      }
    }
    else
    {
      adcReadValidation = false;
      break;
    }
  }

  if (adcReadValidation)
  {
    card_removeFile(assignedSensorsFileName);
    for (int adc = 0; adc < MAXIMUMNUMBEROFADCS; adc++)
    {
      adcSensor_[adc] = adcSensorAssigned_[adc];
      String toWrite = "ADC" + String(adc) + ":";
      if (adcSensor_[adc] != -1)
      {
        toWrite = toWrite + sensorLocation_[adcSensor_[adc]] + serialEndChar + newLine;
      }
      else
      {
        toWrite = toWrite + "na" + serialEndChar + newLine;
      }
      card_writeFile(assignedSensorsFileName, toWrite);
    }
    return true;
  }
  else
  {
    return false;
  }
}
*/
boolean htmlRequest_plotGraph(String receivedLine, String endChar)
{
  String strBuff = "";
  int numBuff;

  if (parse_parameterReader(receivedLine, "graphic=", strBuff, endChar)) //buff is always reset in the parse function
  {
    numBuff = strBuff.toInt();
    if (numBuff >= 0 && numBuff <= MAXIMUMNUMBEROFDATAFILES)
    {
      dataFileReq = numBuff;
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

boolean htmlRequest_rawData(String receivedLine, String endChar)
{
  String strBuff = "";
  int numBuff;

  if (parse_parameterReader(receivedLine, "text=", strBuff, endChar)) //buff is always reset in the parse function
  {
    numBuff = strBuff.toInt();
    if (numBuff >= 0 && numBuff <= MAXIMUMNUMBEROFDATAFILES)
    {
      dataFileReq = numBuff;
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

boolean htmlRequest_defineAlarms(String receivedLine, String endChar)
{
}
