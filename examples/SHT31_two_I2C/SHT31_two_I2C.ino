//
//    FILE: SHT31_two_I2C.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/SHT31


#include "Wire.h"
#include "SHT31.h"

// TwoWire myWire(&sercom5, 16, 17); 
TwoWire myWire = Wire1;    

#define SHT31_ADDRESS_1   0x44
#define SHT31_ADDRESS_2   0x45
#define SHT31_ADDRESS_3   0x44
#define SHT31_ADDRESS_4   0x45


SHT31 sht_1;
SHT31 sht_2;
SHT31 sht_3;
SHT31 sht_4;

bool b1, b2, b3, b4;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SHT31_LIB_VERSION: \t");
  Serial.println(SHT31_LIB_VERSION);

  Wire.begin();
  Wire.setClock(100000);
  Wire1.begin();
  Wire1.setClock(100000);

  b1 = sht_1.begin(SHT31_ADDRESS_1, &Wire);
  b2 = sht_2.begin(SHT31_ADDRESS_2, &Wire);
  b3 = sht_3.begin(SHT31_ADDRESS_3, &myWire);
  b4 = sht_4.begin(SHT31_ADDRESS_4, &myWire);

  // see if they are connected
  Serial.print("BEGIN:\t");
  Serial.print(b1);
  Serial.print("\t");
  Serial.print(b2);
  Serial.print("\t");
  Serial.print(b3);
  Serial.print("\t");
  Serial.print(b4);
  Serial.print("\t");
  Serial.println();
}


void loop()
{
  // read all that are found
  if (b1) sht_1.read();
  if (b2) sht_2.read();
  if (b3) sht_3.read();
  if (b4) sht_4.read();

  Serial.print(sht_1.getTemperature(), 1);
  Serial.print("\t");
  Serial.print(sht_2.getTemperature(), 1);
  Serial.print("\t");
  Serial.print(sht_3.getTemperature(), 1);
  Serial.print("\t");
  Serial.print(sht_4.getTemperature(), 1);
  Serial.print("\t");
  Serial.print(sht_1.getHumidity(), 1);
  Serial.print("\t");
  Serial.print(sht_2.getHumidity(), 1);
  Serial.print("\t");
  Serial.print(sht_3.getHumidity(), 1);
  Serial.print("\t");
  Serial.print(sht_4.getHumidity(), 1);
  Serial.println();
  
  delay(1000);
}

// -- END OF FILE --
