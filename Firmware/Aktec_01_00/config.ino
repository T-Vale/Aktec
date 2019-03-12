boolean config_networkParameters(String nconfigFileName)  // !!!!!!! reads network parameters from the card and applies them
{
  String nconfigFileContent = "";
  String buff = "";

  byte numberOfFields;
  String arrayOfValues[MAXIMUMNUMBEROFFIELDS];

  boolean macRead = false;
  boolean ipRead = false;
  boolean gatewayRead = false;
  boolean dnsRead = false;

  if (card_readFile(nconfigFileName, nconfigFileContent, MAXIMUMNUMBEROFCHARACTERS))
  {
    if (parse_parameterReader(nconfigFileContent, "mac=", buff, serialEndChar)) //buff is always reset in the parse function
    {
      numberOfFields = parse_dataBreaker(buff, arrayOfValues, ':', MAXIMUMNUMBEROFFIELDS);
      convert_addresses(arrayOfValues, macAddress_, numberOfFields, 6, 1);
      macRead = true;
    }
    if (parse_parameterReader(nconfigFileContent, "ip=", buff, serialEndChar))
    {
      numberOfFields = parse_dataBreaker(buff, arrayOfValues, '.', MAXIMUMNUMBEROFFIELDS);
      convert_addresses(arrayOfValues, ipAddress_, numberOfFields, 4, 0);
      ipRead = true;
    }
    if (parse_parameterReader(nconfigFileContent, "dns=", buff, serialEndChar))
    {
      numberOfFields = parse_dataBreaker(buff, arrayOfValues, '.', MAXIMUMNUMBEROFFIELDS);
      convert_addresses(arrayOfValues, dnsAddress_, numberOfFields, 4, 0);
      dnsRead = true;
    }
    if (parse_parameterReader(nconfigFileContent, "gateway=", buff, serialEndChar))
    {
      numberOfFields = parse_dataBreaker(buff, arrayOfValues, '.', MAXIMUMNUMBEROFFIELDS);
      convert_addresses(arrayOfValues, gatewayAddress_, numberOfFields, 4, 0);
      gatewayRead = true;
    }
  }
  return macRead && ipRead && gatewayRead && dnsRead;
}

boolean config_dataNumberParameters(String nconfigFileName)  // !!!!!!! reads number of files values from the card and applies them
{
  String nconfigFileContent = "";
  String buff = "";

  boolean wdelayRead = false;
  int wdelayNum = 0;

  if (card_readFile(nconfigFileName, nconfigFileContent, MAXIMUMNUMBEROFCHARACTERS))
  {
    if (parse_parameterReader(nconfigFileContent, "datafilesnumber=", buff, serialEndChar)) //buff is always reset in the parse function
    {
      wdelayNum = buff.toInt();
      wdelayRead = true;
    }
    else
    {
      wdelayNum = 0;
    }
  }
  else
  {
    wdelayNum = 0;
  }
  dataFilesNumber = wdelayNum;
  return wdelayRead;
}
