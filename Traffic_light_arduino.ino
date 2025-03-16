int red1 = 4;
int yellow1 = 3;
int green1 = 2;
int red2 = 10;
int yellow2 = 9;
int green2 = 8;
int button1_pin = 5;
int button2_pin = 11;
int last_state = LOW;

int trigPin = 6;    // TRIG pin
int echoPin = 7;    // ECHO pin
int trigPin2 = 1;    // TRIG pin
int echoPin2 = 2;    // ECHO pin

float duration_us, distance_cm;

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;  // will store last time LED was updated
unsigned long previousMillis2 = 0;  // will store last time LED was updated

// constants won't change:
const long interval0 = 3000;  // interval at which to blink (milliseconds)
const long interval1 = 1000;
const long interval2 = 5000;
const long interval3 = 3000;  // interval at which to blink (milliseconds)
const long interval4 = 1000;
const long interval5 = 5000;
// state of the light. 0 means yellow, 1 means red, 2 means green
int state = 0;
int state2 = 2;

bool isGreen1 = false; 
bool isRed1 = false;
bool isRed2 = false;

void setup(){
    pinMode(red1, OUTPUT);
    pinMode(yellow1, OUTPUT);
    pinMode(green1,   OUTPUT);
    pinMode(button1_pin, INPUT_PULLUP);
    pinMode(red2, OUTPUT);
    pinMode(yellow2, OUTPUT);
    pinMode(green2, OUTPUT);
    pinMode(button2_pin, INPUT_PULLUP);

    // begin serial port
  Serial.begin (9600);

  // configure the trigger pin to output mode
  pinMode(trigPin, OUTPUT);
  // configure the echo pin to input mode
  pinMode(echoPin, INPUT);
  // configure the trigger pin to output mode
  pinMode(trigPin2, OUTPUT);
  // configure the echo pin to input mode
  pinMode(echoPin2, INPUT);
}
unsigned long priorsensorMillis = millis();

void loop(){
  // generate 10-microsecond pulse to TRIG pin
  unsigned long currsensorMillis = millis();

  if (currsensorMillis - priorsensorMillis >= 500) {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(echoPin, HIGH);

  // calculate the distance
  distance_cm = 0.017 * duration_us;

  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  priorsensorMillis = millis();
  }


  int button1_state = digitalRead(button1_pin);
  int button2_state = digitalRead(button2_pin);
  if (button1_state == HIGH && state != 1 && distance_cm > 10) {
      changeLights();
  }
  else if (button2_state == HIGH && state2 != 1 && distance_cm > 10){
    changeLights2();
  }
  else{
      timedLights();
  }

}
void timedLights(){
  // checks time in order to time the light changes
  unsigned long currentMillis = millis();

  //handles first traffic light
  if (currentMillis - previousMillis >= interval0 && state == 0) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    // green off, yellow on for 3 seconds
    digitalWrite(green1, LOW);
    digitalWrite(yellow1, HIGH);
    isGreen1 = false;
    state = 1;
  }

  if (currentMillis - previousMillis >= interval1 && state == 1) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    // turn off   yellow, then turn red on for 5 seconds
    digitalWrite(yellow1, LOW);
    digitalWrite(red1, HIGH);
    digitalWrite(green1, LOW);
    isRed1 = true;
    state = 2;
  }

  if (currentMillis - previousMillis >= interval2 && state == 2) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    // turn   off red and yellow, then turn on green
    digitalWrite(yellow1, LOW);
    digitalWrite(red1,   LOW);
    digitalWrite(green1, HIGH);
    isGreen1 = true;
    isRed1 = false;
    state = 0;
  }

  // handles second traffic light

  if (currentMillis - previousMillis2 >= interval3 && state2 == 0) {
    // save the last time you blinked the LED
    previousMillis2 = currentMillis;
    // green off, yellow on for 3 seconds
    digitalWrite(green2, LOW);
    digitalWrite(yellow2, HIGH);
    state2 = 1;
  }

  if (currentMillis - previousMillis2 >= interval4 && state2 == 1) {
    // save the last time you blinked the LED
    previousMillis2 = currentMillis;
    // turn off   yellow, then turn red on for 5 seconds
    digitalWrite(yellow2, LOW);
    digitalWrite(red2, HIGH);
    digitalWrite(green2, LOW);
    isRed2 = true;
    state2 = 2;
  }

  if (currentMillis - previousMillis2 >= interval5 && state2 == 2) {
    // save the last time you blinked the LED
    previousMillis2 = currentMillis;
    // turn   off red and yellow, then turn on green
    digitalWrite(yellow2, LOW);
    digitalWrite(red2, LOW);
    digitalWrite(green2, HIGH);
    isRed2 = false;
    state2 = 0;
  }

}

void changeLights(){
    // checks time in order to time the light changes
  unsigned long currentMillis = millis();

  if (isRed2){
    digitalWrite(yellow1, LOW);
    digitalWrite(red1, LOW);
    digitalWrite(green1, HIGH);
    // makes state so the light stays green after button is released
    state = 2;      
  }
  

  if (currentMillis - previousMillis2 >= interval3 && !isRed2) {
    // save the last time you blinked the LED
    previousMillis2 = currentMillis;
    // green off, yellow on for 3 seconds
    digitalWrite(green2, LOW);
    digitalWrite(yellow2, HIGH);
    state2 = 1;
  }

  if (currentMillis - previousMillis2 >= interval4 && state2 == 1) {
    // save the last time you blinked the LED
    isRed2 = true;
    previousMillis2 = currentMillis;
    // turn off   yellow, then turn red on for 5 seconds
    digitalWrite(yellow2, LOW);
    digitalWrite(red2, HIGH);
    digitalWrite(green2, LOW);
    // makes state so the light stays red after button is released
    state2 = 1;
  }
} 
void changeLights2(){
  // checks time in order to time the light changes
  unsigned long currentMillis = millis();

  if (isRed1){
    digitalWrite(yellow2, LOW);
    digitalWrite(red2, LOW);
    digitalWrite(green2, HIGH);
    // makes state so the light stays green after button is released
    state2 = 2;      
  }
  

  if (currentMillis - previousMillis >= interval0 && !isRed1) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    // green off, yellow on for 3 seconds
    digitalWrite(green1, LOW);
    digitalWrite(yellow1, HIGH);
    state = 1;
  }

  if (currentMillis - previousMillis >= interval4 && state == 1) {
    // save the last time you blinked the LED
    isRed1 = true;
    previousMillis = currentMillis;
    // turn off   yellow, then turn red on for 5 seconds
    digitalWrite(yellow1, LOW);
    digitalWrite(red1, HIGH);
    digitalWrite(green1, LOW);
    // makes state so the light stays red after button is released
    state = 1;
  }
}
