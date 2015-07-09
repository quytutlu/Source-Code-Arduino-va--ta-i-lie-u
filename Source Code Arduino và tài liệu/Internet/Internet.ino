#include <SPI.h>
#include <Ethernet.h>
#include <JsonParser.h>
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
boolean received = false;
EthernetClient client;
String str;
String url;
String TenThietBi;
bool flag = false;
float NhietDo;
IPAddress server(192, 99, 66, 193);
unsigned long lastConnectionTime = 0;
boolean lastConnected = false;
String TrangThai;
JsonParser<32> parser;
JsonHashTable hashTable;
const unsigned long postingInterval = 500;  // delay between updates, in milliseconds

void setup() {
  randomSeed(analogRead(0));
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(5,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(6,HIGH);
  Serial.begin(9600);
  Ethernet.begin(mac);
}

void loop() {
  str = "";
  flag = false;
  while (client.available()) {
    char c = client.read();
    if (c == '{')
    {
      flag = true;
    }
    if (flag)
    {
      str += c;
    }
    received = true;
  }
  char *json = new char[str.length() + 1];
  strcpy(json, str.c_str());
  PhanTichJson(json);
  delete[]json;
  if (received)
  {
    client.stop();
    received = false;
  }

  if (!client.connected() && lastConnected) {
    //Serial.println();
    //Serial.println("disconnecting.");
    client.stop();
  }

  if (!client.connected() && (millis() - lastConnectionTime > postingInterval)) {
    httpRequest();
  }
  lastConnected = client.connected();
  delay(500);
}
JsonArray list;
JsonHashTable ThietBi;
void PhanTichJson(char *json)
{
  hashTable = parser.parseHashTable(json);
  if (!hashTable.success())
  {
    //Serial.println("fail");
    return;
  }
  list = hashTable.getArray("list");
  for (int i = 0; i < list.getLength(); i++)
  {
    ThietBi = list.getHashTable(i);
    TenThietBi = ThietBi.getString("TenThietBi");
    TrangThai = ThietBi.getString("TrangThai");
    Serial.println(TrangThai);
    if (TrangThai == "dcp0")
    {
      Serial.println("Den Compac tat");
      digitalWrite(7, LOW);
      continue;
    }
    if (TrangThai == "dcp1")
    {
      Serial.println("Den Compac bat");
      digitalWrite(7, HIGH);
      continue;
    }
    if (TrangThai == "dtd0")
    {
      Serial.println("Den tuyp tat");
      digitalWrite(6, HIGH);
      continue;
    }
    if (TrangThai == "dtd1")
    {
      Serial.println("Den tuyp bat");
      digitalWrite(6, LOW);
      continue;
    }
    if (TrangThai == "qd10")
    {
      Serial.println("Den quat dien 1 tat");
      digitalWrite(5, HIGH);
      continue;
    }
    if (TrangThai == "qd11")
    {
      Serial.println("Den quat dien 1 bat");
      digitalWrite(5, LOW);
      continue;
    }
    if (TrangThai == "qd20")
    {
      Serial.println("Den quat dien 2 tat");
      digitalWrite(4, HIGH);
      continue;
    }
    if (TrangThai == "qd21")
    {
      Serial.println("Den quat dien 2 bat");
      digitalWrite(4, LOW);
      continue;
    }
    if (TrangThai == "tv0")
    {
      Serial.println("Den tivi tat");
      digitalWrite(3, LOW);
      continue;
    }
    if (TrangThai == "tv1")
    {
      Serial.println("Den tivi bat");
      digitalWrite(3, HIGH);
      continue;
    }
  }
}
void httpRequest() {
  if (client.connect(server, 1234)) {
    Serial.println("connecting...");
    NhietDo = analogRead(1);
    NhietDo = (NhietDo * 5.0 * 1000 / 1024) / 10.0;
    url = "GET /kltn_arduino/?cmd=laytrangthaiarduino&id=5&nhietdo=";
    url += NhietDo;
    url += " HTTP/1.1";
    client.println(url);
    client.println("Host: 192.99.66.193:1234");
    client.println("Connection: keep-open");
    client.println("Connection: close");
    client.println();
    lastConnectionTime = millis();
  }
  else {
    Serial.println("connection failed");
    //Serial.println("disconnecting.");
    client.stop();
  }
}




