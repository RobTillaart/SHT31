#include <ArduinoUnitTests.h>

#include "Arduino.h"
#include "SHT31.h"

unittest(test_begin)
{
  SHT31 sht;

  bool b = sht.begin(0x44);
  assertEqual(b, true);

  Serial.println(sht.getTemperature());
 
  // default value == 0
  assertEqual(0, sht.getTemperature());
  assertEqual(0, sht.getHumidity());

}

unittest_main()

// --------