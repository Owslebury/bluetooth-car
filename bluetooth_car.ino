#include <SoftwareSerial.h>
#include <Servo.h>

Servo myservo;                  // Create a servo object
SoftwareSerial bluetooth(2, 3); // RX, TX pins for HC-05

const int motorPin1 = 10;  // Motor pin 1 connected to L298N OUT1
const int motorPin2 = 11;  // Motor pin 2 connected to L298N OUT2

void setup() {
  pinMode(motorPin1, OUTPUT);  // Set motor pins as outputs
  pinMode(motorPin2, OUTPUT);
  
  myservo.attach(9);           // Attach the servo to pin 9
  bluetooth.begin(9600);      // Initialize Bluetooth communication
  Serial.begin(9600);         // Initialize serial communication for debugging
}

void loop() {
  if (bluetooth.available()) {
    char command = bluetooth.read();  // Read the command from Bluetooth
    Serial.println(command);          // Print the received command to the serial monitor

    if (command == 'B') {  // Move forward
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
    } else if (command == 'F') {  // Move backward
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, HIGH);
    } else if (command == 'S') {  // Stop
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW);
    } else if (command >= '1' && command <= '9') {
      int scale = command - '0';  // Convert char to integer scale value (1-9)

      // Map the scale value to the corresponding servo angle (0-180)
      int angle = map(scale, 1, 9, 0, 180);

      myservo.write(angle);  // Move the servo to the calculated angle
    }
  }
}
