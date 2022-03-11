# two-potentiometers-on-one-digital-input
How-to: Connect two potentiometers to one digital (MCU) input.

By applying frequency modulation (FM) and pulse width modulation (PWM) at the same time it is possible to transmit two data signals on one carrier.

The circuit used is a classic opamp-based triangle generator followed by a comparator. With the given component values the frequency is adjustable from 250 Hz up to 500 Hz while the pulse width can be adjusted from 10% up to 90%. Any circuit capable of producing a frequency- and pulse width modulated signal can be used.
![220152-elektor-schematic](https://github.com/ClemensAtElektor/two-potentiometers-on-one-digital-input/blob/main/220152-001-full.png)
The positions of the two potentiometers are encoded in the output signal. A microcontroller can decode the signal and extract the two variables. Two Arduino sketches are povided to decode the modulated rectangle wave. One uses polling, the other interrupts. The potentiometer positions are output as a percentage from 0 to 100.

Here is a [video](https://youtu.be/OXt8EQwODsc) showing how things work.
