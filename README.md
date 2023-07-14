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

## Using different I²C bus

For normal usage of I²C device which is delived from I2C_device class, it will be like sample blelow. This intended to use `Wire` instance of Arduino SDK to access I2C, implicitly.  
(Using test_LM75B class included in this library package.)
```cpp
#include <I2C_device.h>
#include <test_LM75B.h>  //  <-- test_LM75B is just for testing purpose

test_LM75B sensor(Wire);

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;

  Serial.println("\r***** Hello, I2C_device! *****");

  Wire.begin();

  I2C_device::scan();
}

void loop() {
  Serial.println(sensor.read());
  delay(1000);
}
```

If user need to use other instance of TwoWire class (a class for Wire), it could be done like below.  
In this sample, the I²C device is connected Wire1 (It's SDA1&SCL1 pins on Arduino DUE). Wire1 should be used explisitly.  
```cpp
#include <I2C_device.h>
#include <test_LM75B.h>  //  <-- test_LM75B is just for testing purpose

//test_LM75B sensor;  //  Changed to next line
test_LM75B sensor(Wire1);

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;

   Serial.println("\r***** Hello, I2C_device! *****");

  // Wire.begin();  //  Changed to next line
  Wire1.begin();

  I2C_device::scan(Wire1, 124); //  Scan stop at 124
}

void loop() {
  Serial.println(sensor.read());
  delay(1000);
}
```

### TIPS

For more generic way to define the hardware, you can do it by compile option to detect the board and switch compile option.  
In this sample, the compiler detects type of target board and use right instance for the target.  
```cpp
#include <I2C_device.h>
#include <test_LM75B.h>  //  <-- test_LM75B is just for testing purpose

#if defined( ARDUINO_AVR_UNO ) // for Arduino UNO R3
  TwoWire& w = Wire;
  const String s = "Code is compiled for Arduino UNO R3 to use \"Wire\" instance";
#elif defined( ARDUINO_UNOR4_MINIMA ) || defined( ARDUINO_UNOR4_WIFI ) // for Arduino UNO R4
  TwoWire& w = Wire;
  const String s = "Code is compiled for Arduino UNO R4 to use \"Wire\" instance";
#elif defined( ARDUINO_SAM_DUE ) // for Arduino Due
  TwoWire& w = Wire1;
  const String s = "Code is compiled for Arduino DUE to use \"Wire1\" instance";
#else
  #error "not supported board"
#endif

test_LM75B sensor(w);

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;

  Serial.println("\r***** Hello, I2C_device! *****");
  Serial.println(s);

  w.begin();

  I2C_device::scan(w, 124);  //  Scan stop at 124
}

void loop() {
  Serial.println(sensor.read());
  delay(1000);
}
```

# References

## Related libraries
Library|Feature|Target devices|Required library
---|---|---|---
[GPIO_NXP_Arduino](https://github.com/teddokano/GPIO_NXP_Arduino)				|GPIO libraries						|PCAL6408A, PCAL6416A, PCAL6524, PCAL6534, PCA9555, PCA9554	|[I2C_device_Arduino](https://github.com/teddokano/I2C_device_Arduino)
[LCDDriver_NXP_Arduino](https://github.com/teddokano/LCDDriver_NXP_Arduino)		|LCD driver libraries				|PCA8561						|[I2C_device_Arduino](https://github.com/teddokano/I2C_device_Arduino)
[LEDDriver_NXP_Arduino](https://github.com/teddokano/LEDDriver_NXP_Arduino)		|LED driver libraries				|PCA9955B, PCA9956B, PCA9957	|[I2C_device_Arduino](https://github.com/teddokano/I2C_device_Arduino)
[MUX_SW_NXP_Arduino](https://github.com/teddokano/MUX_SW_NXP_Arduino)			|I²C mux/switch libraries			|PCA9846						|[I2C_device_Arduino](https://github.com/teddokano/I2C_device_Arduino)
[RTC_NXP_Arduino](https://github.com/teddokano/RTC_NXP_Arduino)					|RTC libraries						|PCF2131, PCF85063A				|[I2C_device_Arduino](https://github.com/teddokano/I2C_device_Arduino)
[TempSensor_NXP_Arduino](https://github.com/teddokano/TempSensor_NXP_Arduino)	|Temperature sensor libraries		|LM75B, PCT2075, P3T1085		|[I2C_device_Arduino](https://github.com/teddokano/I2C_device_Arduino)
[I2C_device_Arduino](https://github.com/teddokano/I2C_device_Arduino)			|Base library for I²C operations	|none (can be applied as base class for all I²C targets)|---
