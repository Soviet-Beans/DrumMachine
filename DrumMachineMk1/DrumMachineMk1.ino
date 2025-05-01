//#include "Adafruit_LEDBackpack.h"
//Adafruit_7segment display = Adafruit_7segment();

int loopLength = 8;
int bpm = 120;
int drumLoop[32];
int selected = 0;

void setup() {
  //display.begin(112);
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);

  for(int i = 0; i < 32; i++) {
    drumLoop[i] = 0;
    Serial.println("");
  }

  initPrint();
}

void loop() {
  int a = analogRead(A5);
  int b = analogRead(A4);
  int c = analogRead(A3);
  if(a > 0) {
    setLoopLength(a);
  }
  
  else if(b > 0) {
    setBpm(b);
  }

  else if(c > 0) {
    sequencerInputInterpreter(c);
  }
  
  delay(160);
}

void setLoopLength(int buttonIn) {
  if(buttonIn < 500 && loopLength < 32) {
    loopLength++;
  }
  else if(buttonIn > 500 && loopLength > 1) {
    loopLength--;
  }
  loopLengthTest();
}

void setBpm(int buttonIn) {
  if(buttonIn < 500) {
    bpm++;
  }
  else if(buttonIn > 500) {
    bpm--;
  }
  bpmTest();
}

void sequencerInputInterpreter(int buttonIn) {
  if(buttonIn > 178 - 50 && buttonIn < 178 + 50 && selected > 0) {
    selected--;
  }
  else if(buttonIn < 178 - 50) {
    drumLoop[selected] = 0;
  }
  else if(buttonIn > 294 - 50 && buttonIn < 294 + 50) {
    drumLoop[selected] = 1;
  }
  else if(buttonIn > 375 - 50 && buttonIn < 375 + 50) {
    drumLoop[selected] = 2;
  }
  else if(buttonIn > 482 - 50 && buttonIn < 482 + 50) {
    drumLoop[selected] = 3;
  }
  else if(buttonIn > 587 - 50 && buttonIn < 587 + 50) {
    drumLoop[selected] = 4;
  }
  else if(buttonIn > 675 - 50 && buttonIn < 675 + 50 && selected < 31 && selected < loopLength - 1) {
    selected++;
  }
  sequencerLightUpdater(drumLoop[selected]);
  selectedTest();
}

void sequencerLightUpdater(int selected) {
  if(selected == 0) {
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
  }
  
  else if(selected == 1) {
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
  }

  else if(selected == 2) {
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
  }

  else if(selected == 3) {
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(10, LOW);
  }

  else if(selected == 4) {
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, HIGH);
  }
}
// Test Methods
void printLine() {
  Serial.println();
}

template <typename T, typename... Types>
void printLine(T first, Types... other) {
  Serial.print(first);
  printLine(other...);
}

void initPrint() {
  selectedTest();
  loopLengthTest();
  bpmTest();
}

void selectedTest() {
  printLine("selected ", selected + 1);
  printLine("sample ", drumLoop[selected]);
}

void loopLengthTest() {
  printLine("loop length ", loopLength);
}

void bpmTest() {
  printLine("bpm ", bpm);
}

void drumLoopTest() {
  for(int i = 0; i < 32; i++) {
      printLine(i, " ", drumLoop[i]);
    }
}
