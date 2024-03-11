# DFRobot_3DFace
- [中文版](./README_CN.md)

This is a built-in self-developed embedded system 3D depth restoration algorithm, 3D face recognition algorithm and multi-modal live prevention algorithm, which can effectively protect user information and unlock security, under the premise of 99% pass rate, can achieve less than one million error rate. At the same time, the multi-modal live anti-counterfeiting algorithm can effectively shield the attacks of photos, videos and various head models and dummies.

![效果图](resources/images/xxx.jpg)

## Product Link(https://www.dfrobot.com/)

    SKU：xxx

## Table of Contents

* [Summary](#Summary)
* [Installation](#Installation)
* [Methods](#Methods)
* [Compatibility](#Compatibility)
* [History](#History)
* [Credits](#Credits)

## Summary

Provide an Arduino library for the face recognition module, which has the following functions:
Look straight, register faces, recognize faces
Look straight, turn your head up and down, right and left, register faces, recognize faces

## Installation
There are two methods for using this library:<br>
1. Open Arduino IDE, search for "DFRobot_3DFace" on the status bar in Tools ->Manager Libraries and install the library.<br>
2. Download the library file before use, paste it into \Arduino\libraries directory, then open the examples folder and run the demo in the folder.<br>

## Methods

```C++
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
```

## Compatibility

MCU                | Work Well    |   Work Wrong    | Untested    | Remarks
------------------ | :----------: | :-------------: | :---------: | :----:
Arduino Uno        |      √       |                 |             |
Arduino MEGA2560   |      √       |                 |             |
Arduino Leonardo   |      √       |                 |             |
FireBeetle-ESP8266 |      √       |                 |             |
FireBeetle-ESP32   |      √       |                 |             |
FireBeetle-M0      |      √       |                 |             |
Micro:bit          |      √       | nonsupport uart |             |


## History

- 2024/03/08 - Version 1.0.0 released.

## Credits

Written by ZhixinLiu(zhixin.liu@dfrobot.com), 2024. (Welcome to our website)
