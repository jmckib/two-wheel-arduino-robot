Two-wheeled Arduino Robot
=======================

![The robot](https://github.com/jmckib/two-wheel-arduino-robot/blob/master/robot.jpg?raw=true)
*No awkward third wheel!*

This is the source code for a robot with two independent wheels. It receives
commands from a computer via a USB cable.

This is the first robot I've ever built, so don't you judge me! Hopefully
other newbs will find this useful, and the more advanced will have a few
laughs.

## Physical components needed:

- [Tamiya 70168 Double Gearbox Kit](http://www.pololu.com/catalog/product/114): A gearbox plus two 3 volt motors. It only takes about an hour to put this together. Note: you'll need a ruler with mm. You can build it with four different gear ratios; I chose the 38.2:1 gear ratio, the second fastest, for no particular reason.
- [Tamiya 70096 Off-Road Tires (2 tires)](http://www.pololu.com/catalog/product/64): Two wheels that fit on the axle of the Tamiya Double Gearbox.
- [SN754410 Motor Driver IC](http://www.pololu.com/catalog/product/24): Also known as an H-Bridge chip. This is needed to control each motor (make it go forwards and backwards at different speeds) using the arduino digital pins. You can't use the pins directly because they can only provide up to 40 mA of current, while the motor may draw up to 2 A (see [Mabuchi motor FA-130 (#18100) data sheet](http://www.pololu.com/file/download/fa_130ra.pdf?file_id=0J11)).

    The [data sheet](http://www.sparkfun.com/datasheets/IC/SN754410.pdf) is
    pretty helpful in figuring out how to wire this up, in addition to [this
    tutorial](http://itp.nyu.edu/physcomp/Labs/DCMotorControl).

    Warning: this chip is only rated for up to 1 A of current, while the
    motors may draw up to 2 A when stalled. This hasn't caused a problem for
    me yet, but be wary.

- Arduino, breadboard, wiring, 2 AA batteries and battery holder, soldering
  iron. I used an Arduino Duemilanove, but any recent model should work. The
  soldering iron is for connecting wires to the motors' terminals.

How did I figure out what components to use? I just browsed around on
sparkfun.com and pololu.com until I saw something that looked useful for
building a robot with wheels. I found the Double Gearbox Kit first, and most
of the other components were mentioned in the description/comments or linked
in the related products section.
