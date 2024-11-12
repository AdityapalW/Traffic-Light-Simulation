// Define the pins
const int pirPin = 2;    // PIR sensor output connected to digital pin 2
const int ledPin = 10;   // LED connected to digital pin 13

void setup() {
  pinMode(pirPin, INPUT);    // Set PIR sensor pin as input
  pinMode(ledPin, OUTPUT);   // Set LED pin as output

  Serial.begin(9600);        // Start serial communication for debugging
}

void loop() {
  int motionState = digitalRead(pirPin);  // Read PIR sensor state

  if (motionState == HIGH) {  // Motion detected
    digitalWrite(ledPin, HIGH);  // Turn on LED
    Serial.println("Motion detected!");
  } else {
    digitalWrite(ledPin, LOW);   // Turn off LED if no motion
    Serial.println("No motion.");
  }

  delay(500);  // Delay for stability (adjust as needed)
}

