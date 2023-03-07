/*!
 * @file DFRobot_GNSS.cpp
 * @brief Define the basic structure of the DFRobot_GNSS class, the implementation of the basic methods
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [ZhixinLiu](zhixin.liu@dfrobot.com)
 * @version V1.0
 * @date 2023-03-07
 * @url https://github.com/DFRobot/DFRobot_GNSS
 */
#include "DFRobot_GNSS.h"

DFRobot_GNSS::DFRobot_GNSS(){}
DFRobot_GNSS::~DFRobot_GNSS(){}

sTim_t DFRobot_GNSS::getDate(void)
{
  sTim_t data;
  uint8_t _sendData[10] = {0};
  readReg(I2C_YEAR_H, _sendData, 4);
  data.year = ((uint16_t)_sendData[0] << 8) | _sendData[1];
  data.month = _sendData[2];
  data.date = _sendData[3];
  return data;
}

sTim_t DFRobot_GNSS::getUTC(void)
{
  sTim_t data;
  uint8_t _sendData[10] = {0};
  readReg(I2C_HOUR, _sendData, 3);
  data.hour   = _sendData[0];
  data.minute = _sendData[1];
  data.second = _sendData[2];
  return data;
}

sLonLat_t DFRobot_GNSS::getLat(void)
{
  sLonLat_t data;
  uint8_t _sendData[10] = {0};
  readReg(I2C_LAT_1, _sendData, 6);
  data.latDD  = _sendData[0];
  data.latMM = _sendData[1];
  data.latMMMMM = ((uint32_t)_sendData[2] << 16) | ((uint32_t)_sendData[3] << 8) | ((uint32_t)_sendData[4]);
  data.latitude = (double)data.latDD*100.0 + ((double)data.latMM) + ((double)data.latMMMMM / 100000.0);
  data.latitudeDegree = (double)data.latDD + (double)data.latMM/60.0 + (double)data.latMMMMM / 100000.0 / 60.0;
  data.latDirection = _sendData[5];
  return data;
}

sLonLat_t DFRobot_GNSS::getLon(void)
{
  sLonLat_t data;
  uint8_t _sendData[10] = {0};
  readReg(I2C_LON_1, _sendData, 6);
  data.lonDDD  = _sendData[0];
  data.lonMM = _sendData[1];
  data.lonMMMMM = ((uint32_t)_sendData[2]<<16) | ((uint32_t)_sendData[3]<< 8) | ((uint32_t)_sendData[4]) ;
  data.lonitude = (double)data.lonDDD*100.0 + ((double)data.lonMM) + ((double)data.lonMMMMM / 100000.0);

  data.lonitudeDegree = (double)data.lonDDD + (double)data.lonMM/60.0 + (double)data.lonMMMMM / 100000.0/60.0;
  data.lonDirection = _sendData[5];
  return data;
}

uint8_t DFRobot_GNSS::getNumSatUsed(void)
{
  uint8_t _sendData[10] = {0};
  readReg(I2C_USE_STAR, _sendData, 1);
  return _sendData[0];
}

double DFRobot_GNSS::getAlt(void)
{
  double high;
  uint8_t _sendData[10] = {0};
  readReg(I2C_ALT_H, _sendData, 3);
  if(_sendData[0] & 0x80){
    high = (double)((uint16_t)(_sendData[0]&0x7F)<<8 | _sendData[1]) + (double)_sendData[2]/100.0;
  }else{
    high = (double)((uint16_t)(_sendData[0]&0x7F)<<8 | _sendData[1]) + (double)_sendData[2]/100.0;
  }
  return high;
}

double DFRobot_GNSS::getSog(void)
{
  double speed;
  uint8_t _sendData[10] = {0};

  readReg(I2C_SOG_H, _sendData, 3);
  if(_sendData[0] & 0x80){
    speed = (double)((uint16_t)(_sendData[0]&0x7F)<<8 | _sendData[1]) + (double)_sendData[2]/100.0;
  }else{
    speed = (double)((uint16_t)(_sendData[0]&0x7F)<<8 | _sendData[1]) + (double)_sendData[2]/100.0;
  }
  return speed;
}

