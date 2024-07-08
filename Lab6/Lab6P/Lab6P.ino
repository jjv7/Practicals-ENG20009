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

void setup() {
  // put your setup code here, to run once:
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
  tft.setRotation(3);
  tft.setTextColor(ST77XX_WHITE);  
  tft.setTextSize(3);

  pinMode(button, INPUT_PULLUP);
  attachInterrupt(button, displaySymbol, RISING); // Call displaySymbol if button changes state from off to on
  tft.fillScreen(ST77XX_BLACK);
}

void displaySymbol() {
  // button debounce check
  static unsigned long lastMillis = 0;
  unsigned long newMillis = millis();
  if (newMillis - lastMillis >= 50) {
    lastMillis = newMillis;
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(random(0, 160), random(0, 128));
    tft.print("&");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
