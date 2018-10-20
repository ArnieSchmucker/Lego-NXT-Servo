byte enPin = 9;
byte in1Pin = 10;
byte in2Pin = 11;
byte interruptPin = 2;

int count = 0;
int ncount = 0;
void setup() {
  Serial.begin(9600);
  pinMode(enPin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
}
 
void loop() {
  Serial.println("Duration of new case:");
  while (Serial.available() == 0){}
  ncount = Serial.parseInt();
  if (ncount > 0) {
    DriveCW(ncount);
  } else if (ncount < 0) {
    DriveCCW(abs(ncount));
  }
}

void DriveCW(int ncount) {
  attachInterrupt(0, ISR_count, FALLING);
  while(count <= ncount){
    if (ncount > 0) {
      digitalWrite(enPin, HIGH);
      digitalWrite(in1Pin, HIGH);
      digitalWrite(in2Pin, LOW);
    } 
  }
  detachInterrupt(0);
  count=0;
  digitalWrite(enPin, LOW);
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
}

void DriveCCW(int ncount) {
  ncount = abs(ncount);
  attachInterrupt(0, ISR_count, FALLING);
  while(count <= ncount){
    if (ncount > 0) {
      digitalWrite(enPin, HIGH);
      digitalWrite(in1Pin, LOW);
      digitalWrite(in2Pin, HIGH);
    } 
  }
  detachInterrupt(0);
  count=0;
  digitalWrite(enPin, LOW);
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
}



void ISR_count(){
  count++;
}

