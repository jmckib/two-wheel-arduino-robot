#include <Wire.h>
#include <ArduinoNunchuk.h>
#include <VirtualWire.h>

ArduinoNunchuk nunchuk = ArduinoNunchuk();

void setup() {
  // Initialize the RF transmitter.
  vw_set_ptt_inverted(true);  // Required for DR3100
  vw_setup(2000);  // Bits per sec

  // Initialize the nunchuk.
  nunchuk.setPowerPins();
  nunchuk.init();
}

// The range of raw joystick values.
int MIN_JOY = 30;
int MAX_JOY = 225;

// The min and max speed that can be passed to the robot.
int MIN_SPEED = -100;
int MAX_SPEED = 100;

char msg[VW_MAX_MESSAGE_LEN];

// Rotate a vector 45 degrees clockwise.
void rotate_45(int *x, int *y) {
  float neg_45 = -1 * PI / 4;
  int new_x = *x * cos(neg_45) - *y * sin(neg_45);
  int new_y = *x * sin(neg_45) + *y * cos(neg_45);
  *x = new_x;
  *y = new_y;
}

// Convert the raw joystick value into a value between MIN_SPEED and MAX_SPEED.
int get_adjusted_joy_value(int joy_val) {
  joy_val = constrain(joy_val, MIN_JOY, MAX_JOY);
  joy_val = map(joy_val, MIN_JOY, MAX_JOY, MIN_SPEED, MAX_SPEED);
  // Below a certain threshold, the user probably wants to stop the robot.
  if (abs(joy_val) < 20) joy_val = 0;
  return joy_val;
}

void loop() {
  nunchuk.update();

  int left_speed = get_adjusted_joy_value(nunchuk.joyX);
  int right_speed = get_adjusted_joy_value(nunchuk.joyY);

  // Rotate the (left_speed, right_speed) vector 45 degrees clockwise, but
  // keep it along a square. This happens to describe the mapping from
  // joystick values to left, right tire speeds.
  rotate_45(&left_speed, &right_speed);

  float magnitude = sqrt((left_speed * left_speed + right_speed * right_speed));
  float adj = magnitude / max(abs(left_speed), abs(right_speed));

  left_speed *= adj;
  right_speed *= adj;

  // in case there were rounding errors during calculations
  left_speed = constrain(left_speed, MIN_SPEED, MAX_SPEED);
  right_speed = constrain(right_speed, MIN_SPEED, MAX_SPEED);

  sprintf(msg, "%d,%d", left_speed, right_speed);

  digitalWrite(13, HIGH);
  vw_send((uint8_t *)msg, strlen(msg));
  vw_wait_tx();  // Wait until the whole message is gone
  digitalWrite(13, LOW);
}
