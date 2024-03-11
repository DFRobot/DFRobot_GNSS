# -*- coding: utf-8 -*
'''!
  @file DFRobot_GNSS.py
  @brief DFRobot_GNSS Class infrastructure, implementation of underlying methods
  @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license The MIT License (MIT)
  @author [ZhixinLiu](zhixin.liu@dfrobot.com)
  @version V1.0
  @date 2020-10-26
  @url https://github.com/DFRobot/DFRobot_GNSS
'''
import serial
import time
import smbus

I2C_MODE  = 0x01
UART_MODE = 0x02


GNSS_DEVICE_ADDR = 0x20
I2C_YEAR_H = 0
I2C_YEAR_L = 1
I2C_MONTH = 2
I2C_DATE  = 3
I2C_HOUR  = 4
I2C_MINUTE = 5
I2C_SECOND = 6
I2C_LAT_1 = 7
I2C_LAT_2 = 8
I2C_LAT_X_24 = 9
I2C_LAT_X_16 = 10
I2C_LAT_X_8  = 11
I2C_LAT_DIS  = 12
I2C_LON_1 = 13
I2C_LON_2 = 14
I2C_LON_X_24 = 15
I2C_LON_X_16 = 16
I2C_LON_X_8  = 17
I2C_LON_DIS  = 18
I2C_USE_STAR = 19
I2C_ALT_H = 20
I2C_ALT_L = 21
I2C_ALT_X = 22
I2C_SOG_H = 23
I2C_SOG_L = 24
I2C_SOG_X = 25
I2C_COG_H = 26
I2C_COG_L = 27
I2C_COG_X = 28
I2C_START_GET = 29
I2C_ID = 30
I2C_DATA_LEN_H = 31
I2C_DATA_LEN_L = 32
I2C_ALL_DATA = 33
I2C_GNSS_MODE = 34
I2C_SLEEP_MODE = 35
I2C_RGB_MODE = 36

ENABLE_POWER = 0
DISABLE_POWER = 1

RGB_ON = 0x05
RGB_OFF = 0x02
GPS = 1
BeiDou = 2
GPS_BeiDou = 3
GLONASS = 4
GPS_GLONASS = 5
BeiDou_GLONASS = 6
GPS_BeiDou_GLONASS = 7



class struct_utc_tim:
  def __init__(self):
    self.year=2000
    self.month=1
    self.date=1
    self.hour=0
    self.minute=0
    self.second=0

class struct_lat_lon:
  def __init__(self):
    self.lat_dd = 0
    self.lat_mm = 0
    self.lat_mmmmm = 0
    self.lat_direction = "S"
    self.latitude_degree = 0.00
    self.latitude = 0.00
    self.lon_ddd = 0
    self.lon_mm = 0
    self.lon_mmmmm = 0
    self.lon_direction = "W"
    self.lonitude = 0.00
    self.lonitude_degree = 0.00

utc = struct_utc_tim()
lat_lon = struct_lat_lon()


