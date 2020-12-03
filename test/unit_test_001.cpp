//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2020-12-03
// PURPOSE: unit tests for the SHT31 temperature and humidity sensor
//          https://github.com/RobTillaart/SHT31
//          https://www.adafruit.com/product/2857
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// ----------------------------
// assertEqual(expected, actual)
// assertNotEqual(expected, actual)
// assertLess(expected, actual)
// assertMore(expected, actual)
// assertLessOrEqual(expected, actual)
// assertMoreOrEqual(expected, actual)
// assertTrue(actual)
// assertFalse(actual)
// assertNull(actual)

/*
  most unit tests will test for fail 
  as there is no sensor connected
  and there is no mockup.
*/

#include <ArduinoUnitTests.h>

#include "Arduino.h"
#include "SHT31.h"


unittest_setup()
{
}

unittest_teardown()
{
}

unittest(test_begin)
{
  SHT31 sht;

  bool b = sht.begin(0x44);
  assertEqual(b, true);

  assertFalse(sht.reset());

  Serial.println(sht.getTemperature());
  Serial.println(sht.getHumidity());

  // default value == 0
  assertEqual(0, sht.getTemperature());
  assertEqual(0, sht.getHumidity());

}

unittest(test_read)
{
  SHT31 sht;
  bool b = sht.begin(0x44);
  assertEqual(b, true);

  assertFalse(sht.isConnected());
  assertEqual(SHT31_ERR_NOT_CONNECT, sht.getError());

  assertFalse(sht.read());
  assertEqual(SHT31_OK, sht.getError());

  assertFalse(sht.read(false));
  assertEqual(SHT31_OK, sht.getError());

  assertFalse(sht.read(true));
  assertEqual(SHT31_OK, sht.getError());
  
}

unittest(test_readStatus)
{
  SHT31 sht;
  bool b = sht.begin(0x44);
  assertEqual(b, true);
  
  assertEqual(0xFFFF, sht.readStatus());
  assertEqual(SHT31_ERR_NOT_CONNECT, sht.getError());
}

unittest(test_heater)
{
  SHT31 sht;
  bool b = sht.begin(0x44);
  assertEqual(b, true);
  
  assertFalse(sht.heatOn());
  assertEqual(SHT31_OK, sht.getError());

  assertTrue(sht.heatOff());
  assertEqual(SHT31_OK, sht.getError());

  assertFalse(sht.isHeaterOn());
  assertEqual(SHT31_OK, sht.getError());
}

unittest(test_async)
{
  SHT31 sht;
  bool b = sht.begin(0x44);
  assertEqual(b, true);
  
  assertFalse(sht.requestData());
  assertEqual(SHT31_OK, sht.getError());

  assertFalse(sht.dataReady());
  assertEqual(SHT31_OK, sht.getError());

  assertFalse(sht.readData());
  assertEqual(SHT31_ERR_READBYTES, sht.getError());

  assertFalse(sht.readData(true));
  assertEqual(SHT31_ERR_READBYTES, sht.getError());

  assertFalse(sht.readData(false));
  assertEqual(SHT31_ERR_READBYTES, sht.getError());
}

unittest_main()

// --------