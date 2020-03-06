/**************************************************************

Name:      Gizwits + ArduinoUno + raspiberry_bluetooth
Author:   danlis
Version:  V1.0
Init:     2016-12-23
Modify:   2020-02-22
****************************************************************/
#include <Arduino.h>
#include <Gizwits.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <dht11.h>
#include <U8x8lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

SoftwareSerial mySerial(2,3);   //给蓝牙HC-05使用的串口，RX ,TX = 2,3
Servo myservo;
Gizwits myGizwits;
dht11 DHT11;
int pos = 0;            //  初始化舵机位置
int ledPin = 13;                 // LED connected to digital pin 13,it's used for status 
int myledPin = 8;                 // my LED connected to digital pin 4
int sensorValue = 0;        // value read from the pot
bool varR_LED_OnOff = 0;


#define   KEY1              6
#define   KEY2              7
#define   KEY1_SHORT_PRESS  1
#define   KEY1_LONG_PRESS   2
#define   KEY2_SHORT_PRESS  4
#define   KEY2_LONG_PRESS   8
#define   NO_KEY            0
#define   KEY_LONG_TIMER    3

#define DHT11PIN A0

U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE); 
int flag =0;
unsigned long Last_KeyTime = 0;

unsigned long gokit_time_s(void)
{
  return millis() / 1000;
}

//温湿度传感器的使用//
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
////////////////////////温湿度分割线/////////////////////

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);     //esp-8266
  mySerial.begin(9600);   // hc-05
  myservo.attach(9);
  myservo.write(0);
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output
  pinMode(myledPin, OUTPUT);      // sets the digital pin as output
 
  pinMode(KEY1, INPUT_PULLUP);
  pinMode(KEY2, INPUT_PULLUP);
  ////////////////代码部署////////
  pinMode(A2,OUTPUT);//房门标志位
  pinMode(A4,OUTPUT);//报警标志位
  pinMode(3,OUTPUT);//开关1
  pinMode(4,OUTPUT);//开关2（窗）
  pinMode(5,OUTPUT);//开关3
  pinMode(8,OUTPUT);//beeWIFI_AIRLINK成功报警提示这里是配网提示
//  pinMode(9,OUTPUT);//开关4
  pinMode(10,OUTPUT);//开关5（热水器）
  pinMode(11,OUTPUT);//脉冲输出（调光）
  pinMode(12,OUTPUT);//指示灯
  pinMode(13,OUTPUT);//开关6（净化器）
  pinMode(A0,INPUT);//温湿度传感器
  pinMode(A1,INPUT);//烟雾报警器

//  digitalWrite(9,HIGH);
  
  myGizwits.begin();
  begin();
}

void begin ()
{
  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(5,1,"Zhi-Ju");
  u8x8.drawString(0,2,"wendu:");
  u8x8.drawString(0,3,"shidu:");
  u8x8.drawString(0,4,"yanwu:");
  u8x8.drawString(0,5,"led:");
  }
  
void wifiStatusHandle()
{

  if(myGizwits.wifiHasBeenSet(WIFI_CON_ROUTER))
  digitalWrite(ledPin, LOW);    // sets the LED off

}

void servo_init(){
  myservo.write(0);
  delay(1000);
}

void open_the_door(){
    for (pos = 0; pos <= 180; pos += 1) { 
    myservo.write(pos);            
    delay(15);                       
  }
}

void close_the_door(){
    for (pos = 180; pos >= 0; pos -= 1) { 
    myservo.write(pos);              
    delay(15);   
    }
}

void loop() {  

  while(mySerial.available())  
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
       default:servo_init();
        
      }
   }
  //////////////////////温湿度采集
  int chk = DHT11.read(DHT11PIN);
  
  
//  sensorValue = analogRead(A0);
//
//  unsigned long varW_ADCValue = sensorValue;//Add Sensor Data Collection
//  myGizwits.write(VALUE_ADCValue, varW_ADCValue);
int val=analogRead(A1);
u8x8.setCursor(6,4);//这里设置显示的坐标
u8x8.print(val);//输出显示内容

 unsigned long varW_wendu = (float)DHT11.temperature;
 u8x8.setCursor(6,2);//这里设置显示的坐标
u8x8.print(varW_wendu);//输出显示内容
  myGizwits.write(VALUE_wendu, varW_wendu);
  unsigned long varW_shidu = (float)DHT11.humidity ;
   u8x8.setCursor(6,3);//这里设置显示的坐标
u8x8.print(varW_shidu);//输出显示内容
  myGizwits.write(VALUE_shidu, varW_shidu);
  
bool varR_chuang = 0;
  if(myGizwits.hasBeenSet(EVENT_chuang))
  {
    myGizwits.read(EVENT_chuang,&varR_chuang);//Address for storing data
 if(varR_chuang==1)  
    {
      digitalWrite(4,HIGH);
      }
     else
     digitalWrite(4,LOW);
  }

  bool varR_reshuiqi = 0;
  if(myGizwits.hasBeenSet(EVENT_reshiuqi))
  {
    myGizwits.read(EVENT_reshiuqi,&varR_reshuiqi);//Address for storing data
     if(varR_reshuiqi==1)  
    {
      digitalWrite(10,HIGH);
      }
     else
     digitalWrite(10,LOW);
  }
  
  bool varR_jinghuaqi = 0;
  if(myGizwits.hasBeenSet(EVENT_jinhuaqi))
  {
    myGizwits.read(EVENT_jinhuaqi,&varR_jinghuaqi);//Address for storing data
    if(varR_jinghuaqi==1)  
    {
      digitalWrite(13,HIGH);
      }
     else
     digitalWrite(13,LOW);
  }
  
  unsigned long varR_tiaoguang = 0;
  if(myGizwits.hasBeenSet(EVENT_tiaoguang))
  {
    myGizwits.read(EVENT_tiaoguang,&varR_tiaoguang);//Address for storing data
   analogWrite(11,varR_tiaoguang); 
      u8x8.setCursor(6,5);//这里设置显示的坐标
u8x8.print(varR_tiaoguang);//输出显示内容
  }
  

  if(myGizwits.hasBeenSet(EVENT_LED_OnOff))
  {
    myGizwits.read(EVENT_LED_OnOff,&varR_LED_OnOff);//Address for storing data 
  }
  if(varR_LED_OnOff==1)
  {
    digitalWrite(myledPin, HIGH);   // sets the user LED on
  }
  else
  {
    digitalWrite(myledPin, LOW);    // sets the user LED off 
  }
  
//  KEY_Handle();//key handle , network configure
  wifiStatusHandle();//WIFI Status Handle
  myGizwits.process();
}
