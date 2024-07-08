#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <DFRobot_BMX160.h>

#define TFT_CS 10
#define TFT_RST 6
#define TFT_DC 7

#define TFT_SCLK 13
#define TFT_MOSI 11

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

DFRobot_BMX160 bmx160;

int symbolX = 76;
int symbolY = 55;

int xspeed = 0;
int yspeed = 0;

int accelInitX;
int accelInitY;


void setup() {
  Serial.begin(115200);
  delay(100);

  //init the hardware bmx160
  if (bmx160.begin() != true) {
    Serial.println("init false");
    while (1);
  }

  bmx160.softReset();
  bmx160.wakeUp();
  bmx160.setAccelRange(eAccelRange_2G);


  tft.initR(INITR_BLACKTAB);  // Init ST7735S chip, black tab
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setTextWrap(false);


  sBmx160SensorData_t Oaccel;
  bmx160.setAccelRange(eAccelRange_16G);
  bmx160.getAllData(NULL, NULL, &Oaccel);
  accelInitX = Oaccel.x;
  accelInitY = Oaccel.y;
}


void loop() {
  // put your main code here, to run repeatedly:
  sBmx160SensorData_t Oaccel;

  /* Get a new sensor event */
  bmx160.getAllData(NULL, NULL, &Oaccel);

  xspeed, yspeed = 0;

  xspeed = -Oaccel.x + accelInitX;
  yspeed = Oaccel.y - accelInitY;

  symbolX += xspeed;
  symbolY += yspeed;

  if (symbolX < 1) {
    symbolX = 1;
  }

  if (symbolX > 151) {
    symbolX = 151;
  }

  if (symbolY < -2) {
    symbolY = -2;
  }

  if (symbolY > 118) {
    symbolY = 118;
  }

  tft.setCursor(symbolX, symbolY);

  Serial.print("X: ");
  Serial.print(symbolX);
  Serial.print(" ");
  Serial.print("Y: ");
  Serial.print(symbolY);
  Serial.println("");


  tft.print("e");


  delay(100);
  tft.fillScreen(ST77XX_BLACK);
}
