#include "MODEMKA_Driver.h"

const uint16_t MODEMKA_Driver::_UNICODE_KEYS_[] = {
  0x0410, 0x0411, 0x0412, 0x0413, 0x0414, 0x0415, 0x0401, 0x0416, 0x0417,
  0x0418, 0x0419, 0x041A, 0x041B, 0x041C, 0x041D, 0x041E, 0x041F, 0x0420,
  0x0421, 0x0422, 0x0423, 0x0424, 0x0425, 0x0426, 0x0427, 0x0428, 0x0429,
  0x042A, 0x042B, 0x042C, 0x042D, 0x042E, 0x042F, 0x0430, 0x0431, 0x0432,
  0x0433, 0x0434, 0x0435, 0x0451, 0x0436, 0x0437, 0x0438, 0x0439, 0x043A,
  0x043B, 0x043C, 0x043D, 0x043E, 0x043F, 0x0440, 0x0441, 0x0442, 0x0443,
  0x0444, 0x0445, 0x0446, 0x0447, 0x0448, 0x0449, 0x044A, 0x044B, 0x044C,
  0x044D, 0x044E, 0x044F, 0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025,
  0x0026, 0x0027, 0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x002E,
  0x002F, 0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037,
  0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F, 0x0040,
  0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048, 0x0049,
  0x004A, 0x004B, 0x004C, 0x004D, 0x004E, 0x004F, 0x0050, 0x0051, 0x0052,
  0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005A, 0x005B,
  0x005C, 0x005D, 0x005E, 0x005F, 0x0060, 0x0061, 0x0062, 0x0063, 0x0064,
  0x0065, 0x0066, 0x0067, 0x0068, 0x0069, 0x006A, 0x006B, 0x006C, 0x006D,
  0x006E, 0x006F, 0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076,
  0x0077, 0x0078, 0x0079, 0x007A, 0x007B, 0x007C, 0x007D, 0x007E, 0x00AB,
  0x00BB, 0x00A9, 0x00AE, 0x00BA, 0x00D7, 0x00F7, 0x00B1
};

const String MODEMKA_Driver::_UNICODE_VALUES_[] = {
  "А", "Б", "В", "Г", "Д", "Е", "Ё", "Ж", "З",
  "И", "Й", "К", "Л", "М", "Н", "О", "П", "Р",
  "С", "Т", "У", "Ф", "Х", "Ц", "Ч", "Ш", "Щ",
  "Ъ", "Ы", "Ь", "Э", "Ю", "Я", "а", "б", "в",
  "г", "д", "е", "ё", "ж", "з", "и", "й", "к",
  "л", "м", "н", "о", "п", "р", "с", "т", "у",
  "ф", "х", "ц", "ч", "ш", "щ", "ъ", "ы", "ь",
  "э", "ю", "я", " ", "!", "\"", "#", "$", "%",
  "&", "\'", "(", ")", "*", "+", ",", "-", ".",
  "\/", "0", "1", "2", "3", "4", "5", "6", "7",
  "8", "9", ":", "", "<", "=", ">", "?", "@",
  "A", "B", "C", "D", "E", "F", "G", "H", "I",
  "J", "K", "L", "M", "N", "O", "P", "Q", "R",
  "S", "T", "U", "V", "W", "X", "Y", "Z", "[",
  "\\", "]", "^", "_", "`", "a", "b", "c", "d",
  "e", "f", "g", "h", "i", "j", "k", "l", "m",
  "n", "o", "p", "q", "r", "s", "t", "u", "v",
  "w", "x", "y", "z", "{", "|", "}", "~", "«",
  "»", "©", "®", "º", "×", "÷", "±"
};

const int MODEMKA_Driver::_EXCEPTIONS_SIZE_ = 9;

const String MODEMKA_Driver::_EXCEPTIONS_[] = {
  "AT", "OK", "Call Ready", "SMS Ready", "STATE: IP PROCESSING", "ERROR",
  "NO CARRIER", "CLOSED", "NORMAL POWER DOWN"
};

