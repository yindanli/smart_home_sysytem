### samrt_home_sysytem
树莓派和Arduino人脸识别门禁，主要文件结构

* 树莓派人脸识别控制部分 test.py

* 树莓派蓝牙控制 bluetooth_test.py

* Arduino舵机控制代码 servo_test.ino

*** 
*** 
2020-3-16 之前舵机开门关门逻辑有点混乱，不合乎常理，现对树莓派人脸识别代码进行修改，以及Arduino控制代码有所调整；
*** 

在上一篇文章[树莓派调用百度人脸识别API实现人脸识别](https://www.jianshu.com/p/865238503aad)，我们完成了树莓派人脸识别的基础环境配置，人脸识别功能也测试成功了，现在我们做一个小小的案例来实际应用一下，我们想树莓派人脸识别成功后，发送蓝牙串口数据给Arduino的HC-05模块，让Arduino控制舵机开门。
### 准备
##### 设备材料
* 树莓派3b 
* Arduino UNO R3
* HC-05
* 舵机SG90(或者MG995)
* 杜邦线若干
##### 连接图
![连接图.png](https://upload-images.jianshu.io/upload_images/5845585-e036d7232f650bad.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


### 一、树莓派端配置
树莓派自带蓝牙功能，我们可以调用系统指令发送蓝牙信号，


##### 1.1安装树莓派蓝牙模块pybluez
安装完成后再继续下一步操作；
若想让树莓派使用bluetooth,必须给树莓派安装pybluez模块
```
sudo apt-get install libbluetooth-dev  //安装蓝牙开发库
python3 -m pip install pybluez    //安装pybluez
```
##### 1.2 将树莓派手动连接至HC-05
打开树莓派桌面端，点击蓝牙图标后点击add device
![图片.png](https://upload-images.jianshu.io/upload_images/5845585-83f81d500e6475fe.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
选择HC-05模块，配对密码是1234；
![图片.png](https://upload-images.jianshu.io/upload_images/5845585-2858181fc1c0ecc6.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

配对成功后，后面程序就可以直接运行了

##### 1.3 定义树莓派蓝牙控制功能
创建一个bluetooth_test.py文件，分别定义初始化指令、开门指令、关门指令，分别发送字符串’1‘，’2’，‘3’；
```
import bluetooth
 
def servo_init():#初始化指令
	bd_addr = "20:16:08:08:39:75" #arduino连接的蓝牙模块的地址
	port = 1
	 
	sock=bluetooth.BluetoothSocket( bluetooth.RFCOMM )
	sock.connect((bd_addr, port)) #创建连接
	 
	sock.send("1") #发送数据
	sock.close()  #关闭连接
	
def bt_open():#开门指令
	bd_addr = "20:16:08:08:39:75" 
	port = 1
	 
	sock=bluetooth.BluetoothSocket( bluetooth.RFCOMM )
	sock.connect((bd_addr, port)) 
	 
	sock.send("2") 
	sock.close()  

def bt_close():#关门指令
	bd_addr = "20:16:08:08:39:75" 
	port = 1
	 
	sock=bluetooth.BluetoothSocket( bluetooth.RFCOMM )
	sock.connect((bd_addr, port)) 
	 
	sock.send("3") 
	sock.close()  	
```
### 二、Arduino连接方式
##### 2.1 Arduino与HC-05蓝牙模块的连接
由于我们用的是Arduino UNO R3没有蓝牙模块，要接收蓝牙数据，可以通过外接HC-05蓝牙模块解决。

---

HC-05===Arduino
+ RXD<==>TX
+ TXD<==>RX
+ VCC<==>5v
+ GND<==>GND

---

注意：HC-05的vcc一定要接5v，如果接3.3v，虽然可以亮灯工作，但是接收一次数据后会自动断开连接，刚开始我找半天没找到原因，原来是电压给低了，这是一个小细节要注意一下。
#####2.2 Arduino与舵机模块的连接

SG90 舵机导线三种颜色，含义分别是：
棕色：GND
红色：VCC
黄色：DATA

---

舵机SG90===Arduino
+ DATA<==>D9
+ VCC<==>5v
+ GND<==>GND
---
###三、Arduino控制代码
创建工程烧录到Arduino开发板中即可
```
#include <Servo.h>
Servo myservo;  

void setup() {
  Serial.begin(9600); //监听软串口
  myservo.attach(9); //舵机控制
  myservo.write(0);
//  delay(10000); 
}

void loop() {
  while(Serial.available())
  {
    char c;
    c = Serial.read();  //读取串口数据
    Serial.println(c);
    switch(c)
    {
      case '1':servo_init();
      break;
      case '2':open_the_door();
      break;
      case '3':close_the_door();
    }
  }

}


void open_the_door()  //舵机开门
{
  myservo.write(170);
}
void close_the_door()  //舵机关门
{
  myservo.write(0);
}
void servo_init()  //舵机初始化
{
  myservo.write(10);
}
```
###四、树莓派控制代码
按照上一篇文章，我们的树莓派已经准备妥当了，在test.py的基础上，我们再修改一下：
```
# 2020-3-16修正版本
from aip import AipFace
from picamera import PiCamera
import urllib.request
import RPi.GPIO as GPIO
import base64
import time
import bluetooth

from bluetooth_test import bt_open,servo_init,bt_close


#百度人脸识别API账号信息
APP_ID = '18332624'
API_KEY = '2QoqxCzAsZGT9k5CMeaIlPBs'
SECRET_KEY ='9wOlqd4sPvLc7ZKtLxMlBVkcikXHZ4rz'
client = AipFace(APP_ID, API_KEY, SECRET_KEY)#创建一个客户端用以访问百度云
#图像编码方式
IMAGE_TYPE='BASE64'
camera = PiCamera()#定义一个摄像头对象
#用户组
GROUP = 'yusheng01'
 
#照相函数
def getimage():
    camera.resolution = (1024,768)#摄像界面为1024*768
    camera.start_preview()#开始摄像
    time.sleep(2)
    camera.capture('faceimage.jpg')#拍照并保存
    time.sleep(2)
#对图片的格式进行转换
def transimage():
    f = open('faceimage.jpg','rb')
    img = base64.b64encode(f.read())
    return img
#上传到百度api进行人脸检测
def go_api(image):
    result = client.search(str(image, 'utf-8'), IMAGE_TYPE, GROUP);#在百度云人脸库中寻找有没有匹配的人脸
    if result['error_msg'] == 'SUCCESS':#如果成功了
        name = result['result']['user_list'][0]['user_id']#获取名字
        score = result['result']['user_list'][0]['score']#获取相似度
        if score > 80:#如果相似度大于80
            if name == 'yin_danli':
                print("欢迎%s !" % name)
                time.sleep(1)
            if name == 'danli':
                print("欢迎%s !" % name)
                time.sleep(3)
            if name == "yusheng_02":
                print("欢迎%s !" % name)
                time.sleep(3)
     
        else:
            print("对不起，我不认识你！")
            name = 'Unknow'
            return 0
        curren_time = time.asctime(time.localtime(time.time()))#获取当前时间
 
        #将人员出入的记录保存到Log.txt中
        f = open('Log.txt','a')
        f.write("Person: " + name + "     " + "Time:" + str(curren_time)+'\n')
        f.close()
        return 1
    if result['error_msg'] == 'pic not has face':
        print('检测不到人脸')
        time.sleep(3)
        return -1
    else:
        print(result['error_code']+' ' + result['error_code'])
        return 0
#主函数
if __name__ == '__main__':
    servo_init()    #舵机复位，初始化一次就够了
    while True:
        
        print('准备开始，请面向摄像头 ^_^')

        if True:
            getimage()#拍照
            img = transimage()  #转换照片格式
            res = go_api(img)   #将转换了格式的图片上传到百度云
            if(res == 1):   #是人脸库中的人
                bt_open()
                print("欢迎回家，门已打开")
            elif(res == -1):
                print("我没有看见你,我要关门了")
                time.sleep(3)
                bt_close()    
            else:
                print("关门")
                bt_close()
            time.sleep(3)
            print('好了')
            time.sleep(5)

```
##### 注意：
运行程序后，如果报错
```
bluetooth.btcommon.BluetoothError: [Errno 112] Host is down 
```
你则需要回到桌面端，将树莓派与HC-05重新配对一下，再运行一下就好了。

### 最后
至此，当我们运行该代码，把脸凑到摄像头前，舵机自动开门，把脸移开则舵机自动关门，智能门禁系统就做好啦！

*** 

我还拍了一个演示效果的视频
![效果](https://upload-images.jianshu.io/upload_images/5845585-b2ae50e84c5cdc79.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

[视频演示效果传送门](https://www.bilibili.com/video/av91541332/)

[视频制作教程传送门](https://www.bilibili.com/video/bv1U741127yV)

如果有疑问可以联系我：公众号：xiaoxiaoyu1926

----

