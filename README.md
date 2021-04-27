# Arduino-BV4604
This is an Arduino library that interfaces with the BV4604 motor driver board by ByVac.

# Important
By default this board is configured to be used with stepper motors.
This library does only support DC motors. 
To use the full potential of this library,
it is strongly advised to change the mode of operation of this board. 
To correctly configure this board, run the `changeToMode0` example sketch from the Arduino IDE before using this library.

# Compatibility
This library should work on any Arduino board that supports the Wire I2C library. 
However, it has only been tested on the ATmega328 (Nano/Uno).

# Documentation
The documentation for every method is described in the [source code](BV4604.cpp) itself. 

# Installation
Download this repository as a .zip file and uncompress it. Rename the extracted folder to **BV4604**.
Directly inside this folder you should see the BV4604.h, BV4604_registers.h and the BV4604.cpp files. 
Install the library by placing this folder inside the libraries folder. 
This folder is located in the Arduino install location (usally in Program files (x86)/Arduino). 
You may need to create this folder if this is your first time installing a library.

Read more about installing libraries in this tutorial by Adafruit: https://learn.adafruit.com/arduino-tips-tricks-and-techniques/arduino-libraries

# Usage
To use this library, first complete the installation steps and restart the Arduino IDE.
Then connect the BV4604 to your Arduino as specified below:
* +L to 3.3/5V
* GND to Ground on Arduino and external power source for motors.
* SDA to SDA on Arduino
* SCL to SCL on Arduino
* +M to a power source for your motors.

After everything is connected, choose one of the examples to run from the Arduino IDE and press upload.

# Datasheet
https://www.byvac.com/downloads/datasheets/BV4603_4%20DataSheet.pdf
