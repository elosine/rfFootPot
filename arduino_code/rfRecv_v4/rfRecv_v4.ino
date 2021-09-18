#include <RH_ASK.h> //from radiohead lib
#include <SPI.h> // Not actualy used but needed to compile
#include <Keyboard.h>
#include <Mouse.h>

RH_ASK driver(8000, 9, 12, 8, false);

String str_receive;
int val;
int pval;
int ival;

void setup() {
  Serial.begin(115200);
  if (!driver.init())
    Serial.println("init failed");
}

void loop() {
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  if (driver.recv(buf, &buflen)) {
    int i;
    str_receive = String((char*)buf);
    char valStr[buflen];
    str_receive.toCharArray(valStr, buflen);
    val = atoi(valStr);
    if (val != pval) {
      //simple interpolation
      int delta = val - pval;
      int deltaInc = abs(delta);
      for (int i = 0; i < deltaInc; i++) {
        if (delta > 0) {
          ival = pval + i + 1;
        } else {
          ival = pval - i - 1;
        }
      }
      Serial.println(ival);
      delay(5);
    }
  }
  pval = val;
}
