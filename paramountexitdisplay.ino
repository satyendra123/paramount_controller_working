DMD Pin	      Connects To Arduino
A	            D6
B	            D7
CLK         	D11
OE	          D9
STB/LAT     	D10
DATA	        D8
GND	          GND
+5V	          5V (external PSU recommended)



#include <SPI.h>
#include <DMD.h>
#include <TimerOne.h>
#include "Arial_black_16.h"

#define DISPLAYS_ACROSS 2
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

String receivedString = "";
char vehicleNumber[30];

void ScanDMD() {
  dmd.scanDisplayBySPI();
}

void setup() {
  Serial.begin(9600);
  Timer1.initialize(3000);
  Timer1.attachInterrupt(ScanDMD);
  dmd.clearScreen(true);
  dmd.selectFont(Arial_Black_16);
  showWelcome();
}

void loop() {
  if (Serial.available()) {
    receivedString = Serial.readStringUntil('%');
    receivedString.trim();
    Serial.println("Received: " + receivedString);

    if (receivedString.startsWith("|VEHICLE_NUMBER-")) {
      String number = receivedString.substring(17);
      number.trim();
      number.toCharArray(vehicleNumber, sizeof(vehicleNumber));

      showVehicleNumber(vehicleNumber);
      scrollText("Shubh Yatra! Thank you for parking with us !");
      showThankYouScreen();
      showWelcome();
    }
  }
}

void showVehicleNumber(const char* number) {
  dmd.clearScreen(true);
  dmd.selectFont(Arial_Black_16);
  dmd.drawString(0, 0, number, strlen(number), GRAPHICS_NORMAL);
  delay(2000);
  dmd.clearScreen(true);
}

void scrollText(const char* text) {
  dmd.clearScreen(true);
  dmd.selectFont(Arial_Black_16);

  int textLength = strlen(text);
  int textWidth = textLength * 8;
  int displayWidth = DISPLAYS_ACROSS * 32;

  for (int pos = displayWidth; pos > -textWidth; pos--) {
    dmd.clearScreen(true);
    dmd.drawString(pos, 0, text, textLength, GRAPHICS_NORMAL);
    delay(80);
  }
  dmd.clearScreen(true);
}

void showThankYouScreen() {
  dmd.clearScreen(true);
  dmd.selectFont(Arial_Black_16);

  dmd.drawString(0, 0, "Visit", 5, GRAPHICS_NORMAL);
  dmd.drawString(0, 8, "Again", 5, GRAPHICS_NORMAL);

  delay(2000);
  dmd.clearScreen(true);

  dmd.drawString(0, 0, "Thank", 5, GRAPHICS_NORMAL);
  dmd.drawString(0, 8, "You", 3, GRAPHICS_NORMAL);

  delay(2000);
  dmd.clearScreen(true);
}

void showWelcome() {
  dmd.clearScreen(true);
  dmd.selectFont(Arial_Black_16);
  dmd.drawString(0, 0, "WELCOME", 7, GRAPHICS_NORMAL);
}
