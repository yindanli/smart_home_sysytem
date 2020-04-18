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
