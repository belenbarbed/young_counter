// Button library: https://github.com/madleech/Button
#include <Button.h>
#include <EEPROM.h>

// Digit-controlling pins
// D3 D2 : D1 D0
#define D0 0
#define D1 1
#define D2 2
#define D3 3
#define PIN_D0 2
#define PIN_D1 3
#define PIN_D2 4
#define PIN_D3 5
#define DIGITS 4
const int digits[DIGITS] = { PIN_D0, PIN_D1, PIN_D2, PIN_D3 };

// 7-seg controlling pins:
//     a
//    ----
//  f| g  | b
//    ----
//  e|    | c
//    ----
//     d
#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define PIN_A 10
#define PIN_B 9
#define PIN_C 8
#define PIN_D 7
#define PIN_E 6
#define PIN_F 12
#define PIN_G 11
#define SEGS 7
const int segs[SEGS] = { PIN_A, PIN_B, PIN_C, PIN_D, PIN_E, PIN_F, PIN_G };

// Buttons
#define PIN_COUNT A1
#define PIN_RESET A0
Button countButton(PIN_COUNT);
Button resetButton(PIN_RESET);

// Counter & EEPROM
#define COUNT_ADDR 0
int counter = 0;

void setup() {
    Serial.begin(9600);
    countButton.begin();
    resetButton.begin();

    // Set counter value to start where it
    // was before it turned off
    EEPROM.get(COUNT_ADDR, counter);

    // Initialise pin outputs
    for (int i = 0; i < DIGITS; i++) {
        pinMode(digits[i], OUTPUT);
    }
    for (int i = 0; i < SEGS; i++) {
        pinMode(segs[i], OUTPUT);
    }
    off();
}

void loop() {
    if (countButton.pressed()) {
        counter = counter + 1;
        EEPROM.put(COUNT_ADDR, counter);
    }
    if ((resetButton.pressed()) || (counter > 9999)) {
        counter = 0;
        EEPROM.put(COUNT_ADDR, 0);
    }

    digitsController(counter);
}

void digitsController(int number) {
    int val_D0 = number % 10;
    int val_D1 = (number % 100)/10;
    int val_D2 = (number % 1000)/100;
    int val_D3 = (number % 10000)/1000;

    digitController(D0, val_D0);
    digitController(D1, val_D1);
    digitController(D2, val_D2);
    digitController(D3, val_D3);
}

void digitController(int digit, int number) {
    off();
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

    // Turn on LEDs for a short period of time
    // then move on to next digit
    // this way we control one digit at a time
    // (can't do more) but on average all digits
    // appear lit up
    delay(3);
    off();
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
    for (int i = 0; i < DIGITS; i++) {
        digitalWrite(digits[i], LOW);
    }
    for (int i = 0; i < SEGS; i++) {
        digitalWrite(segs[i], LOW);
    }
}
