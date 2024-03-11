# -*- coding: utf-8 -*
'''!
  @file DFRobot_3DFace.py
  @brief DFRobot_3DFace Class infrastructure, implementation of underlying methods
  @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license The MIT License (MIT)
  @author [ZhixinLiu](zhixin.liu@dfrobot.com)
  @version V1.0
  @date 2024-03-06
  @url https://github.com/DFRobot/DFRobot_3DFace
'''
import serial
import time
import smbus
import sys

I2C_MODE = 0x01
UART_MODE = 0x02
DEVICE_ADDR = 0X20
REG_GERENEL_CMD = 0X10
USER = 0x00              # The registration mode is administrator mode or user mode
ADMIN = 0x01
ONE_REG = 0x01           # Single registration or five-item registration
FIVE_REG = 0x00
DIRECT_VIEW = 0X01
LOOK_UP_VIEW = 0x10
LOOK_DOWN_VIEW = 0X08
LOOK_LEFT_VIEW = 0X04
LOOK_RIGHT_VIEW = 0X02
REG_WRITE_AT_LONG = 0x39
REG_WRITE_AT = 0x40
REG_READ_AT_LEN = 0x41
REG_READ_AT = 0x42
ERROR_CODE = 0x6
C_SUCCESS = 0x0
C_REJECT = 0x1
  

class struct_result_data:
  def __init__(self):
    self.result = False
    self.user_count = 0
    self.rslt = [0]*200
    self.lenght = 0

class struct_face_reg:
  def __init__(self):
    self.user_id = 0
    self.result  = False
    self.direction  = 0
    self.error_code = 0

class struct_face_matching:
  def __init__(self):
    self.user_id = 0
    self.result  = False
    self.name = [0]*32
    self.admin = True
    self.state  = 0
    self.error_code = 0

