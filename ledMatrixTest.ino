byte scroll[]={
  0B11111110,
  0B11111101,
  0B11111011,
  0B11110111,
  0B11101111,
  0B11011111,
  0B10111111,
  0B01111111
  };

  byte point[]={
    0B00000001,
    0B00000010,
    0B00000100,
    0B00001000,
    0B00010000,
    0B00100000,
    0B01000000,
    0B10000000
    };

    int latchPin=11;
    int clockPin=12;
    int dataPin=9;
  
void setup() {
  // put your setup code here, to run once:
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin,clockPin,MSBFIRST,scroll[i]);
      shiftOut(dataPin,clockPin,MSBFIRST,point[j]);
      digitalWrite(latchPin,HIGH);
      delay(100);
      }
      }
}
