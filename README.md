# SHT31

Arduino library for the SHT31 temperature and humidity sensor

## Description

The SHT3x family of sensors should work up to 1 MHz I2C

This library should also work for SHT30 and SHT35 but these are 
not tested yet.

| SENSOR | Temperature accuracy | Humidity accuracy |
|:----:|:----:|:----:|
| SHT30 | ~0.3 | 2 |
| SHT31 | ~0.3 | 1.5 |
| SHT35 | ~0.2 | 1.5 |


An elaborated library for the SHT31 sensor can be found here
https://github.com/hawesg/SHT31D_Particle_Photon_ClosedCube

## Interface

TODO elaborate

#### basic interface

- **SHT31()**
- **bool begin(address, dataPin, clockPin)**
- **bool begin(address)**
- **bool begin(address,  TwoWire \*wire)**
- **bool read(bool fast = true)** blocks 15 milliseconds + actual read + math
- **bool isConnected()** check senosr is reachable over I2C
- **uint16_t readStatus()** details see datasheet; summary below
- **uint32_t lastRead()** in milliSeconds since start
- **void reset(bool hard = false)**
- **getHumidity()** returns relative humidity in %
- **getTemperature()** returns temperature in °C

#### Heater interface

Do not use heater for long periods, use it for max 3 minutes to heat up
and let it cool down an equal period.

- **setHeatTimeout(uint8_t seconds)**
- **heatOn()**
- **heatOff()**
- **bool heatUp()** is the sensor still heating up?  // TODO isHeating() better.

#### Async interface

- **requestData()**
- **bool dataReady()**
- **bool readData(bool fast = true)**


## Status fields

TODO elaborate - table 
```
  // bit - description
  // ==================
  // 15 Alert pending status
  //    '0': no pending alerts
  //    '1': at least one pending alert - default
  // 14 Reserved ‘0’
  // 13 Heater status
  //    '0’ : Heater OFF - default
  //    '1’ : Heater ON
  // 12 Reserved '0’
  // 11 Humidity tracking alert
  //    '0’ : no alert - default
  //    '1’ : alert
  // 10 Temp tracking alert
  //    '0’ : no alert - default
  //    '1’ : alert
  // 9:5 Reserved '00000’
  // 4 System reset detected
  //    '0': no reset since last ‘clear status register’ command
  //    '1': reset detected (hard or soft reset command or supply fail) - default
  // 3:2 Reserved ‘00’
  // 1 Command status
  //    '0': last cmd executed successfully
  //    '1': last cmd not processed. Invalid or failed checksum
  // 0 Write data checksum status
  //    '0': checksum of last write correct
  //    '1': checksum of last write transfer failed
```

## Operation

See examples

