#include <stdio.h>

#define CLOCK_PIN 2
#define RESET_BUTTON 3
#define RW_PIN 52
#define LCD_EN 50
#define ROM_EN 42
#define RAM_EN 46

#define HALT_ADDR 0xff69

uint8_t ADDR_PINS[16] = {
  53,
  51,
  49,
  47,
  45,
  43,
  41,
  39,
  37,
  35,
  33,
  31,
  29,
  27,
  25,
  23
};

uint8_t DATA_PINS[8] = {
  36,
  34,
  32,
  30,
  28,
  26,
  24,
  22
};

bool executing = false;

void on_clock() {
  if (digitalRead(RESET_BUTTON) == LOW) {
    executing = true;
  }

  if (executing && digitalRead(RESET_BUTTON) == HIGH) {
    uint16_t addr = 0;
    uint8_t  data = 0;

    for (int i = 0; i < 16; i++) {
      if (digitalRead( ADDR_PINS[i] ) == HIGH) {
        addr |= (1 << i);
      }
    }

    for (int i = 0; i < 8; i++) {
      if (digitalRead( DATA_PINS[i] ) == HIGH) {
        data |= (1 << i);
      }
    }

    char msg[128];

    snprintf(msg, 128, "%04hx %s %02hhx %hhd%hhd%hhd",
      addr,
      digitalRead(RW_PIN) ? "r":"W",
      data,
      digitalRead(LCD_EN),
      !digitalRead(ROM_EN),
      !digitalRead(RAM_EN)
    );

    Serial.println(msg);

    if (addr == HALT_ADDR) {
      executing = false;
    }
  }
}

void setup() {
  Serial.begin(2000000);

  pinMode(CLOCK_PIN, INPUT);

  pinMode(RESET_BUTTON, INPUT);

  pinMode(RW_PIN, INPUT);
  pinMode(VIA_EN, INPUT);
  pinMode(RAM_EN, INPUT);
  pinMode(ROM_EN, INPUT);

  for (int i = 0; i < 16; i++) {
    pinMode( ADDR_PINS[i], INPUT);
  }

  for (int i = 0; i < 8; i++) {
    pinMode( DATA_PINS[i], INPUT );
  }

  attachInterrupt(digitalPinToInterrupt(CLOCK_PIN), on_clock, RISING);
}

void loop() {
}
