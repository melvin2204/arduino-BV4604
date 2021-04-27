/*
 * This example will drive both motors in one direction, stop it, and then turn it the other direction.
 * */

// Replace this with the address of your BV4604 board. Use the Wire i2c_scanner example to find this address.
#define BV4604_ADDRESS (0x31)

#include <BV4604.h>

BV4604 motor(BV4604_ADDRESS);

void setup() {
    Serial.begin(115200);
}

void loop() {
    motor.controlOutputs(1023, FORWARDS, 1023, FORWARDS);

    delay(2500);

    motor.stop();

    delay(2500);

    motor.controlOutputs(1023, BACKWARDS, 1023, BACKWARDS);

    delay(2500);
}
