#include <Sleep_n0m1.h>

// PORTB = D8 to D13
// PORTC = A0 to A7
// PORTD = D0 to D7

#define RD 12 // Rename OE
#define CE 11
#define D1 2
#define D2 3
#define D3 4
#define D4 5
#define D5 6
#define D6 7
#define D7 8
#define LED 13

Sleep sleep;


void setup() {
  // put your setup code here, to run once:
//  pinMode(RD, INPUT_PULLUP);
//  pinMode(CE, OUTPUT);
//  pinMode(D1, OUTPUT);
//  pinMode(D2, OUTPUT);
//  pinMode(D3, OUTPUT);
//  pinMode(D4, OUTPUT);
//  pinMode(D5, OUTPUT);
//  pinMode(D6, OUTPUT);
//  pinMode(D7, OUTPUT);
//
//  pinMode(LED, OUTPUT);
  DDRB = B00101001;
  DDRD = 0xFC;
}

void loop() {
  // put your main code here, to run repeatedly:
//  digitalWrite(CE, HIGH);
  PORTB = B00101000; // Force CE high on the cart $$ LED on

//  outval(0x12); // DEC H
// PORTB = CE & RD pullup = B00011000, PORTD = 0x12 << 2 = 0x48
  outval(0x48, B00111000); // DEC H
  waitRdHigh();

  digitalWrite(LED, 1);

//  outval(0x12); // DEC H
// PORTB = CE & RD pullup = B00011000, PORTD = 0x12 << 2 = 0x48
  outval(0x48, B00111000); // DEC H
  rdSync();

  /* LD HL, $E101 */
//  outval(0x10);
// PORTB = CE & RD pullup = B00011000, PORTD = 0x10 << 2 = 0x40
  outval(0x40, B00111000); // DEC H
  rdSync();
//  outval(0x00);
// PORTB = CE & RD pullup = B00011000, PORTD = 0x00 << 2 = 0x00
  outval(0x00, B00111000); // DEC H
  rdSync();
//  outval(0x70);
// PORTB = CE & RD pullup & 0x01 = B00011001, PORTD = 0x70 << 2 = 0xC0
  outval(0xC0, B00111001); // DEC H
  rdSync();

  /* DEC H */
//  outval(0x12);
// PORTB = CE & RD pullup = B00011000, PORTD = 0x12 << 2 = 0x48
  outval(0x48, B00111000); // DEC H
  rdSync();

  /* LD SP,HL */
//  outval(0x7C);
// PORTB = CE & RD pullup & 0x01 = B00011001, PORTD = 0x7C << 2 = 0xF0
  outval(0xF0, B00111001); // DEC H
  rdSync();

  /* RST $00 */
//  outval(0x63);
// PORTB = CE & RD pullup & 0x01 = B00011001, PORTD = 0x63 << 2 = 0x8C && LED OFF
  outval(0x8C, B00011001); // DEC H
  rdSync();

//  pinMode(CE, INPUT);
//  pinMode(D1, INPUT);
//  pinMode(D2, INPUT);
//  pinMode(D3, INPUT);
//  pinMode(D4, INPUT);
//  pinMode(D5, INPUT);
//  pinMode(D6, INPUT);
//  pinMode(D7, INPUT);
   DDRD = 0;
   DDRB = 0;
  
  digitalWrite(LED, 0);
  
//  sleep.pwrDownMode(); //set sleep mode
  while (1) {
//    sleep.sleepDelay(0xffffffffL); //sleep for: max long, about 50 days
  }
}

void waitRdLow() {
  do {}
//  while (digitalRead(RD) == HIGH);
  while (PINB & 0x10);
}

void waitRdHigh() {
  do {}
//  while (digitalRead(RD) == LOW);
  while (!PINB & 0x10);
}

void rdSync() {
  waitRdLow();
  waitRdHigh();
}

void outval(byte value) {
  digitalWrite(D1, (value & 0x01) > 0);
  digitalWrite(D2, (value & 0x02) > 0);
  digitalWrite(D3, (value & 0x04) > 0);
  digitalWrite(D4, (value & 0x08) > 0);
  digitalWrite(D5, (value & 0x10) > 0);
  digitalWrite(D6, (value & 0x20) > 0);
  digitalWrite(D7, (value & 0x40) > 0);
}

void outval(byte portD, byte portB) {
  PORTB = portB;
  PORTD = portD;
}