double DFRobot_GNSS::getCog(void)
{
  double cog;
  uint8_t _sendData[10] = {0};

  readReg(I2C_COG_H, _sendData, 3);
  if(_sendData[0] & 0x80){
    cog = (double)((uint16_t)(_sendData[0]&0x7F)<<8 | _sendData[1]) + (double)_sendData[2]/100.0;
  }else{
    cog = (double)((uint16_t)(_sendData[0]&0x7F)<<8 | _sendData[1]) + (double)_sendData[2]/100.0;
  }
  return cog;
}


void DFRobot_GNSS::setRgbOn(void)
{
  uint8_t _sendData[10] = {0};
  _sendData[0] = RGB_ON;
  writeReg(I2C_RGB_MODE, _sendData, 1);
  delay(50);
}

void DFRobot_GNSS::setRgbOff(void)
{
  uint8_t _sendData[10] = {0};
  _sendData[0] = RGB_OFF;
  writeReg(I2C_RGB_MODE, _sendData, 1);
  delay(50);
}


void DFRobot_GNSS::enablePower(void)
{
  uint8_t _sendData[10] = {0};
  _sendData[0] = ENABLE_POWER;
  writeReg(I2C_SLEEP_MODE, _sendData, 1);
  delay(50);
}

void DFRobot_GNSS::disablePower(void)
{
  uint8_t _sendData[10] = {0};
  _sendData[0] = DISABLE_POWER;
  writeReg(I2C_SLEEP_MODE, _sendData, 1);
  delay(50);
}

void DFRobot_GNSS::setGnss(eGnssMode_t mode)
{
  uint8_t _sendData[10] = {0};
  _sendData[0] = mode;
  writeReg(I2C_GNSS_MODE, _sendData, 1);
  delay(50);
}

uint8_t DFRobot_GNSS::getGnssMode(void)
{
  uint8_t _sendData[10] = {0};
  readReg(I2C_GNSS_MODE, _sendData, 1);
  return _sendData[0];
}

uint16_t DFRobot_GNSS::getGnssLen(void)
{
  uint8_t _sendData[10] = {0};
  _sendData[0] = 0x55;                  // enable messure
  writeReg(I2C_START_GET, _sendData, 1);
  delay(100);
  readReg(I2C_DATA_LEN_H, _sendData, 2);
  return (uint16_t)_sendData[0] << 8 | _sendData[1];
}

void DFRobot_GNSS::getAllGnss(void)
{
  uint8_t _sendData[260] = {0};
  uint16_t len = getGnssLen();
  if(len > 1024+200 || len == 0){
    return;
  }
  if(uartI2CFlag == UART_FLAG) {
    uint8_t templen = len / 250 +1;
    for(uint16_t i = 0; i < templen; i++){
      if(i == templen - 1){
        readReg(I2C_ALL_DATA, _sendData, len%250);
        for(uint8_t i = 0; i < len%250; i++){
          if(_sendData[i] == '\0'){
            _sendData[i] = '\n';
          }
        }
        if(callback){
          callback((char *)_sendData, (uint8_t)(len%250));
        }
      }else{
        readReg(I2C_ALL_DATA, _sendData, 250);
        for(uint8_t i = 0; i < 250; i++){
          if(_sendData[i] == '\0'){
            _sendData[i] = '\n';
          }
        }
        
        if(callback){
          callback((char *)_sendData, (uint8_t)250);
        }
      }
    }
  }else{
    uint8_t templen = len/32 +1;
    for(uint16_t i = 0; i < templen; i++){
      if(i == templen - 1){
        readReg(I2C_ALL_DATA, _sendData, len%32);
        for(uint8_t i = 0; i < len%32; i++){
          if(_sendData[i] == '\0'){
            _sendData[i] = '\n';
          }
        }
        if(callback){
          callback((char *)_sendData, (uint8_t)(len%32));
        }
      }else{
        readReg(I2C_ALL_DATA, _sendData, 32);
        for(uint8_t i = 0; i < 32; i++){
          if(_sendData[i] == '\0'){
            _sendData[i] = '\n';
          }
        }
        if(callback){
          callback((char *)_sendData, (uint8_t)32);
        }
      }
    }
  }
}

