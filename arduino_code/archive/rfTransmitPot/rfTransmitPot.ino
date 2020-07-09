#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver(2000, 10, 9, 8, false);

int potPin = 1;
int potval = 0;
String pvStr;

void setup()
{
  Serial.begin(9600);    // Debugging only
  if (!driver.init())
    Serial.println("init failed");
}

void loop()
{
  potval = analogRead(potPin);
  pvStr = String(potval);

  //  const char *msg = "Hello World!";
  const char *msg = pvStr.c_str();

  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
  delay(200);
}
