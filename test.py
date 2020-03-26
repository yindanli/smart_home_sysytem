
# 树莓派人脸识别测试 test.py
# 更多教程参考公众号”xiaoxiaoyu1926“

from aip import AipFace
from picamera import PiCamera
import urllib.request
import RPi.GPIO as GPIO
import base64
import time

from bluetooth_test import bt_open,servo_init,bt_close
#百度人脸识别API账号信息
APP_ID = '18965191'
API_KEY = 'lvfieIpAjvGZg04NsF2MWas5'
SECRET_KEY ='2Wpa2dX42GnGI7zt93EVl8S8Tm3hIpup'
client = AipFace(APP_ID, API_KEY, SECRET_KEY)#创建一个客户端用以访问百度云
#图像编码方式
IMAGE_TYPE='BASE64'
camera = PiCamera()#定义一个摄像头对象
#用户组
GROUP = '01'
 
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
            if name == 'xiaoming':
 
                print("欢迎%s !" % name)
                time.sleep(3)
            if name == 'danli':
            	print("欢迎您%s!" % name)
            	time.sleep(3)
            if name == "xiaoyu":
                print("欢迎%s !" % name)
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
        time.sleep(2)
        return 0
    else:
        print(result['error_code']+' ' + result['error_code'])
        return 0
#主函数
if __name__ == '__main__':
	servo_init()
    while True:
        print('准备')
        if True:
            getimage()#拍照
            img = transimage()#转换照片格式
            res = go_api(img)#将转换了格式的图片上传到百度云
            if(res == 1):#是人脸库中的人
            	bt_open()
                print("欢迎回家，门已打开")
            elif(res == -1):
                print("我没有看见你，我要关门了")
                time.sleep(3)
                bt_close()
            else:
            	bt_close()
                print("关门")
            print('好了')
            time.sleep(3)