void DFRobot_GNSS::setCallback(void (*call)(char *, uint8_t))
{
  this->callback = call;
}

DFRobot_GNSS_I2C::DFRobot_GNSS_I2C(TwoWire *pWire, uint8_t addr)
{
  _pWire = pWire;
  this->_I2C_addr = addr;
  uartI2CFlag = I2C_FLAG;
}

bool DFRobot_GNSS_I2C::begin()
{
  _pWire->begin();
  _pWire->beginTransmission(_I2C_addr);
  if(_pWire->endTransmission() == 0){
    return true;
  }else{
    return false;
  }
}

void DFRobot_GNSS_I2C::writeReg(uint8_t reg, uint8_t *data, uint8_t len)
{
  _pWire->beginTransmission(this->_I2C_addr);
  _pWire->write(reg);
  for(uint8_t i = 0; i < len; i++){
    _pWire->write(data[i]);
  }
  _pWire->endTransmission();
}

int16_t DFRobot_GNSS_I2C::readReg(uint8_t reg,uint8_t *data,uint8_t len)
{
  int i=0;
  _pWire->beginTransmission(this->_I2C_addr);
  _pWire->write(reg);
  if(_pWire->endTransmission() != 0){
    return -1;
  }
  _pWire->requestFrom((uint8_t)this->_I2C_addr,(uint8_t)len);
  while (_pWire->available()){
    data[i++]=_pWire->read();
  }
  return 0;
}

// #ifdef ESP_PLATFORM
//   DFRobot_GNSS_UART::DFRobot_GNSS_UART(HardwareSerial *hSerial, uint16_t Baud)
//   {
//     this->_serial = hSerial;
//     this->_baud = Baud;
//     uartI2CFlag = UART_FLAG;
//   }
// #else
//   DFRobot_GNSS_UART::DFRobot_GNSS_UART(SoftwareSerial *sSerial, uint16_t Baud)
//   {
//     this->_serial = sSerial;
//     this->_baud = Baud;
//     uartI2CFlag = UART_FLAG;
//   }
// #endif

#if defined(ARDUINO_AVR_UNO) || defined(ESP8266)
  DFRobot_GNSS_UART::DFRobot_GNSS_UART(SoftwareSerial *sSerial, uint16_t Baud)
  {
    this->_serial = sSerial;
    this->_baud = Baud;
    uartI2CFlag = UART_FLAG;
    _serial->begin(this->_baud);
  }
#else
  DFRobot_GNSS_UART::DFRobot_GNSS_UART(HardwareSerial *hSerial, uint16_t Baud ,uint8_t txpin, uint8_t rxpin)
  {
    this->_serial = hSerial;
    this->_baud = Baud;
    uartI2CFlag = UART_FLAG;
    this->_txpin = txpin;
    this->_rxpin = rxpin;
  }
#endif

bool DFRobot_GNSS_UART::begin()
{
  #ifdef ESP32
    _serial->begin(this->_baud, SERIAL_8N1, _txpin, _rxpin);
  #elif defined(ARDUINO_AVR_UNO) || defined(ESP8266)
    // nothing use software
  #else
    _serial->begin(this->_baud);  // M0 cannot create a begin in a construct
  #endif

  uint8_t _sendData[10] = {0};
  this->readReg (I2C_ID, _sendData, 1);
  if(_sendData[0] == GNSS_DEVICE_ADDR){
    return true;
  }else{
    return false;
  }
}

void DFRobot_GNSS_UART::writeReg(uint8_t reg, uint8_t *data, uint8_t len)
{
  _serial->write(reg | 0x80);
  for(uint8_t i = 0; i < len; i++){
    _serial->write(data[i]);
  }
}

int16_t DFRobot_GNSS_UART::readReg(uint8_t reg, uint8_t *data, uint8_t len)
{
  uint8_t i = 0;
  _serial->write((uint8_t)reg & 0x7F);
  _serial->write(len);
  uint32_t nowtime = millis();
  while(millis() - nowtime < TIME_OUT){
    while(_serial->available() > 0){
      data[i++] = _serial->read();
    }
  }
  return 0;
}
