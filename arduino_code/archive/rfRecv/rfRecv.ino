#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

String str_receive;

RH_ASK driver(2000, 9, 12, 8, false);

void setup()
{
  Serial.begin(9600);  // Debugging only
  if (!driver.init())
    Serial.println("init failed");
}

void loop()
{
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  if (driver.recv(buf, &buflen)) // Non-blocking
  {
    int i;

    str_receive = String((char*)buf);

    Serial.println(str_receive);
    delay(50);
  }
}
