//
//    FILE: SHT31_async.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo async interface
//     URL: https://github.com/RobTillaart/SHT31


#include "Wire.h"
#include "SHT31.h"

#define SHT31_ADDRESS   0x44

uint32_t start;
uint32_t stop;
uint32_t cnt;

SHT31 sht;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SHT31_LIB_VERSION: \t");
  Serial.println(SHT31_LIB_VERSION);

  Wire.begin();
  sht.begin(SHT31_ADDRESS);
  Wire.setClock(100000);

  uint16_t stat = sht.readStatus();
  Serial.print(stat, HEX);
  Serial.println();
  
  sht.requestData();
  cnt = 0;
}


void loop()
{
  uint16_t rawTemperature;
  uint16_t rawHumidity;

  if (sht.dataReady())
  {
    start = micros();
    bool success  = sht.readData();   // default = true = fast
    stop = micros();
    sht.requestData();                // request for next sample

    Serial.print("\t");
    Serial.print(stop - start);
    Serial.print("\t");
    if (success == false)
    {
      Serial.println("Failed read");
    }
    else
    {
      rawTemperature = sht.getRawTemperature();
      rawHumidity = sht.getRawHumidity();
      Serial.print(rawTemperature, HEX);
      Serial.print(" = ");
      Serial.print(rawTemperature * (175.0 / 65535) - 45, 1); // This formula comes from page 14 of the SHT31 datasheet
      Serial.print("°C\t");
      Serial.print(sht.getRawHumidity(), HEX);
      Serial.print(" = ");
      Serial.print(rawHumidity * (100.0 / 65535), 1); // This formula comes from page 14 of the SHT31 datasheet
      Serial.print("%\t");
      Serial.println(cnt);
      cnt = 0;
    }
  }
  cnt++; // simulate other activity
}


// -- END OF FILE --

