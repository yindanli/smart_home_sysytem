/**************************************************************

Name:      Gizwits + ArduinoUno + raspiberry_bluetooth
Author:   danli
Version:  V1.0
Init:     2016-12-23
Modify:   2020-04-10
****************************************************************/
#include <Arduino.h>//Arduino库
#include <Gizwits.h>//机智云库
#include <Wire.h>
#include <SoftwareSerial.h>//软串口
#include <Servo.h>//舵机
#include <dht11.h>//温湿度
#include <U8x8lib.h>//OLED
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

#include "voice.h"//语音播报
#include "function_test.h"   //功能函数
SoftwareSerial mySerial(13,4);   //给蓝牙HC-05使用的串口，RX ,TX = 13,4

//Servo myservo;     //控制门的舵机
//Servo windowservo;  //控制窗户的舵机
Gizwits myGizwits;
dht11 DHT11;
int pos = 0;            //  初始化舵机位置
//int smokepin = 2;    //烟雾报警器
//int fanpin = 6;      //净化器
//int fengminqipin = 7;//蜂鸣器
//int myledPin = 8;    // 客厅灯
//int servopin = 9;    //门servo舵机
//int windowservopin = 12; //窗servo舵机
//int hotwaterpin = 10;//热水器
//int pwmpin =11;      //卧室灯



bool varR_LED_OnOff = 0;
bool varR_jinghuaqi = 0;

#define   KEY1              6
#define   KEY2              7
#define   KEY1_SHORT_PRESS  1
#define   KEY1_LONG_PRESS   2
#define   KEY2_SHORT_PRESS  4
#define   KEY2_LONG_PRESS   8
#define   NO_KEY            0
#define   KEY_LONG_TIMER    3

#define DHT11PIN A0           //读取A0温湿度

U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE); 
//int flag =0;
unsigned long Last_KeyTime = 0;

unsigned long gokit_time_s(void)
{
  return millis() / 1000;
}

//温湿度传感器
double Fahrenheit(double celsius) 
{
        return 1.8 * celsius + 32;
}    //摄氏温度度转化为华氏温度

double Kelvin(double celsius)
{
        return celsius + 273.15;
}     //摄氏温度转化为开氏温度

// 露点（点在此温度时，空气饱和并产生露珠）
// 参考: http://wahiduddin.net/calc/density_algorithms.htm 
double dewPoint(double celsius, double humidity)
{
        double A0= 373.15/(273.15 + celsius);
        double SUM = -7.90298 * (A0-1);
        SUM += 5.02808 * log10(A0);
        SUM += -1.3816e-7 * (pow(10, (11.344*(1-1/A0)))-1) ;
        SUM += 8.1328e-3 * (pow(10,(-3.49149*(A0-1)))-1) ;
        SUM += log10(1013.246);
        double VP = pow(10, SUM-3) * humidity;
        double T = log(VP/0.61078);   // temp var
        return (241.88 * T) / (17.558-T);
}

// 快速计算露点，速度是5倍dewPoint()
// 参考: http://en.wikipedia.org/wiki/Dew_point
double dewPointFast(double celsius, double humidity)
{
        double a = 17.271;
        double b = 237.7;
        double temp = (a * celsius) / (b + celsius) + log(humidity/100);
        double Td = (b * temp) / (a - temp);
        return Td;
}

//初始化
void setup() {
  Serial.begin(9600);     //esp-8266
  mySerial.begin(9600);   // hc-05
  myservo.attach(servopin);      //门舵机控制9
  myservo.write(0); //初始化门舵机
  windowservo.attach(windowservopin);  //窗户舵机控制12
  windowservo.write(0);
  pinMode(KEY1, INPUT_PULLUP);
  pinMode(KEY2, INPUT_PULLUP);
  pinMode(A0,INPUT);//A0 温湿度传感器 
  pinMode(smokepin,INPUT);//2 火灾报警
  pinMode(fanpin,OUTPUT);//6 净化器
  pinMode(fengminqipin,OUTPUT);//7 蜂鸣器
  pinMode(myledPin,OUTPUT);// 8 客厅灯
  pinMode(hotwaterpin,OUTPUT);//10 热水器
  pinMode(pwmpin,OUTPUT);//11 卧室灯
  myGizwits.begin();
  begin();
}

