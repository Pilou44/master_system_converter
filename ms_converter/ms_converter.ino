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
 * V1.1 Mapping
 *
 * PORTD:
 * D1 -> D2
 * D2 -> D3
 * D3 -> D4
 * D4 -> D5
 * D5 -> D6
 * D6 -> D7
 *
 * PORTB:
 * D7 -> D8
 * CE -> D11
 * RD -> D12 // Rename OE
 * LED -> D13
 */

#define WAIT_RD() do { } while (PIND & 0x10)
#define WAIT_RD_HIGH()  do { } while (!(PIND & 0x10))
#define OUTVAL(a,b) do { PORTD = a; PORTB = b | B00111000; } while(0)
#define RD_SYNC() do { WAIT_RD(); WAIT_RD_HIGH(); } while(0)

void setup() {
  DDRB = B00101001; // D8, D11 and D13 outputs
  DDRD = 0xFC; // D2 to D7 outputs
}

void loop() {
  PORTB = B00111000; // Force CE high on the cart && LED on

  /* DEC H */
  /* PORTB = CE & RD pullup = B00011000, PORTD = 0x12 << 2 = 0x48 */
  OUTVAL(0x48, 0x00); // DEC H
  WAIT_RD_HIGH();

  /* DEC H */
  /* PORTB = CE & RD pullup = B00011000, PORTD = 0x12 << 2 = 0x48 */
  OUTVAL(0x48, 0x00); // DEC H
  RD_SYNC();

  /* LD HL, $E101 */
  /* PORTB = CE & RD pullup = B00011000, PORTD = 0x10 << 2 = 0x40 */
  OUTVAL(0x40, 0x00); // DEC H
  RD_SYNC();
  /* PORTB = CE & RD pullup = B00011000, PORTD = 0x00 << 2 = 0x00 */
  OUTVAL(0x00, 0x00); // DEC H
  RD_SYNC();
  /* PORTB = CE & RD pullup & 0x01 = B00011001, PORTD = 0x70 << 2 = 0xC0 */
  OUTVAL(0xC0, 0x01); // DEC H
  RD_SYNC();

  /* DEC H */
  /* PORTB = CE & RD pullup = B00011000, PORTD = 0x12 << 2 = 0x48 */
  OUTVAL(0x48, 0x00); // DEC H
  RD_SYNC();

  /* LD SP,HL */
  /* PORTB = CE & RD pullup & 0x01 = B00011001, PORTD = 0x7C << 2 = 0xF0 */
  OUTVAL(0xF0, 0x01); // DEC H
  RD_SYNC();

  /* RST $00 */
  /* PORTB = CE & RD pullup & 0x01 = B00011001, PORTD = 0x63 << 2 = 0x8C && LED OFF */
  OUTVAL(0x8C, 0x01); // DEC H
  RD_SYNC();

  DDRD = 0; // Inputs
  DDRB = 0; // Inputs
  
  while (1) {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_cpu();
  }
}
