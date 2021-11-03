
const int BUTTON_PIN = 2;
const int GREEN_CARS_PIN = 13;
const int YELLOW_CARS_PIN = 12;
const int BUZZER_PIN = 11;
const int RED_CARS_PIN = 10;
const int GREEN_PEDESTRIANS_PIN = 4;
const int RED_PEDESTRIANS_PIN = 3;

const int GREEN_TO_YELLOW_CARS_INTERVAL = 10000; 
const int YELLOW_TO_RED_CARS_INTERVAL = 13000;
const int GREEN_PEDESTRIANS_INTERVAL = 14000;    // first delay: red light(cars) -> green light(pedestrians)
const int GREEN_TO_BLINKING_INTERVAL = 24000;
const int BLINKING_TO_RED_INTERVAL = 29000;
const int GREEN_CARS_INTERVAL = 30000;    // second delay: red light(pedestrians) -> green light(cars)
const int BLINKING_INTERVAL = 600;    // interval between blinks(pedestrian green light)
const int LONG_BUZZ_INTERVAL = 1000;   // interval between the first buzzes

const int BUZZER_TONE = 150;

// states for the traffic lights and the push button
// states are ready for displaying state 1 (cars - green, pedestrians - red)
bool buttonState = LOW;
bool greenCarsState = HIGH;
bool yellowCarsState = LOW;
bool redCarsState = LOW;
bool greenPedestriansState = LOW;
bool redPedestriansState = HIGH;

//the flow default state is off
//when the button is pressed, the flow begins 
bool flow = false;

unsigned long previousBlink = 0;
unsigned long previousBuzz = 0;
unsigned long startTimer = 0;
unsigned long currentTime = 0;

int reading;
int lastReading;
int passedTime;

// any input change faster than 50 ms is neglijable
// cancels out noise in the push button
unsigned long debounceDelay  = 50;
unsigned long lastDebounceTime = 0;

// main functions that handles state changes 
// the states are handled in reverse cronologycal order for convenience
// each state is set up after a specific time passed from pushing the button,
// thus it is easier to start with the last state and eliminate one by one
void cycleTrafficLights(){
  
  currentTime = millis();
  passedTime = currentTime - startTimer;

  if(passedTime > GREEN_CARS_INTERVAL) {
    // cars traffic light: red -> green
    // end of routine (back to the initial stage)
    
    redCarsState = LOW;
    greenCarsState = HIGH;
    flow = false;
  }

  //---delay between pedestrians -> red and cars -> green---
  
  else if(passedTime > BLINKING_TO_RED_INTERVAL) {
    
    // pedestrian traffic light: green -> red 
    redPedestriansState = HIGH;
    greenPedestriansState = LOW;
    
  }

  else if(passedTime > GREEN_TO_BLINKING_INTERVAL) {
    
    // pedestriang traffic light: green -> blinking green
    // buzzing -> intensifies
    if(currentTime - previousBlink > BLINKING_INTERVAL){
      
      greenPedestriansState = !greenPedestriansState;
      tone(BUZZER_PIN, BUZZER_TONE, 200);
      previousBlink = millis();
      
    }
  }

  else if (passedTime > GREEN_PEDESTRIANS_INTERVAL){
    
    // pedestrian traffic light: red -> green
    greenPedestriansState= HIGH;
    redPedestriansState = LOW;

    // buzzing at a slow rate
    if(currentTime - previousBuzz > LONG_BUZZ_INTERVAL) {
      tone(BUZZER_PIN, BUZZER_TONE, 300);
      previousBuzz = millis();
      
    }
  }

  //---delay between cars -> red and pedestrians -> green---
 
  else if (passedTime > YELLOW_TO_RED_CARS_INTERVAL){
    
    // cars traffic light: yellow -> red 
    yellowCarsState = LOW;
    redCarsState = HIGH;
    
  }
  
  else if (passedTime > GREEN_TO_YELLOW_CARS_INTERVAL){
    
    // cars traffic light: green -> yellow
    yellowCarsState = HIGH;
    greenCarsState = LOW;
    
  }
}

void outputLeds() {
   
  digitalWrite(GREEN_CARS_PIN, greenCarsState);
  digitalWrite(YELLOW_CARS_PIN, yellowCarsState);
  digitalWrite(RED_CARS_PIN, redCarsState);
  digitalWrite(GREEN_PEDESTRIANS_PIN, greenPedestriansState);
  digitalWrite(RED_PEDESTRIANS_PIN, redPedestriansState);
  
}

void readButtonInput() {

  // get the input signal out of the pushbutton
  reading = digitalRead(BUTTON_PIN);
  if(reading != lastReading) {
    
    lastDebounceTime = millis();
    
  }

  // check if the input signal is an actual button push
  // by ignoring state changes faster than 50 ms
  if((millis() - lastDebounceTime) > debounceDelay) {
    
    if(reading != buttonState) {
      
      buttonState = reading;
      if(buttonState == LOW && flow == false) {
        
        startTimer = millis();
        
        //if a button push was detected and the flow is not in motion,
        //the traffic flow starts
        flow = true; 
        
      }
    }
  }
  
  lastReading = reading;
  
}

void setup() {

  //internal 20k pullup resistors
  //inverts behaviour of INPUT mode (high = off, low = on)
  pinMode(BUTTON_PIN, INPUT_PULLUP); 

  //output pins for the 5 traffic lights and the buzzer
  pinMode(GREEN_CARS_PIN, OUTPUT);
  pinMode(YELLOW_CARS_PIN, OUTPUT);
  pinMode(RED_CARS_PIN, OUTPUT);
  pinMode(GREEN_PEDESTRIANS_PIN, OUTPUT);
  pinMode(RED_PEDESTRIANS_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  
  //output led states
  outputLeds();
  
  if(flow == true) {

    //main function that switches between the 4 states 
    cycleTrafficLights();
    
  }

  readButtonInput();
  
}
