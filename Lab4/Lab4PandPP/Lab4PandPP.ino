int LED1 = 11;
int LED2 = 10;
int LED3 = 9;

int LED1State = LOW;
int LED2State = HIGH;
int LED3State = LOW;

int LED2Interval = 1000;
unsigned long previousMillis2 = 0;

int LED3Brightness = 0;


void setup() {
  Serial.begin(9600);
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void cycleLEDs() {
  digitalWrite(LED1, LED1State);

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis2 >= LED2Interval) {
    previousMillis2 = currentMillis;
    LED2State = !LED2State;
    digitalWrite(LED2, LED2State);
  }
  analogWrite(LED3, LED3Brightness);
}

bool confirmationMenu() {
  while (1) {                 // Infinite loop until return
    bool result = false;
    Serial.println("1. Yes");
    Serial.println("2. No");
    Serial.println("Please select an option (1-2)");


    while (Serial.available() == 0) { cycleLEDs(); }
    
    int selection = Serial.parseInt();

    switch(selection) {
      case 1:
        result = true;
        return result;
      case 2:
        return result;
      default:
        Serial.println("Invalid option, please enter an integer between 1-2");
    }
  }
}

void LED1ToggleMenu() {
  bool finished = false;

  while (!finished) {
    Serial.println("LED 1 Toggle Menu:");
    Serial.println("1. Toggle on/off");
    Serial.println("2. Exit to main menu");
    Serial.println("Please select an option (1-2)");

    while (Serial.available() == 0) { cycleLEDs(); }

    int selection = Serial.parseInt();
    bool confirm;

    switch(selection) {
      case 1:
        Serial.println("Are you sure you want to toggle LED 1?");
        confirm = confirmationMenu();
        
        if (confirm) {
          LED1State = !LED1State;
          Serial.println("LED 1 has been toggled");
        }
        break;
      case 2:
        Serial.println("Returning to main menu");
        finished = true;
        break;
      default:
        Serial.println("Invalid option, please enter an integer between 1-2");
    }
  }
}

void LED2IncreaseMenu() {
  bool finished = false;

  while (!finished) {
    Serial.println("LED 2 Blink Speed Increase Menu:");
    Serial.println("1. Increase blink speed");
    Serial.println("2. LED 2 Blink Speed Decrease Menu");
    Serial.println("3. Exit to main menu");
    Serial.println("Please select an option (1-3)");

    while (Serial.available() == 0) { cycleLEDs(); }

    int selection = Serial.parseInt();
    bool confirm;

    switch(selection) {
      case 1:
        Serial.println("Are you sure you want to increase the blink speed of LED 2?");
        confirm = confirmationMenu();
        if (confirm && LED2Interval > 0) {
          LED2Interval -= 250;
          Serial.println("LED 2 blink speed has been increased");
        } else {
          Serial.println("Blink speed is at its maximum");
        }
        break;
      case 2:
        finished = true;
        LED2DecreaseMenu();
        break;
      case 3:
        Serial.println("Returning to main menu");
        finished = true;
        break;
      default:
        Serial.println("Invalid option, please enter an integer between 1-3");
    }
  }
}

void LED2DecreaseMenu() {
  bool finished = false;

  while (!finished) {
    Serial.println("LED 2 Blink Speed Decrease Menu:");
    Serial.println("1. Decrease blink speed");
    Serial.println("2. LED 2 Blink Speed Increase Menu");
    Serial.println("3. Exit to main menu");
    Serial.println("Please select an option (1-3)");

    while (Serial.available() == 0) { cycleLEDs(); }

    int selection = Serial.parseInt();
    bool confirm;

    switch(selection) {
      case 1:
        Serial.println("Are you sure you want to decrease the blink speed of LED 2?");
        confirm = confirmationMenu();
        if (confirm) {
          LED2Interval += 250;
          Serial.println("LED 2 blink speed has been decreased");
        }
        break;
      case 2:
        finished = true;
        LED2IncreaseMenu();
        break;
      case 3:
        Serial.println("Returning to main menu");
        finished = true;
        break;
      default:
        Serial.println("Invalid option, please enter an integer between 1-3");
    }
  }
}

void LED3BrightnessMenu() {
  bool finished = false;

  while (!finished) {
    Serial.println("LED 3 Brightness Control Menu:");
    Serial.println("1. Increase LED 3 Brightness");
    Serial.println("2. Decrease LED 3 Brightness");
    Serial.println("3. Exit to main menu");
    Serial.println("Please select an option (1-3)");

    while (Serial.available() == 0) { cycleLEDs(); }

    int selection = Serial.parseInt();
    bool confirm;

    switch(selection) {
      case 1:
        Serial.println("Are you sure you want to increase the brightness of LED 3?");
        confirm = confirmationMenu();
        if (confirm && LED3Brightness < 254) {
          LED3Brightness += 60;
          Serial.println("LED 3 brightness has been increased");
          if (LED3Brightness > 254) {
            LED3Brightness = 254;
            Serial.println("Maximum LED 3 brightness");
          }
        } else if(confirm && LED3Brightness == 254) {
          Serial.println("LED 3 is already at maximum brightness");
        }
        break;
      case 2:
        Serial.println("Are you sure you want to decrease the brightness of LED 3?");
        confirm = confirmationMenu();
        if (confirm && LED3Brightness > 0) {
          LED3Brightness -= 60;
          Serial.println("LED 3 brightness has been decreased");
          if (LED3Brightness < 0) {
            LED3Brightness = 0;
            Serial.println("LED 3 brightness is at zero");
          }
        } else if(confirm && LED3Brightness == 0) {
          Serial.println("LED 3 is already at zero brightness");
        }
        break;
      case 3:
        Serial.println("Returning to main menu");
        finished = true;
        break;
      default:
        Serial.println("Invalid option, please enter an integer between 1-3");
    }
  }
}

void loop() {
  Serial.println("Main menu:");
  Serial.println("1. Toggle LED 1");
  Serial.println("2. Increase LED 2 blink speed");
  Serial.println("3. Decrease LED 2 blink speed");
  Serial.println("4. Control LED 3 brightness");
  Serial.println("Please select an option (1-4)");

  while (Serial.available() == 0) { cycleLEDs(); }

  int selection = Serial.parseInt();

  switch(selection) {
    case 1:
      LED1ToggleMenu();
      break;
    case 2:
      LED2IncreaseMenu();
      break;
    case 3:
      LED2DecreaseMenu();
      break;
    case 4:
      LED3BrightnessMenu();
      break;
    default:
      Serial.println("Invalid option, please enter an integer between 1-4");
  }
}