//OLED显示
void begin ()
{
  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(3,1,"SMART-HOME");
  u8x8.drawString(0,2,"Temp :");
  u8x8.drawString(0,3,"Hum  :");
  u8x8.drawString(0,4,"Pwm  :");
  u8x8.drawString(0,5,"Fire :");
  u8x8.drawString(0,6,"Danli's Home");
}

//Wifi配网
void wifiStatusHandle()
{
  if(myGizwits.wifiHasBeenSet(WIFI_CON_ROUTER)){}
}

int ketingdeng=1;
int reshuiqi=1;
int jinghuaqi=1;
int chuang=1;
//主函数
void loop() {  
  
  while(mySerial.available())  //如果串口可用
   {  char c;
      c=mySerial.read();
      mySerial.println (c);
      switch(c){
        case '1':servo_init();
        break;
        case '2':open_the_door();
        break;
        case '3':close_the_door();
        break;     
               }
   }

//烟雾报警
  unsigned long varW_fire = 0;
  if(digitalRead(smokepin))//安全是高电平
  {       
    u8x8.setCursor(6,5);
    u8x8.print("Safe");
    fengmingqi_close();
    attachInterrupt(digitalPinToInterrupt(2), fan_open,CHANGE); //中断函数
  }
  else
  {
    u8x8.setCursor(6,5);
    u8x8.print("Fire");
    fengmingqi_open();
    attachInterrupt(digitalPinToInterrupt(2), fan_close,CHANGE); //中断函数
    delay(1000);
    fengmingqi_close();  
  }
 
//温湿度OLED显示
  int chk = DHT11.read(DHT11PIN);
  unsigned long varW_wendu = (float)DHT11.temperature ;
  u8x8.setCursor(6,2);//这里设置显示的坐标
  u8x8.print(varW_wendu);//输出显示内容
  myGizwits.write(VALUE_wendu, varW_wendu);
  
  unsigned long varW_shidu = (float)DHT11.humidity ;
  u8x8.setCursor(6,3);//这里设置显示的坐标
  u8x8.print(varW_shidu);//输出显示内容
  myGizwits.write(VALUE_shidu, varW_shidu);

//客厅灯
  if(myGizwits.hasBeenSet(EVENT_LED_OnOff))
  {
    myGizwits.read(EVENT_LED_OnOff,&varR_LED_OnOff);
    if(ketingdeng==varR_LED_OnOff)
    {
      if(varR_LED_OnOff==1)
      {
        myled_open();
      }
      else
      {
        myled_close();  
      }
      ketingdeng=!varR_LED_OnOff;
    }
  }


//卧室灯
 unsigned long varR_tiaoguang = 0;
  if(myGizwits.hasBeenSet(EVENT_tiaoguang))
  {
      myGizwits.read(EVENT_tiaoguang,&varR_tiaoguang);//读取pwm值
      analogWrite(pwmpin,varR_tiaoguang); //把读取的值写入机智云中间变量
      u8x8.setCursor(6,4);//这里设置显示的坐标
      u8x8.print(varR_tiaoguang);//输出显示内容
  }


//热水器
bool varR_reshuiqi = 0;
  if(myGizwits.hasBeenSet(EVENT_reshiuqi))
  {
    myGizwits.read(EVENT_reshiuqi,&varR_reshuiqi);//Address for storing data
     if(reshuiqi==varR_reshuiqi)
     {
        if(varR_reshuiqi==1)  
        {
          hotwater_open();
        }
        else
        {
          hotwater_close();
        }
        reshuiqi=!varR_reshuiqi;
     }
  }

//净化器
  if(myGizwits.hasBeenSet(EVENT_jinhuaqi))
  {
    myGizwits.read(EVENT_jinhuaqi,&varR_jinghuaqi);
    if(jinghuaqi==varR_jinghuaqi)
    {
      if(varR_jinghuaqi==1)  
      {
        fan_open();
        speak_open_fan();
      }
      else
      {
        fan_close();
        speak_close_fan();
      }
      jinghuaqi=!varR_jinghuaqi;
    }
  } 
  
//窗户
bool varR_chuang = 0;
  if(myGizwits.hasBeenSet(EVENT_chuang))//窗户
  {
    myGizwits.read(EVENT_chuang,&varR_chuang);
    if(chuang==varR_chuang)
    {
      if(varR_chuang==1)  
      {
       window_open();
      }
      else
      {
       window_close();
      }
      chuang=!varR_chuang;
    }
    
  }

  wifiStatusHandle();//WIFI Status Handle
  myGizwits.process();
}
