/*
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
*/

#include <SPI.h>
#include <DMD.h>
#include <TimerOne.h>
#include "fonts/Droid_Sans_16.h"
#include "fonts/SystemFont5x7.h"
#include "fonts/Droid_Sans_12.h"
#include "fonts/Arial14.h"
#include "fonts/Arial_Black_16.h"
#include "fonts/Droid_Sans_24.h"
#include "fonts/Corsiva_12.h"
#include "fonts/Arial_bold_14.h"
#include "fonts/Arial12.h"
#include "fonts/new_fonts_library/Calibri16.h"

#define DISPLAYS_ACROSS 2
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

String receivedString = "";
char vehicleNumber[30];

enum DisplayState { STATE_WELCOME, STATE_VEHICLE, STATE_SCROLL, STATE_THANK1, STATE_THANK2 };
DisplayState currentState = STATE_WELCOME;

unsigned long stateStartTime = 0;
unsigned long lastUpdate = 0;

int scrollPos = 0;
String scrollMsg = "";

// DMD refresh interrupt
void ScanDMD() {
  dmd.scanDisplayBySPI();
}

void setup() {
  Serial.begin(9600);
  Timer1.initialize(1000);
  Timer1.attachInterrupt(ScanDMD);
  dmd.clearScreen(true);
  dmd.selectFont(Calibri16);
  showWelcome();
}

void loop() {
  // ---- Check Serial for New Data ----
  if (Serial.available()) {
    receivedString = Serial.readStringUntil('%');
    receivedString.trim();

    if (receivedString.startsWith("|VEHICLE_NUMBER-")) {
      String number = receivedString.substring(17);
      number.trim();
      number.toCharArray(vehicleNumber, sizeof(vehicleNumber));

      // Interrupt and start showing new vehicle
      currentState = STATE_VEHICLE;
      stateStartTime = millis();
      showVehicleNumber(vehicleNumber);
    }
  }

  // ---- State Machine ----
  switch (currentState) {
    case STATE_WELCOME:
      break;

    case STATE_VEHICLE:
      if (millis() - stateStartTime >= 2000) {
        currentState = STATE_SCROLL;
        scrollMsg = "SHUBH YATRA THANK YOU FOR PARKING WITH US ";
        scrollPos = DISPLAYS_ACROSS * 32;
        lastUpdate = millis();
      }
      break;

    case STATE_SCROLL:
      if (millis() - lastUpdate >= 50) {
        lastUpdate = millis();
        int textLength = scrollMsg.length();
        int charWidth = 8;
        int textWidth = textLength * charWidth;

        dmd.clearScreen(true);
        dmd.selectFont(Calibri16);
        dmd.drawString(scrollPos, 1, scrollMsg.c_str(), textLength, GRAPHICS_NORMAL);

        scrollPos--;
        if (scrollPos < -textWidth) {
          currentState = STATE_THANK1;
          stateStartTime = millis();
          showThankYou1();
        }
      }
      break;

    case STATE_THANK1:
      if (millis() - stateStartTime >= 2000) {
        currentState = STATE_THANK2;
        stateStartTime = millis();
        showThankYou2();
      }
      break;

    case STATE_THANK2:
      if (millis() - stateStartTime >= 2000) {
        currentState = STATE_WELCOME;
        showWelcome();
      }
      break;
  }
}

// ---- Display Functions ----
void showVehicleNumber(const char* number) {
  dmd.clearScreen(true);
  dmd.selectFont(Droid_Sans_12);
  dmd.drawString(0, 3, number, strlen(number), GRAPHICS_NORMAL);
}

void showThankYou1() {
  dmd.clearScreen(true);
  dmd.selectFont(Droid_Sans_12);
  dmd.drawString(0, 4, "VISITAGAIN", strlen("VISITAGAIN"), GRAPHICS_NORMAL);
}

void showThankYou2() {
  dmd.clearScreen(true);
  dmd.selectFont(Droid_Sans_12);
  dmd.drawString(0, 4, "THANKYOU", strlen("THANKYOU"), GRAPHICS_NORMAL);
}

void showWelcome() {
  dmd.clearScreen(true);
  dmd.selectFont(Calibri16);
  dmd.drawString(1, 1, "WELCOME", strlen("WELCOME"), GRAPHICS_NORMAL);
}
