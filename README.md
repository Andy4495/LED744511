74'4511 BCD to 7-Segment LED Library
====================================

This library for Arduino or Energia is designed to interface with the 74'4511 BCD to Seven Segment LED driver chip.

The library supports either one or two 7-segment displays.

For a single digit, a minimum of 5 output pins are required:
   + BCD bit 3 (msb)
   + BCD bit 2
   + BCD bit 1
   + BCD bit 0 (lsb)
   + /LE (Latch Enable)
   + You can also optionally define the /LE and /BL signals

For two digit setups, a minimum of 6 output pins are required:
+ BCD bit 3 (msb)
+ BCD bit 2
+ BCD bit 1
+ BCD bit 0 (lsb)
+ /LE_1 (Latch Enable for most significant digit)
+ /LE_0 (Latch Enable for least significant digit)
+ You can also optionally define the /LE and /BL signals

Usage
-----
_See the sketch included in the `examples` folder._

First, include the library header file:

    #include "LED744511.h"

Next, create an LED object. There are multiple forms for the constructor, depending on whether you are using one or two 7-segment digits.

#### Single Digit ####

    LED744511 myLED(BCD3, BCD2, BCD1, BCD0, BCDLE);

This creates a single-digit 7-segment object which does not control the /LE or /BL pins (they are assumed to be tied high). It uses 5 output pins.

    LED744511 myLED(BCD3, BCD2, BCD1, BCD0, BCDLE, LT, BL);

This creates a single-digit 7-segment object which also controls the /LE and /BL pins. It uses 7 output pins.

#### Double Digit ####

    LED744511 myLED(BCD3, BCD2, BCD1, BCD0, BCDLE1, BCDLE0);

This creates a two-digit 7-segment object which does not control the /LE or /BL pins (they are assumed to be tied high). It uses 6 output pins. BCDLE1 is the most significant digit (tens) and BCDLE0 is the least significant digit (ones).

    LED744511 myLED(BCD3, BCD2, BCD1, BCD0, BCDLE1, BCDLE0, LT, BL);

This creates a two-digit 7-segment object which also controls the /LE and /BL pins. It uses 8 output pins.

#### Controlling the Displays ####

Once you have created an LED744511 object, the following methods can be
used to control the displays:

    void writeBCD(int value)
  Writes `value` to the display.

  Negative values blank the display.

  On a single-digit display, a positive value is displayed modulus 10. For example, a value of 22 will be displayed as 2.

  For two-digit displays, there is a mechanism to display a leading blank or leading zero for values less than 10.

  + To display a leading blank, then use a value less than 10.
  + To display a leading zero, then use a value greater than 99.

For example:
  + `value = -1` will blank both digits of the display (all segments off)
  + `value = 9` will display a leading blank and the digit 9: ` 9`
  + `value = 109` will display a leading 0 and the digit 9: `09`


        void lampTest(int onoff);
Enables or disables the /LT (Lamp Test) signal. Since it is an active-low signal, a value of 0 will turn it on, and a value of 1 will turn it off.

This function only has an effect if the LT pin was defined in the constructor.

    void blankDisplay(int onoff);
Enables or disables the /BL (Blank Display) signal. Since it is an active-low signal, a value of 0 will turn it on, and a value of 1 will turn it off.

This function only has an effect if the BL pin was defined in the constructor.

References
----------
+ [74'4511 Datasheet](http://www.ti.com/lit/ds/symlink/cd74hc4511.pdf)
