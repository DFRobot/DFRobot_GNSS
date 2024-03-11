# DFRobot_3DFace
- [English Version](./README.md)

这是一款内置自研嵌入式系统3D深度还原算法、3D人脸识别算法及多模态活体防范算法,能够有效保障用户信息及解锁安全性，在99%通过率的前提下，能够做到低于百万分之一的误识率。同时使用多模态活体防伪算法，能有效屏蔽照片、视频及各种头模和假人的攻击。

![正反面svg效果图](/resources/images/xxx.jpg) 

## 产品链接(https://www.dfrobot.com.cn)

    SKU：xxx

## 目录

* [概述](#概述)
* [库安装](#库安装)
* [方法](#方法)
* [兼容性](#兼容性y)
* [历史](#历史)
* [创作者](#创作者)

## 概述

提供一个Arduino库给人脸识别模块，此库具有以下功能：
  直视，注册人脸，识别人脸
  直视，向上下左右转头，注册人脸，识别人脸

## 库安装
这里提供两种使用本库的方法：<br>
1.打开Arduino IDE,在状态栏中的Tools--->Manager Libraries 搜索"DFRobot_3DFace"并安装本库.<br>
2.首先下载库文件,将其粘贴到\Arduino\libraries目录中,然后打开examples文件夹并在该文件夹中运行演示.<br>

## 方法

```C++
  /**
   * @fn setStandby
   * @brief 设置为待机模式，此模式下才正常驱动模块
   * @return true or false
   */
  bool setStandby(void);

  /**
   * @fn delFaceID
   * @brief 删除 指定的人脸id
   * @param number 
   * @return true or false
   */
  bool delFaceID(uint16_t number);

  /**
   * @fn delAllFaceID
   * @brief 删除所有的人脸信息
   * @return true or false
   */
  bool delAllFaceID(void);

  /**
   * @fn faceMatching
   * @brief 人脸匹配
   * @return sFaceMatching_t 匹配的结果
   */
  sFaceMatching_t faceMatching(void);

  /**
   * @fn faceRegistration
   * @brief 单项注册人脸
   * @param mode 是否是管理员模式
   * @param name 注册的名字
   * @param direction 注册的方向，单项注册一定是直视注册
   * @param regType 单项注册
   * @param repetition 是否重复注册
   * @param timerout 超时时间
   * @return sFaceReg_t 注册的结果
   */
  sFaceReg_t faceRegistration(char* name, uint8_t mode=ADMIN, eAngleView_t direction=eDirectView, uint8_t regType=ONE_REG, bool repetition=true, uint8_t timerout=0x0A);

  /**
   * @fn directRegistration
   * @brief 直视注册
   * @param name 此函数不使用
   * @param timerout 超时时间
   * @return sFaceReg_t 注册的结果
   */
  sFaceReg_t directRegistration(char* name=NULL, uint8_t timerout=0x0A);

  /**
   * @fn lookUpRegistration
   * @brief 向上看注册人脸
   * @param name 此函数不使用
   * @param timerout 超时时间
   * @return sFaceReg_t 注册的结果
   */
  sFaceReg_t lookUpRegistration(char* name=NULL, uint8_t timerout=0x0A);

  /**
   * @fn lookDownRegistration
   * @brief 向下看注册人脸
   * @param name 此函数不使用
   * @param timerout 超时时间
   * @return sFaceReg_t 注册的结果
   */
  sFaceReg_t lookDownRegistration(char* name=NULL, uint8_t timerout=0x0A);

  /**
   * @fn turnLeftRegistration
   * @brief 向左看注册人脸
   * @param name 此函数不使用
   * @param timerout 超时时间
   * @return sFaceReg_t 注册的结果
   */
  sFaceReg_t turnLeftRegistration(char* name=NULL, uint8_t timerout=0x0A);

  /**
   * @fn turnRightRegistration
   * @brief 向右看注册人脸
   * @param name 注册人脸的名字
   * @param timerout 超时时间
   * @return sFaceReg_t 注册的结果
   */
  sFaceReg_t turnRightRegistration(char* name=NULL, uint8_t timerout=0x0A);

  /**
   * @fn getFaceMessage
   * @brief 获取人脸的信息
   * @return sUserData_t 人脸id ,获取结果
   */
  sUserData_t getFaceMessage(void);
```

## 兼容性

MCU                | Work Well    |   Work Wrong    | Untested    | Remarks
------------------ | :----------: | :-------------: | :---------: | :----:
Arduino Uno        |      √       |                 |             |
Arduino MEGA2560   |      √       |                 |             |
Arduino Leonardo   |      √       |                 |             |
FireBeetle-ESP8266 |      √       |                 |             |
FireBeetle-ESP32   |      √       |                 |             |
FireBeetle-M0      |      √       |                 |             |
Micro:bit          |      √       | nonsupport uart |             |


## 历史
- 2024/03/08 - V1.0.0 版本

## 创作者

Written by ZhixinLiu(zhixin.liu@dfrobot.com), 2024. (Welcome to our website)