void debug_setupprinter()
{
  Serial.print("MAC: ");
  Serial.print(macAddress_[0]);
  Serial.print(":");
  Serial.print(macAddress_[1]);
  Serial.print(":");
  Serial.print(macAddress_[2]);
  Serial.print(":");
  Serial.print(macAddress_[3]);
  Serial.print(":");
  Serial.print(macAddress_[4]);
  Serial.print(":");
  Serial.println(macAddress_[5]);
  Serial.print("IP: ");
  Serial.print(ipAddress_[0]);
  Serial.print(".");
  Serial.print(ipAddress_[1]);
  Serial.print(".");
  Serial.print(ipAddress_[2]);
  Serial.print(".");
  Serial.println(ipAddress_[3]);
  Serial.print("DNS: ");
  Serial.print(dnsAddress_[0]);
  Serial.print(".");
  Serial.print(dnsAddress_[1]);
  Serial.print(".");
  Serial.print(dnsAddress_[2]);
  Serial.print(".");
  Serial.println(dnsAddress_[3]);
  Serial.print("Gateway: ");
  Serial.print(gatewayAddress_[0]);
  Serial.print(".");
  Serial.print(gatewayAddress_[1]);
  Serial.print(".");
  Serial.print(gatewayAddress_[2]);
  Serial.print(".");
  Serial.println(gatewayAddress_[3]);
  Serial.println();
  Serial.print("Number of Files: ");
  Serial.println(dataFilesNumber);
  Serial.println();

}
