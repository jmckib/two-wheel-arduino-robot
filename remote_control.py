import serial


class RemoteControl(object):

    def __init__(self):
        self.min_speed = 0
        self.max_speed = self.default_speed = 100

        # This is probably specific to my computer.
        self.serial = serial.Serial('/dev/tty.usbmodemfd131')

    def _move(self, direction, speed=None):
        if speed is None:
            speed = self.default_speed

        # The command format accepted by the robot is <direction>,<speed>
        # where <direction> is a string and <speed> is an int from 0 to 100.
        self.serial.write('%s,%s' % (direction, speed))

    def forwards(self, speed=None):
        self._move('F', speed=speed)

    def right(self, speed=None):
        self._move('R', speed=speed)

    def left(self, speed=None):
        self._move('L', speed=speed)

    def reverse(self, speed=None):
        self._move('B', speed=speed)

    def stop(self):
        # The command doesn't matter, just set the speed to min.
        self._move('F', speed=self.min_speed)
