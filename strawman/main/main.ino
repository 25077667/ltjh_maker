#include "pitches.h" /* Header of speaker */
#include <Servo.h>   /* Header of SG90 */

#define ECHO 7                // revceiver of HC-05
#define TRIG 6                // trigger of HC-05
#define LED 16                // output the signal of state with LED
#define DISTANCE_THRESHOLD 80 // lower than 80 cm will do act
#define ROTATE_RANGE 60       // angle(degree) of shouder rotation

/**
 * Some tutorials about speaker:
 * Demo code: http://learning.cca.tw/MicroControllers/Arduino/ArduinoSPEAKER.asp
 * Arduino man page: https://www.arduino.cc/en/Tutorial/toneKeyboard
 */
#define SPEAKER 8 // output speaker at PH5 that is digital pin 8

/* Turn on the LED. */
#define LED_ON digitalWrite(LED, HIGH)

/* Turn off the LED. */
#define LED_OFF digitalWrite(LED, LOW)

Servo shoulder;

// notes in the melody:
int melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3,
                NOTE_G3, 0,       NOTE_B3, NOTE_C4};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4};

void playMelody() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    // e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(SPEAKER, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(SPEAKER);
  }
}

float getDis() {
  int distance = 0, duration = 0;
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(ECHO, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  return distance;
}

/* Wave left and right limbs randomly. */
void waveLimbs() {
  /*
   * Servo operating tutorial:
   * https://yehnan.blogspot.com/2013/09/arduinotower-pro-sg90.html
   */
  shoulder.write(ROTATE_RANGE);
  delay(300);
  shoulder.write(-ROTATE_RANGE);
  delay(300);
}

void setup() {
  Serial.begin(9600);
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(SPEAKER, OUTPUT);

  /* Init Limb */
  shoulder.attach(23);
}

void loop() {
  float a = getDis();
  float b = getDis();

  // Because there might have some noice,
  // double check(a and b) will reduce the margin error
  if (a < DISTANCE_THRESHOLD && b < DISTANCE_THRESHOLD) {
    playMelody();
    waveLimbs();
    delay(10);
  }
  Serial.println((a + b) / 2);
}
