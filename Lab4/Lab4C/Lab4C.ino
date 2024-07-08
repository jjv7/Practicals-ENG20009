#include <RTClib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#define TFT_CS    10
#define TFT_RST   6 
#define TFT_DC    7 

#define TFT_SCLK 13   
#define TFT_MOSI 11   

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

RTC_DS1307 rtc;

void setup() {
  // put your setup code here, to run once:
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //rtc.adjust(DateTime(2023, 3, 21, 9, 0, 0));
  
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);  
  tft.setTextWrap(false);
  tft.setTextSize(3);
}

void loop() {
  // put your main code here, to run repeatedly:
  DateTime now = rtc.now();

  tft.setCursor(0, 55);
  char currentTime[9];
  sprintf(currentTime, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  tft.print(currentTime);
  delay(1000);
  tft.fillScreen(ST77XX_BLACK);
}
