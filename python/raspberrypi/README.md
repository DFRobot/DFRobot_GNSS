# DFRobot_GNSS
- [中文版](./README_CN.md)

Global Navigation Satellite Systems (GNSS) provide critical timing and positioning functions for device operations.
This Gravity: GNSS positioning module from DFRobot supports both single and multiple systems positioning. It is capable of quick delivery of position data like longitude, latitude, altitude and time. Compared with traditional single GPS positioning, the multi-system combination embraces higher precision and faster speed thanks to the increased number of visible and available satellites, which ensures stable and accurate performance even in complex urban environments.

With I2C and UART data outputs, the GNSS positioning module works well with main-controllers like Arduino, ESP32, and Raspberry Pi. It is applicable to outdoor positioning scenarios such as vehicle navigation, handheld positioning tracker, item tracking and weather station

![效果图](../../resources/images/TEL0157.jpg)

## Product Link(https://www.dfrobot.com/product-2651.html)

    SKU：TEL0157

## Table of Contents

* [Summary](#Summary)
* [Installation](#Installation)
* [Methods](#Methods)
* [Compatibility](#Compatibility)
* [History](#History)
* [Credits](#Credits)

## Summary

Provide an python library for the GNSS module with the following features:
Retrieval of GNSS data
Retrieval of raw GNSS data.

## Installation
1. Download the library to Raspberry Pi first before use.

```
sudo git clone https://github.com/DFRobot/DFRobot_GNSS
```

1. Open and run the routine. To execute a routine demo_x.py, enter python demo_x.py in the command line. For example, to execute the routine get_gnss.py, you need to enter:

```
python get_gnss.py
or 
python2 get_gnss.py
or 
python3 get_gnss.py
```

## Methods

```python
  '''!
    @brief Init sensor 
  '''
  def begin(self):

  '''!
    @brief Get date information, year, month, day 
    @return struct_utc_tim type, represents the returned year, month, day 
  '''
  def get_date(self):

  '''!
    @brief Get time information, hour, minute, second 
    @return struct_utc_tim type, represents the returned hour, minute, and second 
  '''
  def get_utc(self):

  '''!
    @brief Get latitude 
    @return struct_lat_lon type, represents the returned latitude 
  '''
  def get_lat(self):

  '''!
    @brief Get longitude 
    @return struct_lat_lon type, represents the returned longitude
  '''
  def get_lon(self):

  '''!
    @brief Get the number of the used satellite  
    @return The number of the used satellite 
  '''
  def get_num_sta_used(self):

  '''!
    @brief Get altitude 
    @return double type, represents the altitude 
  '''
  def get_alt(self):

  '''!
    @brief Get course over ground 
    @return Float data(unit, degree) 
  '''
  def get_cog(self):

  '''!
    @brief Get speed over ground 
    @return speed Float data(unit, knot) 
  '''
  def get_sog(self):

  '''!
    @brief Get the used GNSS mode 
    @return mode
    @retval 1 gps
    @retval 2 beidou
    @retval 3 gps + beidou
    @retval 4 glonass
    @retval 5 gps + glonass
    @retval 6 beidou +glonass
    @retval 7 gps + beidou + glonass
  '''
  def get_gnss_mode(self):

  '''!
    @brief Set GNSS to be used 
    @param mode
    @n   GPS              use gps
    @n   BeiDou           use beidou
    @n   GPS_BeiDou       use gps + beidou
    @n   GLONASS          use glonass
    @n   GPS_GLONASS      use gps + glonass
    @n   BeiDou_GLONASS   use beidou +glonass
    @n   GPS_BeiDou_GLONASS use gps + beidou + glonass
  '''
  def set_gnss(self, mode):

  '''!
    @brief Get GNSS data 
  '''
  def get_all_gnss(self):

  '''!
    @brief enable gnss power
  '''
  def enable_power(self):

  '''!
    @brief disable gnss power, the GNSS data will not be refreshed this time 
  '''
  def disable_power(self):
  
  '''!
    @brief Turn rgb on 
  '''
  def rgb_on(self):
  
  '''!
    @brief Turn rgb off
  '''
  def rgb_off(self):
```

## Compatibility

* RaspberryPi Version

| Board        | Work Well | Work Wrong | Untested | Remarks |
| ------------ | :-------: | :--------: | :------: | ------- |
| RaspberryPi2 |           |            |    √     |         |
| RaspberryPi3 |     √     |            |          |         |
| RaspberryPi4 |           |            |    √     |         |

* Python Version

| Python  | Work Well | Work Wrong | Untested | Remarks |
| ------- | :-------: | :--------: | :------: | ------- |
| Python2 |     √     |            |          |         |
| Python3 |     √     |            |          |         |


## History

- 2022/04/02 - Version 0.0.1 released.
- 2022/10/26 - Version 1.0.0 released.

## Credits

Written by ZhixinLiu(zhixin.liu@dfrobot.com), 2022. (Welcome to our website)
