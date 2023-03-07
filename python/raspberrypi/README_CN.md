# DFRobot_GNSS
- [English Version](./README.md)


![正反面svg效果图](../../resources/images/TEL0157.jpg)


## 产品链接(https://www.dfrobot.com.cn/goods-3652.html)

    SKU：TEL0157

## 目录

* [概述](#概述)
* [库安装](#库安装)
* [方法](#方法)
* [兼容性](#兼容性)
* [历史](#历史)
* [创作者](#创作者)

## 概述


## 库安装
1. 下载库至树莓派，要使用这个库，首先要将库下载到Raspberry Pi，命令下载方法如下:

```
sudo git clone https://github.com/DFRobot/DFRobot_GNSS
```

1. 打开并运行例程，要执行一个例程demo_x.py，请在命令行中输入python demo_x.py。例如，要执行 i2c.py例程，你需要输入:

```
python get_gnss.py
或 
python2 get_gnss.py
或 
python3 get_gnss.py
```

## 方法

```python
  '''!
    @brief 初始化传感器
  '''
  def begin(self):

  '''!
    @brief 获取年月日等日期
    @return struct_utc_tim 类型，表示返回的年月日
  '''
  def get_date(self):

  '''!
    @brief 获取年月日等日期
    @return struct_utc_tim 类型，表示返回的时分秒
  '''
  def get_utc(self):

  '''!
    @brief 获取纬度
    @return struct_lat_lon 类型，表示返回的纬度
  '''
  def get_lat(self):

  '''!
    @brief 获取经度
    @return struct_lat_lon 类型，表示返回的经度
  '''
  def get_lon(self):

  '''!
    @brief 获取使用的卫星数
    @return 表示使用的卫星数
  '''
  def get_num_sta_used(self):

  '''!
    @brief 获取大地的高度
    @return double 类型，表示大地的高度
  '''
  def get_alt(self):

  '''!
    @brief 获取对地真航向
    @return 浮点型数据 （单位 度）
  '''
  def get_cog(self):

  '''!
    @brief 获取对地速度
    @return speed 浮点型数据 （单位 节）
  '''
  def get_sog(self):

  '''!
    @brief 获取使用的星系模式
    @return mode
    @retval 1 使用 gps
    @retval 2 使用 beidou
    @retval 3 使用 gps + beidou
    @retval 4 使用 glonass
    @retval 5 使用 gps + glonass
    @retval 6 使用 beidou +glonass
    @retval 7 使用 gps + beidou + glonass
  '''
  def get_gnss_mode(self):

  '''!
    @brief 设置星系
    @param mode
    @n   GPS              使用 gps
    @n   BeiDou           使用 beidou
    @n   GPS_BeiDou       使用 gps + beidou
    @n   GLONASS          使用 glonass
    @n   GPS_GLONASS      使用 gps + glonass
    @n   BeiDou_GLONASS   使用 beidou +glonass
    @n   GPS_BeiDou_GLONASS 使用 gps + beidou + glonass
  '''
  def set_gnss(self, mode):

  '''!
    @brief 获取gnss的数据
  '''
  def get_all_gnss(self):

  '''!
    @brief 使能gnss 电源
  '''
  def enable_power(self):

  '''!
    @brief 失能gnss 电源,此时gnss不更新数据
  '''
  def disable_power(self):
  
  '''!
    @brief 开启rgb
  '''
  def rgb_on(self):
  
  '''!
    @brief 关闭rgb
  '''
  def rgb_off(self):
```

## 兼容性

* RaspberryPi Version

| Board        | 正常运行  | 运行失败   | 未测试    | 备注
| ------------ | :-------: | :--------: | :------: | :-----: |
| RaspberryPi2 |           |            |    √     |         |
| RaspberryPi3 |           |            |    √     |         |
| RaspberryPi4 |     √     |            |          |         |

* Python版本

| Python  | 正常运行  | 运行失败   | 未测试    | 备注
| ------- | :-------: | :--------: | :------: | :-----: |
| Python2 |     √     |            |          |         |
| Python3 |     √     |            |          |         |


## 历史

- 2022/8/17 - V0.0.1 版本
- 2022/10/26 - V1.0.0 版本

## 创作者

Written by ZhixinLiu(zhixin.liu@dfrobot.com), 2022. (Welcome to our website)