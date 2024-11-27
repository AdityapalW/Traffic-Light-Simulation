//define pins

//rain sensor
//const int rain1Pin = 2;

//motion sensor
const int motionPin = 3;

//button
const int buttonPin = 4;

//lights
const int redLightPin = 5;
const int yellowLightPin = 6;
const int greenLightPin = 8;

const int pedLight1Pin = 9;  //Walking Sign
const int pedLight2Pin = 10; //hand sign

const int spkPin = 11; //speaker

 int waitTime;
 int crossTime


//some variables
int buttonState = LOW;           // Variable to hold the button state
int motionDetected = LOW;        // Variable to hold motion sensor state
unsigned long buttonPressTime = 0; // To record the time when the button is pressed


void setup() {
  // Inputs
  //pinMode(rain1Pin, INPUT);    
  pinMode(buttonPin, INPUT);   
  pinMode(motionPin, INPUT);
  //Outputs
  pinMode(redLightPin, OUTPUT);
  pinMode(yellowLightPin, OUTPUT);
  pinMode(greenLightPin, OUTPUT);
  pinMode(pedLight1Pin, OUTPUT);
  pinMode(pedLight2Pin, OUTPUT);
  pinMode (spkPin, OUTPUT);


  //initialise all the Lights
  digitalWrite(redLightPin, LOW);
  digitalWrite(yellowLightPin, LOW);
  digitalWrite(greenLightPin, HIGH);
  digitalWrite(pedLight1Pin, LOW);
  digitalWrite(pedLight2Pin, HIGH);



  // ignore this 
  Serial.begin(9600);                 // Start serial communication for debugging


}

//functions for playing tones (speaker)

int tones[] = {
  3465, 2850, 2333, 1956, 1638, 1380, 1161, 992, 814, 704, 500
};

void playIdle() {
  tone(spkPin, 973, 25);
  delay(25);
  noTone(spkPin);
}

void playChirp() {
  // Iterate through all tones
  for (int i = 0; i < 11; i++) {
    // Play the next tone
    tone(spkPin, tones[i], 11);
    delay(11);
  }

}
void playWoodpecker() {
  // 17x = 2secs; 85x = 10 seconds
  for (int i = 0; i <= 85; i++) {
    tone(spkPin, 500, 30);
    delay(30);
    noTone(spkPin);
    delay(117); // wait
  }
}

void loop() {

  // Read the state of the button
 int  buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) { // Button pressed (LOW with pull-up)
    Serial.println("Button pressed, starting sequence...");
    buttonPressTime = millis(); // Record the time button was pressed
    playChirp();
    // Wait for 3 seconds
    delay(3000);

    // Check for motion
    motionDetected = digitalRead(motionPin);
    if (motionDetected == HIGH) {
      Serial.println("Motion detected! Continuing...");
    } else {
      Serial.println("No motion detected! Light will not turn on.");
      return; // Stop further actions if no motion
    }

    // Wait until 10 seconds have passed since the button was pressed
    while (millis() - buttonPressTime < 10000) {
      // Do nothing, just wait
    }

    // Turn on the light
    Serial.println("10 seconds passed, turning on light.");
         digitalWrite(greenLightPin, LOW);
      digitalWrite(yellowLightPin, HIGH);
      delay(3000); // Yellow light delay
      digitalWrite(yellowLightPin, LOW);
      digitalWrite(redLightPin, HIGH);

      // Pedestrian light ON
      digitalWrite(pedLight1Pin, HIGH);
      digitalWrite(pedLight2Pin, LOW);
      playChirp();
    // Keep the light on for demonstration; you can modify this part as needed
    delay(5000); // Light stays on for 5 seconds (for testing purposes)
      digitalWrite(redLightPin, LOW);
      digitalWrite(greenLightPin, HIGH);
      digitalWrite(pedLight1Pin, LOW);
      digitalWrite(pedLight2Pin, HIGH);
    Serial.println("Light turned off.");
  }
  else {
    Serial.println("Button not pressed");
  }
  //delay(1000);
}
