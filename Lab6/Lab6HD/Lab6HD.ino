#include <cctype>

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

const int A [8][8] = {
  0,0,0,0,0,0,0,0,
  0,0,1,1,1,1,0,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,1,1,1,1,1,1,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0
};
  
const int B [8][8] = {
  0,0,0,0,0,0,0,0,
  0,1,1,1,1,1,0,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,1,1,1,1,1,0,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,1,1,1,1,1,0,0
};
  
const int C [8][8] = {
  0,0,0,0,0,0,0,0,
  0,0,1,1,1,1,0,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,0,0,0,
  0,1,1,0,0,0,0,0,
  0,1,1,0,0,0,0,0,
  0,1,1,0,0,1,1,0,
  0,0,1,1,1,1,0,0
};

const int D [8][8] = {
  0,0,0,0,0,0,0,0,
  0,1,1,1,1,1,0,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,1,1,1,1,1,0,0
};
  
const int E [8][8] = {
  0,0,0,0,0,0,0,0,
  0,1,1,1,1,1,1,0,
  0,1,1,0,0,0,0,0,
  0,1,1,0,0,0,0,0,
  0,1,1,1,1,1,0,0,
  0,1,1,0,0,0,0,0,
  0,1,1,0,0,0,0,0,
  0,1,1,1,1,1,1,0
};
  
const int F [8][8] = {
  0,0,0,0,0,0,0,0,
  0,1,1,1,1,1,1,0,
  0,1,1,0,0,0,0,0,
  0,1,1,0,0,0,0,0,
  0,1,1,1,1,1,0,0,
  0,1,1,0,0,0,0,0,
  0,1,1,0,0,0,0,0,
  0,1,1,0,0,0,0,0
};
  
const int G [8][8] = {
  0,0,0,0,0,0,0,0,
  0,0,1,1,1,1,0,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,0,0,0,
  0,1,1,0,0,0,0,0,
  0,1,1,0,1,1,1,0,
  0,1,1,0,0,1,1,0,
  0,0,1,1,1,1,0,0
};

const int H [8][8] = {
  0,0,0,0,0,0,0,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,1,1,1,1,1,1,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0
};

const int I [8][8] = {
  0,0,0,0,0,0,0,0,
  0,0,1,1,1,1,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,1,1,1,1,0,0
};
  
const int J [8][8] = {
  0,0,0,0,0,0,0,0,
  0,0,0,1,1,1,1,0,
  0,0,0,0,1,1,0,0,
  0,0,0,0,1,1,0,0,
  0,0,0,0,1,1,0,0,
  0,1,1,0,1,1,0,0,
  0,1,1,0,1,1,0,0,
  0,0,1,1,1,0,0,0
};

const int K [8][8] = {
  0,0,0,0,0,0,0,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,1,1,0,0,
  0,1,1,1,1,0,0,0,
  0,1,1,1,0,0,0,0,
  0,1,1,1,1,0,0,0,
  0,1,1,0,1,1,0,0,
  0,1,1,0,0,1,1,0
};
  
const int L [8][8] = {
  0,0,0,0,0,0,0,0,
  0,1,1,0,0,0,0,0,
  0,1,1,0,0,0,0,0,
  0,1,1,0,0,0,0,0,
  0,1,1,0,0,0,0,0,
  0,1,1,0,0,0,0,0,
  0,1,1,0,0,0,0,0,
  0,1,1,1,1,1,1,0
};
  
const int M [8][8] = {
  0,0,0,0,0,0,0,0,
  0,1,1,0,0,0,1,1,
  0,1,1,1,0,1,1,1,
  0,1,1,1,1,1,1,1,
  0,1,1,0,1,0,1,1,
  0,1,1,0,0,0,1,1,
  0,1,1,0,0,0,1,1,
  0,1,1,0,0,0,1,1
};
  
const int N [8][8] = {
  0,0,0,0,0,0,0,0,
  0,1,1,0,0,0,1,1,
  0,1,1,1,0,0,1,1,
  0,1,1,1,1,0,1,1,
  0,1,1,0,1,1,1,1,
  0,1,1,0,0,1,1,1,
  0,1,1,0,0,0,1,1,
  0,1,1,0,0,0,1,1
};
  
