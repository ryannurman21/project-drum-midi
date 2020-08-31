#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

#define SNARETHRESHOLD 20
#define TOM1THRESHOLD  20
#define TOM3THRESHOLD  20
#define KICKTHRESHOLD  20
#define HIHATTHRESHOLD  20
#define CYMBAL3THRESHOLD  20

unsigned long snareInterval       = 10;
unsigned long previousSnareMillis = 0;
unsigned long tom1Interval        = 10;
unsigned long previousTom1Millis  = 0;
unsigned long tom3Interval       = 10;
unsigned long previousTom3Millis = 0;
unsigned long kickInterval       = 10;
unsigned long previousKickMillis = 0;
unsigned long hihatInterval       = 10;
unsigned long previousHihatMillis = 0;
unsigned long cymbal3Interval       = 10;
unsigned long previousCymbal3Millis = 0;

int snarePin  = A0;
int tom1Pin = A1;
int tom3Pin = A2;
int kickPin = A3;
int hihatPin = A4;
int cymbal3Pin = A5;

int snareValue = 0;
int tom1Value = 0;
int tom3Value = 0;
int kickValue = 0;
int hihatValue = 0;
int cymbal3Value = 0;

// MAPPING FOR ADDICTIVE DRUMS
byte KICK                  = 36;
byte SNARE_RIMCLICK        = 44;
byte SNARE_SHALLOW_HIT     = 43;
byte SNARE_SIDESTICK       = 42;
byte SNARE_SHALLOW_RIMSHOT = 41;
byte SNARE_FLAM_HIT        = 40;
byte SNARE_FLAM_RIM        = 39;
byte SNARE_OPEN_HIT        = 38;
byte SNARE_RIMSHOT         = 37;
byte HIHAT_PEDAL_OPEN      = 59;
byte HIHAT_OPEN_BELL       = 58;
byte HIHAT_OPEN_D          = 57;
byte HIHAT_OPEN_C          = 56;
byte HIHAT_OPEN_B          = 55;
byte HIHAT_OPEN_A          = 54;
byte HIHAT_CLOSED_BELL     = 53;
byte HIHAT_CLOSED2_SHAFT   = 52;
byte HIHAT_CLOSED2_TIP     = 51;
byte HIHAT_CLOSED1_SHAFT   = 50;
byte HIHAT_CLOSED1_TIP     = 49;
byte HIHAT_PEDAL_CLOSED    = 48;
byte EXTRA                 = 47;
byte TOM1_RIMSHOT          = 72;
byte TOM1_HIT              = 71;
byte TOM2_RIMSHOT          = 70;
byte TOM2_HIT              = 69;
byte TOM3_RIMSHOT          = 68;
byte TOM3_HIT              = 67;
byte TOM4_RIMSHOT          = 68;
byte TOM4_HIT              = 67;
byte CYMBAL1              = 77;
byte CYMBAL2              = 79;
byte CYMBAL3              = 81;

void setup() {
  MIDI.begin();
  Serial.begin(115200);
}

boolean noteReady(unsigned long previousMillis, unsigned long interval) {
  if((unsigned long)(millis() - previousMillis) >= interval) {
    return true;
  }
  else {
    return false;
  }
}

void hitNote(int value, byte note, int multiply, int treshold) {
  int velocity = value - treshold;
  
  if(velocity > 127)
    velocity = 127;
  else if(velocity < 0)
    velocity = 0;
  
  MIDI.sendNoteOn(note, velocity, 1);
  MIDI.sendNoteOff(note, 0, 1);
}

void loop() {
  snareValue = analogRead(snarePin);
  tom1Value = analogRead(tom1Pin);
  tom3Value = analogRead(tom3Pin);
  kickValue  = analogRead(kickPin);
  hihatValue = analogRead(hihatPin);
  cymbal3Value = analogRead(cymbal3Pin);
  
  if(snareValue >= SNARETHRESHOLD && noteReady(previousSnareMillis, snareInterval)) {
    previousSnareMillis = millis();
    hitNote(snareValue, SNARE_OPEN_HIT, 1, SNARETHRESHOLD);
  }
  
  if(tom1Value >= TOM1THRESHOLD && noteReady(previousTom1Millis, tom1Interval)) {
    previousTom1Millis = millis();
    hitNote(tom1Value, TOM1_RIMSHOT, 1, TOM1THRESHOLD);
  }

  if(tom3Value >= TOM3THRESHOLD && noteReady(previousTom3Millis, tom3Interval)) {
    previousTom3Millis = millis();
    hitNote(tom3Value, TOM3_RIMSHOT, 1, TOM3THRESHOLD);
  }

  if(kickValue >= KICKTHRESHOLD && noteReady(previousKickMillis, kickInterval)) {
    previousKickMillis = millis();
    hitNote(kickValue, KICK, 5, KICKTHRESHOLD);
  }
  if(hihatValue >= HIHATTHRESHOLD && noteReady(previousHihatMillis, hihatInterval)) {
    previousHihatMillis = millis();
    hitNote(hihatValue, HIHAT_OPEN_A, 1, HIHATTHRESHOLD);
  }

  if(cymbal3Value >= CYMBAL3THRESHOLD && noteReady(previousCymbal3Millis, cymbal3Interval)) {
    previousCymbal3Millis = millis();
    hitNote(cymbal3Value, CYMBAL3, 1, CYMBAL3THRESHOLD);
  }
}
