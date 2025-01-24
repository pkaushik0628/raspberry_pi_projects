from machine import Pin, PWM
from L298N_motor import L298N
import time
from machine import UART, Pin
from time import sleep_us

ENA = PWM(Pin(0))
IN1 = Pin(1, Pin.OUT)
IN2 = Pin(2, Pin.OUT)

IN3 = Pin(3, Pin.OUT)
IN4 = Pin(4, Pin.OUT)
ENA1 = PWM(Pin(5))

motor1 = L298N(ENA, IN1, IN2)  # create a motor1 object
motor1.setSpeed(25000)  # set the speed of motor1. Speed value varies from 25000 to 65534
motor2 = L298N(ENA1, IN3, IN4)  # create a motor2 object
motor2.setSpeed(25000)  # set the speed of motor2. Speed value varies from 25000 to 65534

class myUART(UART):
    def readUntil(self, termination, maxlen=-1, includeTermination=True):
        result = ''
        while maxlen < 0 or len(result) < maxlen:
            if self.any():
                # print("here")
                result += chr(self.read(1)[0])
                # print(result)
                if result.endswith(termination):
                    if not includeTermination:
                        result = result[:-len(termination)]
                    break
            sleep_us(10)
        return result

uart = myUART(0, baudrate=921600, tx=Pin(16), rx=Pin(17), bits=8, parity=None, stop=1)

while True:
    if uart.any():
        data = uart.read()
        print(data)
    else:
        data = b'S'

    if data == b'F':
        motor1.forward()  # run motor1 forward
        motor2.forward()  # run motor2 forward

    elif data == b'B':
        motor1.backward()  # run motor1 backward
        motor2.backward()  # run motor2 backward

    elif data == b'R':
        motor1.forward()  # run motor1 forward
        motor2.stop()  # motor2 stop

    elif data == b'L':
        motor1.stop()  # run motor1 stop
        motor2.forward()  # run motor2 forward

    else:
        motor1.stop()  # run motor1 forward
        motor2.stop()  # motor2 stop

