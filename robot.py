import serial


class Robot(object):

    def __init__(self):
        self.serial = serial.Serial('/dev/tty.usbserial-A6008bDI')

    def forwards(self):
        self.serial.write('F')

    def right(self):
        self.serial.write('R')

    def left(self):
        self.serial.write('L')

    def reverse(self):
        self.serial.write('B')

    def stop(self):
        self.serial.write('S')
