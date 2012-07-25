#include <assert.h>
#include <Wire.h>
#include <ArduinoNunchuk.h>
#include <VirtualWire.h>

ArduinoNunchuk nunchuk = ArduinoNunchuk();

void setup() {
  Serial.begin(9600);

  // Initialize the RF transmitter.
  vw_set_ptt_inverted(true);  // Required for DR3100
  vw_setup(2000);  // Bits per sec

  // Initialize the nunchuk.
  nunchuk.setPowerPins();
  nunchuk.init();
}

// The raw values when joystick untouched.
int MED_JOY = 128;
// When the absolute difference between MED_JOY and actual value
// is larger than this, start moving.
int JOY_THRESHOLD = 30;

char msg[VW_MAX_MESSAGE_LEN];

int speed;
char *direction;

void loop() {
  nunchuk.update();

  int x_diff = nunchuk.joyX - MED_JOY;
  int y_diff = nunchuk.joyY - MED_JOY;
  int abs_diff;

  if (abs(y_diff) > abs(x_diff)) {  // go forwards or backwards
    abs_diff = abs(y_diff);

    if (y_diff > 0) {
      direction = "F";
    } else {
      direction = "B";
    }
  } else {  // go left or right
    abs_diff = abs(x_diff);
    if (x_diff > 0) {
      direction = "R";
    } else {
      direction = "L";
    }
  }

  if (abs_diff > JOY_THRESHOLD) {
    speed = 100;
  } else {
    speed = 0;
  }

  sprintf(msg, "%s,%d", direction, speed);

  Serial.print("'");
  Serial.print(msg);
  Serial.println("'");

  digitalWrite(13, HIGH);
  vw_send((uint8_t *)msg, strlen(msg));
  vw_wait_tx();  // Wait until the whole message is gone
  digitalWrite(13, LOW);

  // Sending commands more often than this won't make a difference.
  delay(100);
}
