#define R1 54
#define R2 55
#define R3 56
#define R4 57
#define R5 58
#define R6 59
#define R7 70
#define R8 71

#define C1 6
#define C2 7
#define C3 8
#define C4 9
#define C5 10
#define C6 11
#define C7 12
#define C8 13

#define button 2
#define pot A0

int position = 0;
int selection = 0;
int buttonLastState;

int sine[8][16] {
  0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,
  0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,
  0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,
  1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,
  1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,
  0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,
  0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,
  0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,
};

int triangle[8][16] {
  0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,
  0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,
  0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,
  0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,
  0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,
  0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,
  0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1
};

int square[8][16] {
  1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,
  1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,
  1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,
  1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,
  1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,
  1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,
  1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,
  1,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1
};

int sawtooth[8][16] {
  0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
  0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,
  0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,
  0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,
  0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
  0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,
  0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,
  1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1
};


void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
  pinMode(pot, INPUT);
  
  for (int j = 54; j <= 59; j++) {
    pinMode(j, OUTPUT);
  }
  pinMode(R7, OUTPUT);
  pinMode(R8, OUTPUT);

  for (int i = 6; i <= 13; i++) {
    pinMode(i, OUTPUT);
  } 

  buttonLastState = digitalRead(button);
}

void scanRow(int row) {
  if (row == 1) digitalWrite(R1, HIGH); else digitalWrite(R1, LOW);
  if (row == 2) digitalWrite(R2, HIGH); else digitalWrite(R2, LOW);
  if (row == 3) digitalWrite(R3, HIGH); else digitalWrite(R3, LOW);
  if (row == 4) digitalWrite(R4, HIGH); else digitalWrite(R4, LOW);
  if (row == 5) digitalWrite(R5, HIGH); else digitalWrite(R5, LOW);
  if (row == 6) digitalWrite(R6, HIGH); else digitalWrite(R6, LOW);
  if (row == 7) digitalWrite(R7, HIGH); else digitalWrite(R7, LOW);
  if (row == 8) digitalWrite(R8, HIGH); else digitalWrite(R8, LOW);
}

void activateColumn(int column, int state) {
  if (column == 1) digitalWrite(C1, !state);  
  if (column == 2) digitalWrite(C2, !state); 
  if (column == 3) digitalWrite(C3, !state);  
  if (column == 4) digitalWrite(C4, !state); 
  if (column == 5) digitalWrite(C5, !state);  
  if (column == 6) digitalWrite(C6, !state); 
  if (column == 7) digitalWrite(C7, !state);  
  if (column == 8) digitalWrite(C8, !state); 
}

void displayWave(int wave[8][16], int frequency) {
  for (int x = 0; x < frequency; x++) {
    for (int j = 0; j < 8; j++){
      scanRow(j + 1);
      for (int i = 0; i < 16; i++) {
        int columnPosition = (i - position + 16) % 16;            // Calculates column position for scrolling
        activateColumn(i + 1, wave[j][columnPosition]);
      }
      delay(1);                                                 // Scanning delay
    }
  }
  
  position = (position + 1) % 16; // Basically allows the position to reset once it reaches 16
  
}



void loop() {
  int potValue = analogRead(pot);
  int frequency = map(potValue, 0, 1023, 10, 1);



  byte buttonState = digitalRead(button);

  if (buttonState != buttonLastState) {
    buttonLastState = buttonState;
    if (buttonState == LOW) {
      selection++;
      if (selection == 4) {
        selection = 0;
      }
    }
  }

  switch (selection) {
    case 1:
      displayWave(triangle, frequency); // triangle
      break;
    case 2:
      displayWave(square, frequency);   // square
      break;
    case 3:
      displayWave(sawtooth, frequency); // sawtooth
      break;
    default:
      displayWave(sine, frequency);     // sine
  }

}





