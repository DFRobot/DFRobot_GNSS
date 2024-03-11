# DFRobot_3DFace
- [中文版](./README_CN.md)
This is a built-in self-developed embedded system 3D depth restoration algorithm, 3D face recognition algorithm and multi-modal live prevention algorithm, which can effectively protect user information and unlock security, under the premise of 99% pass rate, can achieve less than one million error rate. At the same time, the multi-modal live anti-counterfeiting algorithm can effectively shield the attacks of photos, videos and various head models and dummies.

![效果图](../../resources/images/face.jpg)

## Product Link(https://www.dfrobot.com)

    SKU：xxx

## Table of Contents

* [Summary](#Summary)
* [Installation](#Installation)
* [Methods](#Methods)
* [Compatibility](#Compatibility)
* [History](#History)
* [Credits](#Credits)

## Summary

Provides an Arduino library that has the following features:
  Face recognition routine

## Installation
1. Download the library to Raspberry Pi first before use.

```
sudo git clone https://github.com/DFRobot/DFRobot_3DFace
```

1. Open and run the routine. To execute a routine demo_x.py, enter python demo_x.py in the command line. For example, to execute the routine get_mm wavewave.py, you need to enter:

```
python face_recognition.py
or 
python2 face_recognition.py
or 
python3 face_recognition.py
```

## Methods

```python
  def begin(self):
    '''!
      @brief begin
      @return True 
    '''

  def set_standby(self):
    '''!
      @brief Set it to standby mode. 
      @n     The driver module can work properly only in this mode
      @return True or False
    '''

  def delete_face_id(self, number):
    '''!
      @brief Deletes the specified face id
      @param number delete face id
      @return True or False
    '''

  def delete_all_face_id(self):
    '''!
      @brief Delete all facial information
      @return True or False
    '''
    
  def direct_registration(self, name="", timerout=0x0a):
    '''!
      @brief Look direct at face registration
      @param name must is null
      @param timerout
      @return struct_face_reg
    '''

  def look_up_registration(self, name="", timerout=0x0a):
    '''!
      @brief Look up at face registration
      @param name must is null
      @param timerout
      @return struct_face_reg
    '''
  
  def look_down_registration(self, name="", timerout=0x0a):
    '''!
      @brief Look down at face registration
      @param name must is null
      @param timerout
      @return struct_face_reg
    '''

  def turn_left_registration(self, name="", timerout=0x0a):
    '''!
      @brief Look left at face registration
      @param name must is null
      @param timerout
      @return struct_face_reg
    '''

  def turn_right_registration(self, name="", timerout=0x0a):
    '''!
      @brief Look right at face registration
      @param name register name
      @param timerout
      @return struct_face_reg
    '''

  def face_registration(self, name, mode=ADMIN, direction=DIRECT_VIEW, reg_type=ONE_REG ,repetition=1 ,timerout=0X0A):
    '''!
      @brief Single registered face
      @param mode = ADMIN
      @param direction = DIRECT_VIEW
      @param reg_type = ONE_REG
      @param repetition = 1
      @param name register name
      @param timerout
      @return struct_face_reg
    '''

  def face_matching(self):
    '''!
      @brief face_matching
      @return match
    '''

  def get_face_message(self):
    '''!
      @brief get_face_message
      @return struct_result_data
    '''
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

- 2024/03/06 - Version 1.0.0 released.

## Credits

Written by ZhixinLiu(zhixin.liu@dfrobot.com), 2024. (Welcome to our website)
