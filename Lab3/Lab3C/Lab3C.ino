#define POT A0

int buzzer = 6;


void setup() {
  // put your setup code here, to run once:
  pinMode(POT, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int potValue = map(analogRead(POT), 0, 1023, 0, 255);
  analogWrite(buzzer, potValue);
  
}
