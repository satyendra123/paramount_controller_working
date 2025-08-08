#include <SPI.h>
#include <DMD.h>
#include <TimerOne.h>
#include "fonts/Droid_Sans_16.h"
#include "fonts/SystemFont5x7.h"
#include "fonts/Droid_Sans_12.h"
// Remove unused Arial_Black_16
#include "fonts/Arial14.h"
#include "fonts/Arial_Black_16.h"
#include "fonts/Droid_Sans_24.h" 
#include "fonts/Corsiva_12.h"
#include "fonts/Arial_bold_14.h"
#include "fonts/Arial12.h"
#include "fonts/new_fonts_library/Calibri16.h"
 // Ensure the file is available

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
  Timer1.initialize(1000);
  Timer1.attachInterrupt(ScanDMD);
  dmd.clearScreen(true);
  dmd.selectFont(Droid_Sans_16);
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
      scrollText("SWAGAT HAI PLEASE FOLLOW THE PARKING RULES");
      showThankYouScreen();
      delay(2000);
      showWelcome();
    }
  }
}

void showVehicleNumber(const char* number) {
  dmd.clearScreen(true);
  //dmd.selectFont(Arial14);
  dmd.selectFont(Droid_Sans_12);
  dmd.drawString(0, 3, number, strlen(number), GRAPHICS_NORMAL);
  delay(2000);
  dmd.clearScreen(true);
}

void scrollText(const char* text) {
  dmd.clearScreen(true);
  //dmd.selectFont(Arial14);
  dmd.selectFont(Calibri16);
  int textLength = strlen(text);
  int charWidth = 8;
  int textWidth = textLength * charWidth;
  int displayWidth = DISPLAYS_ACROSS * 32;

  for (int pos = displayWidth; pos > -textWidth; pos--) {
    dmd.clearScreen(true);
    dmd.drawString(pos, 1, text, textLength, GRAPHICS_NORMAL);
    delay(50);
  }
  dmd.clearScreen(true);
}

void showThankYouScreen() {
  dmd.clearScreen(true);
  dmd.selectFont(Droid_Sans_12);
  dmd.drawString(0, 4, "VISITAGAIN", strlen("VISITAGAIN"), GRAPHICS_NORMAL);
  delay(2000);
  dmd.clearScreen(true);
  dmd.drawString(0, 4, "THANKYOU", strlen("THANKYOU"), GRAPHICS_NORMAL);
  delay(2000);
  dmd.clearScreen(true);
}

void showWelcome() {
  dmd.clearScreen(true);
  //dmd.selectFont(Droid_Sans_12);
  //dmd.selectFont(Arial14);
  //dmd.selectFont(Arial_bold_14);
  dmd.selectFont(Calibri16);
  dmd.drawString(1,1, "WELCOME", strlen("WELCOME"), GRAPHICS_NORMAL);
  }

