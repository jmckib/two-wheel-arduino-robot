#include <VirtualWire.h>

int right_wheel_1 = 2;
int right_wheel_2 = 3;
int right_wheel_power = 6;

int left_wheel_1 = 4;
int left_wheel_2 = 7;
int left_wheel_power = 5;


void setup() {
  pinMode(right_wheel_1, OUTPUT);
  pinMode(right_wheel_2, OUTPUT);
  pinMode(right_wheel_power, OUTPUT);

  pinMode(left_wheel_1, OUTPUT);
  pinMode(left_wheel_2, OUTPUT);
  pinMode(left_wheel_power, OUTPUT);

  analogWrite(left_wheel_power, 0);
  analogWrite(right_wheel_power, 0);

  // Initialise the RF receiver.
  vw_set_ptt_inverted(true);  // Required for DR3100
  vw_setup(2000);  // Bits per sec
  vw_rx_start();  // Start the receiver PLL running
}

// min and max absolute value of speeds in message.
int MIN_SPEED = 0;
int MAX_SPEED = 100;

// min and max values you can pass to AnalogWrite (except for 0)
int MIN_RAW_SPEED = 160;  // motor isn't happy below this
int MAX_RAW_SPEED = 255;

char msg[VW_MAX_MESSAGE_LEN];
char *msg_ptr;
int left_speed, right_speed;

// Given the absolute speed from the remote (value between 0 and 100),
// get the speed to pass to the motor.
int get_raw_speed(int speed) {
    if (speed == 0) return 0;
    return map(abs(speed), MIN_SPEED, MAX_SPEED, MIN_RAW_SPEED, MAX_RAW_SPEED);
}

void loop() {
  uint8_t msg_len = VW_MAX_MESSAGE_LEN;

  if (vw_get_message((uint8_t *)msg, &msg_len)) {  // Non-blocking
    // Parse the message into direction and speed.
    // See remote_control.py for the message format.
    msg[msg_len] = '\0';  // need null-terminated string for strsep
    msg_ptr = msg;
    left_speed = atoi(strsep(&msg_ptr, ","));
    right_speed = atoi(msg_ptr);

    // set speed
    analogWrite(left_wheel_power, get_raw_speed(left_speed));
    analogWrite(right_wheel_power, get_raw_speed(right_speed));

    // set direction
    if (left_speed > 0) {
      go_forwards(left_wheel_1, left_wheel_2);
    } else {
      go_backwards(left_wheel_1, left_wheel_2);
    }

    if (right_speed > 0) {
      go_forwards(right_wheel_1, right_wheel_2);
    } else {
      go_backwards(right_wheel_1, right_wheel_2);
    }
  }
}

void go_forwards(int wheel_input_1, int wheel_input_2) {
  digitalWrite(wheel_input_1, HIGH);
  digitalWrite(wheel_input_2, LOW);
}

void go_backwards(int wheel_input_1, int wheel_input_2) {
  digitalWrite(wheel_input_1, LOW);
  digitalWrite(wheel_input_2, HIGH);
}
