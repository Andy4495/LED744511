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
#ifndef LED744511_H
#define LED744511_H

#include <Arduino.h>

class LED744511 {
public:
  // Single digit constructors
  LED744511(int bcd3, int bcd2, int bcd1, int bcd0, int LE);
  LED744511(int bcd3, int bcd2, int bcd1, int bcd0, int LE, int LT, int BL);

  // Dual digit constructors
  LED744511(int bcd3, int bcd2, int bcd1, int bcd0, int LE_1, int LE_0);
  LED744511(int bcd3, int bcd2, int bcd1, int bcd0, int LE_1, int LE_0, int LT, int BL);

  void writeBCD(int value);
  void lampTest(int onoff);
  void blankDisplay(int onoff);

  enum {NO_PIN=255};

private:
  enum {BLANK_DIGIT=10};   // Per 74'4511 datasheet, BCD 10 -> Blank segments
  int bcd3_pin;
  int bcd2_pin;
  int bcd1_pin;
  int bcd0_pin;
  int LE_pin[2];
  int LT_pin;
  int BL_pin;

  void init(int bcd3, int bcd2, int bcd1, int bcd0, int LE_1, int LE_0, int LT, int BL);
  void writeDigit(int value, int digit);
};

#endif
