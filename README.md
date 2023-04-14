# I2C_device_Arduino
An I²C utility class for [Arduino](https://www.arduino.cc) 

# What is this?
An Arduino library for I²C device operations.  
This is an abstraction class which can be used for all I²C devices to manage its access in register access level.  

On addition to the device abstraction, it provides method `ping()` and `scan()` as class methods.  

See `test_LM75B.cpp` and `test_LM75B.h` as a sample for how the sub-class can be derived to make actual device supporting class. 

# Document
Details of the library is provided in [this document](https://teddokano.github.io/I2C_device_Arduino/md__r_e_a_d_m_e.html).

# Example
An example code is available using test_LM75B class which is included in this library distribution.  
It performs 
1. Scan of I²C bus. Result is shown as a table (executed by `I2C_device::scan()`)
1. temperature reading from LM75B and its compatible device and showing result in every second. 

# References

## Related libraries
Library|Feature|Target devices|Required library
---|---|---|---
[GPIO_NXP_Arduino](https://github.com/teddokano/GPIO_NXP_Arduino)				|LED driver libraries				|PCAL6408A, PCAL6416A, PCAL6524, PCAL6534	|[I2C_device_Arduino](https://github.com/teddokano/I2C_device_Arduino)
[LEDDriver_NXP_Arduino](https://github.com/teddokano/LEDDriver_NXP_Arduino)		|LED driver libraries				|PCA9955B, PCA9956B, PCA9957	|[I2C_device_Arduino](https://github.com/teddokano/I2C_device_Arduino)
[RTC_NXP_Arduino](https://github.com/teddokano/RTC_NXP_Arduino)					|RTC driver libraries				|PCF2131, PCF85063A				|[I2C_device_Arduino](https://github.com/teddokano/I2C_device_Arduino)
[TempSensor_NXP_Arduino](https://github.com/teddokano/TempSensor_NXP_Arduino)	|Temperature sensor libraries		|LM75B, PCT2075, P3T1085		|[I2C_device_Arduino](https://github.com/teddokano/I2C_device_Arduino)
[I2C_device_Arduino](https://github.com/teddokano/I2C_device_Arduino)			|Base library for I²C operations	|none (can be applied as base class for all I²C targets)|---
