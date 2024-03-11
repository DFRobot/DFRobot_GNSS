# -*- coding: utf-8 -*
'''!
  @file face_recoognition.py
  @brief Register and recognize faces
  @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license    The MIT License (MIT)
  @author     [ZhixinLiu](zhixin.liu@dfrobot.com)
  @version    V1.0
  @date       2024-02-27
  @url https://github.com/DFRobot/DFRobot_3DFace
'''
from __future__ import print_function
import sys
import os
sys.path.append("../")
import time
import RPi.GPIO as GPIO
from DFRobot_3DFace import *

'''
  Select to use i2c or UART
  I2C_MODE
  UART_MODE
'''
ctype = I2C_MODE

if ctype == I2C_MODE:
  I2C_1 = 0x01
  face = DFRobot_3DFace_I2C (I2C_1, DEVICE_ADDR)
elif ctype == UART_MODE:
  face = DFRobot_3DFace_UART(57600)


def setup():
  while (face.begin() == False):
    print("Sensor initialize failed!!")
    time.sleep(1)
  face.set_standby()
  print("Sensor initialize success!!")
  
  data = face.get_face_message()
  if data.result == True:
    print("user count = " + str(data.user_count))
  
  #status = face.delete_all_face_id()
  status = face.delete_face_id(1)
  
  if status == True:
    print("delete face id success !")
  else:
    print("delete face id faild !")
  
  time.sleep(1)
  
  face_reg = face.face_registration("raspberry 18")
  if face_reg.result == True:
    print("face resgistering success!")
    print("regiseter user id = " + str(face_reg.user_id));
    print("register direction = " + str(face_reg.direction))
  else:
    print("face resgistering faild!")
    print("error code = " + str(face_reg.error_code))
    
  
  
def loop():
  print("matching face .............")
  match = face.face_matching()
  if match.result:
    print("matching success")
    print("matching user ID = ", match.user_id)
    print("matching name = ", match.name)
    print("")
  else:
    print("matching error")
    print("")
  
  time.sleep(1)

if __name__ == "__main__":
  setup()
  while True:
    loop()
