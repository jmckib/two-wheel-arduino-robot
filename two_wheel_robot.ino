#include <string.h>
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

  // Initialise the RF receiver.
  vw_set_ptt_inverted(true);  // Required for DR3100
  vw_setup(2000);  // Bits per sec
  vw_rx_start();  // Start the receiver PLL running
}


void right_wheel_forwards() {
  digitalWrite(right_wheel_1, HIGH);
  digitalWrite(right_wheel_2, LOW);
}

void right_wheel_reverse() {
  digitalWrite(right_wheel_1, LOW);
  digitalWrite(right_wheel_2, HIGH);
}


void left_wheel_forwards() {
  digitalWrite(left_wheel_1, HIGH);
  digitalWrite(left_wheel_2, LOW);
}


void left_wheel_reverse() {
  digitalWrite(left_wheel_1, LOW);
  digitalWrite(left_wheel_2, HIGH);
}


char msg[VW_MAX_MESSAGE_LEN];
char *msg_ptr, *direction;
int speed;

void loop() {
  uint8_t msg_len = VW_MAX_MESSAGE_LEN;

  if (vw_get_message((uint8_t *)msg, &msg_len)) {  // Non-blocking
    // Parse the message into direction and speed.
    // See remote_control.py for the message format.
    msg[msg_len] = '\0';  // need null-terminated string for strsep
    msg_ptr = msg;
    direction = strsep(&msg_ptr, ",");
    speed = atoi(msg_ptr) / 100.0 * 255;

    // set speed
    analogWrite(left_wheel_power, speed);
    analogWrite(right_wheel_power, speed);

    // set direction
    if (!strcmp(direction, "F")) {  // forwards
      right_wheel_forwards();
      left_wheel_forwards();
    } else if (!strcmp(direction, "B")) {  // reverse
      right_wheel_reverse();
      left_wheel_reverse();
    } else if (!strcmp(direction, "R")) {  // right
      right_wheel_reverse();
      left_wheel_forwards();
    } else if (!strcmp(direction, "L")) {  // left
      right_wheel_forwards();
      left_wheel_reverse();
    }
  }
}
