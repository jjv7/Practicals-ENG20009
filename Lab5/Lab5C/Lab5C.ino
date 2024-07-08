#include <OneWire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#define TFT_CS    10
#define TFT_RST   6 
#define TFT_DC    7 

#define TFT_SCLK 13   
#define TFT_MOSI 11

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// Define the one wire bus and the address of the DS28E07 chip
OneWire ds(8);  // One wire bus is on digital pin 2
byte addr[] = {0x2D, 0xD9 , 0xED , 0x67 , 0x40 , 0x0 , 0x0 , 0x94}; //insert the Address of EEPROM value into here after you run the searchFunction

void setup() {
  Serial.begin(9600);
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);  
  tft.setTextSize(3);
  tft.setTextWrap(false);

  Serial.println("Getting Family code / Address of EEPROM:");
  searchFunction();
}

void loop() {
  writeToEEPROM("1045472");
  String readString = readFromEEPROM(8);
  readString.remove(7, 12);
  tft.setCursor(0, 55);
  tft.print(readString);
  writeToEEPROM("42");
  readString = readFromEEPROM(8);
  readString.remove(2, 12);
  tft.print(readString);
  delay(1000);
  tft.fillScreen(ST77XX_BLACK);
}

void searchFunction() {
  byte i;
  byte addr[8];

  if (!ds.search(addr)) {
    ds.reset_search();
    delay(1000);
  }

  for (i = 0; i < 8; i++) {
    Serial.print(addr[i], HEX);
    Serial.print(" ");
  }
  Serial.print("\n");
}

// Function to write a string to the DS28E07 EEPROM
void writeToEEPROM(String data) {
  // Convert the input string to a char array
  char dataChars[30];
  data.toCharArray(dataChars, 30);

  // Write the data to the EEPROM
  ds.reset(); //reset device
  ds.select(addr);//select address of device to talk to
  ds.write(0x0F,1);   // Write ScratchPad       Configuration/mode bytes can be in datasheet
  ds.write(0x01,1);   //TA1 addresses           TA (Target Address) can also be found in the datasheet
  ds.write(0x09,1);   //TA2 addresses
  for ( int i = 0; i < data.length(); i++) {
    ds.write(dataChars[i],1);
  }
  ds.reset();
  ds.select(addr);
  ds.write(0x0F, 1);  // Copy ScratchPad
}

// Function to read a string from the DS28E07 EEPROM
String readFromEEPROM(int length) {
  byte dataBytes[30];
  ds.reset();
  ds.select(addr);
  ds.write(0xAA);  // Read Scratchpad
  for (int i = 0; i < length+4; i++) {
    dataBytes[i] = ds.read();
  }
  return String((char*)dataBytes).substring(3);
}