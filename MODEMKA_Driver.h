#ifndef _MODEMKA_Driver_H_
  #define _MODEMKA_Driver_H_

  #include <Arduino.h>
  #include <time.h>

  #define TCP_PROTOCOL 0
  #define UDP_PROTOCOL 1

  typedef void (*pInt)(int);
  typedef void (*pStr)(String);
  typedef void (*pStrStrTm)(String, String, tm);

  class MODEMKA_Driver
  {
    private:
      static const int _EXCEPTIONS_SIZE_;
      static const uint16_t _UNICODE_KEYS_[];
      static const String _EXCEPTIONS_[];
      static const String _UNICODE_VALUES_[];

      bool _DEBUG_ = false;
      bool _PAUSE_ = false;
      bool _UNICODE_ = false;
      bool _INIT_ = false;
      bool _READY_ = false;
      int _GPRS_ = 0;
      int _WARM_UP_TIME_SEC_ = 40;
      int _RX_PIN_;
      int _TX_PIN_;
      int _BAUDRATE_;
      int _RESET_PIN_;
      int _LENGTH_ = 0;
      int _POINTER_ = 0;
      char* _PAYLOAD_ = NULL;
      String _PIN_ = "0000";
      String _APN_ = "";
      String _USER_ = "";
      String _PASSWORD_ = "";
      String _LEAK_BUFFER_ = "";
      HardwareSerial _UART_ = NULL;
      IPAddress _LOCAL_IP_;

      void flush();
      void cap(int);
      void leak_buffer(String);
      bool only_digits(String);
      bool ip_is_set(IPAddress);
      int read_n_char(char*, int, int);
      int char_in_str(char, String);
      String remove_char(char, String);
      String read_line();
      String read_to_char(char);
      String pop_line(String&);
      String decode(String);
      IPAddress str_to_ip(String);
      tm parse_time(String);

    public:
      pInt error_handler = NULL;
      pStr call_handler = NULL;
      pStrStrTm sms_handler = NULL;
      pInt data_handler = NULL;

      MODEMKA_Driver(HardwareSerial&, int, int, int, int);
      ~MODEMKA_Driver();

      bool PIN();
      bool PIN(String);
      bool accept();
      bool call(String);
      bool close();
      bool decline();
      void live();
      void unicode(bool);
      void network(String, String, String);
      bool begin(bool debug = false);
      bool read(char*, int);
      bool write(char*, int);
      bool DTMF(String);
      bool SMS(String, String);
      int available();
      bool connect(IPAddress, int, int, bool);
      bool connect(String, int, int, bool);
      String IMEI();
      String USSD(String);
      String GET(String);
      String ip_to_str(IPAddress);
      String str_parse(int, char, String);
      String AT(String command, String response = "OK", int timeout = 10000);
      //IPAddress localIP();
  };

#endif
