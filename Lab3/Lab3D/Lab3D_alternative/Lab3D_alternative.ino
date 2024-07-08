#define POT A0
#define LDR A1

int buzzer = 6;

int button = 2;

int buttonLastState;

bool toggled;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(POT, INPUT);
  pinMode(LDR, INPUT); 
  pinMode(buzzer, OUTPUT);

  pinMode(button, INPUT_PULLUP);
  buttonLastState = digitalRead(button);

  toggled = false;
}


void playTone(int speed, int volume, int duration, float offset) {
  analogWrite(buzzer, volume);
  delay(duration);
  analogWrite(buzzer, 0);
  delay(speed * offset);
}

void tone1(int speed, int volume) {
  playTone(speed, volume, 125, 0.25);
  playTone(speed, volume, 125, 0.25);
  playTone(speed, volume * 8, 250, 0.25);
  playTone(speed, volume * 6, 250, 0.75);
  playTone(speed, volume * 5.6, 125, 0.5);
  playTone(speed, volume * 5.32, 250, 0.5);
  playTone(speed, volume * 4.8, 250, 0.5);
  playTone(speed, volume, 125, 0.25);
  playTone(speed, volume * 4.8, 125, 0.25);
  playTone(speed, volume * 5.32, 125, 1);
}

void tone2(int speed, int volume) {
  playTone(speed, volume * 5, 200, 1);
  playTone(speed, volume * 6, 200, 0.5);
  playTone(speed, volume * 7.5, 200, 0.9);
  playTone(speed, volume * 6.7, 250, 1);
  playTone(speed, volume * 5, 200, 0.45);
  playTone(speed, volume, 200, 0.5);
  playTone(speed, volume, 200, 0.5);
  playTone(speed, volume, 200, 1);
}


void loop() {
  int potValue = analogRead(POT);
  int light = analogRead(LDR);
  int volume = map(light, 0, 1023, 0, 255);
  byte buttonState = digitalRead(button);

  if (buttonState != buttonLastState) {
    buttonLastState = buttonState;
    if (buttonState == LOW) {
      toggled = !toggled;
    }
  }

  if (toggled) {
    tone2(potValue, volume);
  } else {
    tone1(potValue, volume);
  }

  


}
