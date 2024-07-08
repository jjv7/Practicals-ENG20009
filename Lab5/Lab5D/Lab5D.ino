#include <RTClib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <SdFat.h>

#define TFT_CS    10
#define TFT_RST   6 
#define TFT_DC    7 

#define TFT_SCLK 13   
#define TFT_MOSI 11  

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

const int button1 = 2;
const int button2 = 3;
const int button3 = 4;
const int button4 = 5;

int button1State;
int button1LastState;
int button2State;
int button2LastState;
int button3State;
int button3LastState;
int button4State;
int button4LastState;

int previousClockScreenRefresh = 1000;
unsigned long previousMillisClock = 0;

bool timeFormat24 = true;

int alarmHours = 0;
int alarmMinutes = 0;
int alarmSeconds = 0;

bool alarmActive = false;
bool alarmTriggered = false;

bool displayFlash = false;

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

RTC_DS1307 rtc;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //rtc.adjust(DateTime(2023, 3, 21, 0, 59, 30));
  
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
  tft.setRotation(3);
  tft.setTextColor(ST77XX_WHITE); 
  tft.setTextWrap(false);
 

  for (int i = 2; i <= 5; i++) {
    pinMode(i, INPUT_PULLUP);
  }
  button1LastState = digitalRead(button1);
  button2LastState = digitalRead(button2);
  button3LastState = digitalRead(button3);
  button4LastState = digitalRead(button4);

  if (!sd.begin(SD_CONFIG)) {
    Serial.println("SD card initialization failed!");
    sd.initErrorHalt();
    while (1);
  }

  // Open/create a file for writing
  if (!file.open("buttonInputLogs.txt", O_RDWR | O_CREAT)) {
    sd.errorHalt(F("open failed"));
  }

  if (sd.exists("buttonInputLogs.txt")) {
    if (sd.remove("buttonInputLogs.txt")) {
      Serial.println("File deleted successfully");
    } else {
      Serial.println("Error deleting file");
    }
  } else {
    Serial.println("File does not exist");
  }

  file.close();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  byte button1State = digitalRead(button1);

  if (button1State != button1LastState) {
    button1LastState = button1State;
    if (button1State == LOW) {
      WriteSD(file, clockInformation());
      clockMenu();
    }
  }

  byte button3State = digitalRead(button3);

  if (button3State != button3LastState) {
    button3LastState = button3State;
    if (button3State == LOW && alarmTriggered) {
      displayFlash = false;
      tft.invertDisplay(false);
      alarmActive = false;
      alarmTriggered = false;
      WriteSD(file, clockInformation());
    }
  }

  unsigned long currentMillis = millis();
  
  if (currentMillis - previousClockScreenRefresh >= 1000) {
    previousClockScreenRefresh = currentMillis;
    tft.fillScreen(ST77XX_BLACK);
    DateTime now = rtc.now();

    if (alarmActive && alarmHours == now.hour() && alarmMinutes == now.minute()) {
      alarmTriggered = true;
    }

    tft.setTextSize(2);
    char currentTime[9];
    if (timeFormat24) {
      tft.setCursor(30, 55);
      sprintf(currentTime, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
    } else {
      tft.setCursor(20, 55);
      int hours = now.hour();
      switch(hours) {
        case 0:
          hours = 12;
          sprintf(currentTime, "%02d:%02d:%02d am", hours, now.minute(), now.second());
          break;
        case 1 ... 11:
          sprintf(currentTime, "%02d:%02d:%02d am", now.hour(), now.minute(), now.second());
          break;
        case 12:
          sprintf(currentTime, "%02d:%02d:%02d pm", now.hour(), now.minute(), now.second());
          break;
        default:
          hours -= 12;
          sprintf(currentTime, "%02d:%02d:%02d pm", hours, now.minute(), now.second());
      }
    }
    tft.print(currentTime);

    if (alarmTriggered) {
      displayFlash = !displayFlash;
      tft.invertDisplay(displayFlash);
    }
  }  
}

