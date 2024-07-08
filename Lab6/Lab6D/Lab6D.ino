#include <DueTimer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#define TFT_CS    10
#define TFT_RST   6 
#define TFT_DC    7 

#define TFT_SCLK 13   
#define TFT_MOSI 11   

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

const int button = 2;

volatile int hours = 0;
volatile int minutes = 0;
volatile int seconds = 0;

volatile bool digital = false;

const int centerX = 80;
const int centerY = 64;
const int secondHandLength = 45;
const int minuteHandLength = 40;
const int hourHandLength = 25;

void setup() {
  // put your setup code here, to run once:
  pinMode(button, INPUT_PULLUP);

  // Change initial time here, or it will default to 00:00:00
  hours = 16;
  minutes = 42;
  seconds = 0;

  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
  tft.setRotation(3);
  tft.setTextColor(ST77XX_WHITE); 
  tft.setTextWrap(false);
  tft.setTextSize(2);

  attachInterrupt(button, changeClock, RISING);   // Will cause digital = true after setup

  // Increments the clock once per second (1Hz)
  Timer3.attachInterrupt(incrementClock);
  Timer3.setFrequency(1).start();

  tft.fillScreen(ST77XX_BLACK);       
}

void changeClock() {
  // button debounce check
  static unsigned long lastMillis = 0;
  unsigned long newMillis = millis();
  if (newMillis - lastMillis >= 50) {
    lastMillis = newMillis;
    digital = !digital;                   // Change clock style
  }
}

void incrementClock() {
  seconds++;
  if (seconds >= 60) {
    seconds = 0;
    minutes++;
  }
  if (minutes >= 60) {
    minutes = 0;
    hours++;
  }
  if (hours >= 24) {
    hours = 0;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digital) {
    char currentTime[9];
    tft.setCursor(30, 55);
    sprintf(currentTime, "%02d:%02d:%02d", hours, minutes, seconds);
    tft.print(currentTime);
  } else {
    displayAnalogue();
  }
  delay(1000);
  tft.fillScreen(ST77XX_BLACK);
}

void displayAnalogue() {
  // Calculate hand angles
  float secondAngle = map(seconds, 0, 60, 0, 360);
  float minuteAngle = map(minutes, 0, 60, 0, 360) + secondAngle / 60.0;
  float hourAngle = map(hours % 12, 0, 12, 0, 360) + minuteAngle / 12.0;

  // Draw clock hands based on angles
  // Angle - 90 to move hand starting position from positive x-axis to positive y-axis
  int hourEndX = centerX + (hourHandLength * cos((hourAngle - 90) * DEG_TO_RAD));
  int hourEndY = centerY + (hourHandLength * sin((hourAngle - 90) * DEG_TO_RAD));
  tft.drawLine(centerX, centerY, hourEndX, hourEndY, ST77XX_YELLOW);

  int minuteEndX = centerX + (minuteHandLength * cos((minuteAngle - 90) * DEG_TO_RAD));
  int minuteEndY = centerY + (minuteHandLength * sin((minuteAngle - 90) * DEG_TO_RAD));
  tft.drawLine(centerX, centerY, minuteEndX, minuteEndY, ST77XX_GREEN);

  int secondEndX = centerX + (secondHandLength * cos((secondAngle - 90) * DEG_TO_RAD));
  int secondEndY = centerY + (secondHandLength * sin((secondAngle - 90) * DEG_TO_RAD));
  tft.drawLine(centerX, centerY, secondEndX, secondEndY, ST77XX_RED); // Second hand in red

  //makes clock look nicer
  tft.drawCircle(centerX, centerY, 50, ST77XX_WHITE);
  tft.fillCircle(centerX, centerY, 3, ST77XX_WHITE);
}