const int O [8][8] = {
  0,0,0,0,0,0,0,0,
  0,0,1,1,1,1,0,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,0,1,1,1,1,0,0
};
  
const int P [8][8] = {
  0,0,0,0,0,0,0,0,
  0,1,1,1,1,1,0,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,1,1,1,1,1,0,0,
  0,1,1,0,0,0,0,0,
  0,1,1,0,0,0,0,0
};
  
const int Q [8][8] = {
  0,0,0,0,0,0,0,0,
  0,0,1,1,1,1,0,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,1,1,1,0,
  0,0,1,1,1,1,0,0,
  0,0,0,0,0,1,1,0
};
  
const int R [8][8] = {
  0,0,0,0,0,0,0,0,
  0,1,1,1,1,1,0,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,1,1,1,1,1,0,0,
  0,1,1,1,1,0,0,0,
  0,1,1,0,1,1,0,0,
  0,1,1,0,0,1,1,0
};
  
const int S [8][8] = {
  0,0,0,0,0,0,0,0,
  0,0,1,1,1,1,0,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,0,0,0,
  0,0,1,1,1,1,0,0,
  0,0,0,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,0,1,1,1,1,0,0
};
  
const int T [8][8] = {
  0,0,0,0,0,0,0,0,
  0,1,1,1,1,1,1,0,
  0,1,0,1,1,0,1,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0
};
  
const int U [8][8] = {
  0,0,0,0,0,0,0,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,0,1,1,1,1,1,0
};
  
const int V [8][8] = {
  0,0,0,0,0,0,0,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,0,1,1,1,1,0,0,
  0,0,0,1,1,0,0,0
};
  
const int W [8][8] = {
  0,0,0,0,0,0,0,0,
  0,1,1,0,0,0,1,1,
  0,1,1,0,0,0,1,1,
  0,1,1,0,0,0,1,1,
  0,1,1,0,1,0,1,1,
  0,1,1,1,1,1,1,1,
  0,1,1,1,0,1,1,1,
  0,1,1,0,0,0,1,1
};
  
const int X [8][8] = {
  0,0,0,0,0,0,0,0,
  0,1,1,0,0,0,1,1,
  0,1,1,0,0,0,1,1,
  0,0,1,1,0,1,1,0,
  0,0,0,1,1,1,0,0,
  0,0,1,1,0,1,1,0,
  0,1,1,0,0,0,1,1,
  0,1,1,0,0,0,1,1
};
  
const int Y [8][8] = {
  0,0,0,0,0,0,0,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,0,1,1,1,1,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0
};
  
const int Z [8][8] = {
  0,0,0,0,0,0,0,0,
  0,1,1,1,1,1,1,0,
  0,0,0,0,0,1,1,0,
  0,0,0,0,1,1,0,0,
  0,0,0,1,1,0,0,0,
  0,0,1,1,0,0,0,0,
  0,1,1,0,0,0,0,0,
  0,1,1,1,1,1,1,0
};
  
const int space [8][8] = {
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0
};

int position = 0;

const int button = 2;

volatile bool scrollFlip = false;
volatile int scrollSpeed = 10;
volatile unsigned long buttonPressTime = 0;

char text[101];

int inputText[8][808];

int totalWidth = 0;

void setup() {
  for (int j = 54; j <= 59; j++) {
    pinMode(j, OUTPUT);
  }
  pinMode(R7, OUTPUT);
  pinMode(R8, OUTPUT);

  for (int i = 6; i <= 13; i++) {
    pinMode(i, OUTPUT);
  } 

  Serial.begin(9600);
  getText();
  concatenateMatrices();

  pinMode(button, INPUT_PULLUP);
  attachInterrupt(button, buttonIsPressed, CHANGE);
  
  scrollSpeed = 10;             // attaching the interrupt causes the scrollSpeed change to trigger once
}