void clockMenu() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(1);
  bool done = false;
  do {
    tft.setCursor(0, 45);
    tft.println(" Clock Menu:");
    if (timeFormat24) {
      tft.println(" 1. 24-hour format (on)");
    } else {
      tft.println(" 1. 24-hour format (off)");
    }
    tft.println(" 2. Set time");
    tft.println(" 3. Alarm settings");
    tft.println(" 4. Return to clock");

    byte button1State = digitalRead(button1);

    if (button1State != button1LastState) {
      button1LastState = button1State;
      if (button1State == LOW) {
        timeFormat24 = !timeFormat24;
        tft.fillScreen(ST77XX_BLACK);
        WriteSD(file, clockInformation());
      }
    }

    byte button2State = digitalRead(button2);
    
    if (button2State != button2LastState) {
      button2LastState = button2State;
      if (button2State == LOW) {
        WriteSD(file, clockInformation());
        setTimeMenu();
      }
    }

    byte button3State = digitalRead(button3);

    if (button3State != button3LastState) {
      button3LastState = button3State;
      if (button3State == LOW) {
        WriteSD(file, clockInformation());
        setAlarmMenu();
      }
    }

    byte button4State = digitalRead(button4);
    
    if (button4State != button4LastState) {
      button4LastState = button4State;
      if (button4State == LOW) {
        WriteSD(file, clockInformation());
        done = true;
      }
    }  

  } while (done == false);
}

void setTimeMenu() {
  tft.fillScreen(ST77XX_BLACK);
  int newHours = 0;
  int newMinutes = 0;
  int newSeconds = 0;
  char setTime[9];
  int fieldSelected = 1;

  bool done = false;
  do {
    tft.setCursor(30, 35);
    tft.setTextSize(2);
    sprintf(setTime, "%02d:%02d:%02d", newHours, newMinutes, newSeconds);
    tft.print(setTime);
        
    tft.setCursor(0, 85);
    tft.setTextSize(1);
    tft.println(" Set Time Menu:");
    tft.println(" 1. Next field");
    tft.println(" 2. Increase field");
    tft.println(" 3. Confirm time and exit");
    tft.println(" 4. Return to Clock Menu");

    switch(fieldSelected) {
      case 1:
        tft.fillTriangle(41, 55, 36, 60, 46, 60, ST77XX_WHITE);
        break;
      case 2:
        tft.fillTriangle(77, 55, 72, 60, 82, 60, ST77XX_WHITE);
        break;
      default:
        tft.fillTriangle(112, 55, 107, 60, 117, 60, ST77XX_WHITE);
    }

    byte button1State = digitalRead(button1);

    if (button1State != button1LastState) {
      button1LastState = button1State;
      if (button1State == LOW) {
        fieldSelected++;
        if (fieldSelected >= 4) {
          fieldSelected = 1;
        }
        tft.fillScreen(ST77XX_BLACK);
        WriteSD(file, clockInformation());
      }
    }

    byte button2State = digitalRead(button2);
    
    if (button2State != button2LastState) {
      button2LastState = button2State;
      if (button2State == LOW) {
        switch(fieldSelected) {
          case 1:
            newHours++;
            if (newHours >= 24) {
              newHours = 0;
            }
            tft.fillScreen(ST77XX_BLACK);
            break;
          case 2:
            newMinutes++;
            if (newMinutes >= 60) {
              newMinutes = 0;
            }
            tft.fillScreen(ST77XX_BLACK);
            break;
          default:
            newSeconds++;
            if (newSeconds >= 60) {
              newSeconds = 0;
            }
            tft.fillScreen(ST77XX_BLACK);
        }
        WriteSD(file, clockInformation());
      }
    }

    byte button3State = digitalRead(button3);

    if (button3State != button3LastState) {
      button3LastState = button3State;
      if (button3State == LOW) {
        rtc.adjust(DateTime(2024, 3, 31, newHours, newMinutes, newSeconds));
        tft.fillScreen(ST77XX_BLACK);
        WriteSD(file, clockInformation());
        done = true;
      }
    }

    byte button4State = digitalRead(button4);
    
    if (button4State != button4LastState) {
      button4LastState = button4State;
      if (button4State == LOW) {
        tft.fillScreen(ST77XX_BLACK);
        WriteSD(file, clockInformation());
        done = true;
      }
    }
  } while (done == false);

}

