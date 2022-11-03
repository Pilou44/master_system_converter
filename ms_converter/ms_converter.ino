#include <avr/sleep.h>

/**
 * Values to write:
 * 21 01 E1 : LD HL, $E101
 * 25 -- -- : DEC H
 * F9 -- -- : LD SP,HL
 * C7 -- -- : RST $00
 * 01 01 -- : LD BC, $xx01
 *
 * data 0 is always high and can be pulled high using a resitor.
 * Values with >>1
 * 0x10 0x00 0x70 0x12 0x7C 0x63
 *
 * Arduino port mapping:
 * PORTB = D8 to D13
 * PORTC = A0 to A7
 * PORTD = D0 to D7
 *
 * V2.0 Mapping
 *
 * PORTC:
 * D1 -> A0
 * D2 -> A1
 * D3 -> A2
 * D4 -> A3
 * D5 -> A4
 * D6 -> A5
 * D7 -> A6
 * D8 -> A7
 *
 * PORTD:
 * CE -> D2
 * RD -> D3 // Rename OE
 *
 * PORTB:
 * LED -> D13
 */

#define WAIT_RD()  do { } while (PIND & 0x08)
#define WAIT_RD_HIGH()  do { } while (!(PIND & 0x08))
#define RD_SYNC() do { WAIT_RD(); WAIT_RD_HIGH(); } while(0)

void setup() {
  DDRC = 0xFF; // All outputs
  DDRB = B00100000; // D13 outputs
  DDRD = B00000100; // D2 outputs
}

void loop() {
  PORTD = B00000110; // Force CE high on the cart & RD pullup
  PORTB = B00100000; // LED on

  /* DEC H */
  PORTC = 0x12; // DEC H
  WAIT_RD_HIGH();

  /* DEC H */
  PORTC = 0x12; // DEC H
  RD_SYNC();

  /* LD HL, $E101 */
  PORTC = 0x10; // DEC H
  RD_SYNC();
  PORTC = 0x00; // DEC H
  RD_SYNC();
  PORTC = 0x70; // DEC H
  RD_SYNC();

  /* DEC H */
  PORTC = 0x12; // DEC H
  RD_SYNC();

  /* LD SP,HL */
  PORTC = 0x7C; // DEC H
  RD_SYNC();

  /* RST $00 */
  PORTC = 0x63; // DEC H
  RD_SYNC();

  DDRC = 0; // Inputs
  DDRD = 0; // Inputs

  PORTB = 0x00; // LED off

  while (1) {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_cpu();
  }
}
