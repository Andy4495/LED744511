/* Library to interface with 74'4511 BCD to 7-segment LED driver chip.

   https://gitlab.com/Andy4495/LED744511

   The library supports either 1 or 2 7-segment displays.
   For a single digit, a minimum of 5 output pins are required:
      BCD bits 3-0 and /LE.
      You can also optionally define the /LE and /BL signals.
   For two digit setups, a minimum of 6 output pins are required:
      BCD bits 3-0, /LE for each of the two digits
      You can also optionally define the /LE and /BL signals.
*/
/* Version History
   1.0.0    03/28/2018  A.T.   Original
*/

#include "LED744511.h"


// Single digit constructors
LED744511::LED744511(int bcd3, int bcd2, int bcd1, int bcd0, int LE) {
  init(bcd3, bcd2, bcd1, bcd0, NO_PIN, LE, NO_PIN, NO_PIN);
}

LED744511::LED744511(int bcd3, int bcd2, int bcd1, int bcd0, int LE, int LT, int BL) {
  init(bcd3, bcd2, bcd1, bcd0, NO_PIN, LE, LT, BL);
}

// Dual digit constructors
LED744511::LED744511(int bcd3, int bcd2, int bcd1, int bcd0, int LE_1, int LE_0) {
  init(bcd3, bcd2, bcd1, bcd0, LE_1, LE_0, NO_PIN, NO_PIN);
}

LED744511::LED744511(int bcd3, int bcd2, int bcd1, int bcd0, int LE_1, int LE_0, int LT, int BL) {
  init(bcd3, bcd2, bcd1, bcd0, LE_1, LE_0, LT, BL);
}

void LED744511::init(int bcd3, int bcd2, int bcd1, int bcd0, int LE_1, int LE_0, int LT, int BL) {
  bcd3_pin  = bcd3;
  bcd2_pin  = bcd2;
  bcd1_pin  = bcd1;
  bcd0_pin  = bcd0;
  LE_pin[1] = LE_1;
  LE_pin[0] = LE_0;
  LT_pin    = LT;
  BL_pin    = BL;

  // Make sure that the control signals are disabled during initialization
  if (LE_pin[1] != NO_PIN) {
    digitalWrite(LE_pin[1], HIGH);
    pinMode(LE_pin[1], OUTPUT);
  }
  if (LE_pin[0] != NO_PIN) {
    digitalWrite(LE_pin[0], HIGH);
    pinMode(LE_pin[0], OUTPUT);
  }
  if (LT_pin != NO_PIN) {
    digitalWrite(LT_pin, HIGH);
    pinMode(LT_pin, OUTPUT);
  }
  if (BL_pin != NO_PIN) {
    digitalWrite(BL_pin, HIGH);
    pinMode(BL_pin, OUTPUT);
  }
  // Set up the BCD data pins
  pinMode(bcd3_pin, OUTPUT);
  pinMode(bcd2_pin, OUTPUT);
  pinMode(bcd1_pin, OUTPUT);
  pinMode(bcd0_pin, OUTPUT);
}

void LED744511::writeBCD(int value) {
  // 2 digit displays:
  //   values between 10 and 99 inclusive: display normally
  //   values < 10: display leading blank digit
  //   values > 100: display leading '0' digit
  //   values < 0: blank display (all segments off)
  // 1 digit displays:
  //   values >= 0: display value (modulus 10)
  //   values < 0: blank display (all segments off)
  if (LE_pin[1] != NO_PIN) {             // 2 LED digits defined
    // Values between 10 and 99 includes print normally
    if ((value < 100) && (value > 9)) {
      writeDigit(1, value/10);
    }
    // Values < 10 or negative values print a blank leading digit
    if ((value < 10) || (value < 0)) {
      writeDigit(1, LED744511::BLANK_DIGIT);
    }
    // Values > 99 print a zero leading digit, regardless of 10's value
    if (value > 99) {
      writeDigit(1, 0);
    }
  }
  // Least significant digit: blank display if < 0
  if (value < 0) writeDigit(0, LED744511::BLANK_DIGIT);
  else writeDigit(0, value%10);
}

void LED744511::lampTest(int onoff) {
  if (LT_pin != NO_PIN) {
    pinMode(LT_pin, onoff);
  }
}

void LED744511::blankDisplay(int onoff) {
  if (BL_pin != NO_PIN) {
    pinMode(BL_pin, onoff);
  }
}

void LED744511::writeDigit(int digit, int n) {
  digitalWrite(bcd3_pin, (n >> 3) & 1);
  digitalWrite(bcd2_pin, (n >> 2) & 1);
  digitalWrite(bcd1_pin, (n >> 1) & 1);
  digitalWrite(bcd0_pin,  n       & 1);
  digitalWrite(LE_pin[digit], LOW);
  digitalWrite(LE_pin[digit], HIGH);
}