MODEMKA_Driver::MODEMKA_Driver(HardwareSerial& port, int rx_pin, int tx_pin,
  int baudrate, int reset_pin) {

  if (_INIT_ == true)
  {
    return;
  }

  if (port == NULL)
  {
    return;
  }

  _RX_PIN_ = rx_pin;
  _TX_PIN_ = tx_pin;
  _BAUDRATE_ = baudrate;

  _RESET_PIN_ = reset_pin;

  _UART_ = port;
  _UART_.begin(_BAUDRATE_, SERIAL_8N1, _RX_PIN_, _TX_PIN_);
  delay(100);
  flush();

  if (_RESET_PIN_ > -1)
  {
    pinMode(_RESET_PIN_, OUTPUT);
  }

  _INIT_ = true;
}

MODEMKA_Driver::~MODEMKA_Driver() {

  if (_INIT_ == false)
  {
    return;
  }

  _UART_ = NULL;
  _INIT_ = false;
}

bool MODEMKA_Driver::begin(bool debug) {

  if (_INIT_ == false)
  {
    (*error_handler)(40);
    return false;
  }

  if (_READY_ == true)
  {
    (*error_handler)(41);
    return false;
  }

  _DEBUG_ = debug;

  if (1)
  {
    if (_RESET_PIN_ > -1)
    {
      digitalWrite(_RESET_PIN_, HIGH);
      delay(500);
      digitalWrite(_RESET_PIN_, LOW);
      delay(500);
      digitalWrite(_RESET_PIN_, HIGH);
    }
    else
    {
      AT("AT+CPOWD=1\r", "NORMAL POWER DOWN");
    }

    for (int i = 1; i <= _WARM_UP_TIME_SEC_; i++)
    {
      delay(1000);

      if (_DEBUG_)
      {
        Serial.println("begin: warming-up " + String(i) + " / " +
        String(_WARM_UP_TIME_SEC_) + " s.");
      }
    }
  }

  flush();

  if (AT("AT\r") == "")
  {
    (*error_handler)(1);
    return false;
  }

  if (AT("ATE0\r") == "")
  {
    (*error_handler)(2);
    return false;
  }
  if (PIN() == true)
  {
    if (AT("AT+CPIN=" + _PIN_ + "\r") == "")
    {
      (*error_handler)(11);
      return false;
    }
  }

  if (AT("AT+CPAS\r", "+CPAS: 0") == "")
  {
    (*error_handler)(3);
    return false;
  }

  if (AT("AT+CMGD=1,4\r") == "")
  {
    (*error_handler)(4);
    return false;
  }

  if (AT("AT+CSCB=1\r") == "")
  {
    (*error_handler)(5);
    return false;
  }

  if (AT("AT+CLIP=1\r") == "")
  {
    (*error_handler)(6);
    return false;
  }

  if (AT("AT+CMGF=1\r") == "")
  {
    (*error_handler)(7);
    return false;
  }

  if (AT("AT+CSCS=\"GSM\"\r") == "")
  {
    (*error_handler)(8);
    return false;
  }

  if (AT("AT+CNMI=2,2\r") == "")
  {
    (*error_handler)(9);
    return false;
  }

  if (AT("AT+CREG?\r", "+CREG: 0,1") == "")
  {
    (*error_handler)(10);
    return false;
  }

  if (_DEBUG_)
  {
    Serial.println("begin: device is ready.");
  }

  _READY_ = true;

  return true;
}

