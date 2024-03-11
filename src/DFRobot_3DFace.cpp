/*!
 * @file DFRobot_3DFace.cpp
 * @brief Define the basic structure of the DFRobot_3DFace class, the implementation of the basic methods
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [ZhixinLiu](zhixin.liu@dfrobot.com)
 * @version V1.0
 * @date 2023-03-07
 * @url https://github.com/DFRobot/DFRobot_3DFace
 */
#include "DFRobot_3DFace.h"

DFRobot_3DFace::DFRobot_3DFace(){}
DFRobot_3DFace::~DFRobot_3DFace(){}

bool DFRobot_3DFace::setStandby(void)
{
  uint16_t len = 0;
  uint8_t tx_temp[40] = {0xEF, 0xAA, 0x23, 0x00, 0x00, 0x23};
  uint8_t rx_temp[40] = {0x00};
  writeReg(REG_WRITE_AT, tx_temp, 6);
  while(1){
    delay(100);
    len = readReg(0, rx_temp, 0);
    if(len != 0){
      return true;
    }
  }
  return true;
}

bool DFRobot_3DFace::delFaceID(uint16_t number)
{
  uint16_t len = 0;
  uint8_t tx_temp[10] = {0xEF, 0xAA, 0x20, 0x00, 0x02};
  uint8_t rx_temp[50] = {0x00};
  tx_temp[DATA_CODE] = (uint8_t)(number>>8);
  tx_temp[DATA_CODE+1] = (uint8_t)(number);
  tx_temp[7] = getParityCheck(tx_temp, 7);
  setStandby();
  delay(100);
  writeReg(REG_WRITE_AT, tx_temp, 8);
  delay(100);
  while(1){
    delay(100);
    len = readReg(0, rx_temp, 0);
    if(len != 0){
      if(rx_temp[ERROR_CODE] == C_SUCCESS){
        return true;
      }else{
        return false;
      }
    }
  }
  return true;
}

bool DFRobot_3DFace::delAllFaceID(void)
{
  uint16_t len = 0;
  uint8_t tx_temp[10] = {0xEF, 0xAA, 0x21, 0x00, 0x00};
  uint8_t rx_temp[40] = {0x00};
  tx_temp[5] = getParityCheck(tx_temp, 5);
  setStandby();
  delay(100);
  writeReg(REG_WRITE_AT, tx_temp, 6);
  while(1){
    delay(100);
    len = readReg(0, rx_temp, 0);
    if(len != 0){
      if(rx_temp[ERROR_CODE] == C_SUCCESS){
        return true;
      }else{
        return false;
      }
    }
  }
  return true;
}

sFaceReg_t DFRobot_3DFace::directRegistration(char* name, uint8_t timerout)
{
  return faceRegistration(NULL, ADMIN, eDirectView, FIVE_REG, true, timerout);
}

sFaceReg_t DFRobot_3DFace::lookUpRegistration(char* name, uint8_t timerout)
{
  return faceRegistration(NULL, ADMIN, eLookUpView, FIVE_REG, true, timerout);
}

sFaceReg_t DFRobot_3DFace::lookDownRegistration(char* name, uint8_t timerout)
{
  return faceRegistration(NULL, ADMIN, eLookDownView, FIVE_REG, true, timerout);
}

sFaceReg_t DFRobot_3DFace::turnLeftRegistration(char* name, uint8_t timerout)
{
  return faceRegistration(NULL, ADMIN, eLookLeftView, FIVE_REG, true, timerout);
}

sFaceReg_t DFRobot_3DFace::turnRightRegistration(char* name, uint8_t timerout)
{
  return faceRegistration(name, ADMIN, elookRightView, FIVE_REG, true, timerout);
}

