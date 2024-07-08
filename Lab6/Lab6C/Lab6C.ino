#include <DueTimer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <DFRobot_BMX160.h>

#define TFT_CS    10
#define TFT_RST   6 
#define TFT_DC    7 

#define TFT_SCLK 13   
#define TFT_MOSI 11   

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

DFRobot_BMX160 bmx160;

volatile float xData[600];             // Array to store x-axis data up to 5 mins
volatile float yData[600];             // Array to store y-axis data up to 5 mins
volatile float zData[600];             // Array to store z-axis data up to 5 mins
volatile int currentIndex = 0;         // Index to keep track of current data point

volatile int currentGraph = 1;

const int button1 = 2;
const int button2 = 3;
const int button3 = 4;

int button1State;
int button1LastState;
int button2State;
int button2LastState;
int button3State;
int button3LastState;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
  tft.setRotation(3); 
  tft.setTextSize(1);
  tft.fillScreen(ST77XX_BLACK);

  if (bmx160.begin() != true){
    Serial.println("init false");
    while(1);
  }

  bmx160.setAccelRange(eAccelRange_16G);

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);

  button1LastState = digitalRead(button1);
  button2LastState = digitalRead(button2);
  button3LastState = digitalRead(button3);

  Timer3.attachInterrupt(getSensorData);
  Timer3.setFrequency(0.5).start();
}

void getSensorData() {
  sBmx160SensorData_t Omagn, Ogyro, Oaccel;

  /* Get a new sensor event */
  bmx160.getAllData(&Omagn, &Ogyro, &Oaccel);

  switch(currentGraph) {
    case 1:
      xData[currentIndex] = map(Omagn.x, -600, 600, 128, 0);
      yData[currentIndex] = map(Omagn.y, -600, 600, 128, 0);
      zData[currentIndex] = map(Omagn.z, -600, 600, 128, 0);
      break;
    case 2:
      xData[currentIndex] = map(Ogyro.x, -30, 30, 128, 0);
      yData[currentIndex] = map(Ogyro.y, -30, 30, 128, 0);
      zData[currentIndex] = map(Ogyro.z, -30, 30, 128, 0);
      break;
    default:
      xData[currentIndex] = map(Oaccel.x, -100, 100, 128, 0);
      yData[currentIndex] = map(Oaccel.y, -100, 100, 128, 0);
      zData[currentIndex] = map(Oaccel.z, -100, 100, 128, 0);
  }
  
  currentIndex = (currentIndex + 1) % 600;
}

void loop() {
  // put your main code here, to run repeatedly:
  byte button1State = digitalRead(button1);
  if (button1State != button1LastState) {
    button1LastState = button1State;
    if (button1State == LOW && currentGraph != 1) {
      currentGraph = 1;
      currentIndex = 0;
    }
  }

  byte button2State = digitalRead(button2);
  if (button2State != button2LastState) {
    button2LastState = button2State;
    if (button2State == LOW && currentGraph != 2) {
      currentGraph = 2;
      currentIndex = 0;
    }
  }

  byte button3State = digitalRead(button3);
  if (button3State != button3LastState) {
    button3LastState = button3State;
    if (button3State == LOW && currentGraph != 3) {
      currentGraph = 3;
      currentIndex = 0;
    }
  }

  tft.setCursor(0, 5);
  tft.setTextColor(ST77XX_WHITE);
  tft.println(" Current:");
  switch(currentGraph) {
    case 1:
      tft.print(" Magn");
      break;
    case 2:
      tft.print(" Gyro");
      break;
    default:
      tft.print(" Accel");
  }
  
  tft.setCursor(0, 45); 
  tft.println(" Legend:");
  tft.setTextColor(ST77XX_RED);
  tft.println(" red: x");
  tft.setTextColor(ST77XX_GREEN);
  tft.println(" green: y");
  tft.setTextColor(ST77XX_BLUE);
  tft.println(" blue: z");
  tft.setCursor(0, 90);
  tft.setTextColor(ST77XX_WHITE);
  tft.println(" 1. Magn");
  tft.println(" 2. Gyro");
  tft.println(" 3. Accel");
  
  drawGraphLine(xData, ST77XX_RED);
  drawGraphLine(yData, ST77XX_GREEN);
  drawGraphLine(zData, ST77XX_BLUE);

  delay(1000);
  tft.fillScreen(ST77XX_BLACK);
}

void drawGraphLine(volatile float data[], uint16_t color) {
  int i = currentIndex;
  int xpos = 60;
    // needed to subtract 1 from currentIndex for it to print properly, even though this is the same code from Lab 5HD which worked fine
    for (i = currentIndex - 1; i > 0; i--) {
      tft.drawLine(xpos, data[i], xpos + 10, data[i-1], color);
      xpos += 10;
    }
}
