#ifndef _ARDUINO_BV4604_H_
#define _ARDUINO_BV4604_H_

#include <Arduino.h>
#include "BV4604_registers.h"

typedef enum {FORWARDS=1, STOP=0, BACKWARDS=2} BV4604_direction_t;
typedef enum {OUTPUT_A=1,OUTPUT_B=2} BV4604_output_t;

class BV4604 {
public:
    BV4604(uint8_t address);
    uint8_t eepromRead(uint8_t address);
    void eepromWrite(uint8_t address, uint8_t value);
    void reset();
    void stop();
    void test();
    void controlOutputs(
            uint16_t a_speed,
            BV4604_direction_t a_direction,
            uint16_t b_speed,
            BV4604_direction_t b_direction
            );
    void controlOutput(BV4604_output_t output, uint16_t speed, BV4604_direction_t direction);
    void setSoftStartValue(uint8_t value);
    uint8_t getDeviceID();

private:
    uint8_t address;
    void I2CWrite(uint8_t *values, uint8_t length);
    uint8_t I2CRead();
    void splitWord(uint8_t *hb, uint8_t *lb, uint16_t value);
};

#endif //_ARDUINO_BV4604_H_
