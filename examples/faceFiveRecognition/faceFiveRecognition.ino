 /*!
  * @file  faceRecognition.ino
  * @brief  face recognition demo
  * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  * @license The MIT License (MIT)
  * @author ZhixinLiu(zhixin.liu@dfrobot.com)
  * @version V1.0
  * @date 2023-12-07
  * @url https://github.com/dfrobot/DFRobot_3DFace
  */

#include "DFRobot_3DFace.h"

#define I2C_COMMUNICATION  //use I2C for communication, but use the serial port for communication if the line of codes were masked

#ifdef  I2C_COMMUNICATION
  DFRobot_3DFace_I2C face(&Wire ,DEVICE_ADDR);
#else
/* ---------------------------------------------------------------------------------------------------------------------
 *    board   |             MCU                | Leonardo/Mega2560/M0 |    UNO    | ESP8266 | ESP32 |  microbit  |   m0  |
 *     VCC    |            3.3V/5V             |        VCC           |    VCC    |   VCC   |  VCC  |     X      |  vcc  |
 *     GND    |              GND               |        GND           |    GND    |   GND   |  GND  |     X      |  gnd  |
 *     RX     |              TX                |     Serial1 TX1      |     5     |   5/D6  |  D2   |     X      |  tx1  |
 *     TX     |              RX                |     Serial1 RX1      |     4     |   4/D7  |  D3   |     X      |  rx1  |
 * ----------------------------------------------------------------------------------------------------------------------*/
/* Baud rate cannot be changed */
  #if defined(ARDUINO_AVR_UNO) || defined(ESP8266)
    SoftwareSerial mySerial(4, 5);
    DFRobot_3DFace_UART face(&mySerial ,57600);
  #elif defined(ESP32)
    DFRobot_3DFace_UART face(&Serial1 ,57600 ,/*rx*/D2 ,/*tx*/D3);
  #else
    DFRobot_3DFace_UART face(&Serial1 ,57600);
  #endif
#endif

void setup()
{
  Serial.begin(115200);
  while(!face.begin()){
    Serial.println("NO Deivces !");
    delay(1000);
  } 
  Serial.println("Device connected!");
  face.setStandby();

  sUserData_t data;
  sFaceReg_t  faceReg;
  data = face.getFaceMessage();
  if(data.result == true){
    Serial.print("user count = ");
    Serial.println(data.user_count);
  }

  if(face.delAllFaceID()){
    Serial.println("delete face id success!");
  }

  delay(2000);
  Serial.println("face resgistering !");
  Serial.println("Please look straight into the camera.");
  faceReg = face.directRegistration();
  if(faceReg.result){
    Serial.print("register      direction = ");
    Serial.println(faceReg.direction);
    Serial.println("Direct view record success");
    Serial.println();
    Serial.println("Please look up.");
    faceReg = face.lookUpRegistration();
  }
  if(faceReg.result){
    Serial.print("register      direction = ");
    Serial.println(faceReg.direction);
    Serial.println("look up view record success");
    Serial.println();
    Serial.println("Please look down.");
    faceReg = face.lookDownRegistration();
  }
  if(faceReg.result){
    Serial.print("register      direction = ");
    Serial.println(faceReg.direction);
    Serial.println("loop down view record success");
    Serial.println();
    Serial.println("Please look to the left.");
    faceReg = face.turnLeftRegistration();
  }
  if(faceReg.result){
    Serial.print("register      direction = ");
    Serial.println(faceReg.direction);
    Serial.println("turn left view record success");
    Serial.println();
    Serial.println("Please look to the right.");
    faceReg = face.turnRightRegistration("3333333333333333333333");
  }

  if(faceReg.result){
    Serial.println("turn right view record success");
    Serial.println("five face resgistering success!");
    Serial.print("regiseter     user id = ");
    Serial.println(faceReg.userID);
    Serial.print("register      direction = ");
    Serial.println(faceReg.direction);
    Serial.println();
  }else{
    Serial.println("five face resgistering error!");
    Serial.print("error code = ");
    Serial.println(faceReg.errorCode);
    Serial.println();
  }
}

void loop()
{
  sFaceMatching_t matching;
  Serial.println("face matching ..............");
  matching = face.faceMatching();
  if(matching.result){
    Serial.println("face matching success!");
    Serial.print("matching   user id = ");
    Serial.println(matching.userID);
    Serial.print("matching   name  = ");
    Serial.println((char*)matching.name);
    Serial.print("matching   admin = ");
    Serial.println(matching.admin);
    Serial.println();
  }else{
    Serial.println("face matching error !");
    Serial.print("error code = ");
    Serial.println(matching.errorCode);
    Serial.println();
  }
  delay(3000);
}