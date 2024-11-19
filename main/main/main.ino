//define pins

//rain sensor
const int rain1Pin = 1;

//motion sensor
const int motionPin = 2;

//button
const int buttonPin = 3;

//lights
const int redLightPin = 5;
const int yellowLightPin = 6;
const int greenLightPin = 8;

const int pedLight1Pin = 9;
const int pedLight2Pin = 10;

const int speakerPin = 11; //speaker

//some variables
int buttonState = LOW;           // Variable to hold the button state
int motionDetected = LOW;        // Variable to hold motion sensor state
unsigned long buttonPressTime = 0; // To record the time when the button is pressed


void setup() {
  // Inputs
  pinMode(rain1Pin, INPUT);    
  pinMode(buttonPin, INPUT);   
  pinMode(motionPin, INPUT);
  //Outputs
  pinMode(redLightPin, OUTPUT);
  pinMode(yellowLightPin, OUTPUT);
  pinMode(greenLightPin, OUTPUT);
  pinMode(pedLight1Pin, OUTPUT);
  pinMode(pedLight2Pin, OUTPUT);
  pinMode(speakerPin, OUTPUT);


}

void loop() {
  
  //match pin to input value
  int rain1 = digitalRead(rain1Pin);
  int button = digitalRead(buttonPin); //needs timer?
  int motion = digitalRead(motionPin);

  //make array made of input values


}
