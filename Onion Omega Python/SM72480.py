# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# SM72480
# This code is designed to work with the ADC121C021_SM72480_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/products

from OmegaExpansion import onionI2C
import time

# Get I2C bus
i2c = onionI2C.OnionI2C()

# SM72480 address, 0x50(80)
# Select configuration register, 0x02(02)
#		0x20(32)	Automatic conversion mode enabled
i2c.writeByte(0x50, 0x02, 0x20)

time.sleep(0.5)

# SM72480 address, 0x50(80)
# Read data back from 0x00(00), 2 bytes
# raw_adc MSB, raw_adc LSB
data = i2c.readBytes(0x50, 0x00, 2)

# Convert the data to 12-bits
raw_adc = (data[0] & 0x0F) * 256 + data[1]

# Output data to screen
print "Digital value of analog input : %d" %raw_adc
