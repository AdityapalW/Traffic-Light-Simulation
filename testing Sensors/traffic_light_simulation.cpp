#include "TrafficSystem.h"
void setup() {
  setupTrafficSystem(); // Calls the setup function for the traffic system
}

void loop() {
  loopTrafficSystem(); // Calls the main loop function for the traffic system
}

// State Variables
bool isRaining = false;
bool isPedestrianWaiting = false;
bool pedestrianCrossing = false;

void setupTrafficSystem() {
  pinMode(rainSensorPin, INPUT);
  pinMode(motionSensorPin, INPUT);
  pinMode(pedestrianButtonPin, INPUT);

  pinMode(pedestrianLedPin, OUTPUT);
  pinMode(trafficLedPin, OUTPUT);
  pinMode(speakerPin, OUTPUT);

  // Initialize traffic light to green (for vehicles)
  digitalWrite(trafficLedPin, HIGH);  // Traffic light on
  digitalWrite(pedestrianLedPin, LOW); // Pedestrian light off

  Serial.begin(9600); // Initialize serial monitor for debugging
}

void loopTrafficSystem() {
  int rainSensorValue = analogRead(rainSensorPin);
  isRaining = (rainSensorValue > rainThreshold);
  Serial.print("Rain Sensor Value: ");
  Serial.println(rainSensorValue);

  if (digitalRead(pedestrianButtonPin) == HIGH) {
    isPedestrianWaiting = true;
  }

  bool pedestrianDetected = (digitalRead(motionSensorPin) == HIGH);

  if (isPedestrianWaiting && (isRaining || pedestrianDetected)) {
    pedestrianCrossing = true;
    isPedestrianWaiting = false;
    activatePedestrianCrossing();
  }

  if (!pedestrianDetected && pedestrianCrossing) {
    pedestrianCrossing = false;
    resetTrafficLights();
  }

  delay(100); // Delay to stabilize the loop
}

void activatePedestrianCrossing() {
  Serial.println("Pedestrian Crossing Activated");

  digitalWrite(pedestrianLedPin, HIGH);  // Turn on pedestrian light
  digitalWrite(trafficLedPin, LOW);      // Turn off traffic light

  tone(speakerPin, 1000, 500);           // Play sound notification
  delay(5000);                           // Time for pedestrian to cross safely
}

void resetTrafficLights() {
  Serial.println("Traffic Resumed");

  digitalWrite(pedestrianLedPin, LOW);   // Turn off pedestrian light
  digitalWrite(trafficLedPin, HIGH);     // Turn on traffic light
}
