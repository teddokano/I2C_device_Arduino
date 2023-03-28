# I2C_device_Arduino
An I²C utility class for [Arduino](https://www.arduino.cc) 

# What is this?
An Arduino library for I²C device operations.  
This is an abstraction class which can be used for all I²C devices to manage its access in register access level.  

On addition to the device abstraction, it provides method `ping()` and `scan()` as class methods.  

See `test_LM75B.cpp` and `test_LM75B.h` as a sample for how the sub-class can be derived to make actual device supporting class. 

## Example
An example code is available using test_LM75B class which is included in this library distribution.  
It performs 
1. Scan of I²C bus. Result is shown as a table (executed by `I2C_device::scan()`)
1. temperature reading from LM75B and its compatible device and showing result in every second. 
