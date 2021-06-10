#include <MODEMKA_Driver.h>

#define DEBUG false 

#define TX_PIN 16
#define RX_PIN 17
#define BAUDRATE 115200
#define RESET_PIN -1 // -1 if not using

#define MOBILE_DATA_APN ""
#define MOBILE_DATA_USERNAME ""
#define MOBILE_DATA_PASSWORD ""

#define SSL false
#define HOST_PORT 80
#define HOST_URL "example.com"
//#define HOST_IP 0, 0, 0, 0

bool status;

MODEMKA_Driver COM_GSM(Serial2, TX_PIN, RX_PIN, BAUDRATE, RESET_PIN);

void error_handler(int code) {
  Serial.println("[x] Error code: " + String(code));
}

void data_handler(int length) {
  Serial.println("[W] Got: " + String(length) + " bytes.");

  char* buffer = (char*)malloc(length * sizeof(char));
  status =  COM_GSM.read(buffer, length);

  if (status == false) {
    Serial.println("[x] Can't read data.");
    while(true);
  }

  for (int i = 0; i < length; i++) {
    Serial.print(buffer[i]);
  }

  free(buffer);

  status = COM_GSM.close();

  if (status == false) {
    Serial.println("[x] Can't close connection.");
    while(true);
  }

  Serial.println("[v] Connection was closed.");
}

void setup() {
  Serial.begin(BAUDRATE);

  COM_GSM.error_handler = error_handler;
  COM_GSM.network(MOBILE_DATA_APN, MOBILE_DATA_USERNAME, MOBILE_DATA_PASSWORD);

  Serial.println("[I] Warming-up SIM module. Pls wait ~1 min.");
  
  status = COM_GSM.begin(DEBUG);
  
  if (status == false) {
    Serial.println("[x] Module is NOT ready.");
    while(true);
  }

  COM_GSM.data_handler = data_handler;
  
  Serial.println("[v] Module is ready.");
  Serial.println("IMEI: " + COM_GSM.IMEI());

  status = COM_GSM.connect(HOST_URL, HOST_PORT, TCP_PROTOCOL, SSL);
  // bool connected = COM_GSM.connect(IPAddress(HOST_IP), HOST_PORT, UDP_PROTOCOL, false);

  if (status == false) {
    Serial.println("[x] Can't connect to host.");
    while(true);
  }

  char* payload = "GET / HTTP/1.0\r\nHost: example.com\r\n\r\n";
  int length = 38;
  
  status = COM_GSM.write(payload, length);

  if (status == false) {
    Serial.println("[x] Can't write payload to host.");
    while(true);
  }
}

void loop() {
  COM_GSM.live();
  delay(10);
}
