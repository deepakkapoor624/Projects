import herkulex
import math
import numpy as np
from herkulex import servo
from time import sleep

from scipy import interpolate
k=0
while(k!=1):   
    try:
        herkulex.connect('COM9',115200)
        k=1
    except:
        print "Serial port closed Trying connection"
        herkulex.close()

top=servo()


top.reboot(2)
sleep(.1)
top.reboot(5)
sleep(.1)
top.reboot(7)
sleep(.1)
top.reboot(9)
sleep(.1)
top.torque_on(2)
sleep(.1)
top.torque_on(5)
sleep(.1)
top.torque_on(7)
sleep(.1)
top.torque_on(9)
sleep(.1)


A=0
A2=0
A3=0
A1=0


B=20
B1=20
B2=-20
B3=50


x = np.arange(0, 2*np.pi+np.pi/4, 2*np.pi/8)
y = np.cos(x)

tck = interpolate.splrep(x, y, s=0)
xnew = np.arange(0,2*np.pi,np.pi/50)
y_cos = interpolate.splev(xnew, tck, der=0)


y = np.sin(x)
print len(y_cos)

tck = interpolate.splrep(x, y, s=0)
xnew = np.arange(0,2*np.pi,np.pi/50)
y_sin = interpolate.splev(xnew, tck, der=0)


top.moveall_angle(2,5,7,9,20,20,-20,50,255,0x04)
sleep(1)
for i,j in zip(y_cos,y_sin):
    C=A+B*j
    C1=A1+B1*i
    C2=A2+B2*j
    C3=A3+B3*j
    print C1,C2,C3,C
    top.moveall_angle(2,5,7,9,C,C1,C2,C3,10,0x04)

    #sleep(.0001)
top.moveall_angle(2,5,7,9,0,0,0,0,100,0x04)


print top.get_servo_kd(02)
print top.get_servo_kd(05)
print top.get_servo_kd(07)
print top.get_servo_kd(9)

print top.get_servo_kp(02)
print top.get_servo_kp(05)
print top.get_servo_kp(07)
print top.get_servo_kp(9)
    
herkulex.close()



