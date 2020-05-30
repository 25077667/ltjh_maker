#include "pitches.h" /* Header of speaker */
#include <Servo.h>   /* Header of SG90 */

#define DOPPLER 15; // input of DOPPLER sensor(RCWL-0516) at PH3
#define LED 16;     // output the signal of state with LED

/**
 * Some tutorials about speaker:
 * Demo code: http://learning.cca.tw/MicroControllers/Arduino/ArduinoBuzzer.asp
 * Arduino man page: https://www.arduino.cc/en/Tutorial/toneKeyboard
 */
#define SPEAKER 17; // output speaker at PH5 that is digital pin 8

/* Turn on the LED. */
#define LED_ON digitalWrite(LED, HIGH)

/* Turn off the LED. */
#define LED_OFF digitalWrite(LED, LOW)

typedef struct _arm {
  Servo elbow, shoulder;
} ARM;

typedef struct _limb {
  ARM left, right;
} LIMB;

LIMB limbs;

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

/* Return "true" if senced something moved(in 5~7m). */
bool getDopplerMoved() { return (digitalRead(SPEAKER) == HIGH); }

/* Wave left and right limbs randomly. */
void waveLimbs() {
  /*
   * Servo operating tutorial:
   * https://yehnan.blogspot.com/2013/09/arduinotower-pro-sg90.html
   */
  limbs.left.elbow.write(random(180));
  limbs.left.shoulder.write(random(180));
  limbs.right.elbow.write(random(180));
  limbs.right.shoulder.write(random(180));
}

void setup() {
  pinMode(DOPPLER, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(SPEAKER, OUTPUT);

  /* Init Limb */
  limbs.left.elbow.attach(23);
  limbs.left.shoulder.attach(24);
  limbs.right.elbow.attach(25);
  limbs.right.shoulder.attach(26);
}

void loop() {}