void getText() {
  bool finished = false;
  do {
    Serial.println("Please enter text (100 character limit):");

    while(Serial.available() == 0) { }

    strncpy(text, Serial.readString().c_str(), sizeof(text));

    for (int i = 0; i < strlen(text); i++) {
      text[i] = tolower(text[i]);
    }

    Serial.println(text);

    bool validString = true;
    for (int i = 0; i < strlen(text); i++) {
      if (!isalpha(text[i]) && !isspace(text[i])) {
        validString = false;
        break;
      }
    }

    if (validString) {
      finished = true;
    } else {
      Serial.println("Invalid input: Text cannot contain numbers or special characters.");
    }

    if (strlen(text) > 100) {
      finished = false;
      Serial.println("Invalid input: Cannot enter text greater than 100 characters");
    }
  } while (!finished);
}

void concatenateMatrices() {
  // Initialise array with all 0s. This is mainly so when there is no characters, for positions after the char array has been read in, they will be given a value of 0.
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 808; ++j) {
      inputText[i][j] = 0;
    }
  }

  int columnOffset = 0;
  for (int i = 0; i < strlen(text); i++) {
    switch(text[i]) {
      case 'a':
        for (int row = 0; row < 8; row++) {
          for (int col = 0; col < 8; col++) {
            inputText[row][col + columnOffset] = A[row][col];
          }
        }
        break;
      case 'b':
        for (int row = 0; row < 8; row++) {
          for (int col = 0; col < 8; col++) {
            inputText[row][col + columnOffset] = B[row][col];
          }
        }
        break;
      case 'c':
        for (int row = 0; row < 8; row++) {
          for (int col = 0; col < 8; col++) {
            inputText[row][col + columnOffset] = C[row][col];
          }
        }
        break;
      case 'd':
        for (int row = 0; row < 8; row++) {
          for (int col = 0; col < 8; col++) {
            inputText[row][col + columnOffset] = D[row][col];
          }
        }
        break;
      case 'e':
        for (int row = 0; row < 8; row++) {
          for (int col = 0; col < 8; col++) {
            inputText[row][col + columnOffset] = E[row][col];
          }
        }
        break;
      case 'f':
        for (int row = 0; row < 8; row++) {
          for (int col = 0; col < 8; col++) {
            inputText[row][col + columnOffset] = F[row][col];
          }
        }
        break;
      case 'g':
        for (int row = 0; row < 8; row++) {
          for (int col = 0; col < 8; col++) {
            inputText[row][col + columnOffset] = G[row][col];
          }
        }
        break;
      case 'h':
        for (int row = 0; row < 8; row++) {
          for (int col = 0; col < 8; col++) {
            inputText[row][col + columnOffset] = H[row][col];
          }
        }
        break;
      case 'i':
        for (int row = 0; row < 8; row++) {
          for (int col = 0; col < 8; col++) {
            inputText[row][col + columnOffset] = I[row][col];
          }
        }
        break;
      case 'j':
        for (int row = 0; row < 8; row++) {
          for (int col = 0; col < 8; col++) {
            inputText[row][col + columnOffset] = J[row][col];
          }
        }
        break;
      case 'k':
        for (int row = 0; row < 8; row++) {
          for (int col = 0; col < 8; col++) {
            inputText[row][col + columnOffset] = K[row][col];
          }
        }
        break;
      case 'l':
        for (int row = 0; row < 8; row++) {
          for (int col = 0; col < 8; col++) {
            inputText[row][col + columnOffset] = L[row][col];
          }
        }
        break;
      case 'm':
        for (int row = 0; row < 8; row++) {
          for (int col = 0; col < 8; col++) {
            inputText[row][col + columnOffset] = M[row][col];
          }
        }
        break;
      case 'n':
        for (int row = 0; row < 8; row++) {
          for (int col = 0; col < 8; col++) {
            inputText[row][col + columnOffset] = N[row][col];
          }
        }
        break;
      case 'o':
        for (int row = 0; row < 8; row++) {
          for (int col = 0; col < 8; col++) {
            inputText[row][col + columnOffset] = O[row][col];
          }
        }
        break;
      case 'p':
        for (int row = 0; row < 8; row++) {
          for (int col = 0; col < 8; col++) {
            inputText[row][col + columnOffset] = P[row][col];
          }
        }
        break;
      case 'q':
        for (int row = 0; row < 8; row++) {
          for (int col = 0; col < 8; col++) {
            inputText[row][col + columnOffset] = Q[row][col];
          }
        }
        break;
      case 'r':
        for (int row = 0; row < 8; row++) {
          for (int col = 0; col < 8; col++) {
            inputText[row][col + columnOffset] = R[row][col];
          }
        }
        break;
      case 's':
        for (int row = 0; row < 8; row++) {
          for (int col = 0; col < 8; col++) {
            inputText[row][col + columnOffset] = S[row][col];
          }
        }
        break;
      case 't':
        for (int row = 0; row < 8; row++) {
          for (int col = 0; col < 8; col++) {
            inputText[row][col + columnOffset] = T[row][col];
          }
        }
        break;
      case 'u':
        for (int row = 0; row < 8; row++) {
          for (int col = 0; col < 8; col++) {
            inputText[row][col + columnOffset] = U[row][col];
          }
        }
        break;
      case 'v':
        for (int row = 0; row < 8; row++) {
          for (int col = 0; col < 8; col++) {
            inputText[row][col + columnOffset] = V[row][col];
          }
        }
        break;
      case 'w':
        for (int row = 0; row < 8; row++) {
          for (int col = 0; col < 8; col++) {
            inputText[row][col + columnOffset] = W[row][col];
          }
        }
        break;
      case 'x':
        for (int row = 0; row < 8; row++) {
          for (int col = 0; col < 8; col++) {
            inputText[row][col + columnOffset] = X[row][col];
          }
        }
        break;
      case 'y':
        for (int row = 0; row < 8; row++) {
          for (int col = 0; col < 8; col++) {
            inputText[row][col + columnOffset] = Y[row][col];
          }
        }
        break;
      case 'z':
        for (int row = 0; row < 8; row++) {
          for (int col = 0; col < 8; col++) {
            inputText[row][col + columnOffset] = Z[row][col];
          }
        }
        break;
      default:
        for (int row = 0; row < 8; row++) {
          for (int col = 0; col < 8; col++) {
            inputText[row][col + columnOffset] = space[row][col];
          }
        }
    }
    columnOffset += 8;
    totalWidth += 8;
  }
  totalWidth += 8;                // Just makes some space at the back
}

