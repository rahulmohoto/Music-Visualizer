#include "fix_fft.h"

#define CLOCK 3
#define LATCH 4
#define DATA 5

#define SAMPLES 32 //define according to your need

#define AUDIO A0

char im[SAMPLES];
char data[SAMPLES];
int barht[SAMPLES];

int binary[] = {1, 2, 4, 8, 16, 32, 64, 128};
int columnBinary[] = {1, 2, 4, 8, 16, 32, 64, 128};

void setup()
{
  pinMode(CLOCK,OUTPUT);
  pinMode(LATCH,OUTPUT);
  pinMode(DATA,OUTPUT);
}

void loop()
{
  static int i, j;
  int val;
  
  // get audio data
  for(i = 0; i < SAMPLES; i++)
  {
    val = analogRead(AUDIO); // 0-1023
    data[i] = (char)(val/4 - SAMPLES); // store as char
    im[i] = 0; // init all as 0
  }

  // run FFT
  fix_fft(data, im, 5, 0); //2^5=32, as we are taking 32 samples

  // extract absolute value of data only, for 32 results
  for(i = 0; i < SAMPLES/2; i++)
  {
    barht[i] = (int)sqrt(data[i] * data[i] + im[i] * im[i]);
  }
  
  for(i = 0, j = 0; i < SAMPLES/2; i++, j += 2)
  {
    barht[i] = barht[j] + barht[j + 1];
  }

  // display barchart
  for(int k = 0; k < SAMPLES/4; k++){ //as we have 8rows and 8columns, so only 8 times we need to iterate. That's why 32/4=8 .
    digitalWrite(LATCH, LOW);
    int x = columnBinary[barht[k]%8]-1;
    shiftOut(DATA, CLOCK, LSBFIRST, ~x); // columns
    shiftOut(DATA, CLOCK, LSBFIRST, binary[k]); // rows
    digitalWrite(LATCH, HIGH);
    }
} 
