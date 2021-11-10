
//pins of 7 segment display
const int pinA = 2;
const int pinB = 3;
const int pinC = 4;
const int pinD = 5;
const int pinE = 6;
const int pinF = 7;
const int pinG = 8;
const int pinDP = 9;

const int anthenaPin = A0;
const int buzzerPin = 11;

const int buzzerDuration = 10;
const int segSize = 8;  //size of array used for storing the dipslay pins
const int noOfDigits = 10;
const int sampleSize = 1000;  // number of readings needed for displaying one level

unsigned long averaging = 0;  // variable for tracking the average value of the readings
int val = 0 ;  // variable to track each reading's value
int buzzerTone;


//  pins are stored in an array for easier access
int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

byte digitMatrix[noOfDigits][segSize - 1] = {
// a  b  c  d  e  f  g
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1} //9
};


void displayNumber(byte digit) {
  
  for (int i = 0; i < segSize - 1; i++) {
      digitalWrite(segments[i], digitMatrix[digit][i]);
  }
  
}

// function that performs multiple readings and returns an aggregate value
int readSamples(){

  averaging = 0; //reset the average for the next reading
  for (int i = 0 ; i < sampleSize; i++){
    val = analogRead(anthenaPin);
    val = constrain(val, 0, 300);  // only consider emf input between 0 and 300
    averaging += val;
  }
   averaging = averaging/sampleSize;
   return averaging;
   
}

void setup() {

  //the anthena will capture the emf signal
  pinMode(anthenaPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // the display pins are all used for output
  for (int i = 0; i < segSize; i++) {
      pinMode(segments[i], OUTPUT);
  }

  Serial.begin(9600);
  
}

void loop() {
  
  averaging = readSamples();  
  
  averaging = map(averaging, 0, 350, 0, 10); // mapping to a 0-9 digit to broadcast on the display
  displayNumber(averaging);
  
  buzzerTone = map(averaging, 0, 10, 200, 1000); // mapping the tone according to the emf level
  tone(buzzerPin, buzzerTone, buzzerDuration);
  
}


 
