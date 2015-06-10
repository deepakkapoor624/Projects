#!/usr/bin/env python2.7


import serial
import array



BYTE1 = 0x01
BYTE2 = 0x02

BROADCAST_ID = 0xFE



def connect(port,baudrate):                                          ##connecting serial port at baud rate
    global serial
    try:
        serial=serial.Serial(port,baudrate,timeout=1)
    except:
        print "Serial Port not connected"

def close():
    global serial
    try:
        serial.close()
    except:
        print "Failed to close serial port"

def checksum1(data):                                                ##calculating checksum
    xor=0x00
    for i in data:
        xor=xor^int(i)
    return xor&0xFE
    
    
def checksum2(data):
    xor=(~data)&0xFE
    return xor

def send_data(data,read_byte):                                                       ##  sending data to herkulex Servo
    length=len(data)+5
    data.insert(0,length)
    csm1 = checksum1(data)
    csm2 = checksum2(csm1)
    data.insert(0,0xFF)
    data.insert(1,0xFF)
    data.insert(5,csm1)
    data.insert(6,csm2)
    #print data
   
    stringtosend = ""
    for i in range(len(data)):
        byteformat = '%02X' % data[i]
        stringtosend = stringtosend + "\\x" + byteformat
        
    try:
            
        serial.write(stringtosend.decode('string-escape'))
        t=13
        if(read_byte!=0):                                                                          ##reading data from servo ACK
            rxdata=serial.read(t)
        
        
        return rxdata
    except:
        return -1





   

     