class DFRobot_GNSS(object):
  __m_flag   = 0                # mode flag
  __count    = 0                # acquisition count    
  __txbuf        = [0]          # i2c send buffer
  __gnss_all_data  = [0]*1300     # gnss data
  __uart_i2c     =  0
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
      @brief Init sensor 
    '''
    rslt = self.read_reg(I2C_ID, 1)
    time.sleep(0.1)
    if rslt == -1:
      return False
    if rslt[0] != GNSS_DEVICE_ADDR:
      return False
    return True

  def get_date(self):
    '''!
      @brief Get date information, year, month, day 
      @return struct_utc_tim type, represents the returned year, month, day
    '''
    rslt = self.read_reg(I2C_YEAR_H, 4)
    if rslt != -1:
      utc.year = rslt[0]*256 + rslt[1]
      utc.month = rslt[2]
      utc.date = rslt[3]
    return utc

  def get_utc(self):
    '''!
      @brief Get time information, hour, minute second 
      @return struct_utc_tim type, represents the returned hour, minute, second 
    '''
    rslt = self.read_reg(I2C_HOUR, 3)
    if rslt != -1:
      utc.hour = rslt[0]
      utc.minute = rslt[1]
      utc.second = rslt[2]
    return utc


  def get_lat(self):
    '''!
      @brief Get latitude 
      @return struct_lat_lon type, represents the returned latitude 
    '''
    rslt = self.read_reg(I2C_LAT_1, 6)
    if rslt != -1:
      lat_lon.lat_dd = rslt[0]
      lat_lon.lat_mm = rslt[1]
      lat_lon.lat_mmmmm = rslt[2]*65536 + rslt[3]*256 + rslt[4]
      lat_lon.lat_direction = chr(rslt[5])
      lat_lon.latitude = lat_lon.lat_dd*100.0 + lat_lon.lat_mm + lat_lon.lat_mmmmm/100000.0
      lat_lon.latitude_degree = lat_lon.lat_dd + lat_lon.lat_mm/60.0 + lat_lon.lat_mmmmm/100000.0/60.0
    return lat_lon

  def get_lon(self):
    '''!
      @brief Get longitude 
      @return struct_lat_lon type, represents the returned longitude 
    '''
    rslt = self.read_reg(I2C_LON_1, 6)
    if rslt != -1:
      lat_lon.lon_ddd = rslt[0]
      lat_lon.lon_mm = rslt[1]
      lat_lon.lon_mmmmm = rslt[2]*65536 + rslt[3]*256 + rslt[4]
      lat_lon.lon_direction = chr(rslt[5])
      lat_lon.lonitude = lat_lon.lon_ddd*100.0 + lat_lon.lon_mm + lat_lon.lon_mmmmm/100000.0
      lat_lon.lonitude_degree = lat_lon.lon_ddd + lat_lon.lon_mm/60.0 + lat_lon.lon_mmmmm/100000.0/60.0
    return lat_lon

  def get_num_sta_used(self):
    '''!
      @brief Get the number of the used satellites 
      @return The number of the used satellites 
    '''
    rslt = self.read_reg(I2C_USE_STAR, 1)
    if rslt != -1:
      return rslt[0]
    else:
      return 0

  def get_alt(self):
    '''!
      @brief Get altitude 
      @return double type, represent the altitude 
    '''
    rslt = self.read_reg(I2C_ALT_H, 3)
    if rslt != -1:
      high = rslt[0]*256 + rslt[1] + rslt[2]/100.0
    else:
      high = 0.0
    return high

  def get_cog(self):
    '''!
      @brief Get course over ground 
      @return Float data(unit: degree)
    '''
    rslt = self.read_reg(I2C_COG_H, 3)
    if rslt != -1:
      cog = rslt[0]*256 + rslt[1] + rslt[2]/100.0
    else:
      cog = 0.0
    return cog

  def get_sog(self):
    '''!
      @brief Get speed over ground 
      @return speed Float data (unit: knot)
    '''
    rslt = self.read_reg(I2C_SOG_H, 3)
    if rslt != -1:
      sog = rslt[0]*256 + rslt[1] + rslt[2]/100.0
    else:
      sog = 0.0 
    return sog

  def get_gnss_mode(self):
    '''!
      @brief Get the used GNSS mode 
      @return mode
      @retval 1 gps
      @retval 2 beidou
      @retval 3 gps + beidou
      @retval 4 glonass
      @retval 5 gps + glonass
      @retval 6 beidou +glonass
      @retval 7 gps + beidou + glonass
    '''
    rslt = self.read_reg(I2C_GNSS_MODE, 1)
    return rslt[0]

  def set_gnss(self, mode):
    '''!
      @brief Set GNSS to be used 
      @param mode
      @n   GPS              use gps
      @n   BeiDou           use beidou
      @n   GPS_BeiDou       use gps + beidou
      @n   GLONASS          use glonass
      @n   GPS_GLONASS      use gps + glonass
      @n   BeiDou_GLONASS   use beidou +glonass
      @n   GPS_BeiDou_GLONASS use gps + beidou + glonass
    '''
    self.__txbuf[0] = mode
    self.write_reg(I2C_GNSS_MODE, self.__txbuf)
    time.sleep(0.1)
  
  def enable_power(self):
    '''!
      @brief Enable gnss power
    '''
    self.__txbuf[0] = ENABLE_POWER
    self.write_reg(I2C_SLEEP_MODE, self.__txbuf)
    time.sleep(0.1)
    
  def disable_power(self):
    '''!
      @brief Disable gnss power, the GNSS data will not be refreshed this time 
    '''
    self.__txbuf[0] = DISABLE_POWER
    self.write_reg(I2C_SLEEP_MODE, self.__txbuf)
    time.sleep(0.1)
    

  def rgb_on(self):
    '''!
      @brief Turn rgb on 
    '''
    self.__txbuf[0] = RGB_ON
    self.write_reg(I2C_RGB_MODE, self.__txbuf)
    time.sleep(0.1)
  
  def rgb_off(self):
    '''!
      @brief Turn rgb off
    '''
    self.__txbuf[0] = RGB_OFF
    self.write_reg(I2C_RGB_MODE, self.__txbuf)
    time.sleep(0.1)

  def get_gnss_len(self):
    '''!
      @brief Get length of GNSS data 
      @return length of GNSS data 
    '''
    self.__txbuf[0] = 0x55
    self.write_reg(I2C_START_GET, self.__txbuf)
    time.sleep(0.1)
    rslt = self.read_reg(I2C_DATA_LEN_H, 2)
    if rslt != -1:
      return rslt[0]*256 + rslt[1]
    else:
      return 0

  def get_all_gnss(self):
    '''!
      @brief Get gnss data
    '''
    len = self.get_gnss_len()
    time.sleep(0.1)
    all_data = [0]*(len+1)
    len1 = (len) / 32
    len2 = ((len)%32) 
    for num in range (0, len1+1):
      if num == len1:
        rslt = self.read_reg(I2C_ALL_DATA, len2)
        for i in range (0, len2):
          if rslt[i] == 0:
            rslt[i] = 0x0A
        all_data[num*32:] = rslt
      else:
        rslt = self.read_reg(I2C_ALL_DATA, 32)
        for i in range (0, 32):
          if rslt[i] == 0:
            rslt[i] = 0x0A
        all_data[num*32:] = rslt
    return all_data

class DFRobot_GNSS_I2C(DFRobot_GNSS): 
  def __init__(self, bus, addr):
    self.__addr = addr
    super(DFRobot_GNSS_I2C, self).__init__(bus,0)

  def write_reg(self, reg, data):
    while 1:
      try:
        self.i2cbus.write_i2c_block_data(self.__addr, reg, data)
        return
      except:
        print("please check connect!")
        time.sleep(1)

  def read_reg(self, reg, len):
    try:
      rslt = self.i2cbus.read_i2c_block_data(self.__addr, reg, len)
    except:
      rslt = -1
      
    return rslt

class DFRobot_GNSS_UART(DFRobot_GNSS):

  def __init__(self, Baud):
    self.__Baud = Baud
    super(DFRobot_GNSS_UART, self).__init__(0, Baud)

  def write_reg(self, reg, data):
    send = [0]*2
    send[0] = reg|0x80
    send[1] = data[0]
    self.ser.write(send)
    return

  def read_reg(self, reg, len):
    recv = [0]*len
    send = [0]*2
    send[0] = reg&0x7F
    send[1] = len
    self.ser.write(send)
    time.sleep(0.05)
    timenow = time.time()
    while(time.time() - timenow) <= 1:
      count = self.ser.inWaiting()
      if count != 0:
        recv = self.ser.read(count)
        self.ser.flushInput()
        recv =[ord(c) for c in recv]
        return recv
    return recv
