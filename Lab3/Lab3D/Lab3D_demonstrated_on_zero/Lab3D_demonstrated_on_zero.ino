#define POT A0
#define LDR A1

int buzzer = 6;

int button = 2;

int buttonLastState;

bool toggled;

// Demonstrated on Zero


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

void tone1(int pwmValue, int potValue) {
  tone(buzzer, 294 + pwmValue, 125);
  delay(potValue * 0.25);
  tone(buzzer, 294 + pwmValue, 125);
  delay(potValue * 0.25);
  tone(buzzer, 587 + pwmValue, 250);
  delay(potValue * 0.25);
  tone(buzzer, 440 + pwmValue, 250);
  delay(potValue * 0.75);
  tone(buzzer, 415 + pwmValue, 125);
  delay(potValue * 0.5);
  tone(buzzer, 392 + pwmValue, 250);
  delay(potValue * 0.5);
  tone(buzzer, 349 + pwmValue, 250);
  delay(potValue * 0.5);
  tone(buzzer, 294 + pwmValue, 125);
  delay(potValue * 0.25);
  tone(buzzer, 349 + pwmValue, 125);
  delay(potValue * 0.25);
  tone(buzzer, 392 + pwmValue, 125);
  delay(potValue * 0.25);
}

void tone2(int pwmValue, int potValue) {
  tone(buzzer, 370 + pwmValue, 200); //370
  delay(potValue);
  tone(buzzer, 440 + pwmValue, 200); //440
  delay(potValue * 0.5);
  tone(buzzer, 554 + pwmValue, 200); //554
  delay(potValue * 0.9);
  tone(buzzer, 494 + pwmValue, 250); //494
  delay(potValue);
  tone(buzzer, 370 + pwmValue, 200); //370
  delay(potValue * 0.45);
  tone(buzzer, 294 + pwmValue, 200); //294
  delay(potValue * 0.5);
  tone(buzzer, 294 + pwmValue, 200); //294
  delay(potValue * 0.5);
  tone(buzzer, 294 + pwmValue, 200); //294
  delay(potValue);
}


void loop() {
  // put your main code here, to run repeatedly:
  int potValue = analogRead(POT);
  int light = analogRead(LDR);
  int pwmValue = map(light, 0, 1023, 0, 255);
  

  byte buttonState = digitalRead(button);

  if (buttonState != buttonLastState) {
    buttonLastState = buttonState;
    if (buttonState == LOW) {
      toggled = !toggled;
    }
  }

  if (toggled) {
    tone2(pwmValue, potValue);
  } else {
    tone1(pwmValue, potValue);
  }
  


}