class DFRobot_3DFace(object):
  __uart_i2c     =  0
  __speed_null_count = 0
  def __init__(self, bus, Baud):
    if bus != 0:
      self.i2cbus = smbus.SMBus(bus)
      self.__uart_i2c = I2C_MODE
    else:
      self.ser = serial.Serial("/dev/ttyAMA0", baudrate=Baud,stopbits=1, timeout=0.5)
      self.__uart_i2c = UART_MODE
      if self.ser.isOpen == False:
        self.ser.open()

  def begin(self):
    '''!
      @brief begin
      @return True 
    '''
    if self.__uart_i2c == UART_MODE:
      self.read_reg(REG_READ_AT_LEN, 0)  # flash uart rx
    return True

  def set_standby(self):
    '''!
      @brief Set it to standby mode. 
      @n     The driver module can work properly only in this mode
      @return True or False
    '''
    length = 0
    tx_temp = [0xEF, 0xAA, 0x23, 0x00, 0x00, 0x23]
    self.write_reg(REG_WRITE_AT, tx_temp)
    if self.__uart_i2c == I2C_MODE:
      while True:
        time.sleep(0.1)
        rslt = self.read_reg(REG_READ_AT_LEN, 5)
        length = rslt[0]
        if(length != 0):
          rslt = self.read_reg(REG_READ_AT, length)
          return True
    else:
      while True:
        rslt = self.read_reg(REG_READ_AT_LEN, 0)
        result_list = [byte for byte in rslt]
        if len(result_list) != 0:
          return True

  def delete_face_id(self, number):
    '''!
      @brief Deletes the specified face id
      @param number delete face id
      @return True or False
    '''
    tx_temp = [0xEF, 0xAA, 0x20, 0x00, 0x02, 0x00, 0x00, 0x00]
    tx_temp[5] = (number>>8)&0xff
    tx_temp[6] = (number&0xff)
    tx_temp[7] = self.get_parity_check(tx_temp, 7)
    self.set_standby()
    time.sleep(0.1)
    self.write_reg(REG_WRITE_AT, tx_temp)
    time.sleep(0.1)
    if self.__uart_i2c == I2C_MODE:
      while True:
        time.sleep(0.5)
        rslt = self.read_reg(REG_READ_AT_LEN, 5)
        len1 = rslt[0]
        if(len1 != 0):
          rslt = self.read_reg(REG_READ_AT, len1)
          if rslt[ERROR_CODE] == C_SUCCESS:
            return True
          else:
            return False
    else:
      while True:
        time.sleep(0.1)
        rslt = self.read_reg(REG_READ_AT_LEN, 0)
        result_list = [byte for byte in rslt]
        len1 = len(result_list)
        if len1 != 0:
          if result_list[ERROR_CODE] == C_SUCCESS:
            return True
          else:
            return False
    

  def delete_all_face_id(self):
    '''!
      @brief Delete all facial information
      @return True or False
    '''
    tx_temp = [0xEF, 0xAA, 0x21, 0x00, 0x00, 0x00]
    tx_temp[5] = self.get_parity_check(tx_temp, 5)
    self.set_standby()
    time.sleep(0.1)
    self.write_reg(REG_WRITE_AT, tx_temp)
    
    if self.__uart_i2c == I2C_MODE:
      while True:
        time.sleep(0.5)
        rslt = self.read_reg(REG_READ_AT_LEN, 5)
        len1 = rslt[0]
        if(len1 != 0):
          rslt = self.read_reg(REG_READ_AT, len1)
          if rslt[ERROR_CODE] == C_SUCCESS:
            return True
          else:
            return False
    else:
      while True:
        time.sleep(0.1)
        rslt = self.read_reg(REG_READ_AT_LEN, 0)
        result_list = [byte for byte in rslt]
        len1 = len(result_list)
        if len1 != 0:
          if result_list[ERROR_CODE] == C_SUCCESS:
            return True
          else:
            return False
    

  def direct_registration(self, name="", timerout=0x0a):
    '''!
      @brief Look direct at face registration
      @param name must is null
      @param timerout
      @return struct_face_reg
    '''
    return self.face_registration("", ADMIN, DIRECT_VIEW, FIVE_REG, 1, timerout)

  def look_up_registration(self, name="", timerout=0x0a):
    '''!
      @brief Look up at face registration
      @param name must is null
      @param timerout
      @return struct_face_reg
    '''
    return self.face_registration("", ADMIN, LOOK_UP_VIEW, FIVE_REG, 1, timerout)
  
  def look_down_registration(self, name="", timerout=0x0a):
    '''!
      @brief Look down at face registration
      @param name must is null
      @param timerout
      @return struct_face_reg
    '''
    return self.face_registration("", ADMIN, LOOK_DOWN_VIEW, FIVE_REG, 1, timerout)

  def turn_left_registration(self, name="", timerout=0x0a):
    '''!
      @brief Look left at face registration
      @param name must is null
      @param timerout
      @return struct_face_reg
    '''
    return self.face_registration("", ADMIN, LOOK_LEFT_VIEW, FIVE_REG, 1, timerout)

  def turn_right_registration(self, name="", timerout=0x0a):
    '''!
      @brief Look right at face registration
      @param name register name
      @param timerout
      @return struct_face_reg
    '''
    return self.face_registration(name, ADMIN, LOOK_RIGHT_VIEW, FIVE_REG, 1, timerout)

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
    face = struct_face_reg()
    tx_temp = [0]*46
    tx_temp[0] = 0xEF
    tx_temp[1] = 0xAA
    tx_temp[2] = 0x26
    tx_temp[3] = 0x00
    tx_temp[4] = 0x28
    tx_temp[5] = mode
    if len(name) != 0:
      tx_temp[6:6+len(name)] = [ord(c) for c in name]
    tx_temp[38] = direction
    tx_temp[39] = reg_type
    tx_temp[40] = repetition
    tx_temp[41] = timerout
    tx_temp[45] = self.get_parity_check(tx_temp, 45)
    if reg_type == ONE_REG or direction == DIRECT_VIEW:
      time.sleep(0.1)
      self.set_standby()
      time.sleep(0.1)
    self.write_reg(REG_WRITE_AT, tx_temp)
    i2c_count = 0    
    if self.__uart_i2c == I2C_MODE:
      while True:
        i2c_count += 1
        if i2c_count > 20:
          time.sleep(0.1)
          self.set_standby()
          return face  
        time.sleep(0.1)
        rslt = self.read_reg(REG_READ_AT_LEN, 5)
        len1 = rslt[0]
        if len1 != 0:
          rslt = self.read_reg(REG_READ_AT, len1)
          time.sleep(0.1)
          count = self.wait_true_data(rslt, len1)
          if count != -1:
            time.sleep(0.1)
            face.error_code = rslt[count+6]
            if rslt[ERROR_CODE] != C_SUCCESS:
              face.result = False
            else:
              face.result = True
              face.user_id = (rslt[count+7] << 8) | rslt[count+8]
              face.direction = rslt[count+9]
              rslt = self.read_reg(REG_READ_AT_LEN, 5)
              len2 = rslt[0]
              rslt = self.read_reg(REG_READ_AT, len2)
              if reg_type == ONE_REG or direction == LOOK_RIGHT_VIEW:
                time.sleep(0.1)
                self.set_standby()    
            return face
          else:
            pass
        else:
          pass
    else:
      while True:
        time.sleep(0.1)
        rslt = self.read_reg(REG_READ_AT, 0)
        result_list = [byte for byte in rslt]
        len1 = len(result_list) 
        if len1 != 0:
          count = self.wait_true_data(result_list, len1)
          if count != -1:
            time.sleep(0.1)
            face.error_code = rslt[count+6]
            if rslt[ERROR_CODE] != C_SUCCESS:
              face.result = False
            else:
              face.result = True
              face.user_id = (rslt[count+7] << 8) | rslt[count+8]
              face.direction = rslt[count+9]
            if reg_type == ONE_REG or direction == LOOK_RIGHT_VIEW:
              time.sleep(0.1)
              self.set_standby()    
            return face
    return face

  def face_matching(self):
    '''!
      @brief face_matching
      @return match
    '''
    face = struct_face_matching()
    tx_temp = [0xEF, 0xAA, 0x12, 0x00, 0x02, 0x00, 0x00, 0x00]
    tx_temp[5] = 0x00
    tx_temp[6] = 0x15
    tx_temp[7] = self.get_parity_check(tx_temp, 7)    
    time.sleep(0.1)
    self.set_standby()
    time.sleep(0.1)
    self.write_reg(REG_WRITE_AT, tx_temp)
    if self.__uart_i2c == I2C_MODE:
      while True:
        time.sleep(0.5)
        rslt = self.read_reg(REG_READ_AT_LEN, 5)
        len1 = rslt[0]
        rslt = self.read_reg(REG_READ_AT, len1)
        if len1 != 0:
          count = self.wait_true_data(rslt, len1)
          if count != -1:
            time.sleep(0.1)
            face.error_code = rslt[count+6]
            if rslt[ERROR_CODE] != C_SUCCESS:
              face.result = False
            else:            
              face.result = True
              face.user_id = (rslt[count+7] << 8) | rslt[count+8]
              face.admin = rslt[count+41]
              face.state = rslt[count+42]
              char_list = [chr(num) for num in rslt[count+9: count+9+32]]
              result_string = ''.join(char_list)
              face.name = result_string
            time.sleep(0.1)
            rslt = self.read_reg(REG_READ_AT_LEN, 5)
            len1 = rslt[0]
            time.sleep(0.1)
            rslt = self.read_reg(REG_READ_AT, len1)
            time.sleep(0.1)
            self.set_standby()
            time.sleep(0.1)    
            return face
    else:
      while True:
        time.sleep(1.2)      # must delay time
        rslt = self.read_reg(REG_READ_AT_LEN, 0)
        result_list = [byte for byte in rslt]
        len1 = len(result_list)
        if len1 != 0:
          count = self.wait_true_data(result_list, len1)
          if count != -1:
            time.sleep(0.1)
            face.error_code = result_list[count+6]
            if rslt[ERROR_CODE] != C_SUCCESS:
              face.result = False
            else:
              face.result = True
              face.user_id = (result_list[count+7] << 8) | result_list[count+8]
              face.admin = result_list[count+41]
              face.state = result_list[count+42]
              char_list = [chr(num) for num in result_list[count+9: count+9+32]]
              result_string = ''.join(char_list)
              face.name = result_string
            time.sleep(0.1)
            rslt = self.read_reg(REG_READ_AT_LEN, 0)  
            time.sleep(0.1)
            self.set_standby()
            time.sleep(0.1)    
            return face
      return face

  def wait_true_data(self, data, length):
    '''!
      @brief wait_true_data
      @return number wait true data
    '''
    for i in range(len(data)):
      if data[i] == 0xEF and data[i+1] == 0xAA and data[i+2] == 0x00:
        return 0
    return -1
    
  def get_face_message(self):
    '''!
      @brief get_face_message
      @return struct_result_data
    '''
    data = struct_result_data()
    tx_temp = [0xEF, 0xAA, 0x24, 0x00, 0x00, 0x00]
    tx_temp[5] = self.get_parity_check(tx_temp, 5)
    self.set_standby()
    time.sleep(0.1)
    self.write_reg(REG_WRITE_AT, tx_temp)
    if self.__uart_i2c == I2C_MODE:
      time.sleep(0.1)
      rslt = self.read_reg(REG_READ_AT_LEN, 5)
      len1 = rslt[0]
      result = [0]*len1
      if(len1 != 0):
        rslt = self.read_reg(REG_READ_AT, len1)
        if rslt[ERROR_CODE] != C_SUCCESS:
          data.result = False
        data.user_count = rslt[7]
        data.result = True
        data.rslt = rslt[8:len1]
      else:
        data.result = False
      return data
    else:
      time.sleep(0.1)
      rslt = self.read_reg(REG_READ_AT_LEN, 0)
      result_list = [byte for byte in rslt]
      len1 = len(result_list)
      if len1 != 0:
        if rslt[ERROR_CODE] != C_SUCCESS:
          data.result = False
        data.user_count = result_list[7]
        data.result = True
        data.rslt == result_list[8:len1]
      else:
        data.result = False
      return data

  def get_parity_check(self, p, length):
    '''!
      @brief get_parity_check
      @param p data point
      @param len
      @return check_result
    '''
    parity_check = 0
    for i in range(2, length):
        parity_check ^= p[i]
    return parity_check

