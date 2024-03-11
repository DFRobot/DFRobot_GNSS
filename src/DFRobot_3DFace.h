/*!
 * @file DFRobot_3DFace.h
 * @brief Define the basic structure of the DFRobot_3DFace class, the implementation of the basic methods
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [ZhixinLiu](zhixin.liu@dfrobot.com)
 * @version V1.0
 * @date 2023-03-07
 * @url https://github.com/DFRobot/DFRobot_3DFace
 */
#ifndef __DFROBOT_FACE_RECOGNITION_H__
#define __DFROBOT_FACE_RECOGNITION_H__

#include <Arduino.h>
#include <Wire.h>

#if defined(ARDUINO_AVR_UNO) || defined(ESP8266)
#include "SoftwareSerial.h"
#else
#include "HardwareSerial.h"
#endif

typedef struct {
  uint16_t userID;
  bool result;
  uint8_t direction;
  uint8_t errorCode;
}sFaceReg_t;

typedef struct {
  uint16_t userID;
  bool result;
  uint8_t name[32] = {0};
  bool admin;
  uint8_t state;
  uint8_t errorCode;
}sFaceMatching_t;

typedef struct {
  uint8_t user_count;
  uint8_t data[200];
  bool result;
}sUserData_t;

typedef enum{
  eDirectView = 0x01,
  eLookUpView = 0x10,
  eLookDownView = 0x08,
  eLookLeftView = 0x04,
  elookRightView = 0x02,
}eAngleView_t;

typedef enum{
  eResDirect = 0x01,
  eResLookUp = 0x11,
  eLookDown = 0x19,
  eLookLeft = 0x1d,
  elookRight = 0x1f,
}eResponseView_t;

typedef enum{
  eSuccess        = 0x00,
  eReject         = 0x01,
  eTermination    = 0x02,
  eMessErr        = 0x03,
  eCrameErr       = 0x04,
  eError          = 0x05,
  eParamErr       = 0x06,
  eMemoryErr      = 0x07,
  eUserNoExist    = 0x08,
  eUserUserLimit  = 0x09,
  eFaceExist      = 0x0A,
  eLivingErr      = 0x0C,
  eTimerout       = 0x0D,
}eResponseCode_t;

class DFRobot_3DFace{
public:
  #define REG_GERENEL_CMD 0x10
  #define DEVICE_ADDR     0x20
  #define TIME_OUT        0x64     ///< time out
  #define I2C_FLAG        0x01
  #define UART_FLAG       0x02
  #define DATA_CODE       0x05
  #define ERROR_CODE      0x06
  #define C_SUCCESS       0x00
  #define C_REJECT        0x01
  // The registration mode is administrator mode or user mode
  #define USER 0
  #define ADMIN 1
  // Single registration or five-item registration
  #define ONE_REG  1
  #define FIVE_REG 0
  #define REG_WRITE_AT_LONG       0x39
  #define REG_WRITE_AT            0x40
  #define REG_READ_AT_LEN         0x41
  #define REG_READ_AT             0x42
  DFRobot_3DFace();
  ~DFRobot_3DFace();
  uint8_t  uartI2CFlag = 0;
  /**
   * @fn setStandby
   * @brief Set it to standby mode. 
   * @n     The driver module can work properly only in this mode
   * @return true or false
   */
  bool setStandby(void);

  /**
   * @fn delFaceID
   * @brief Deletes the specified face id
   * @param number 
   * @return true or false
   */
  bool delFaceID(uint16_t number);

  /**
   * @fn delAllFaceID
   * @brief Delete all facial information
   * @return true or false
   */
  bool delAllFaceID(void);

  /**
   * @fn faceMatching
   * @brief Face matching
   * @return sFaceMatching_t match result
   */
  sFaceMatching_t faceMatching(void);

  /**
   * @fn faceRegistration
   * @brief Single registered face
   * @param mode Administrator mode or not
   * @param name Registered name
   * @param direction The direction of registration, single registration must be directly registered
   * @param regType  ONE_REG
   * @param repetition Whether to repeat registration
   * @param timerout
   * @return sFaceReg_t Result of registration
   */
  sFaceReg_t faceRegistration(char* name, uint8_t mode=ADMIN, eAngleView_t direction=eDirectView, uint8_t regType=ONE_REG, bool repetition=true, uint8_t timerout=0x0A);

  /**
   * @fn directRegistration
   * @brief Look direct at face registration
   * @param name name must null
   * @param timerout
   * @return sFaceReg_t Result of registration
   */
  sFaceReg_t directRegistration(char* name=NULL, uint8_t timerout=0x0A);

  /**
   * @fn lookUpRegistration
   * @brief Look up at face registration
   * @param name name nust null
   * @param timerout
   * @return sFaceReg_t Result of registration
   */
  sFaceReg_t lookUpRegistration(char* name=NULL, uint8_t timerout=0x0A);

  /**
   * @fn lookDownRegistration
   * @brief Look down at face registration
   * @param name name must null
   * @param timerout
   * @return sFaceReg_t Result of registration
   */
  sFaceReg_t lookDownRegistration(char* name=NULL, uint8_t timerout=0x0A);

  /**
   * @fn turnLeftRegistration
   * @brief Look left at face registration
   * @param name name must null
   * @param timerout
   * @return sFaceReg_t Result of registration
   */
  sFaceReg_t turnLeftRegistration(char* name=NULL, uint8_t timerout=0x0A);

  /**
   * @fn turnLeftRegistration
   * @brief Look right at face registration
   * @param name register name
   * @param timerout
   * @return sFaceReg_t Result of registration
   */
  sFaceReg_t turnRightRegistration(char* name=NULL, uint8_t timerout=0x0A);

  /**
   * @fn getFaceMessage
   * @brief get face message
   * @return sUserData_t face id ,face result
   */
  sUserData_t getFaceMessage(void);

  uint8_t getParityCheck(uint8_t * p ,int len);
  int8_t waitTrueData(uint8_t *data, uint8_t len);
private:
  uint8_t  _addr;
  uint8_t  _M_Flag = 0;

  virtual void writeReg(uint8_t reg, uint8_t *data, uint8_t len) = 0;
  virtual int16_t readReg(uint8_t reg, uint8_t *data, uint8_t len) = 0;
};

class DFRobot_3DFace_I2C:public DFRobot_3DFace{
public:
  DFRobot_3DFace_I2C(TwoWire *pWire=&Wire, uint8_t addr = DEVICE_ADDR);
  bool begin(void);
protected:
  virtual void writeReg(uint8_t reg, uint8_t *data, uint8_t len);
  virtual int16_t readReg(uint8_t reg, uint8_t *data, uint8_t len);
private:
  TwoWire *_pWire;
  uint8_t _I2C_addr;
};

class DFRobot_3DFace_UART:public DFRobot_3DFace{
public:
#if defined(ARDUINO_AVR_UNO) || defined(ESP8266)
  DFRobot_3DFace_UART(SoftwareSerial *sSerial, uint32_t Baud);
#else
  DFRobot_3DFace_UART(HardwareSerial *hSerial, uint32_t Baud ,uint8_t rxpin = 0, uint8_t txpin = 0);
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
