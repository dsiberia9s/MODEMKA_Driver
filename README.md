Function | Arguments | Return | Purpose
---|---|---|---
bool PIN() | – | true – require PIN | Check for require PIN-code.
bool PIN(String) | String – PIN-code *like "8888"*. | true – PIN-code format is correct. | Enter PIN-code.
bool accept() | – | true – if call answered. | Answer on call.
bool call(String) | String – phone number *like "+12223334455"*. | true – if call phone number success. | Call phone number.
bool close() | – | true – if connection closed success. | Close GPRS-connection.
bool decline() | – | true – if call decline success. | Decline call.
void live() | – | – | Need's repeat in loop.
void unicode(bool) | bool – true for Turn ON unicode decoding. | – | Turn ON/OFF unicode decoding.
void network(String, String, String) | 1st String – APN. 2nd String – user name. 3rd String – password. | – | Setup mobile data.
bool begin(bool) | bool – true for print debug messages to Serial port. | true – if modem succefull prepeared for work. | Prepearing modem for work.
