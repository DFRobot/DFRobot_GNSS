/*!
 * @file DFRobot_GNSS.h
 * @brief Define the basic structure of the DFRobot_GNSS class, the implementation of the basic methods
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [ZhixinLiu](zhixin.liu@dfrobot.com)
 * @version V1.0
 * @date 2023-03-07
 * @url https://github.com/DFRobot/DFRobot_GNSS
 */
#ifndef __DFRobot_GNSS_H__
#define __DFRobot_GNSS_H__

#include <Arduino.h>
#include <Wire.h>

#if defined(ARDUINO_AVR_UNO) || defined(ESP8266)
#include "SoftwareSerial.h"
#else
#include "HardwareSerial.h"
#endif

/**
 * @struct sTim_t
 * @brief Store the time and date information obtained from GPS 
 */
typedef struct {
  uint16_t year;
  uint8_t month;
  uint8_t date;
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
}sTim_t;

/**
 * @struct sLonLat_t
 * @brief Store latitude, longitude and direction information obtained from GPS 
 */
typedef struct {
  uint8_t lonDDD;
  uint8_t lonMM;
  uint32_t lonMMMMM;
  char lonDirection;
  uint8_t latDD;
  uint8_t latMM;
  uint32_t latMMMMM;
  char latDirection;
  double latitude;
  double latitudeDegree;
  double lonitude;
  double lonitudeDegree;
}sLonLat_t;


/**
 * @brief Set GNSS 
 */
typedef enum {
  eGPS=1,
  eBeiDou,
  eGPS_BeiDou,
  eGLONASS,
  eGPS_GLONASS,
  eBeiDou_GLONASS,
  eGPS_BeiDou_GLONASS,
}eGnssMode_t;

class DFRobot_GNSS{
public:
  #define GNSS_DEVICE_ADDR  0x20
  #define I2C_YEAR_H 0
  #define I2C_YEAR_L 1
  #define I2C_MONTH 2
  #define I2C_DATE  3
  #define I2C_HOUR  4
  #define I2C_MINUTE 5
  #define I2C_SECOND 6
  #define I2C_LAT_1 7
  #define I2C_LAT_2 8
  #define I2C_LAT_X_24 9
  #define I2C_LAT_X_16 10
  #define I2C_LAT_X_8  11
  #define I2C_LON_DIS  12
  #define I2C_LON_1 13
  #define I2C_LON_2 14
  #define I2C_LON_X_24 15
  #define I2C_LON_X_16 16
  #define I2C_LON_X_8  17
  #define I2C_LAT_DIS  18
  #define I2C_USE_STAR 19
  #define I2C_ALT_H 20
  #define I2C_ALT_L 21
  #define I2C_ALT_X 22

  #define I2C_SOG_H 23
  #define I2C_SOG_L 24
  #define I2C_SOG_X 25
  #define I2C_COG_H 26
  #define I2C_COG_L 27
  #define I2C_COG_X 28

  #define I2C_START_GET 29
  #define I2C_ID 30
  #define I2C_DATA_LEN_H 31
  #define I2C_DATA_LEN_L 32
  #define I2C_ALL_DATA 33

  #define I2C_GNSS_MODE 34
  #define I2C_SLEEP_MODE 35
  #define I2C_RGB_MODE 36

  #define I2C_FLAG  1
  #define UART_FLAG 2
  #define TIME_OUT  500            ///< time out

  #define ENABLE_POWER 0
  #define DISABLE_POWER 1
  
  #define RGB_ON 0x05
  #define RGB_OFF 0x02


