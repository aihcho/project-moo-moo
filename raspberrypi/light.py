import smbus
import time
import requests

# Constants
DEVICE     = 0x23 
POWER_DOWN = 0x00 
POWER_ON   = 0x01 
RESET      = 0x07 
HIGH_RES_MODE = 0x20

webhook_url = 'https://maker.ifttt.com/trigger/light/with/key/kRLN1DkKFq-kliji8lNDX'

# Uses I2C1 port
bus = smbus.SMBus(1)

# Converts data to lux
def convert(data):
    return int((data[1] + (256 * data[0])) / 1.2)
 

def read(addr=DEVICE):
    data = bus.read_i2c_block_data(addr,HIGH_RES_MODE)
    return convert(data)
 
while True:
    r = requests.post(webhook_url, json={"value1": str(read())})
    time.sleep(300)
