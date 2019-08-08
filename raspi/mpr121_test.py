import sys
import time
 
import Adafruit_MPR121.MPR121 as MPR121
 
 
print('Adafruit MPR121 Capacitive Touch Sensor Test')

# Create MPR121 instance.
cap = MPR121.MPR121()
 
# Initialize communication with MPR121 using default I2C bus of device, and 
# default I2C address (0x5A).  On BeagleBone Black will default to I2C bus 0.
if not cap.begin():
    print 'Error initializing MPR121.  Check your wiring!'
    sys.exit(1)
 
# Alternatively, specify a custom I2C address such as 0x5B (ADDR tied to 3.3V),
# 0x5C (ADDR tied to SDA), or 0x5D (ADDR tied to SCL).
#cap.begin(address=0x5B)
 
# Also you can specify an optional I2C bus with the bus keyword parameter.
#cap.begin(bus=1)

# Main loop to print a message every time a pin is touched.
print 'Press Ctrl-C to quit.'
last_touched = cap.touched()
while True:
    current_touched = cap.touched()
    # Check each pin's last and current state to see if it was pressed or released.
    for i in range(12):
        # Each pin is represented by a bit in the touched value.  A value of 1
        # means the pin is being touched, and 0 means it is not being touched.
        pin_bit = 1 << i
        # First check if transitioned from not touched to touched.
        if current_touched & pin_bit and not last_touched & pin_bit:
            print '{0} touched!'.format(i)
        # Next check if transitioned from touched to not touched.
        if not current_touched & pin_bit and last_touched & pin_bit:
            print '{0} released!'.format(i)
    # Update last state and wait a short period before repeating.
    last_touched = current_touched
    time.sleep(0.1)
