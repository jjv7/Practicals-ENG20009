#define POT A0

int LED1 = 2;
int LED2 = 3;
int LED3 = 4;
int LED4 = 5;
int LED5 = 6;
int LED6 = 7;
int LED7 = 8;
int LED8 = 9;
int LED9 = 10;
int LED10 = 11;


void setup() {
  // put your setup code here, to run once:
  pinMode(POT, INPUT);
  for (int i = 2; i <= 11; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int potValue = map(analogRead(POT), 0, 1023, 0, 255);
  int ledLevel = map(potValue, 0, 255, 1, 11);

  for (int i = 2; i <= 11; i++) {
    if (i <= ledLevel) {
      digitalWrite(i, HIGH);
    } else {
      digitalWrite(i, LOW);
    }
  }
}