void buttonIsPressed() {
  static unsigned long lastInterruptTime = 0;
  unsigned long currentInterruptTime = millis();

  // button debounce check
  if (currentInterruptTime - lastInterruptTime < 10) {
    return;
  }

  bool buttonState = digitalRead(button);

  if (buttonState == HIGH) {  // Button is released
    buttonPressTime = currentInterruptTime - buttonPressTime;

    if (buttonPressTime < 375) {
      // if short press
      scrollFlip = !scrollFlip;
    } else {
      // if long press
      scrollSpeed -= 4;
      if (scrollSpeed < 2) {
        scrollSpeed = 10;
      }
    }
  } else {  // Button is still pressed down
    buttonPressTime = currentInterruptTime;  // Start of button press
  }
  lastInterruptTime = currentInterruptTime;  // Update last interrupt time
}

void loop() {
  for (int x = 0; x < scrollSpeed; x++) {
    for (int j = 0; j < 8; j++){
      for (int i = 1; i <= 8; i++) {
        activateColumn(i, LOW);                             // Removes selected columns from previous loop to reduce ghosting
      }
      scanRow(j + 1);
      for (int i = 0; i < 8; i++) {
        int columnPosition;
        columnPosition = (i - position + totalWidth) % totalWidth;        // Calculates column position for scrolling
        activateColumn(i + 1, inputText[j][columnPosition]);
      }
      delay(2);                                             // Scanning delay
    }
  }

  if (scrollFlip) {
    position = (position - 1) % totalWidth;                        // Basically allows the position to reset once it reaches the offset value
  } else {
    position = (position + 1) % totalWidth;                        // Basically allows the position to reset once it reaches the offset value
  }
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