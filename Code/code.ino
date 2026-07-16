#include <ESP32Servo.h>

// ---------------- Joystick / tilt ----------------
const int joyXPin = 34;   // X -> GPIO 34 (input only)
const int joyYPin = 35;   // Y -> GPIO 35 (input only)

// Joystick smoothing variables (Exponential Moving Average)
float smoothedX = 2048.0; // Start at midpoint
float smoothedY = 2048.0;
const float alpha = 0.15; // Smoothing factor (0.05 to 0.3). Lower is smoother but slower.

int xAngle = 0, yAngle = 0;      // mapped (115-125 and 65-75)

Servo tservoX;   // tilt servo for X
Servo tservoY;   // tilt servo for Y

// ---------------- Button (Joystick Click) ----------------
const int joyButtonPin = 2;

int lastJoyButtonState = HIGH;
unsigned long lastDebounce = 0;
const unsigned long debounceDelay = 50;

// ---------------- Maze walls ----------------
const int NUM_WALLS = 5;

Servo wallServos[NUM_WALLS];
const int wallPins[NUM_WALLS] = {13, 14, 27, 26, 25};

const int wall1States[] = {0, 90, 180};   // wall 1: 90 is up, 180 left
const int wall2States[] = {0, 90, 180};   // wall 2: 90 is down, 180 right
const int wall3States[] = {90, 180};      // wall 3
const int wall4States[] = {90, 180};      // wall 4: 90 is left, 180 down
const int wall5States[] = {0, 90, 180};   // wall 5: 90 is up, 180 left

// Pointers to each state array
const int* wallStates[NUM_WALLS] = {
  wall1States, wall2States, wall3States, wall4States, wall5States
};

// Automatically calculate state counts dynamically to prevent out-of-bounds crashes
const int wallStateCounts[NUM_WALLS] = {
  sizeof(wall1States) / sizeof(wall1States[0]),
  sizeof(wall2States) / sizeof(wall2States[0]),
  sizeof(wall3States) / sizeof(wall3States[0]),
  sizeof(wall4States) / sizeof(wall4States[0]),
  sizeof(wall5States) / sizeof(wall5States[0])
};

// Pick a random state for every wall
void newRun() {
  Serial.println("--- New run ---");
  for (int i = 0; i < NUM_WALLS; i++) {
    int choice = random(wallStateCounts[i]);   // Safe limit based on actual array sizes
    int angle  = wallStates[i][choice];
    wallServos[i].write(angle);

    Serial.print("Wall ");
    Serial.print(i + 1);
    Serial.print(" -> state ");
    Serial.print(choice);
    Serial.print(" (");
    Serial.print(angle);
    Serial.println(" deg)");
  }
}

void setup() {
  Serial.begin(115200);

  // Tilt servos
  tservoX.attach(17);
  tservoY.attach(22);

  // Wall servos
  for (int i = 0; i < NUM_WALLS; i++) {
    wallServos[i].attach(wallPins[i]);
  }

  // Button input with internal pullup (pressed = LOW)
  pinMode(joyButtonPin, INPUT_PULLUP);

  randomSeed(analogRead(39)); // Seed off unused floating pin
  newRun();                   // Start with a randomized maze
}

void loop() {
  // ---- 1. Read & Filter Joystick (Continuous) ----
  int rawX = analogRead(joyXPin);
  int rawY = analogRead(joyYPin);

  // Exponential Moving Average filter to kill jitter
  smoothedX = (alpha * rawX) + ((1.0 - alpha) * smoothedX);
  smoothedY = (alpha * rawY) + ((1.0 - alpha) * smoothedY);

  // Map smoothed values to servo angles
  xAngle = map((int)smoothedX, 0, 4095, 115, 125); // 120 is middle
  yAngle = map((int)smoothedY, 0, 4095, 65, 75);   // 70 is middle

  tservoX.write(xAngle);
  tservoY.write(yAngle);

  // ---- 2. Button Check (Debounced Edge Detection) ----
  int readingJoyButton = digitalRead(joyButtonPin);

  if (readingJoyButton != lastJoyButtonState) {
    Serial.print("Button changed to ");
    Serial.println(readingJoyButton);   // 1 = released, 0 = pressed
  }
  // Trigger only on transition from released (HIGH) to pressed (LOW)
  bool joyPressed = (readingJoyButton == LOW && lastJoyButtonState == HIGH);

  if (joyPressed && (millis() - lastDebounce) > debounceDelay) {
    lastDebounce = millis();
    newRun();
  }

  lastJoyButtonState = readingJoyButton;

  delay(10);
}