sFaceReg_t DFRobot_3DFace::faceRegistration(char* name, uint8_t mode, eAngleView_t direction, uint8_t regType, bool repetition, uint8_t timerout)
{
  uint16_t len = 0;
  int8_t count = -1;
  uint8_t tx_temp[50] = {0xEF, 0xAA, 0x26, 0x00, 0x28};
  uint8_t rx_temp[200] = {0x00};
  sFaceReg_t data;
  tx_temp[5] = mode;
  if(name != NULL){
    memcpy(tx_temp+6,(uint8_t *)name ,strlen((const char *)name));
  }
  tx_temp[38] = direction;
  tx_temp[39] = regType;
  tx_temp[40] = repetition;
  tx_temp[41] = timerout;
  tx_temp[45] = getParityCheck(tx_temp, 45);
  if(regType == ONE_REG || direction == eDirectView){
    delay(100);
    setStandby();
    delay(100);
  }
  writeReg(REG_WRITE_AT, tx_temp, 46);
  while(1){
    delay(50);
    len = readReg(REG_READ_AT_LEN, rx_temp, 0);
    if(len != 0){
      count = waitTrueData(rx_temp, len);
      if(count != -1){
        delay(100);
        data.errorCode = rx_temp[count + 6];
        if(rx_temp[count + 6] != C_SUCCESS){
          data.result = false;
        }else{
          data.result = true;
          data.userID = (uint16_t)((rx_temp[count+7]) << 8) | rx_temp[count+8];
          data.direction = rx_temp[count + 9];
        }
        len = readReg(REG_READ_AT_LEN, rx_temp, 0);
        if(regType == ONE_REG || direction == elookRightView){
          delay(100);
          setStandby();
        }
        return data;
      }
    }
  }
  return data;
}

sFaceMatching_t DFRobot_3DFace::faceMatching(void)
{
  sFaceMatching_t data;
  uint16_t len = 0;
  int8_t count = -1;
  uint8_t tx_temp[40] = {0xEF, 0xAA, 0x12, 0x00, 0x02};
  uint8_t rx_temp[200] = {0x00};
  tx_temp[5] = 0x00;
  tx_temp[6] = 0x15;
  tx_temp[7] = getParityCheck(tx_temp, 7);
  setStandby();
  delay(100);
  writeReg(REG_WRITE_AT, tx_temp, 8);
  while(1){
    delay(500);
    len = readReg(REG_READ_AT_LEN, rx_temp, 0);
    if(len != 0){
      count = waitTrueData(rx_temp, len);
      if(count != -1){
        data.errorCode = rx_temp[count + 6];
        if(rx_temp[count + 6] != C_SUCCESS){
          data.result = false;
        }else{
          data.result = true;
          data.userID = (uint16_t)((rx_temp[count+7]) << 8) | rx_temp[count+8];
          memcpy(data.name, &rx_temp[count+9],32);
          data.admin = rx_temp[count+41];
          data.state = rx_temp[count+42];
        }
        delay(100);
        len = readReg(REG_READ_AT_LEN, rx_temp, 0);
        delay(100);
        count = waitTrueData(rx_temp, len);
        data.errorCode = rx_temp[count + 6];
        if(count != -1){
          if(rx_temp[count + 6] != C_SUCCESS){
            data.result = false;
          }else{
            data.result = true;
            data.userID = (uint16_t)((rx_temp[count+7]) << 8) | rx_temp[count+8];
            memcpy(data.name, &rx_temp[count+9],32);
            data.admin = rx_temp[count+41];
            data.state = rx_temp[count+42];
          }
        }
        delay(100);
        setStandby();
        return data;
      }
    }
  }
}

int8_t DFRobot_3DFace::waitTrueData(uint8_t *data, uint8_t len)
{
  uint8_t count = 0;
  uint8_t temp[2] = {0x00};
  for(uint8_t i = 0; i < len; i++){
    if(data[i] == 0xEF){
      temp[count++] = i;
    }
  }
  if(count == 2){
    return temp[1];
  }
  if(data[0] == 0xEF && data[1] == 0xAA && data[2] == 0x00){
    return 0;
  }
  return -1;
}

sUserData_t DFRobot_3DFace::getFaceMessage(void)
{
  sUserData_t data;
  uint16_t len = 0;
  uint8_t tx_temp[10] = {0xEF, 0xAA, 0x24, 0x00, 0x00};
  uint8_t rx_temp[300] = {0x00};
  tx_temp[5] = getParityCheck(tx_temp, 5);
  setStandby();
  delay(100);
  writeReg(REG_WRITE_AT, tx_temp, 6);
  delay(100);
  len = readReg(REG_READ_AT_LEN, rx_temp, 0);
  if(len != 0){
    if(rx_temp[ERROR_CODE] != C_SUCCESS){
      data.result = false;
    }
    data.user_count = rx_temp[7];
    data.result = true;
    memcpy(data.data, (uint8_t *)(rx_temp+8), 200);
  }else{
    data.result = false;
  }
  return data;
}

uint8_t DFRobot_3DFace::getParityCheck(uint8_t * p ,int len)
{
  uint8_t parityCheck = 0;
  for(int i = 2; i < len; i++){
    parityCheck ^= p[i];
  }
  return parityCheck;
}

