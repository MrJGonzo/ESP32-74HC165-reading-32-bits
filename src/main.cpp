#include <Arduino.h>

//Pin connected to ST_CP of 74HC595 PIN 12 --> 74HC165 SR PIN 15.
int latchPin = 19;
//Pin connected to SH_CP of 74HC595 PIN 11 --> 74HC165 SR PIN 2.
int clockPin = 21;
//Pin connected to DS of 74HC595 PIN 14
int dataPin = 23;
//Pin connected to DS of 74HC165 PIN 9
int dataInput = 22;      

int clockEnablePin = 5;

u_int32_t incoming = 0B00000000000000000000000000000000;

byte a = 0B00000000;
byte b = 0B00000000;
byte c = 0B00000000;
byte d = 0B00000000;

void setup() {

  // Setup Serial Monitor
  Serial.begin(9600);

  // Setup 74HC165 connections
  pinMode(latchPin, OUTPUT);
  //pinMode(clockEnablePin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataInput, INPUT);
  pinMode(clockEnablePin, LOW);
}

void loop() {

  // Write pulse to load pin
  digitalWrite(latchPin, LOW);
  delayMicroseconds(5);
  digitalWrite(latchPin, HIGH);
  delayMicroseconds(5);

  // Get data from 74HC165
  digitalWrite(clockPin, LOW);

  a = shiftIn(dataInput, clockPin, LSBFIRST);
  b = shiftIn(dataInput, clockPin, LSBFIRST);
  c = shiftIn(dataInput, clockPin, LSBFIRST);
  d = shiftIn(dataInput, clockPin, LSBFIRST);

  Serial.print("byte a: ");
  Serial.println(a, BIN);
  Serial.print("byte b: ");
  Serial.println(b, BIN);
  Serial.print("byte c: ");
  Serial.println(c, BIN);
  Serial.print("byte d: ");
  Serial.println(d, BIN);

  Serial.print("Reading:");
  incoming = a | b << 8 | c << 16 | d << 24;
  Serial.println(incoming, BIN);
  
  delay(1000);

}