String MODEMKA_Driver::AT(String command, String response, int timeout) {

  _PAUSE_ = true;

  if (_DEBUG_)
  {
    Serial.println("AT: " + command + ", " + response);
  }

  bool exit = false;
  bool recording = false;
  int flag = 0;
  unsigned long last_time;
  String output = "";
  String line = "";

  String option = str_parse(0, char(0x1F), response);

  if ( option == "___ONLY_DIGITS___" )
  {
    flag = 1;
  }
  else if ( option == "___ALL___" )
  {
    response = str_parse(1, char(0x1F), response);
    flag = 2;
  }

  for (int i = 0; i < 6; i++)
  {
    _UART_.print(command);
    last_time = millis();

    while (true)
    {
      line = read_line();

      if (line != "")
      {
        last_time = millis();

        if (flag == 0)
        {
          if ( strstr(line.c_str(), response.c_str()) != NULL )
          {
            output = line;
            exit = true;
            break;
          }
          else
          {
            leak_buffer(line + '\n');
          }
        }
        else if (flag == 1)
        {
          if (only_digits(line) == true)
          {
            output = line;
            exit = true;
            break;
          }
          else
          {
            leak_buffer(line + '\n');
          }
        }
        else if (flag == 2)
        {
          if (recording == false)
          {
            if ( strstr(line.c_str(), response.c_str()) != NULL )
            {
              recording = true;
            }
          }

          if (recording == true)
          {
            output += line + '\n';
          }
          else
          {
            leak_buffer(line + '\n');
          }
        }
      }

      if (millis() - last_time >= timeout)
      {
        if (flag != 2)
        {
          output = "";
        }
        else
        {
          exit = true;
        }

        break;
      }
    }

    if (exit == true)
    {
      break;
    }

    flush();
  }

  flush();

  _PAUSE_ = false;

  return output;
}

void MODEMKA_Driver::live() {

  if (_READY_ == false)
  {
    (*error_handler)(42);
    return;
  }

  if (_PAUSE_ == true)
  {
    return;
  }

  bool leaked = false;
  String line = read_line();

  if (line == "")
  {
    line = pop_line(_LEAK_BUFFER_);

    if (line != "")
    {
      leaked = true;

      if (_DEBUG_)
      {
        if (_LEAK_BUFFER_.length() > 0)
        {
          Serial.println("LEAK_BUFFER >>> " + _LEAK_BUFFER_ + "<<< END OF LEAK_BUFFER");
        }
      }
    }
  }

  if (line == "")
  {
    return;
  }

  // CALL
  if (strstr(line.c_str(), "+CLIP: "))
  {
    String phone = str_parse(1, '\"', line);

    if (call_handler != NULL)
    {
      (*call_handler)(phone);
    }
  }

  // SMS
  else if (strstr(line.c_str(), "+CMT: "))
  {
    String phone = str_parse(1, '\"', line);
    String time = str_parse(5, '\"', line);
    String message;

    if (leaked == false)
    {
      message = read_line();
    }
    else
    {
      message = pop_line(_LEAK_BUFFER_);
    }

    if (sms_handler != NULL)
    {
      (*sms_handler)( phone, decode(message), parse_time(time) );
    }
  }

  // DATA SINGLE MODE
  else if ( strstr(line.c_str(), "+CIPRXGET: 1") )
  {
    String ciprxget = AT("AT+CIPRXGET=4\r", "+CIPRXGET: ");
    int length;

    if (ciprxget == "")
    {
      (*error_handler)(45);
    }
    else
    {
      length = str_parse(1, ',', ciprxget).toInt();

      if (_PAYLOAD_ == NULL)
      {
        _PAYLOAD_ = (char*)malloc(length * sizeof(char));
      }
      else
      {
        char* payload = (char*)realloc(_PAYLOAD_, (length + _LENGTH_) * sizeof(char));

        if (payload == NULL)
        {
          free(payload);
        }
        else
        {
          _PAYLOAD_ = payload;
        }
      }

      if (_PAYLOAD_ == NULL)
      {
        (*error_handler)(47);
      }
      else
      {
        ciprxget = AT("AT+CIPRXGET=2," + String(length) + "\r", "+CIPRXGET: ");

        if (ciprxget == "")
        {
          free(_PAYLOAD_);
          (*error_handler)(46);
        }
        else
        {
          if (read_n_char(_PAYLOAD_, length, _LENGTH_) != length)
          {
            (*error_handler)(58);
          }
          else
          {
            _LENGTH_ += length;

            if (_DEBUG_)
            {
              for (int i = 0; i < _LENGTH_; i++)
              {
                Serial.print((char)_PAYLOAD_[i]);
              }
            }

            if (data_handler != NULL)
            {
              (*data_handler)(_LENGTH_);
            }
          }
        }
      }
    }
  }
}

bool MODEMKA_Driver::call(String number) {

  if (AT("ATD" + number + ";\r") == "")
  {
    (*error_handler)(68);
    return false;
  }

  return true;
}

