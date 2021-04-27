/*
 * This example will change the driver mode to mode 0. This is necessary for this library to work.
 * */

// Replace this with the address of your BV4604 board. Use the Wire i2c_scanner example to find this address.
#define BV4604_ADDRESS (0x31)

#include <BV4604.h>

BV4604 motor(BV4604_ADDRESS);

void setup() {
    Serial.begin(115200);

    if (motor.eepromRead(20) == 0) {
        Serial.println("Your board is already in mode 0 and can be used by this library.");
    } else {
        motor.eepromWrite(20, 0);
        delay(100);
        motor.reset();
        delay(1000);
        Serial.println("Your board is now correctly configured to be used by this library.");
    }
}

void loop() {}
