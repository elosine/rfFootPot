#include <RH_ASK.h>
#include <SPI.h>
RH_ASK driver(8000, 10, 9, 8, false);

int potPin = 1;
int potval = 0;
String potvalStr;

void setup()
{
  Serial.begin(9600);
  if (!driver.init())
    Serial.println("init failed");
}

void loop()
{
  potval = analogRead(potPin);
  potvalStr = String(potval);

  const char *msg = potvalStr.c_str();

  driver.send((uint8_t *)msg, strlen(msg));          
  driver.waitPacketSent();


}