  DFRobot_GNSS();
  ~DFRobot_GNSS();
  uint8_t  uartI2CFlag = 0;

/**
 * @fn getUTC
 * @brief Get UTC, standard time 
 * @return sTim_t type, represents the returned hour, minute and second 
 * @retval sTim_t.hour hour 
 * @retval sTim_t.minute minute 
 * @retval sTim_t.second second 
 */
  sTim_t getUTC(void);

/**
 * @fn getDate
 * @brief Get date information, year, month, day 
 * @return sTim_t type, represents the returned year, month, day 
 * @retval sTim_t.year year
 * @retval sTim_t.month month 
 * @retval sTim_t.day day 
 */
  sTim_t getDate(void);

/**
 * @fn getLat
 * @brief Get latitude 
 * @return sLonLat_t type, represents the returned latitude  
 * @retval sLonLat_t.latDD   Latitude degree(0-90)
 * @retval sLonLat_t.latMM   The first and second digits behind the decimal point 
 * @retval sLonLat_t.latMMMMM Latitude  The third and seventh digits behind the decimal point 
 * @retval sLonLat_t.latitude Latitude value with 7 decimal digits
 * @retval sLonLat_t.latDirection Direction of latitude
 */
  sLonLat_t getLat(void);

/**
 * @fn getLon
 * @brief Get longitude 
 * @return sLonLat_t Type, represents the returned longitude
 * @retval sLonLat_t.lonDDD  Longitude degree(0-90)
 * @retval sLonLat_t.lonMM   Longitude  The first and second digits behind the decimal point
 * @retval sLonLat_t.lonMMMMM Longitude The third and seventh digits behind the decimal point
 * @retval sLonLat_t.lonitude Longitude value with 7 decimal digits
 * @retval sLonLat_t.lonDirection Direction of longitude 
 */
  sLonLat_t getLon(void);

/**
 * @fn getNumSatUsed
 * @brief Get the number of the used satellite used
 * @return uint8_t type, represents the number of the used satellite
 */
  uint8_t getNumSatUsed(void);

/**
 * @fn getAlt
 * @brief Get altitude
 * @return double type, represents altitude 
 */
  double getAlt(void);

/**
 * @fn getSog
 * @brief Get speed over ground 
 * @return speed Float data(unit: knot)
 */
  double getSog(void);

/**
 * @fn getCog
 * @brief Get course over ground
 * @return Float data(unit: degree) 
 */
  double getCog(void);

/**
 * @fn setGnss
 * @brief Set GNSS to be used
 * @param mode
 * @n   eGPS              use gps
 * @n   eBeiDou           use beidou
 * @n   eGPS_BeiDou       use gps + beidou
 * @n   eGLONASS          use glonass
 * @n   eGPS_GLONASS      use gps + glonass
 * @n   eBeiDou_GLONASS   use beidou +glonass
 * @n   eGPS_BeiDou_GLONASS use gps + beidou + glonass
 * @return NULL
 */
  void setGnss(eGnssMode_t mode);

/**
 * @fn getGnssMode
 * @brief Get the used gnss mode
 * @return mode
 * @retval 1 gps
 * @retval 2 beidou
 * @retval 3 gps + beidou
 * @retval 4 glonass
 * @retval 5 gps + glonass
 * @retval 6 beidou +glonass
 * @retval 7 gps + beidou + glonass
 */
  uint8_t getGnssMode(void);

/**
 * @fn getAllGnss
 * @brief Get GNSS data, call back and receive
 * @return null
 */
  void getAllGnss(void);

/**
 * @fn enablePower
 * @brief Enable gnss power
 * @return null
 */
void enablePower(void);

/**
 * @fn disablePower
 * @brief Disable gnss power
 * @return null
 */
void disablePower(void);

/**
 * @fn setRgbOn
 * @brief Turn rgb on
 * @return null
 */
void setRgbOn(void);

/**
 * @fn setRgbOn
 * @brief Turn rgb off
 * @return null
 */
void setRgbOff(void);


/**
 * @fn setCallback
 * @brief Set callback function type
 * @param  call function name 
 * @return null
 */
  void setCallback(void (*call)(char *, uint8_t));

  void (* callback)(char *data, uint8_t len);
private:
  uint8_t  _addr;
  uint8_t  _M_Flag = 0;

/**
 * @fn getGnssLen
 * @brief Get length of gnss data 
 * @return Length 
 */
  uint16_t getGnssLen(void);
  virtual void writeReg(uint8_t reg, uint8_t *data, uint8_t len) = 0;
  virtual int16_t readReg(uint8_t reg, uint8_t *data, uint8_t len) = 0;
};

class DFRobot_GNSS_I2C:public DFRobot_GNSS{
public:
  DFRobot_GNSS_I2C(TwoWire *pWire=&Wire, uint8_t addr = 0x75);
  bool begin(void);
protected:
  virtual void writeReg(uint8_t reg, uint8_t *data, uint8_t len);
  virtual int16_t readReg(uint8_t reg, uint8_t *data, uint8_t len);
private:
  TwoWire *_pWire;
  uint8_t _I2C_addr;
};

class DFRobot_GNSS_UART:public DFRobot_GNSS{
public:
#if defined(ARDUINO_AVR_UNO) || defined(ESP8266)
  DFRobot_GNSS_UART(SoftwareSerial *sSerial, uint16_t Baud);
#else
  DFRobot_GNSS_UART(HardwareSerial *hSerial, uint16_t Baud ,uint8_t rxpin = 0, uint8_t txpin = 0);
#endif

  bool begin(void);
protected:
  virtual void writeReg(uint8_t reg, uint8_t *data, uint8_t len);
  virtual int16_t readReg(uint8_t reg, uint8_t *data, uint8_t len);
private:

#if defined(ARDUINO_AVR_UNO) || defined(ESP8266)
  SoftwareSerial *_serial;
#else
  HardwareSerial *_serial;
#endif
  uint32_t _baud;
  uint8_t _rxpin;
  uint8_t _txpin;
};
#endif
