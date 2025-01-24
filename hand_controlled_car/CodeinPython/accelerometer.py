import machine
from machine import UART, Pin
from time import sleep_us
import time
import math

# ADXL335 analog pins connected to Pico's ADC channels
X_PIN = 26
Y_PIN = 27
Z_PIN = 28

led = Pin(25, Pin.OUT)

# Create ADC objects for each axis
adc_x = machine.ADC(machine.Pin(X_PIN))
adc_y = machine.ADC(machine.Pin(Y_PIN))
adc_z = machine.ADC(machine.Pin(Z_PIN))

def read_acceleration(adc):
    # Read the ADC value and convert it to voltage
    voltage = adc.read_u16() * 3.3 / 65535
    # Convert the voltage to acceleration (assuming 3.3V supply)
    acceleration = (voltage - 1.65) / 0.330
    return acceleration

def calculate_tilt_angles(x, y, z):
    pitch = math.atan2(y, math.sqrt(x**2 + z**2))
    roll = math.atan2(x, math.sqrt(y**2 + z**2))

    # Convert the angles to degrees
    pitch = math.degrees(pitch)
    roll = math.degrees(roll)

    return pitch, roll

# UART class
class myUART(UART):
    def readUntil(self, termination, maxlen=-1, includeTermination=True):
        result = b''  # Use bytes to handle binary data
        termination_bytes = termination.encode('utf-8')  # Convert termination string to bytes

        while maxlen < 0 or len(result) < maxlen:
            if self.any():
                result += self.read(1)
                if result.endswith(termination_bytes):
                    if not includeTermination:
                        result = result[:-len(termination_bytes)]
                    break
            sleep_us(10)
        
        return result.decode('utf-8')  # Convert the result to a string before returning

# UART Initalize
uart = myUART(0, baudrate=921600, tx=Pin(0), rx=Pin(1), bits=8, parity=None, stop=1)


class FSM:
    def __init__(self):
        self.state = "Initial"

    def update_state(self, pitch, roll):
        if self.state == "Initial":
            if -20 <= pitch <= 20 and -25 <= roll <= 0:
                self.state = "Stop"
                uart.write('S')
                print("Stop")
            elif (roll > 0 or roll < -25) and (pitch <= 20 and pitch >= -15):
                if roll < -66:
                    self.state = "Forward"
                    uart.write('F')
                    print("Forward")
                elif roll > 30:
                    self.state = "Back"
                    uart.write('B')
                    print("Back")
                else:
                    self.state = "Stable"
                    uart.write('S')
                    print("Stable")
            elif (pitch > -20 or pitch <= -20) and (-20 < roll <= 15):
                if pitch < -40:
                    self.state = "Left"
                    uart.write('L')
                    print("Left")
                elif pitch > 40:
                    self.state = "Right"
                    uart.write('R')
                    print("Right")
                else:
                    self.state = "Stable"
                    uart.write('S')
                    print("Stable")
            else:
                self.state = "Stop"
                uart.write('S')
while True:
    # Read the acceleration values from the ADXL335
    x = read_acceleration(adc_x)
    y = read_acceleration(adc_y)
    z = read_acceleration(adc_z)
    
    # Test UART
    if uart.any():
        data = uart.read()
        print(data)
        led.toggle()
        time.sleep(1)
    
    
    # Calculate the tilt angles
    pitch, roll = calculate_tilt_angles(x, y, z)

    # Print the acceleration values and tilt angles
    print("X: {:.2f}g, Y: {:.2f}g, Z: {:.2f}g, Pitch: {:.2f}°, Roll:{:.2f}°".format(x, y, z, pitch, roll))
    
    # Wait for a while before reading again
    time.sleep(0.1)
    
    my_fsm = FSM()
    
    my_fsm.update_state(pitch,roll)
    

