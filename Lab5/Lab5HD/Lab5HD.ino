#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>
#include <RTClib.h>
#include <DFRobot_BMX160.h>
#include <SdFat.h>

#define TFT_CS    10
#define TFT_RST   6 
#define TFT_DC    7 

#define TFT_SCLK 13   
#define TFT_MOSI 11   

//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

RTC_DS1307 rtc;

DFRobot_BMX160 bmx160;

//define file system for sd card
SdFs sd;
FsFile file;
//^ configuration for FAT16/FAT32 and exFAT.

// Chip select may be constant or RAM variable.
const uint8_t SD_CS_PIN = A3;
//
// Pin numbers in templates must be constants.
const uint8_t SOFT_MISO_PIN = 12;
const uint8_t SOFT_MOSI_PIN = 11;
const uint8_t SOFT_SCK_PIN  = 13;

// SdFat software SPI template
SoftSpiDriver<SOFT_MISO_PIN, SOFT_MOSI_PIN, SOFT_SCK_PIN> softSpi;

#define SD_CONFIG SdSpiConfig(SD_CS_PIN, SHARED_SPI, SD_SCK_MHZ(0), &softSpi)

float xData[600];             // Array to store x-axis data up to 10 mins
float yData[600];             // Array to store y-axis data up to 10 mins
float zData[600];             // Array to store z-axis data up to 10 mins
int currentIndex = 0;         // Index to keep track of current data point


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
  tft.setRotation(3);
  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(1);


  rtc.begin();
  rtc.adjust(DateTime(2024, 1, 1, 0, 0, 0));

  if (bmx160.begin() != true){
    Serial.println("init false");
    while(1);
  }

  bmx160.setAccelRange(eAccelRange_16G);

  if (!sd.begin(SD_CONFIG)) {
    Serial.println("SD card initialization failed!");
    sd.initErrorHalt();
    while (1);
  }

  // Open/create a file for writing
  if (!file.open("imuData.txt", O_RDWR | O_CREAT)) {
    sd.errorHalt(F("open failed"));
  }

  if (sd.exists("imuData.txt")) {
    if (sd.remove("imuData.txt")) {
      Serial.println("File deleted successfully");
    } else {
      Serial.println("Error deleting file");
    }
  } else {
    Serial.println("File does not exist");
  }

  file.close(); //release file
}

void loop() {
  // put your main code here, to run repeatedly:
  sBmx160SensorData_t Omagn, Ogyro, Oaccel;
  
  DateTime now = rtc.now();
  bmx160.getAllData(NULL, NULL, &Oaccel);

  // min: -100, max: 100 to xmin: 0, xmax: 160 and ymin: 0, ymax: 128
  // red: x, green: y, blue: z
  Serial.print("A ");
  Serial.print("X: "); Serial.print(Oaccel.x    ); Serial.print("  ");
  Serial.print("Y: "); Serial.print(Oaccel.y    ); Serial.print("  ");
  Serial.print("Z: "); Serial.print(Oaccel.z    ); Serial.print("  ");
  Serial.println("m/s^2");
  Serial.println("");

  // Display stuff here:
  tft.setCursor(0, 45);
  tft.setTextColor(ST77XX_WHITE); 
  tft.println(" Legend:");
  tft.setTextColor(ST77XX_RED);
  tft.println(" red: x");
  tft.setTextColor(ST77XX_GREEN);
  tft.println(" green: y");
  tft.setTextColor(ST77XX_BLUE);
  tft.println(" blue: z");

  xData[currentIndex] = map(Oaccel.x, -100, 100, 128, 0);
  yData[currentIndex] = map(Oaccel.y, -100, 100, 128, 0);
  zData[currentIndex] = map(Oaccel.z, -100, 100, 128, 0);

  drawGraphLine(xData, ST77XX_RED);
  drawGraphLine(yData, ST77XX_GREEN);
  drawGraphLine(zData, ST77XX_BLUE);


  // Saving IMU accelerometer data to SD card:
  String data = concatenateSensorData(Oaccel.x, Oaccel.y, Oaccel.z, now.hour(), now.minute(), now.second());
  WriteSD(file, data);
  delay(1000);
  tft.fillScreen(ST77XX_BLACK);

  currentIndex = (currentIndex + 1) % 600;
}

void drawGraphLine(float data[], uint16_t color) {
  int i = currentIndex;
  int xpos = 60;
  if (i > 0) {
    for (i = currentIndex; i > 0; i--) {
      tft.drawLine(xpos, data[i], xpos + 10, data[i-1], color);
      xpos += 10;
    }
  }
}

String concatenateSensorData(float x, float y, float z, int hours, int minutes, int seconds) {
  char text[50];
  sprintf(text, "%02d:%02d:%02d - x: %f, y: %f, z: %f", hours, minutes, seconds, x, y, z);
  return text;
}

void WriteSD(File file, String message) {  
  file.open("imuData.txt", FILE_WRITE);
  file.println(message);
  file.close();
}