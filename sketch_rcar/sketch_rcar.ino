#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to enable it.
#endif

BluetoothSerial SerialBT;

// Motor control pins
const int mr1 = 13; // Motor Right Forward
const int mr2 = 12; // Motor Right Backward
const int ml1 = 14; // Motor Left Forward
const int ml2 = 27; // Motor Left Backward

void setup() {
  // Initialize Serial communication
  Serial.begin(115200);
  SerialBT.begin("ESP32_RC_Car"); // Bluetooth device name
  Serial.println("The device started, now you can pair it with Bluetooth!");

  // Set motor pins as outputs
  pinMode(mr1, OUTPUT);
  pinMode(mr2, OUTPUT);
  pinMode(ml1, OUTPUT);
  pinMode(ml2, OUTPUT);

  // Ensure all motors are off initially
  stopMotors();
}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read();
    Serial.println("Received command: " + String(command));
    handleCommand(command);
  }
}

// Function to handle commands from the Bluetooth app
void handleCommand(char command) {
  switch (command) {
    case 'F': // Forward
      moveForward();
      break;
    case 'B': // Backward
      moveBackward();
      break;
    case 'L': // Left
      turnLeft();
      break;
    case 'R': // Right
      turnRight();
      break;
    case 'S': // Stop
      stopMotors();
      break;
    default:
      Serial.println("Invalid command");
      stopMotors();
      break;
  }
}

// Function to move forward
void moveForward() {
  Serial.println("Moving forward");
  digitalWrite(mr1, HIGH);
  digitalWrite(mr2, LOW);
  digitalWrite(ml1, HIGH);
  digitalWrite(ml2, LOW);
}

// Function to move backward
void moveBackward() {
  Serial.println("Moving backward");
  digitalWrite(mr1, LOW);
  digitalWrite(mr2, HIGH);
  digitalWrite(ml1, LOW);
  digitalWrite(ml2, HIGH);
}

// Function to turn left
void turnLeft() {
  Serial.println("Turning left");
  digitalWrite(mr1, HIGH);
  digitalWrite(mr2, LOW);
  digitalWrite(ml1, LOW);
  digitalWrite(ml2, LOW);
}

// Function to turn right
void turnRight() {
  Serial.println("Turning right");
  digitalWrite(mr1, LOW);
  digitalWrite(mr2, LOW);
  digitalWrite(ml1, HIGH);
  digitalWrite(ml2, LOW);
}

// Function to stop all motors
void stopMotors() {
  Serial.println("Stopping motors");
  digitalWrite(mr1, LOW);
  digitalWrite(mr2, LOW);
  digitalWrite(ml1, LOW);
  digitalWrite(ml2, LOW);
}
