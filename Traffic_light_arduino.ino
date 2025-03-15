int red1 = 4;
int yellow1 = 3;
int green1 = 2;
int red2 = 10;
int yellow2 = 11;
int green2 = 12;
int button1_pin = 5;
int button2_pin = 6
int last_state = LOW;

int trigPin = 9;    // TRIG pin
int echoPin = 8;    // ECHO pin

float duration_us, distance_cm;

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;  // will store last time LED was updated

// constants won't change:
const long interval = 1000;  // interval at which to blink (milliseconds)

// state of the light. 0 means yellow, 1 means red, 2 means green
int state = 0;

void setup(){
    pinMode(red1, OUTPUT);
    pinMode(yellow1, OUTPUT);
    pinMode(green1,   OUTPUT);
    pinMode(button1_pin, INPUT_PULLUP);
    pinMode(red2, OUTPUT);
    pinMode(yellow2, OUTPUT);
    pinMode(green2,   OUTPUT);
    pinMode(button2_pin, INPUT_PULLUP);

    // begin serial port
  Serial.begin (9600);

  // configure the trigger pin to output mode
  pinMode(trigPin, OUTPUT);
  // configure the echo pin to input mode
  pinMode(echoPin, INPUT);
}
void loop(){
  // generate 10-microsecond pulse to TRIG pin
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

  delay(500);

  if (button1_state == LOW and distance_cm < 100) {
      timedLights();
  }
  else {
      changeLights();
  }
    

}
void timedLights(){
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval && state = 0) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    // green off, yellow on for 3 seconds
    digitalWrite(green1, LOW);
    digitalWrite(yellow1, HIGH);
    state = 1
  }

  if (currentMillis - previousMillis >= interval && state = 1) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    // turn off   yellow, then turn red on for 5 seconds
    digitalWrite(yellow1, LOW);
    digitalWrite(red1, HIGH);
    state = 2
  }

  if (currentMillis - previousMillis >= interval && state = 2) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    // turn   off red and yellow, then turn on green
    digitalWrite(yellow1, LOW);
    digitalWrite(red1,   LOW);
    digitalWrite(green1, HIGH);
    state = 0
  }
}

void changeLights(){
    digitalWrite(yellow1, LOW);
    digitalWrite(red1, LOW);
    digitalWrite(green1, HIGH);
}
