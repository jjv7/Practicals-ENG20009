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
}


void loop() {
  // put your main code here, to run repeatedly:
  sBmx160SensorData_t Oaccel;

  /* Get a new sensor event */
  bmx160.getAllData(NULL, NULL, &Oaccel);

  // Tilt left
  if (Oaccel.x > 0) {
    tft.fillTriangle(0, 64, 30, 88, 30, 40, ST77XX_WHITE);
  }

  // Tilt right
  if (Oaccel.x < 0) {
    tft.fillTriangle(160, 64, 130, 88, 130, 40, ST77XX_WHITE);
  }

  // Tilt up
  if (Oaccel.y < 0) {
    tft.fillTriangle(80, 0, 56, 30, 104, 30, ST77XX_WHITE);
  }

  // Tilt down
  if (Oaccel.y > 0) {
    tft.fillTriangle(80, 128, 56, 98, 104, 98, ST77XX_WHITE);
  }

  delay(100);
  tft.fillScreen(ST77XX_BLACK);
}
