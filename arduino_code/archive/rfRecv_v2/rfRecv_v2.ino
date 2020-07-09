#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile
#include <Keyboard.h>
#include <Mouse.h>

RH_ASK driver(8000, 9, 12, 8, false);

String str_receive;
int val;
int pval;

void setup() {
  Serial.begin(9600);  // Debugging only
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
      //When you go to 0, move mouse to bottom of screen 
      // moving -128px(max in one move) 50 times, can accomodate the biggest resolutions
      if (val == 0) {
        for (int i = 0; i < 50; i++) {
          Mouse.move(0, 127, 0);
        }
      }
      //calculate how much the pot moved since last frame
      int delta = (val - pval) * -1;
      //move the mouse that many pixels
      Mouse.move(0, delta, 0);
    }
    Serial.println(val);
    pval = val;
  }
  delay(50);
}