bool MODEMKA_Driver::decline() {

  if (AT("ATH0\r") == "")
  {
    (*error_handler)(37);
    return false;
  }

  return true;
}

bool MODEMKA_Driver::accept() {

  if (AT("ATA\r") == "")
  {
    (*error_handler)(38);
    return false;
  }

  return true;
}

String MODEMKA_Driver::read_line() {

  _PAUSE_ = true;

  bool exit = false;
  char symbol;
  unsigned long last_time = millis();
  String line = "";

  while (true)
  {
    if (millis() - last_time > 100)
    {
      break;
    }

    if (exit == true)
    {
      break;
    }

    for (int i = 0; i < _UART_.available(); i++)
    {
      symbol = _UART_.read();

      if (symbol != '\r')
      {
        if (symbol == '\n')
        {
            if (line.length() != 0)
            {
              exit = true;
              break;
            }
        }
        else
        {
          line += symbol;
        }
      }

      last_time = millis();
    }
  }

  if (_DEBUG_)
  {
    if (line != "")
    {
      Serial.println("read_line: " + line);
    }
  }

  _PAUSE_ = false;

  return line;
}

int MODEMKA_Driver::read_n_char(char* payload, int length, int offset) {

  _PAUSE_ = true;

  bool exit = false;
  int count = 0;
  unsigned long last_time = millis();

  while (true)
  {
    if (exit == true)
    {
      break;
    }

    if (millis() - last_time > 100)
    {
      break;
    }

    for ( ; _UART_.available(); count++)
    {
      if (count < length)
      {
        payload[count + offset] = (char)_UART_.read();
      }
      else
      {
        exit = true;
        break;
      }

      last_time = millis();
    }
  }

  _PAUSE_ = false;

  return count;
}

String MODEMKA_Driver::read_to_char(char flag) {

  _PAUSE_ = true;

  String line = "";
  bool exit = false;
  char symbol;
  unsigned long last_time = millis();
  int length = 0;

  while (true)
  {
    if (exit == true)
    {
      break;
    }

    if (millis() - last_time > 100)
    {
      break;
    }

    for (int i = 0; i < _UART_.available(); i++)
    {
      symbol = (char)_UART_.read();

      if (symbol == flag)
      {
        exit = true;
        break;
      }

      line += symbol;

      last_time = millis();
    }
  }

  _PAUSE_ = false;

  return line;
}

void MODEMKA_Driver::flush() {

  _UART_.flush();

  while (_UART_.available())
  {
    _UART_.read();
  }
}

void MODEMKA_Driver::unicode(bool mode) {
  _UNICODE_ = mode;
}

String MODEMKA_Driver::decode(String a) {

  // it's will work incorrectly for now. sorry.

  if (_UNICODE_ == false)
  {
    return a;
  }

  int l = a.length();

  int unicode_dictionary_size = sizeof(_UNICODE_KEYS_) /
  sizeof(const uint16_t);

  String c = "";

  for (int i = 0; i < l; i += 4)
  {
    String b = "0x";

    b += a[i];
    b += a[i + 1];
    b += a[i + 2];
    b += a[i + 3];

    for (int j = 0; j < unicode_dictionary_size; j++)
    {
      if (strtol(b.c_str(), NULL, 16) == _UNICODE_KEYS_[j])
      {
        c += _UNICODE_VALUES_[j];
        break;
      }
    }
  }

  return c;
}

String MODEMKA_Driver::IMEI() {

  String output = AT("AT+CGSN\r", "___ONLY_DIGITS___" + String(char(0x1F)));

  if (output == "")
  {
    (*error_handler)(43);
  }

  return output;
}

bool MODEMKA_Driver::PIN() {

  if ( AT("AT+CPIN?\r", "+CPIN: READY") != "" )
  {
    return false;
  }

  return true;
}

bool MODEMKA_Driver::PIN(String pin) {

  if ( (pin.length() != 4) || (only_digits(pin) == false) )
  {
    return true;
  }

  return false;
}

bool MODEMKA_Driver::ip_is_set(IPAddress ip) {

  return ip[0] && ip[1] && ip[2] && ip[3];
}

