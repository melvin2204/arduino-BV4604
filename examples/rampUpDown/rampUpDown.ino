/*
 * This example will ramp up motor A and then ramp it down.
 * */

// Replace this with the address of your BV4604 board. Use the Wire i2c_scanner example to find this address.
#define BV4604_ADDRESS (0x31)

#include <BV4604.h>

BV4604 motor(BV4604_ADDRESS);

void setup() {
    Serial.begin(115200);

    motor.controlOutput(OUTPUT_A, 1023, FORWARDS);
}

void loop() {
    for (int i = 0; i < 1024; ++i) {
        motor.controlOutput(OUTPUT_A, i, FORWARDS);
        delay(2);
    }

    for (int i = 1023; i >= 0; --i) {
        motor.controlOutput(OUTPUT_A, i, FORWARDS);
        delay(2);
    }
}
