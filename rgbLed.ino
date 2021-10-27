const int RED_LED_PIN = 11;
const int GREEN_LED_PIN  = 10;
const int BLUE_LED_PIN = 9;

const int RED_POT_PIN = A3;
const int GREEN_POT_PIN = A5;
const int BLUE_POT_PIN = A2;

int redPotValue = 0;
int greenPotValue = 0;
int bluePotValue = 0;

int redBrightness = 0;
int greenBrightness = 0;
int blueBrightness = 0;

/*
    The 'setup' function initializes the pins connected to the RGB led
    as output pins(they receive analog signal) and the ones connected 
    to the potentiometers as input pins(they give analog signal) 
 */
void setup() {
  
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  
  pinMode(RED_POT_PIN, INPUT);
  pinMode(GREEN_POT_PIN, INPUT);
  pinMode(BLUE_POT_PIN, INPUT);
  
}

/*  
    Analog input values are taken from the potentiometers and stored into variables for 
    each of the 3 colours(red, green, blue)
*/
void readValues(){
  
  bluePotValue = analogRead(BLUE_POT_PIN);
  redPotValue = analogRead(RED_POT_PIN);
  greenPotValue = analogRead(GREEN_POT_PIN);
  
}

/*
    Function that takes the stored input values taken from the potentiometers(range 0 - 1023) and
    assignes them a value suitable for analog output(range 0 - 255), using the 'map' function.
 */ 
void mapValues(){
  
  redBrightness = map(redPotValue, 0 ,1023, 0, 255);
  greenBrightness = map(greenPotValue, 0 ,1023, 0, 255);
  blueBrightness = map(bluePotValue, 0 ,1023, 0, 255);
  
}

/*
    Function that takes the mapped values and passes them to each specific led pin(red, green, blue);
    Thus, the rgb led outputs the brightness for each colour all at once (within neglijable time
    discrepancies).
 */
void writeValues(){
  
  analogWrite(RED_LED_PIN, redBrightness);
  analogWrite(GREEN_LED_PIN, greenBrightness);
  analogWrite(BLUE_LED_PIN, blueBrightness);
  
}

/*
    Main function that calls 'readValues','mapValues', 'writeValues' functions;
    The output is the mixed intensity of each of the 3 colours (red, green, blue)
    resulting in a unique colour.
 */
void loop() {

  readValues();
  mapValues();
  writeValues();
  
}
