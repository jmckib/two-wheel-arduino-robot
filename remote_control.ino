#include <assert.h>
#include <VirtualWire.h>

void setup() {
  Serial.begin(9600);

  // Initialise the RF transmitter
  vw_set_ptt_inverted(true);  // Required for DR3100
  vw_setup(2000);  // Bits per sec
}

char msg[VW_MAX_MESSAGE_LEN];
byte msg_len;

void loop() {
  // Receive a newline-terminated message via USB and pass to robot.
  if (msg_len = Serial.readBytesUntil('\n', msg, VW_MAX_MESSAGE_LEN)) {
    // To make sure we don't get a partial messages, messages with
    // length == VW_MAX_MESSAGE_LEN are not allowed.
    assert(msg_len < VW_MAX_MESSAGE_LEN);

    vw_send((uint8_t *)msg, msg_len);
    vw_wait_tx();  // Wait until the whole message is gone
  }
}
