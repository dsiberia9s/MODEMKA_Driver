#include <MODEMKA_Driver.h>

#define DEBUG false

#define TX_PIN 16
#define RX_PIN 17
#define BAUDRATE 115200
#define RESET_PIN -1 // -1 if not using

#define PHONE_NUMBER "+"
#define MESSAGE "Thank you for using MODEMKA_Driver!"

bool status;

MODEMKA_Driver COM_GSM(Serial2, TX_PIN, RX_PIN, BAUDRATE, RESET_PIN);

void error_handler(int code) {
  Serial.println("[x] Error code: " + String(code));
}

void sms_handler(String phone, String message, tm time) {
  Serial.println("[M] " + String(time.tm_hour) + ":" + String(time.tm_min) + ":" + String(time.tm_sec) + " " + phone + " => " + message);
}

void setup() {
  Serial.begin(BAUDRATE);

  COM_GSM.error_handler = error_handler;
  COM_GSM.sms_handler = sms_handler;
  
  COM_GSM.unicode(false);

  Serial.println("[I] Warming-up SIM module. Pls wait ~1 min.");
  
  status = COM_GSM.begin(DEBUG);
  
  if (status == false) {
    Serial.println("[x] Module is NOT ready.");
    while(true);
  }

  Serial.println("[v] Module is ready.");
  Serial.println("IMEI: " + COM_GSM.IMEI());

  COM_GSM.SMS(PHONE_NUMBER, MESSAGE);
}

void loop() {
  COM_GSM.live();
  delay(10);
}
