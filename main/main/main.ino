// Pin Definitions
const int buttonPin = 4;          // Pedestrian button
const int motionPin = 3;          // Motion sensor
const int redLightPin = 5;        // Traffic red light
const int yellowLightPin = 6;     // Traffic yellow light
const int greenLightPin = 7;      // Traffic green light
const int pedWalkLightPin = 10;   // Pedestrian walk light
const int pedStopLightPin = 9;    // Pedestrian stop light
const int spkPin = 8;             // Speaker
const int weatherSensorPin = A0;  // Weather sensor (rain detection)

// Timing Variables
int waitTime = 10000;             // Default wait time for button press (in ms)
int crossTime = 15000;            // Default pedestrian crossing time (in ms)
int halfWaitTime = waitTime / 2;  // Half the wait time for checking motion

// Sound tones
int tones[] = {3465, 2850, 2333, 1956, 1638, 1380, 1161, 992, 814, 704, 500};

// Rain thresholds
const int rainThreshold = 500;   // Analog value threshold for rain detection

void playChirp() {
  for (int i = 0; i < 11; i++) {
    tone(spkPin, tones[i], 11);
    delay(11);
  }
}

void playIdleTone() {
  tone(spkPin, 973, 25);
  delay(25);
  noTone(spkPin);
}

void handlePedestrianLights(bool walk) {
  if (walk) {
    digitalWrite(pedWalkLightPin, LOW); // Walk light ON
    digitalWrite(pedStopLightPin, HIGH); // Stop light OFF
  } else {
    digitalWrite(pedWalkLightPin, HIGH); // Walk light OFF
    digitalWrite(pedStopLightPin, LOW);  // Stop light ON
  }
}

void idleState() {
  digitalWrite(redLightPin, HIGH);  // Red OFF
  digitalWrite(yellowLightPin, HIGH); // Yellow OFF
  handlePedestrianLights(false); // Pedestrian hand ON, walk OFF

  for (int i = 0; i < 5; i++) { // Blink green 5 times
    digitalWrite(greenLightPin, LOW);  // Green ON
    delay(1500);
    digitalWrite(greenLightPin, HIGH); // Green OFF
    delay(1500);
  }
}

void pedestrianCrossing() {
  digitalWrite(greenLightPin, LOW);  // Green ON
  delay(halfWaitTime);

  if (digitalRead(motionPin) == LOW) {
    Serial.println("Motion detected. Proceeding with pedestrian crossing...");

    digitalWrite(greenLightPin, HIGH); // Green OFF
    digitalWrite(yellowLightPin, LOW); // Yellow ON
    delay(2000);

    digitalWrite(yellowLightPin, HIGH); // Yellow OFF
    digitalWrite(redLightPin, LOW);    // Red ON

    handlePedestrianLights(true);

    unsigned long startTime = millis();
    while (millis() - startTime < crossTime) {
      playChirp();
      delay(500); // Slight pause between chirps
    }

    digitalWrite(redLightPin, HIGH); // Red OFF
    handlePedestrianLights(false);
    idleState();
  } else {
    Serial.println("No motion detected. Returning to idle state...");
    idleState();
  }
}

void adjustTimingForWeather() {
  int rainValue = analogRead(weatherSensorPin);
  if (rainValue < rainThreshold) {
    // Rain detected
    Serial.println("Rain detected. Adjusting timings...");
    waitTime = 15000; // Increase wait time in rain
    crossTime = 20000; // Increase crossing time in rain
  } else {
    // No rain
    Serial.println("No rain detected. Using default timings...");
    waitTime = 10000; // Default wait time
    crossTime = 15000; // Default crossing time
  }
  halfWaitTime = waitTime / 2;
}

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(motionPin, INPUT);
  pinMode(redLightPin, OUTPUT);
  pinMode(yellowLightPin, OUTPUT);
  pinMode(greenLightPin, OUTPUT);
  pinMode(pedWalkLightPin, OUTPUT);
  pinMode(pedStopLightPin, OUTPUT);
  pinMode(spkPin, OUTPUT);

  digitalWrite(redLightPin, HIGH); // Red OFF
  digitalWrite(yellowLightPin, HIGH); // Yellow OFF
  digitalWrite(greenLightPin, HIGH); // Green OFF
  handlePedestrianLights(false); // Hand ON, Walk OFF

  Serial.begin(9600);
}

void loop() {
  adjustTimingForWeather(); // Check and adjust timings based on weather

  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) { // Button pressed
    Serial.println("Button pressed. Starting pedestrian crossing process...");
    delay(50); // Debounce
    pedestrianCrossing();
  } else {
    idleState(); // Default idle state
    delay(500);  // Short delay to prevent rapid state toggling
  }
}