class DFRobot_3DFace_I2C(DFRobot_3DFace): 
  def __init__(self, bus, addr):
    self.__addr = addr
    super(DFRobot_3DFace_I2C, self).__init__(bus,0)

  def write_reg(self, reg, data):
    while 1:
      try:
        if len(data) > 31:
          self.i2cbus.write_i2c_block_data(self.__addr, REG_WRITE_AT_LONG, data[0:31])
          time.sleep(0.01)
          self.i2cbus.write_i2c_block_data(self.__addr, reg, data[31:len(data)])
        else:
          self.i2cbus.write_i2c_block_data(self.__addr, reg, data)
        return
      except:
        print("please check connect!")
        time.sleep(1)

  def read_reg(self, reg, len):
    rslt = [0]*len
    count = 0
    try:
      while len > 0:
        if len > 32:
          rslt1 = self.i2cbus.read_i2c_block_data(self.__addr, reg, 32)
          len -= 32
          j = 0
          for i in range(count, count+32):
            rslt[i] = rslt1[j]
            j += 1
          count += 32
          time.sleep(0.05)
        else:
          rslt1 = self.i2cbus.read_i2c_block_data(self.__addr, reg, len)
          for i in range(0, len):
            if count < 32:
              rslt[i] = rslt1[i]
            else:
              rslt[i+count] = rslt1[i]
          len = 0
    except:
      rslt[0] = -1
    return rslt

class DFRobot_3DFace_UART(DFRobot_3DFace):

  def __init__(self, Baud):
    self.__uart_i2c = UART_MODE
    self.__Baud = Baud 
    super(DFRobot_3DFace_UART, self).__init__(0, Baud)

  def write_reg(self, reg, data):
    self.ser.flushInput()
    self.ser.write(data)
    return

  def read_reg(self, reg, len):
    recv = [0]*len
    timenow = time.time()  
    while(time.time() - timenow) <= 0.5:
      count = self.ser.inWaiting()
      if count != 0:
        if len == 0:
          recv = self.ser.read(count)
        else:
          recv = self.ser.read(len)
        self.ser.flushInput()
        return recv
    return recv