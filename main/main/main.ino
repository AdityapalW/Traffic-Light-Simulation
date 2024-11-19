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

const int speakerPin = 11; //speaker

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
  pinMode(speakerPin, OUTPUT);


  //initialise all the Lights
  digitalWrite(redLightPin, LOW);
  digitalWrite(yellowLightPin, LOW);
  digitalWrite(greenLightPin, HIGH);
  digitalWrite(pedLight1Pin, LOW);
  digitalWrite(pedLight2Pin, HIGH);



  // ignore this 
  Serial.begin(9600);                 // Start serial communication for debugging


}

void loop() {

  //match pin to input value
  int rain1value = analogRead(A0); //Since rain sensor is a analog sensor
  buttonState = digitalRead(buttonPin); //needs timer?
  motionDetected = digitalRead(motionPin);

  //make array made of input values




  // If the button is pressed
  if (buttonState == LOW) {
    Serial.println("Button pressed. Pedestrian crossing requested.");

  if (rain1value > 500) { // Threshold for detecting rain (adjust as needed)
      Serial.println("Rain detected. Adjusting timings...");
      waitTime = 5000;   // Shorten pedestrian wait time
      crossTime = 8000;  // Extend pedestrian crossing time
    } else {
      Serial.println("No rain detected. Using default timings.");
      waitTime = 10000;  // Default wait time
      crossTime = 5000;  // Default crossing time
    }
    delay(waitTime/2);

    if (motionDetected == HIGH) {
      Serial.println("Motion detected. Pedestrian is still here");

    delay(waitTime/2);

      // After the wait time is donr turn the light red
      digitalWrite(greenLightPin, LOW);
      digitalWrite(yellowLightPin, HIGH);
      delay(3000); // Yellow light delay
      digitalWrite(yellowLightPin, LOW);
      digitalWrite(redLightPin, HIGH);

      // Pedestrian light ON
      digitalWrite(pedLight1Pin, HIGH);
      digitalWrite(pedLight2Pin, LOW);


      //let the padestrian cross

      delay(crossTime);


      //reseting all the light
      digitalWrite(redLightPin, LOW);
      digitalWrite(greenLightPin, HIGH);
      digitalWrite(pedLight1Pin, LOW);
      digitalWrite(pedLight2Pin, HIGH);

      Serial.println("Crossing complete. Lights reset.");

  }  else {  // if no motion was detected
      Serial.println("No motion detected. Cancelling crossing.");
  }



}
