int right_wheel_1 = 2;
int right_wheel_2 = 3;
int right_wheel_power = 9;

int left_wheel_1 = 6;
int left_wheel_2 = 7;
int left_wheel_power = 10;

void setup() {
  pinMode(right_wheel_1, OUTPUT);
  pinMode(right_wheel_2, OUTPUT);
  pinMode(right_wheel_power, OUTPUT);
  
  pinMode(left_wheel_1, OUTPUT);
  pinMode(left_wheel_2, OUTPUT);
  pinMode(left_wheel_power, OUTPUT);

  analogWrite(left_wheel_power, 255);
  analogWrite(right_wheel_power, 255);

  Serial.begin(9600);
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

void loop() {
  while (Serial.available() > 0) {
     char command = Serial.read();
     if (command == 'F') {  // forwards
       right_wheel_forwards();
       left_wheel_forwards();
     } else if (command == 'B') {  // reverse
       right_wheel_reverse();
       left_wheel_reverse();
     } else if (command == 'R') {  // right
       right_wheel_reverse();
       left_wheel_forwards();
     } else if (command == 'L') {  // left
       right_wheel_forwards();
       left_wheel_reverse();
     } else if (command == 'S') {  // stop
       digitalWrite(left_wheel_1, LOW);
       digitalWrite(left_wheel_2, LOW);
       digitalWrite(right_wheel_1, LOW);
       digitalWrite(right_wheel_2, LOW);
     }
  }
}
