//define pins

//rain sensor
const int rain1Pin = 1;

//button
const int buttonPin = 3;

//motion sensor
const int motionPin = 4;

//lights
const int redLightPin = 5;
const int yellowLightPin = 6;
const int greenLightPin = 7;

const int pedLight1Pin = 8;
const int pedLight2Pin = 9;

const int speakerPin = 10; //speaker


//setup function

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
