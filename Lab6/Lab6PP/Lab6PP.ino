#include <DueTimer.h>

const int LED = 11;
int state = LOW;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);

  Timer3.attachInterrupt(toggleLed);
  Timer3.start(3500000);      // Start 3.5 second timer to turn on LED
}

void toggleLed() {
  state = !state;
  digitalWrite(LED, state);
  if (state == LOW) {
    Timer3.start(3500000);
  } else {
    Timer3.start(1000000);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
