# include <Servo.h>

Servo myservo;      //门舵机
Servo windowservo;  //窗户舵机

int tick = 0; //计数值
int smokepin = 2;    //烟雾报警器
int fanpin = 6;      //净化器
int fengminqipin = 7;//蜂鸣器
int myledPin = 8;    // 客厅灯
int servopin = 9;    //门servo舵机
int hotwaterpin = 10;//热水器
int pwmpin =11;      //卧室灯
int windowservopin = 12; //窗servo舵机



//蜂鸣器
void fengmingqi_open()
{
  digitalWrite(fengminqipin,HIGH);
  speak_smoke();//检测到烟雾  
}

void fengmingqi_close()
{
  digitalWrite(fengminqipin,LOW);  
}

//客厅灯
void myled_open()
{
  digitalWrite(myledPin, HIGH); 
  speak_open_sittingroom();
}

void myled_close()
{
  digitalWrite(myledPin, LOW); 
  speak_close_sittingroom() ;
}

//热水器
void hotwater_open()
{
  digitalWrite(hotwaterpin,HIGH); 
  speak_open_hotwater(); 
}

void hotwater_close()
{
  digitalWrite(hotwaterpin,LOW); 
  speak_close_hotwater(); 
}

//净化器风扇高电平触发
void fan_open(){
  digitalWrite(fanpin,HIGH);
}

void fan_close(){
  digitalWrite(fanpin,LOW);
}

//门舵机
void servo_init(){
  myservo.write(10);
}

void open_the_door(){
  myservo.write(90);
  speak_open_door();
}

void close_the_door(){
  myservo.write(0);
  speak_close_door();
}

//窗户舵机
void window_init(){
  windowservo.write(10);
}

void window_open(){
  windowservo.write(170);
  speak_open_window();
}

void window_close(){
  windowservo.write(0);
  speak_close_window();
}
