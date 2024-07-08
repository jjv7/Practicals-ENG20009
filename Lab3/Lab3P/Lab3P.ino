#define LDR A1

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
  pinMode(LDR, INPUT);
  for (int i = 2; i <= 11; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int light = analogRead(LDR);
  if (light < 50) {
    for (int i = 2; i <= 11; i++) {
      digitalWrite(i, HIGH);
    }
  } else {
    for (int i = 2; i <= 11; i++) {
      digitalWrite(i, LOW);
    }
  }
  
}
