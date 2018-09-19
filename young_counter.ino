#include <SevSeg.h>

#define D0 0
#define D1 1
#define D2 2
#define D3 3
#define PIN_D0 5
#define PIN_D1 4
//#define PIN_D2 3
//#define PIN_D3 2
//#define DIGITS 4
//const int digits[DIGITS] = { PIN_D0, PIN_D1, PIN_D2, PIN_D3 };
#define DIGITS 2
const int digits[DIGITS] = { PIN_D0, PIN_D1 };

#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define PIN_A 7
#define PIN_B 8
#define PIN_C 9
#define PIN_D 10
#define PIN_E 11
#define PIN_F 12
#define PIN_G 13
#define SEGS 7
const int segs[SEGS] = { PIN_A, PIN_B, PIN_C, PIN_D, PIN_E, PIN_F, PIN_G };

void setup() {
    for (int i = 0; i < DIGITS; i++) {
        pinMode(digits[i], OUTPUT);
    }
    for (int i = 0; i < SEGS; i++) {
        pinMode(segs[i], OUTPUT);
    }

    off();
}

void loop() {
    for (int i = 0; i < 100; i++) {
        time = millis();
        while (millis() < (time+1000)) {
            numbers(i);
        }
    }
}

void numbers(int number) {
    int val_D0 = number % 10;
    int val_D1 = number % 100;
    int val_D2 = number % 1000;
    int val_D3 = number % 10000;

    number(D0, val_D0);
    number(D1, val_D1);
    number(D2, val_D2);
    number(D3, val_D3);
}

void number(int digit, int number) {
    reset_digits();
    reset_segs();
    digitalWrite(digits[digit], HIGH);

    switch(number) {
        case 1: one(digit); break;
        case 2: two(digit); break;
        case 3: three(digit); break;
        case 4: four(digit); break;
        case 5: five(digit); break;
        case 6: six(digit); break;
        case 7: seven(digit); break;
        case 8: eight(digit); break;
        case 9: nine(digit); break;
        default: zero(digit); break;
    }

    delay(5);
    reset_digits();
    reset_segs();
}

void zero(int digit) {
    digitalWrite(segs[A], HIGH);
    digitalWrite(segs[B], HIGH);
    digitalWrite(segs[C], HIGH);
    digitalWrite(segs[D], HIGH);
    digitalWrite(segs[E], HIGH);
    digitalWrite(segs[F], HIGH);
}
void one(int digit) {
    digitalWrite(segs[B], HIGH);
    digitalWrite(segs[C], HIGH);
}
void two(int digit) {
    digitalWrite(segs[A], HIGH);
    digitalWrite(segs[B], HIGH);
    digitalWrite(segs[D], HIGH);
    digitalWrite(segs[E], HIGH);
    digitalWrite(segs[G], HIGH);
}
void three(int digit) {
    digitalWrite(segs[A], HIGH);
    digitalWrite(segs[B], HIGH);
    digitalWrite(segs[C], HIGH);
    digitalWrite(segs[D], HIGH);
    digitalWrite(segs[G], HIGH);
}
void four(int digit) {
    digitalWrite(segs[B], HIGH);
    digitalWrite(segs[C], HIGH);
    digitalWrite(segs[F], HIGH);
    digitalWrite(segs[G], HIGH);
}
void five(int digit) {
    digitalWrite(segs[A], HIGH);
    digitalWrite(segs[C], HIGH);
    digitalWrite(segs[D], HIGH);
    digitalWrite(segs[F], HIGH);
    digitalWrite(segs[G], HIGH);
}
void six(int digit) {
    digitalWrite(segs[A], HIGH);
    digitalWrite(segs[C], HIGH);
    digitalWrite(segs[D], HIGH);
    digitalWrite(segs[E], HIGH);
    digitalWrite(segs[F], HIGH);
    digitalWrite(segs[G], HIGH);
}
void seven(int digit) {
    digitalWrite(segs[A], HIGH);
    digitalWrite(segs[B], HIGH);
    digitalWrite(segs[C], HIGH);
}
void eight(int digit) {
    digitalWrite(segs[A], HIGH);
    digitalWrite(segs[B], HIGH);
    digitalWrite(segs[C], HIGH);
    digitalWrite(segs[D], HIGH);
    digitalWrite(segs[E], HIGH);
    digitalWrite(segs[F], HIGH);
    digitalWrite(segs[G], HIGH);
}
void nine(int digit) {
    digitalWrite(segs[A], HIGH);
    digitalWrite(segs[B], HIGH);
    digitalWrite(segs[C], HIGH);
    digitalWrite(segs[F], HIGH);
    digitalWrite(segs[G], HIGH);
}

void on() {
    for (int i = 0; i < DIGITS; i++) {
        digitalWrite(digits[i], HIGH);
    }
    for (int i = 0; i < SEGS; i++) {
        digitalWrite(segs[i], HIGH);
    }
}
void off() {
    reset_digits();
    reset_segs();
}
void reset_digits() {
    for (int i = 0; i < DIGITS; i++) {
        digitalWrite(digits[i], LOW);
    }
}
void reset_segs() {
    for (int i = 0; i < SEGS; i++) {
        digitalWrite(segs[i], LOW);
    }
}
