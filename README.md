# Arduino-BV4604
This is an Arduino library that interfaces with the BV4604 motor driver board by ByVac.

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

# Datasheet
https://www.byvac.com/downloads/datasheets/BV4603_4%20DataSheet.pdf