void setAlarmMenu() {
  tft.fillScreen(ST77XX_BLACK);
  int newAlarmHours = alarmHours;
  int newAlarmMinutes = alarmMinutes;
  char setAlarm[9];
  int fieldSelected = 1;

  bool done = false;
  do {
    tft.setCursor(30, 35);
    tft.setTextSize(2);
    sprintf(setAlarm, "%02d:%02d:00", newAlarmHours, newAlarmMinutes);
    tft.print(setAlarm);
        
    tft.setCursor(0, 85);
    tft.setTextSize(1);
    tft.println(" Set Alarm Menu:");
    tft.println(" 1. Next field");
    tft.println(" 2. Increase field");
    if (alarmActive) {
      tft.println(" 3. Alarm active (on)");
    } else {
      tft.println(" 3. Alarm active (off)");
    }
    tft.println(" 4. Return to Clock Menu");

    switch(fieldSelected) {
      case 1:
        tft.fillTriangle(41, 55, 36, 60, 46, 60, ST77XX_WHITE);
        break;
      default:
        tft.fillTriangle(77, 55, 72, 60, 82, 60, ST77XX_WHITE);
        break;
    }

    byte button1State = digitalRead(button1);

    if (button1State != button1LastState) {
      button1LastState = button1State;
      if (button1State == LOW) {
        fieldSelected++;
        if (fieldSelected >= 3) {
          fieldSelected = 1;
        }
        tft.fillScreen(ST77XX_BLACK);
        WriteSD(file, clockInformation());
      }
    }

    byte button2State = digitalRead(button2);
    
    if (button2State != button2LastState) {
      button2LastState = button2State;
      if (button2State == LOW) {
        if (fieldSelected == 1) {
          newAlarmHours++;
          if (newAlarmHours >= 24) {
            newAlarmHours = 0;
          }
          tft.fillScreen(ST77XX_BLACK);
        } else {
          newAlarmMinutes++;
          if (newAlarmMinutes >= 60) {
            newAlarmMinutes = 0;
          }
          tft.fillScreen(ST77XX_BLACK);
        }
        WriteSD(file, clockInformation());
      }
    }

    byte button3State = digitalRead(button3);

    if (button3State != button3LastState) {
      button3LastState = button3State;
      if (button3State == LOW) {
        alarmHours = newAlarmHours;
        alarmMinutes = newAlarmMinutes;
        alarmActive = !alarmActive;
        tft.fillScreen(ST77XX_BLACK);
        WriteSD(file, clockInformation());
      }
    }

    byte button4State = digitalRead(button4);
    
    if (button4State != button4LastState) {
      button4LastState = button4State;
      if (button4State == LOW) {
        tft.fillScreen(ST77XX_BLACK);
        alarmHours = newAlarmHours;
        alarmMinutes = newAlarmMinutes;
        WriteSD(file, clockInformation());
        done = true;
      }
    }
  } while (done == false);
}

String clockInformation() {
  char information[120];
  DateTime now = rtc.now();
  sprintf(information, "---------------------\nTime: %02d:%02d:%02d\nAlarm: %02d:%02d:%02d\nAlarm active? (0 = no, 1 = yes): %d\n24h format? (0 = no, 1 = yes): %d", now.hour(), now.minute(), now.second(), alarmHours, alarmMinutes, alarmSeconds, alarmActive, timeFormat24);
  return information;
}

void WriteSD(File file, String message) {  
  // file.open("buttonInputLogs.txt", O_RDWR);
  file.open("buttonInputLogs.txt", FILE_WRITE);
  // file.rewind();                //Go to file position 0
  file.println(message);
  file.close();
}