DFRobot_3DFace_I2C::DFRobot_3DFace_I2C(TwoWire *pWire, uint8_t addr)
{
  _pWire = pWire;
  this->_I2C_addr = addr;
  uartI2CFlag = I2C_FLAG;
}

bool DFRobot_3DFace_I2C::begin()
{
  _pWire->begin();
  _pWire->beginTransmission(_I2C_addr);
  if(_pWire->endTransmission() == 0){
    return true;
  }else{
    return false;
  }
}

void DFRobot_3DFace_I2C::writeReg(uint8_t reg, uint8_t *data, uint8_t len)
{
  if(len > 31){
    _pWire->beginTransmission(this->_I2C_addr);
    _pWire->write(REG_WRITE_AT_LONG);
    _pWire->write(data, 31);
    _pWire->endTransmission();
    len -= 31;
    _pWire->beginTransmission(this->_I2C_addr);
    _pWire->write(reg);
    _pWire->write(data+31, len);
    _pWire->endTransmission();
  }else{
    _pWire->beginTransmission(this->_I2C_addr);
    _pWire->write(reg);
    _pWire->write(data, len);
    _pWire->endTransmission();
  }
}

int16_t DFRobot_3DFace_I2C::readReg(uint8_t reg,uint8_t *data,uint8_t len)
{
  /* i2c get data */
  uint8_t i = 0, rxLen = 0;
  _pWire->beginTransmission(this->_I2C_addr);
  _pWire->write(REG_READ_AT_LEN);
  if(_pWire->endTransmission() != 0){
    return -1;
  }
  _pWire->requestFrom((uint8_t)this->_I2C_addr,(uint8_t)5);
  while (_pWire->available()){
    data[i++]=_pWire->read();
  }
  rxLen = data[0];
  i = 0;
  if(rxLen == 0){
    return 0;       // data = 0;
  }else{
    while(rxLen){
      if(rxLen > 32){
        _pWire->beginTransmission(this->_I2C_addr);
        _pWire->write(REG_READ_AT);
        if(_pWire->endTransmission() != 0){
          return -1;
        }
        _pWire->requestFrom((uint8_t)this->_I2C_addr,(uint8_t)32);
        while(_pWire->available()){
          data[i++]=_pWire->read();
        }
        rxLen -= 32;
      }else{
        _pWire->beginTransmission(this->_I2C_addr);
        _pWire->write(REG_READ_AT);
        if(_pWire->endTransmission() != 0){
          return -1;
        }
        _pWire->requestFrom((uint8_t)this->_I2C_addr,(uint8_t)rxLen);
        while(_pWire->available()){
          data[i++]=_pWire->read();
        }
        rxLen = 0;
      }
    }
  }
  return i;
}

#if defined(ARDUINO_AVR_UNO) || defined(ESP8266)
  DFRobot_3DFace_UART::DFRobot_3DFace_UART(SoftwareSerial *sSerial, uint32_t Baud)
  {
    this->_serial = sSerial;
    this->_baud = Baud;
    uartI2CFlag = UART_FLAG;
    _serial->begin(this->_baud);
  }
#else
  DFRobot_3DFace_UART::DFRobot_3DFace_UART(HardwareSerial *hSerial, uint32_t Baud ,uint8_t txpin, uint8_t rxpin)
  {
    this->_serial = hSerial;
    this->_baud = Baud;
    uartI2CFlag = UART_FLAG;
    this->_txpin = txpin;
    this->_rxpin = rxpin;
  }
#endif

bool DFRobot_3DFace_UART::begin()
{
  uint8_t rx_temp[40] = {0x00};
  int len = 0;
  #ifdef ESP32
    _serial->begin(this->_baud, SERIAL_8N1, _txpin, _rxpin);
  #elif defined(ARDUINO_AVR_UNO) || defined(ESP8266)
    // nothing use software
  #else
    _serial->begin(this->_baud);  // M0 cannot create a begin in a construct
  #endif
  len = readReg(0, rx_temp, 0);
  return true;
}

void DFRobot_3DFace_UART::writeReg(uint8_t reg, uint8_t *data, uint8_t len)
{
  for(uint8_t i = 0; i < len; i++){
    _serial->write(data[i]);
  }
}

int16_t DFRobot_3DFace_UART::readReg(uint8_t reg, uint8_t *data, uint8_t len)
{
  uint16_t i = 0;
  uint32_t nowtime = millis();
  while(millis() - nowtime < TIME_OUT){
    while(_serial->available() > 0){
      //if(i == len){ return i; }       // Prevent data overflow
      data[i++] = _serial->read();
    }
  }
  return i;
}
