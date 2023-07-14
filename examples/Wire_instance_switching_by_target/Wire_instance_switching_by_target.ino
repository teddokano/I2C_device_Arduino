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
