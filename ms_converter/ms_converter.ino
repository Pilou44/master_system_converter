#include <Sleep_n0m1.h>

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
  pinMode(RD, INPUT_PULLUP);
  pinMode(CE, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);

  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(CE, HIGH);
  
  outval(0x12); // DEC H
  waitRdHigh();

  outval(0x12); // DEC H
  rdSync();

  /* LD HL, $E101 */
  outval(0x10);
  rdSync();
  outval(0x00);
  rdSync();
  outval(0x70);
  rdSync();

  /* DEC H */
  outval(0x12);
  rdSync();

  /* LD SP,HL */
  outval(0x7C);
  rdSync();

  /* RST $00 */
  outval(0x63);
  rdSync();

  pinMode(CE, INPUT);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D4, INPUT);
  pinMode(D5, INPUT);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);
  
  digitalWrite(LED, 1);
  
//  sleep.pwrDownMode(); //set sleep mode
  int count = 0;
  while (1) {
//    rdSync();
//    count++;
//    count = count % 3000000;
//    if (count > 1500000) {
//      digitalWrite(LED, 1);
//    } else {
//      digitalWrite(LED, 0);
//    }

//    waitRdHigh();
//    digitalWrite(LED, 1);
//    waitRdLow();
//    digitalWrite(LED, 0);

//    if (count > 1500000) {
//      digitalWrite(LED, 1);
//    } else {
//      digitalWrite(LED, 0);
//    }

//    delay(500);
//    sleep.sleepDelay(0xffffffffL); //sleep for: max long, about 50 days
  }
}

void waitRdLow() {
  do {}
  while (digitalRead(RD) == HIGH);
}

void waitRdHigh() {
  do {}
  while (digitalRead(RD) == LOW);
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