class servo:

   
    def torque_on(self,servoid):                                                                           ##enabling torque on 
        data=[]
        #data.append(0x0A)
        data.append(servoid)
        data.append(0x03)
        data.append(0x34)
        data.append(0x01)
        data.append(0x60)                                             ##command for torque on
        send_data(data,0)


   
   
   
    def set_position(self,servoid,goalposition,goaltime,servo_led):                 ##setting the position of servo
        goalposition_msb = int(goalposition) >> 8
        goalposition_lsb = int(goalposition) & 0xff
        data=[]
        
        data.append(servoid)         
        data.append(0x05)
       
        data.append(goalposition_lsb)
        data.append(goalposition_msb)
        data.append(servo_led)
        data.append(self.servoid)
        data.append(goaltime)
        send_data(data,0)



   
   
    def set_angle(self,servoid,goalangle,goaltime,servo_led):                           ##seting the angle of servo
        
        goalposition=(goalangle/0.325)+512
        self.set_position(servoid,goalposition,goaltime,servo_led)



    def break_on(self,servoid):                                ##enable brake on
       data=[]
       #data.append(0x0A)
       data.append(servoid)
       data.append(0x03)
       data.append(0x34)
       data.append(0x01)
       data.append(0x40)
       send_data(data,0)


    def torque_off(self,servoid):                               ##disabling torque off
       data=[]
       #data.append(0x0A)
       data.append(servoid)
       data.append(0x03)
       data.append(0x34)
       data.append(0x01)
       data.append(0x00)
       send_data(data,0)

    def continuous_rotation(self,servoid,clk_anticlk,goalspeed,servo_led):                     ##continuous rotation
       if(clk_anticlk):
           goalspeed_msb = int(goalspeed) >> 8
           goalspeed_lsb = int(goalspeed) & 0xff
       else:
          
           goalspeed_msb = 64+((int(goalspeed)) >> 8)
           goalspeed_lsb = (goalspeed) & 0xff
      
     
       data = []
       #data.append(0x0C)
       data.append(servoid)
       data.append(0x05)
       data.append(goalspeed_lsb)
       data.append(goalspeed_msb)
       data.append(0x02|servo_led)
       data.append(servoid)
       data.append(0x00)    
       send_data(data,0)



    def Ram_read(self,servoid,address,byte_read):                      ##reading data from Ram register
       data=[]
       check_data=[]
       #data.append(0x09)
       data.append(servoid)
       data.append(0x04)
       data.append(address)
       data.append(byte_read)
       t_byte_read=11+byte_read
       read_byte=send_data(data,t_byte_read)
       #read_byte=[]
       
       result=[]
       check_data.append(ord(read_byte[2]))
       check_data.append(ord(read_byte[3]))
       check_data.append(ord(read_byte[4]))
       check_data.append(ord(read_byte[7]))
       check_data.append(ord(read_byte[8]))
       check_data.append(ord(read_byte[9]))
       check_data.append(ord(read_byte[10]))
       check_data.append(ord(read_byte[11]))
           
       if(byte_read==2):
           check_data.append(ord(read_byte[12]))
       #print check_data  
       csum1=checksum1(check_data)
       csum2=checksum2(csum1)
       if (csum1==ord(read_byte[5]) and(csum2==ord(read_byte[6]) )):
           result.append(ord(read_byte[10]))
           result.append(ord(read_byte[9]))
          
       return result
       
        
        

    def get_servo_position(servoid,self):                                                            ##getting servo position
       s=self.Ram_read(servoid,0x3A,0x02)
       if(len(s)):
           s=((s[0]&0x03)<<8 |(s[1]&0xff))
           angle=(s-512)*.325
           return angle



   


    def moveall_position(self,servoid,servoid1,servoid2,servoid3,goalposition,goalposition1,goalposition2,goalposition3,goaltime,servo_led):  ##moving 4 servos at a time
        goalposition_msb = int(goalposition) >> 8
        goalposition_lsb = int(goalposition) & 0xff
        data=[]
        data.append(0xFE)
        data.append(0x06)
        data.append(goaltime)
        data.append(goalposition_lsb)
        data.append(goalposition_msb)
        data.append(servo_led)
        data.append(servoid)
        
        goalposition_msb = int(goalposition1) >> 8
        goalposition_lsb = int(goalposition1) & 0xff
        
        data.append(goalposition_lsb)
        data.append(goalposition_msb)
        data.append(servo_led)
        data.append(servoid1)
        
        goalposition_msb = int(goalposition2) >> 8
        goalposition_lsb = int(goalposition2) & 0xff
        
        data.append(goalposition_lsb)
        data.append(goalposition_msb)
        data.append(servo_led)
        data.append(servoid2)

        goalposition_msb = int(goalposition3) >> 8
        goalposition_lsb = int(goalposition3) & 0xff
        
        data.append(goalposition_lsb)
        data.append(goalposition_msb)
        data.append(servo_led)
        data.append(servoid3)
        
        send_data(data,0)
        

   
   
    def moveall_angle(self,servoid,servoid1,servoid2,servoid3,goalangle,goalangle1,goalangle2,goalangle3,goaltime,servo_led):      ##setting angle of 4 servos at a time
        goalposition1=(goalangle1/0.325)+512
        goalposition2=(goalangle2/0.325)+512
        goalposition=(goalangle/0.325)+512
        goalposition3=(goalangle3/0.325)+512
        self.moveall_position(servoid,servoid1,servoid2,servoid3,goalposition,goalposition1,goalposition2,goalposition3,goaltime,servo_led)



    
        

    def reboot(self,servoid):                      ##rebooting the servos
        data=[]
        data.append(servoid)
        data.append(0x09)
        send_data(data,0)

   



    def Ram_write(self,servoid,address,byte_data):              ## writing  1 byte data to ram register
        data=[]
        data.append(servoid)
        data.append(0x03)
        data.append(address)
        data.append(01)
        data.append(byte_data)
        send_data(data,0)    


    def write_ticktime(self,servoid,data):
        self.Ram_write(servoid,0x39,data)



    


    def get_servo_ticktime(self,servoid):                            #getting servo angle from feedback
       return self.Ram_read(servoid,0x39,0x01)




    def get_servo_kp(self,servoid):                                 ##getting kp of the servo
       s=self.Ram_read(servoid,0x18,0x02)
       if(len(s)):
           s=((s[0]&0x03)<<8 |(s[1]&0xff))
           
           return s


    def get_servo_kd(self,servoid):                                   ##getting the kd of the servo
       s=self.Ram_read(servoid,0x1A,0x02)
       if(len(s)):
           s=((s[0]&0x03)<<8 |(s[1]&0xff))
           
           return s



    
                      
