#include <avr/pgmspace.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#define TFT_CS    10
#define TFT_RST   6 
#define TFT_DC    7 

#define TFT_SCLK 13   
#define TFT_MOSI 11   

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

const prog_uchar studentID[] PROGMEM = "104547242";
const prog_uchar studentName[] PROGMEM = "Jayden Kong";
const prog_uchar unitInformation[] PROGMEM = "ENG20009 Engineering Technology Inquiry Project";
const prog_uchar semester[] PROGMEM = "Semester 1, 2024";

void printText(const prog_uchar *str) {
  char c;
  while(c = pgm_read_byte(str++)) {
    tft.write(c);
  }
}

int textLength(const prog_uchar *str) {
  char c;
  int length = 0;
  while(c = pgm_read_byte(str++)) {
    length++;
  }
  return length;
}

void scrollText(const prog_uchar *str) {
  int textX = 160;
  int lengthOffset = textLength(str) * 10;
  for(int i = 0; i < lengthOffset + 160; i += 10) {
    textX -= 16;
    tft.setCursor(textX, 55);
    printText(str);
    delay(10);
    tft.fillScreen(ST77XX_BLACK);
  }
}




void setup() {
  // put your setup code here, to run once:
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);  
  tft.setTextSize(3);
  tft.setTextWrap(false);
}

void loop() {
  // put your main code here, to run repeatedly:
  scrollText(studentID);
  scrollText(studentName);
  scrollText(unitInformation);
  scrollText(semester);
}
