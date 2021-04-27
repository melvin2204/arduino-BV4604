#include "BV4604.h"
#include <Wire.h>


/*!
 * @brief Instantiates a new BV4604 class.
 *
 * @param address   The I2C address of the BV4604 device
 * */
BV4604::BV4604(uint8_t address) {
    this->address = address;
    Wire.begin();
}

/*!
 *  @brief Writes multiple values to the I2C bus.
 *
 *  @param values   Array with values to be written
 *  @param length   The amount of values to be written
 * */
void BV4604::I2CWrite(uint8_t *values, uint8_t length) {
    Wire.beginTransmission(this->address);
    for (uint8_t i = 0; i < length; ++i) {
        Wire.write(values[i]);
    }
    Wire.endTransmission();
}

/*!
 * @brief Reads a single value from the I2C bus.
 *
 * @returns The value read from the bus
 * */
uint8_t BV4604::I2CRead() {
    Wire.requestFrom(this->address, (uint8_t) 1);
    return Wire.read();
}

/*!
 * @brief Reads a byte from the BV4604 EEPROM at a given address.
 *
 * @param address   Address to read from
 *
 * @returns The value read from the EEPROM
 * */
uint8_t BV4604::eepromRead(uint8_t address) {
    uint8_t commands[] = {BV4604_READ_EEPROM_COMMAND, address};
    this->I2CWrite(commands, sizeof(commands));
    return this->I2CRead();
}

/*!
 * @brief Write a byte to the BV4604 EEPROM.
 *
 * @param address   Address to write to
 * @param value     Byte value to write
 * */
void BV4604::eepromWrite(uint8_t address, uint8_t value) {
    // Check if the address already has the specified value to reduce wear.
    if (this->eepromRead(address) != value) {
        uint8_t commands[] = {BV4604_WRITE_EEPROM_COMMAND, address, value};
        this->I2CWrite(commands, sizeof(commands));
        delay(10); // Slight delay to finish writing.
    }
}

/*!
 * @brief Resets the BV4604 microcontroller. It is recommended to wait a short while after resetting.
 * */
void BV4604::reset() {
    uint8_t commands[] = {BV4604_RESET_COMMAND};
    this->I2CWrite(commands, sizeof(commands));
}

/*!
 * @brief Stops both motors.
 * */
void BV4604::stop() {
    uint8_t commands[] = {BV4604_STOP_COMMAND};
    this->I2CWrite(commands, sizeof(commands));
}

/*!
 * @brief Tests the BV4604. The only way to stop this is by a physical reset.
 * */
void BV4604::test() {
    uint8_t commands[] = {BV4604_TEST_COMMAND};
    this->I2CWrite(commands, sizeof(commands));
}

/*!
 * @brief Controls both outputs at the same time with different values.
 *
 * @param a_speed       Speed for output A (0-1023)
 * @param a_direction   Direction for output A (0,1,2)
 * @param b_speed       Speed for output B (0-1023)
 * @param b_direction   Direction for output B (0,1,2)
 * */
void BV4604::controlOutputs(uint16_t a_speed, BV4604_direction_t a_direction, uint16_t b_speed,
                            BV4604_direction_t b_direction) {
    // I2C only supports byte sized data, so the speed has to be split into two bytes.
    uint8_t hb_a, lb_a, hb_b, lb_b;
    this->splitWord(&hb_a, &lb_a, a_speed);
    this->splitWord(&hb_b, &lb_b, b_speed);

    uint8_t commands[] = {
            BV4604_OUTPUTS_COMMAND,
            hb_a,
            lb_a,
            (uint8_t) a_direction,
            hb_b,
            lb_b,
            (uint8_t) b_direction
    };

    this->I2CWrite(commands, sizeof(commands));
}

/*!
 * @brief Controls one output from the BV4604.
 *
 * @param output        Which output to select
 * @param speed         Speed for the selected output
 * @param direction     Direction for the selected output
 * */
void BV4604::controlOutput(BV4604_output_t output, uint16_t speed, BV4604_direction_t direction) {
    // I2C only supports byte sized data, so the speed has to be split into two bytes.
    uint8_t hb, lb;
    this->splitWord(&hb, &lb, speed);

    uint8_t commands[] = {
            (uint8_t) output,
            hb,
            lb,
            (uint8_t) direction
    };
    this->I2CWrite(commands, sizeof(commands));
}

/*!
 * @brief Splits a word into two bytes.
 *
 * @param hb    Pointer to High Byte result
 * @param lb    Pointer to Low Byte result
 * @param value Word to be split
 * */
void BV4604::splitWord(uint8_t *hb, uint8_t *lb, uint16_t value) {
    *hb = (value >> 8) & 0xFF;
    *lb = value & 0xFF;
}

/*!
 * @brief Set the value of the soft starter. See chapter 12.14 of the datasheet for more information.
 *
 * @param value     Value for the soft starter
 * */
void BV4604::setSoftStartValue(uint8_t value) {
    this->eepromWrite(BV4604_SOFT_START_LOCATION, value);

    // The soft start value is only applied on restart.
    this->reset();
    delay(1000); // Wait for the board to boot again.
}

/*!
 * @brief Gets the device ID.
 *
 * @returns The device ID
 * */
uint8_t BV4604::getDeviceID() {
    uint8_t commands[] = {BV4604_DEVICE_ID_COMMAND};
    this->I2CWrite(commands, sizeof(commands));
    return this->I2CRead();
}
