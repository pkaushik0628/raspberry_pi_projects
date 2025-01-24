from machine import UART, Pin
from time import sleep_us
import time



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

    
uart = myUART(0, baudrate=921600, tx=Pin(0), rx=Pin(1), bits=8, parity=None, stop=0)

led = Pin(25, Pin.OUT)

while True:
    uart.write("F")
    if uart.any():
        data = uart.read()
        print(data)
        led.toggle()
        time.sleep(1)
