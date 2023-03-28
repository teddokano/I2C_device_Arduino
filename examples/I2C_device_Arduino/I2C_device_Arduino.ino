/** I2C_device class operation sample using tiny test_LM75B class
 *  
 *  This sample code is showing I2C_device operation with test_LM75B.
 *  I2C_device is a abstraction class for I2C devices. So it cannot be used as itself. 
 *  In this sample code, the I2C_device is used as base class of test_LM75B. 
 *  The sample code performns the LM75B temperature sensor access using I2C_device methods and its class method: I2C_device::scan()
 *
 *  @author  Tedd OKANO
 *  @version 0.1
 *  @date    29-Mar-2023
 *
 *  Released under the MIT license License
 */

#include <I2C_device.h>
#include <test_LM75B.h>  //  <-- test_LM75B is just for testing purpose

test_LM75B sensor;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("\r***** Hello, I2C_device! *****");

  I2C_device::scan();

  float temp = sensor.read();
  
  sensor.thresholds(temp + 1, temp + 2);
  sensor.os_mode(test_LM75B::INTERRUPT);
}

void loop() {
  Serial.println(sensor.read());
  delay(1000);
}
