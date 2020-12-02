[![Arduino CI](https://github.com/robtillaart/SHT31/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)

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

#### Base interface

- **SHT31()**  constructor.
- **begin(address, dataPin, clockPin)** begin function for ESP8266 & ESP32;
returns false if device address is incorrect.
- **begin(address)** for single I2C bus platforms, e.g UNO.
- **begin(address,  TwoWire \*wire)** for platforms with multiple I2C busses.
- **read(bool fast = true)** blocks 15 milliseconds + actual read + math
- **isConnected()** check sensor is reachable over I2C. Returns false if not connected.
- **uint16_t readStatus()** details see datasheet and **Status fields** below
- **uint32_t lastRead()** in milliSeconds since start of program.
- **reset(bool hard = false)** resets the sensor, soft reset by default.
- **getHumidity()** returns relative humidity in %
- **getTemperature()** returns temperature in °C


#### Heater interface

Use the heater for max **180** seconds, and let it cool down an equal period of time.

**WARNING:** Do not use heater for long periods.

**WARNING:** The user is responsible to switch the heater off manually! 
The class does **NOT** do this automatically.

- **setHeatTimeout(uint8_t seconds)** Set the time out of the heat cycle.
This value is truncated to max 180 seconds. 
- **heatOn()** switches heat cycle on.
- **heatOff()** switches  heat cycle off.
- **isHeaterOn()** is the sensor still in heating cycle? replaces **heatUp()**.
Will switch heat off if max heating time has passed. 
- **heatUp()** will be obsolete in the future.

#### Async interface

See async example for usage

- **requestData()** requests a new measurement.
- **dataReady()** checks if enough time has passed to read the data. (15 millis)
- **readData(bool fast = true)** fast skips CRC check.


## Status fields

| BIT | Description | values |
|:----:|:----|:----|
| 15  | Alert pending status | '0': no pending alerts|
|     |                      | '1': at least one pending alert - default |
| 14  | Reserved | '0' |
| 13  | Heater status  | '0’ : Heater OFF - default |
|     |                | '1’ : Heater ON |
| 12  | Reserved | '0' |
| 11  | Humidity tracking alert | '0’ : no alert - default |
|     |                         | '1’ : alert |
| 10  | Temperature tracking alert | '0’ : no alert - default |
|     |                            | '1’ : alert |
| 9-5 | Reserved | '00000' |
|  4  | System reset detected  | '0': no reset since last ‘clear status register’ command |
|     |                        | '1': reset detected (hard or soft reset command or supply fail) - default |
| 3-2 | Reserved | '00' |
|  1  | Command status | '0': last cmd executed successfully |
|     |                | '1': last cmd not processed. Invalid or failed checksum |
| 0   | Write data checksum status | '0': checksum of last write correct |
|     |                            | '1': checksum of last write transfer failed |

## Operation

See examples

