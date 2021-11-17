const int dataPin = 12; //DS
const int latchPin = 11; //STCP - STORAGE CLOCK PIN
const int clockPin = 10; //SHCP - SHIFT REGISTER PIN

const int pinSW = 2; // switch input
const int xPin = A0; // Ox axis input
const int yPin = A1; // Oy axis input
const int segD1 = 7; 
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

// joystick deadzone(how far the stick must move off center until it registers as an input)
const int minThreshold = 400; 
const int maxThreshold = 600;

const int debounceInterval = 100; // minimum interval between button inputs 
const int blinkingInterval = 300;
unsigned long startTimer = 0; // timer for blinking 

const  int segmentDigits[] = {
  segD1, segD2, segD3, segD4  // pins that control the digits
};


int digitsValues[] = { 
  0, 0, 0, 0  // array that stores each digit's value
  };

// total number of digits on the display
const int digitsCount = 4;

int digitArray[17] = {
//A B C D E F G DP 
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B11101110, // A
  B00111110, // b
  B10011100, // C
  B01111010, // d
  B10011110, // E
  B10001110, // F
  B00000001  // DP; if we want to display DP we just need to add 1 to any of the display digits
};


int xValue = 0;
int yValue = 0;
int displayDigit = 0; // the current active digit - where DP is active
bool joyMoved = false; 
bool buttonPressed = false; // checks if the button was pushed an uneven amount of times
bool dpState = LOW;

void setup(){

  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(pinSW, INPUT_PULLUP);  //inverts behaviour of INPUT mode (high = off, low = on)
  // button presses will be handled with interrupts
  attachInterrupt(digitalPinToInterrupt(pinSW), toggle, FALLING);  

  for (int i = 0; i < digitsCount; i++) {
    
    pinMode(segmentDigits[i], OUTPUT);
    
  }
  Serial.begin(9600);
}


void loop(){

  outputDigits();
  handleEvents();
  
}

void showDigit(int digitNumber) {
  
  for (int i = 0; i < digitsCount; i++) {
    
    digitalWrite(segmentDigits[i], HIGH); // close all displays apart from one
  }
  
  digitalWrite(segmentDigits[digitNumber], LOW); // open one display at a time
  
}

// write the digit on the display

void writeReg(int digit) {
  
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  digitalWrite(latchPin, HIGH);
  
}


// eliminate noise on the button (only take in actual user input)

void toggle() {

  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();
  if (interruptTime - lastInterruptTime > debounceInterval) {
    
    buttonPressed = !buttonPressed;
    
  }

  lastInterruptTime = interruptTime;
}


// main function that handles the 2 main states

void handleEvents() {
  
  xValue = analogRead(xPin);
  yValue = analogRead(yPin);

 
  // state 1 - button has not been pushed yet/ has been pushed twice
  // only Ox axis input counts
  // dp is blinking and we can shift through digits
  
  if (buttonPressed == false) {
    
    if (xValue < minThreshold && joyMoved == false) {
      
      if (displayDigit > 0) {
        
        displayDigit--;
      
      }
      
      joyMoved = true;
      
    }
    if (xValue > maxThreshold && joyMoved == false) {
      
      if (displayDigit < 3) {
        
        displayDigit++;
        
      }
      
      joyMoved = true;
      
    }

     outputDigits();  
     if (xValue >= minThreshold && xValue <= maxThreshold) {
      
      joyMoved = false; //joystick is back in neutral position on Oy axis
      
     }
  }

  // state 2(button was pushed); 
  // only Oy axis input counts
  // decimal point is locked and we can increment/decrement the current digit
  
  else {
    
    if (yValue < minThreshold && joyMoved == false) {
      
      joyMoved = true;
      
      if (digitsValues[displayDigit] > 0) {
        
        digitsValues[displayDigit] --;  // decrement digit
        
      }
      else {
        
        digitsValues[displayDigit] = 9; // loop back arond from 0-9
        
      }
    }
    
    if (yValue > maxThreshold && joyMoved == false) {
 
      joyMoved = true;
      
      if (digitsValues[displayDigit] < 9) {
        
        digitsValues[displayDigit] ++;  //increment digit
        
      }

       else {
        
        digitsValues[displayDigit] = 0; // loop back arond from 9-0
        
      }
    }
    
    outputDigits(); 
    if (yValue >= minThreshold && yValue <= maxThreshold) {
      
      joyMoved = false; //joystick is back in neutral position on Oy axis
      
    }
  }
}


// function that displays the digit configuration
 
void outputDigits() {

  for (int i = 0; i < digitsCount; i++) {
    
    showDigit(i);
    
    if (i == displayDigit) {
      
      // making the dp blink when we are changing displays
      if (buttonPressed == false) {
        
         if (millis() - startTimer > blinkingInterval) {
          
          dpState = !dpState;
          startTimer = millis();
          
         }
         if (dpState == HIGH) {
          
          writeReg(digitArray[digitsValues[i]]); //output without decimal point
          
         }
         else {
          
          writeReg(digitArray[digitsValues[i]]+1); //output with decimal point
          
         }
      }

      // if button was pushed
      else {
        
        writeReg(digitArray[digitsValues[i]]+1); //output with decimal point
        
      }
      
    }
    // the values of the other digits are stored in digitsValues
    else {

       writeReg(digitArray[digitsValues[i]]);
      
    }
    delay(6);
    
  }
}
