#include <I2C_device.h>
#include <test_LM75B.h>  //  <-- test_LM75B is just for testing purpose

#if defined( ARDUINO_AVR_UNO ) // for Arduino Uno
  TwoWire& w = Wire;
  const String s = "Code is compiled for Arduino Uno to use \"Wire\" instance";
#elif defined( ARDUINO_SAM_DUE ) // for Arduino Due
  TwoWire& w = Wire1;
  const String s = "Code is compiled for Arduino Due to use \"Wire1\" instance";
#else
  #error "not supported board"
#endif

test_LM75B sensor(w);

void setup() {
  w.begin();
  Serial.begin(9600);
  Serial.println("\r***** Hello, I2C_device! *****");
  Serial.println(s);

  I2C_device::scan(w, 124);  //  Scan stop at 124
}

void loop() {
  Serial.println(sensor.read());
  delay(1000);
}
