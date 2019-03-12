#define MAXIMUMNUMBEROFFIELDS 10
#define LINELENGTH 400

String myNameIs = "Aktec";
String myFWIs = "00.01.00";

byte macAddress_[6] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0}; //colocar alguma coisa que diga que estas variaveis sao globais
byte ipAddress_ [4] = {0, 0, 0, 0};
byte gatewayAddress_[4] = {0, 0, 0, 0};
byte dnsAddress_[4] = {0, 0, 0, 0};

EthernetServer server(80);

