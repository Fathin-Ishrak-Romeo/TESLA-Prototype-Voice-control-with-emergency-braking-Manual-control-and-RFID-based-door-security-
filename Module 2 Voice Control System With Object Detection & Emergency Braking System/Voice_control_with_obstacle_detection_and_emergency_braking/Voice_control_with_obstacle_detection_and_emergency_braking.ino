#include <NewPing.h>
#include <Servo.h>

// ================== ULTRASONIC PINS ==================
#define FRONT_TRIG 2
#define FRONT_ECHO 3
#define REAR_TRIG  A0
#define REAR_ECHO  A1

#define LEFT_TRIG  A2
#define LEFT_ECHO  A3
#define RIGHT_TRIG A4
#define RIGHT_ECHO A5

// ================== MOTOR PINS ==================
#define ENA 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 10
#define ENB 11

// ================== SERVO ==================
#define SERVO_PIN 5
#define SERVO_LEFT   5
#define SERVO_CENTER 90
#define SERVO_RIGHT  175

// ================== SPEED SETTINGS ==================
#define MOVE_SPEED 170        //Adjust according to your preference 
#define TURN_SPEED 170        //Adjust according to your preference 
#define KICK_SPEED 180        //Adjust according to your preference 

// ================== TURN CALIBRATION ==================
#define TURN_DURATION 900     //Adjust according to your preference 

// ================== DISTANCES ==================
#define FRONT_STOP_DISTANCE 30      //Adjust according to your preference 
#define REAR_STOP_DISTANCE  30      //Adjust according to your preference 
#define SIDE_STOP_DISTANCE  15      //Adjust according to your preference 
#define MAX_DISTANCE        250

// ================== OBJECTS ==================
NewPing frontSonar(FRONT_TRIG, FRONT_ECHO, MAX_DISTANCE);
NewPing rearSonar(REAR_TRIG, REAR_ECHO, MAX_DISTANCE);
NewPing leftSonar(LEFT_TRIG, LEFT_ECHO, MAX_DISTANCE);
NewPing rightSonar(RIGHT_TRIG, RIGHT_ECHO, MAX_DISTANCE);

Servo scanServo;

// ================== STATE ==================
String command = "";
String motionState = "STOP";
String turnDirection = "";
unsigned long turnStartTime = 0;

// ================== SETUP ==================
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(15);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  scanServo.attach(SERVO_PIN);
  scanServo.write(SERVO_CENTER);
  delay(300);

  stopCar();
}

// ================== LOOP ==================
void loop() {
  readBluetoothCommand();

  if (motionState == "FORWARD") {
    if (frontObstacleDetected()) emergencyStop();
    else moveForward();
  }
  else if (motionState == "BACKWARD") {
    if (rearObstacleDetected()) emergencyStop();
    else moveBackward();
  }
  else if (motionState == "TURNING") {
    handleTurning();
  }
}

// ================== BLUETOOTH ==================
void readBluetoothCommand() {
  if (!Serial.available()) return;

  command = Serial.readStringUntil('\n');
  command.trim();
  command.toLowerCase();

  if (command == "stop stop") emergencyStop();
  else if (command == "move forward") motionState = "FORWARD";
  else if (command == "move backward") motionState = "BACKWARD";
  else if (command == "move left") prepareTurn("LEFT");
  else if (command == "move right") prepareTurn("RIGHT");
}

// ================== TURN PREP ==================
void prepareTurn(String dir) {
  stopCar();

  // ---- SIDE SAFETY CHECK BEFORE TURN ----
  if (dir == "LEFT" && sideObstacleDetected(leftSonar)) return;
  if (dir == "RIGHT" && sideObstacleDetected(rightSonar)) return;

  scanServo.write(dir == "LEFT" ? SERVO_LEFT : SERVO_RIGHT);
  delay(450);
  scanServo.write(SERVO_CENTER);
  delay(200);

  turnDirection = dir;
  turnStartTime = millis();
  motionState = "TURNING";
}

// ================== TURN EXECUTION ==================
void handleTurning() {

  // ---- LIVE SIDE MONITORING DURING TURN ----
  if (turnDirection == "LEFT" && sideObstacleDetected(leftSonar)) {
    emergencyStop();
    return;
  }
  if (turnDirection == "RIGHT" && sideObstacleDetected(rightSonar)) {
    emergencyStop();
    return;
  }

  analogWrite(ENA, TURN_SPEED);
  analogWrite(ENB, TURN_SPEED);

  if (turnDirection == "LEFT") {
    leftForward();
    rightBackward();
  } else {
    leftBackward();
    rightForward();
  }

  if (millis() - turnStartTime >= TURN_DURATION) {
    emergencyStop();
  }
}

// ================== SENSOR FUNCTIONS ==================
bool frontObstacleDetected() {
  return stableDetect(frontSonar, FRONT_STOP_DISTANCE);
}

bool rearObstacleDetected() {
  return stableDetect(rearSonar, REAR_STOP_DISTANCE);
}

bool sideObstacleDetected(NewPing &sonar) {
  return stableDetect(sonar, SIDE_STOP_DISTANCE);
}

bool stableDetect(NewPing &sonar, int limit) {
  int hits = 0;
  for (int i = 0; i < 5; i++) {
    int d = sonar.ping_cm();
    if (d > 0 && d <= limit) hits++;
    delay(6);
  }
  return hits >= 3;
}

// ================== MOTOR CONTROL ==================
void motorKickStart() {
  analogWrite(ENA, KICK_SPEED);
  analogWrite(ENB, KICK_SPEED);
  delay(35);
}

void moveForward() {
  motorKickStart();
  analogWrite(ENA, MOVE_SPEED);
  analogWrite(ENB, MOVE_SPEED);
  leftForward();
  rightForward();
}

void moveBackward() {
  motorKickStart();
  analogWrite(ENA, MOVE_SPEED);
  analogWrite(ENB, MOVE_SPEED);
  leftBackward();
  rightBackward();
}

void leftForward()  { digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); }
void leftBackward() { digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH); }
void rightForward() { digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); }
void rightBackward(){ digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH); }

void emergencyStop() {
  stopCar();
  motionState = "STOP";
}

void stopCar() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