IPAddress MODEMKA_Driver::str_to_ip(String str) {

  return IPAddress( str_parse(0, '.', str).toInt(),
  str_parse(1, '.', str).toInt(), str_parse(2, '.', str).toInt(),
  str_parse(3, '.', str).toInt() );
}

String MODEMKA_Driver::ip_to_str(IPAddress ip) {

  return String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." +
  String(ip[3]);
}

tm MODEMKA_Driver::parse_time(String s) {

  tm out;

  // Example: 21/05/17,20:39:32+12

  String main = str_parse(0, '+', s);

  String date = str_parse(0, ',', main);
  String time = str_parse(1, ',', main);

  out.tm_year = str_parse(0, '/', date).toInt() + 2000;
  out.tm_mon = str_parse(1, '/', date).toInt();
  out.tm_mday = str_parse(3, '/', date).toInt();

  out.tm_hour = str_parse(0, ':', time).toInt();
  out.tm_min = str_parse(1, ':', time).toInt();
  out.tm_sec = str_parse(2, ':', time).toInt();

  return out;
}

bool MODEMKA_Driver::SMS(String phone, String message) {

  if (AT("AT+CMGS=?\r") == "")
  {
    (*error_handler)(30);
    return false;
  }

  if (AT("AT+CMGS=\"" + phone + "\"\r", ">") == "")
  {
    (*error_handler)(31);
    return false;
  }
  else
  {
    if (AT(message + (char)0x1A) == "")
    {
      (*error_handler)(32);
      return false;
    }
  }

  return true;
}

String MODEMKA_Driver::USSD(String command) {

  String output = AT("AT+CUSD=1,\"" + command + "\"\r", "+CUSD: ");

  if (output == "")
  {
    (*error_handler)(33);
  }
  else
  {
    output = str_parse(1, ',', output);
    output = str_parse(1, '\"', output);
    output = decode(output);
  }

  return output;
}

bool MODEMKA_Driver::DTMF(String sequency) {

  int l = sequency.length();

  if (l > 20)
  {
    (*error_handler)(34);
    return false;
  }

  if (AT("AT+VTD=1\r") == "")
  {
    (*error_handler)(35);
    return false;
  }

  if (char_in_str(',', sequency) == 0)
  {
    String new_sequency = "";

    for (int i = 0; i < l; i++)
    {
      new_sequency += sequency[i];

      if (i < l - 1)
      {
        new_sequency += ',';
      }
    }

    sequency = new_sequency;
  }

  if (AT("AT+VTS=\"" + sequency + "\"\r") == "")
  {
    (*error_handler)(36);
    return false;
  }

  return true;
}

void MODEMKA_Driver::network(String apn, String user, String password) {

  _APN_ = apn;
  _USER_ = user;
  _PASSWORD_ = password;
}

bool MODEMKA_Driver::connect(IPAddress ip, int port, int protocol_code, bool ssl) {

  return connect(ip_to_str(ip), port, protocol_code, ssl);
}

bool MODEMKA_Driver::connect(String address, int port, int protocol_code, bool ssl) {

  if (_GPRS_ == 0)
  {
    if (AT("AT+CGATT?\r", "+CGATT: 1") == "")
    {
      (*error_handler)(44);
      return false;
    }

    if (AT("AT+CIPRXGET=1\r") == "")
    {
      (*error_handler)(52);
      return false;
    }

    if (AT("AT+CIPMUX=0\r") == "")
    {
      (*error_handler)(51);
      return false;
    }

    if (AT("AT+CSTT=\"" + _APN_ + "\",\"" + _USER_ + "\",\"" + _PASSWORD_ + "\"\r") == "")
    {
      (*error_handler)(48);
      return false;
    }

    if (AT("AT+CIICR\r") == "")
    {
      (*error_handler)(49);
      return false;
    }

    String cifsr = AT("AT+CIFSR\r", ".");

    if (cifsr == "")
    {
      (*error_handler)(50);
      return false;
    }

    _LOCAL_IP_ = str_to_ip(cifsr);

    _GPRS_ = 1;
  }

  if (ssl == true)
  {
    if (AT("AT+CIPSSL=1\r") == "")
    {
      (*error_handler)(52);
      return false;
    }
  }
  else
  {
    if (AT("AT+CIPSSL=0\r") == "")
    {
      (*error_handler)(53);
      return false;
    }
  }

  String protocol;

  switch (protocol_code) {
    case 1:
      protocol = "UDP";
      break;

    default:
      protocol = "TCP";
      break;
  }

  if (AT("AT+CIPSTART=\"" + protocol + "\",\"" + address + "\",\"" + String(port) + "\"\r", "CONNECT OK") == "")
  {
    (*error_handler)(54);
    return false;
  }

  _GPRS_ = 2;

  return true;
}

