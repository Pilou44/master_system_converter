#include <Sleep_n0m1.h>

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

Sleep sleep;


void setup() {
  DDRB = B00101001; // D8, D9 and D13 outputs
  DDRD = 0xFC; // D2 to D7 outputs
  // ToDo input pull-up on RD ?
}

void loop() {
  PORTB = B00101000; // Force CE high on the cart && LED on

  /* DEC H */
  /* PORTB = CE & RD pullup = B00011000, PORTD = 0x12 << 2 = 0x48 */
  outval(0x48, B00111000); // DEC H
  waitRdHigh();

  /* DEC H */
  /* PORTB = CE & RD pullup = B00011000, PORTD = 0x12 << 2 = 0x48 */
  outval(0x48, B00111000); // DEC H
  rdSync();

  /* LD HL, $E101 */
  /* PORTB = CE & RD pullup = B00011000, PORTD = 0x10 << 2 = 0x40 */
  outval(0x40, B00111000); // DEC H
  rdSync();
  /* PORTB = CE & RD pullup = B00011000, PORTD = 0x00 << 2 = 0x00 */
  outval(0x00, B00111000); // DEC H
  rdSync();
  /* PORTB = CE & RD pullup & 0x01 = B00011001, PORTD = 0x70 << 2 = 0xC0 */
  outval(0xC0, B00111001); // DEC H
  rdSync();

  /* DEC H */
  /* PORTB = CE & RD pullup = B00011000, PORTD = 0x12 << 2 = 0x48 */
  outval(0x48, B00111000); // DEC H
  rdSync();

  /* LD SP,HL */
  /* PORTB = CE & RD pullup & 0x01 = B00011001, PORTD = 0x7C << 2 = 0xF0 */
  outval(0xF0, B00111001); // DEC H
  rdSync();

  /* RST $00 */
  /* PORTB = CE & RD pullup & 0x01 = B00011001, PORTD = 0x63 << 2 = 0x8C && LED OFF */
  outval(0x8C, B00011001); // DEC H
  rdSync();

  DDRD = 0; // Inputs
  DDRB = 0; // Inputs
  
//  sleep.pwrDownMode(); //set sleep mode
  while (1) {
//    sleep.sleepDelay(0xffffffffL); //sleep for: max long, about 50 days
  }
}

void waitRdLow() {
  do {}
  while (PINB & 0x10);
}

void waitRdHigh() {
  do {}
  while (!PINB & 0x10);
}

void rdSync() {
  waitRdLow();
  waitRdHigh();
}

void outval(byte portD, byte portB) {
  PORTB = portB;
  PORTD = portD;
}
