# -*- coding: utf-8 -*
'''!
  @file face_five_recognition.py
  @brief Five things to register and recognize faces
  @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license    The MIT License (MIT)
  @author     [ZhixinLiu](zhixin.liu@dfrobot.com)
  @version    V1.0
  @date       2024-2-28
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
ctype = UART_MODE

if ctype == I2C_MODE:
  I2C_1 = 0x01
  face = DFRobot_3DFace_I2C (I2C_1, DEVICE_ADDR)
elif ctype == UART_MODE:
  face = DFRobot_3DFace_UART(57600)


def setup():
  while (face.begin() == False):
    print("Sensor initialize failed!!")
    time.sleep(1)
  data = face.get_face_message()
  if data.result == True:
    print("user count = " + str(data.user_count))
  status = face.delete_all_face_id()
  if status == True:
    print("delete face id success")
  time.sleep(2)
  
  print("face resgistering !")
  print("Please look straight into the camera.")
  
  face_reg = face.direct_registration()
  if face_reg.result:
    print("register direction = ", face_reg.direction)
    print("Direct view record success")
    print("Please look up.")
    face_reg = face.look_up_registration()

  if face_reg.result:
    print("register direction = ", face_reg.direction)
    print("look up view record success")
    print("Please look down.")
    face_reg = face.look_down_registration()
  
  if face_reg.result:
    print("register direction = ", face_reg.direction)
    print("look down view record success")
    print("Please look to the left.")
    face_reg = face.turn_left_registration()
    
  if face_reg.result:
    print("register direction = ", face_reg.direction)
    print("turn left view record success")
    print("Please look to the right.")
    face_reg = face.turn_right_registration("five_raspberry")

  if face_reg.result:
    print("turn right view record success")
    print("five face resgistering success!")
    print("register user id = ", face_reg.user_id)
    print("register direction = ", face_reg.direction)
  else:
    print("five face resgistering error!");
    print("error code = ", faceReg.errorCode)
  

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

if __name__ == "__main__":
  setup()
  while True:
    loop()