bool MODEMKA_Driver::close() {

  if (AT("AT+CIPSHUT\r") == "")
  {
    (*error_handler)(70);
    return false;
  }

  _GPRS_ = 0;
  _LENGTH_ = 0;
  _POINTER_ = 0;
  free(_PAYLOAD_);

  return true;
}

bool MODEMKA_Driver::write(char* payload, int length) {

  if (_GPRS_ != 2)
  {
    (*error_handler)(55);
    return false;
  }

  if (AT("AT+CIPSEND=" + String(length) + "\r", ">") == "")
  {
    (*error_handler)(56);
    return false;
  }

  for (int i = 0; i < length; i++)
  {
    _UART_.write(payload[i]);
  }

  if (AT(String(char(0x1A)), "SEND OK") == "")
  {
    (*error_handler)(57);
    return false;
  }

  return true;
}

bool MODEMKA_Driver::read(char* payload, int length) {

  if (_GPRS_ != 2)
  {
    (*error_handler)(66);
    return false;
  }

  if (_POINTER_ + length > _LENGTH_)
  {
    (*error_handler)(69);
    return false;
  }

  for (int i = 0; _POINTER_ < length; i++, _POINTER_++)
  {
    payload[i] = _PAYLOAD_[_POINTER_];
  }

  if (_POINTER_ == _LENGTH_)
  {
    free(_PAYLOAD_);
    _PAYLOAD_ = NULL;
    _LENGTH_ = 0;
    _POINTER_ = 0;
  }

  return true;
}

int MODEMKA_Driver::available() {

  if (_GPRS_ != 2)
  {
    (*error_handler)(67);
    return -1;
  }

  return _LENGTH_ - _POINTER_;
}

void MODEMKA_Driver::leak_buffer(String line) {

  for (int i = 0; i < _EXCEPTIONS_SIZE_; i++)
  {
    if ( strstr(line.c_str(), _EXCEPTIONS_[i].c_str()) != NULL )
    {
      return;
    }
  }

  _LEAK_BUFFER_ += line;
}

String MODEMKA_Driver::remove_char(char c, String s) {

  String t = "";

  for (int i = 0; i < s.length(); i++)
  {
    if (s[i] != c)
    {
      t += (char)s[i];
    }
  }

  return t;
}

int MODEMKA_Driver::char_in_str(char c, String s) {

  int j = 0;

  for (int i = 0; i < s.length(); i++)
  {
    if (s[i] == c)
    {
      j++;
    }
  }

  return j;
}

String MODEMKA_Driver::str_parse(int id, char flag, String input) {

  String output = "";

  for (int i = 0, count = 0; i < input.length(); i++)
  {
    if (input[i] == flag)
    {
      count++;
    }
    else
    {
      if (count == id)
      {
        output += input[i];
      }
      else if (count > id)
      {
        break;
      }
    }
  }

  return output;
}

String MODEMKA_Driver::pop_line(String& input) {

  bool complite = false;
  char symbol;
  int i;
  int j;
  int l = input.length();
  String output = "";

  for (i = 0, j = 0; i < l; i++)
  {
    symbol = input[i];

    if (complite == false)
    {
      if ( (symbol == '\n') || (symbol == '\r') )
      {
        complite = true;
      }
      else
      {
        output += symbol;
      }
    }
    else
    {
      input[j] = input[i];
      j++;
    }
  }

  int l2 = output.length() + 1;
  input.remove(l - l2, l2);

  return output;
}

bool MODEMKA_Driver::only_digits(String str) {

  for (int i = 0; i < str.length(); i++)
  {
    if ( (str[i] < '0') || (str[i] > '9') )
    {
      return false;
    }
  }

  return true;
}
