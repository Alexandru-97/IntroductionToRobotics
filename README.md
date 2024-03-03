# Robotics Projects
Repo containing small projects i made for the Introduction to Robotics course


Introduction to Robotics laboratory homeworks, taken in the 3rd year at the Faculty of Mathematics and Computer Science, University of Bucharest. Each homework includes requirements, implementation details, code and image files.


# Project 1 (RGB LED)

### Requirements ###

Use a separate potentiometer in controlling each of the color of the RGB led (Red, Green and Blue). The control must be done with digital electronics (aka you must read the value of the potentiometer with Arduino, and write a mapped value to each of the pins connected to the led).

Components: RBG led (1 minimum), potentiometers (3 minimum), resistors and wires (per logic)

### Picture of setup ###
![WhatsApp Image 2021-10-27 at 15 31 20 (1)](https://user-images.githubusercontent.com/62179598/139066010-7fd1b010-e98d-4ef9-a28a-83d60500d9c3.jpeg)


### Video demonstration ###
https://youtu.be/kEyHzu88KyY

# Project 2 (TRAFFIC LIGHTS FOR PEOPLE AND CARS)
### Requirements ###

• Components: 5 LEDs, 1 button, 1 buzzer, resistors and wires (per logic)
• General description: Building the traffic lights for a crosswalk. 2 LEDs will be used to represent the traffic lights for people (red and green)
and 3 LEDs to represent the traffic lights for cars (red, yellow and green).

The system has the following states:
1. State 1 (default, reinstated after state 4 ends): green light for cars,
red light for people, no sounds. Duration: indefinite, changed by
pressing the button.
2. State 2 (initiated by counting down 10 seconds after a button press):
the light is yellow for cars, red for people and no sounds.
Duration: 3 seconds.
3. State 3 (iniated after state 2 ends): red for cars, green for people and
a beeping sound from the buzzer at a constant interval. Duration:
10 seconds.
4. State 4 (initiated after state 3 ends): red for cars, blinking green
for people and a beeping sound from the buzzer, at a constant interval, faster than the beeping in state 3.
Duration: 5 seconds.

### Picture of setup ###
![WhatsApp Image 2021-11-03 at 21 28 45](https://user-images.githubusercontent.com/62179598/140181636-4a98dfb8-7fdc-4ff5-bdd4-090e1697969e.jpeg)

### Video demonstration ###
https://www.youtube.com/watch?v=FuNRmDtvhxA&ab_channel=AlexandruOana

# Project 3 (ELECTROMAGNETIC FIELD DETECTOR)
### Requirements ###

• Components: a buzzer and a 7-segment display

• Task: detects EMF (check body and near outlets). It prints the value on the 7-segment display and makes a sound based on the intensity.

### Picture of setup ###
![IMG_20211110_214938](https://user-images.githubusercontent.com/62179598/141189574-25c48259-1d68-4510-8d50-db2718c7baa0.jpg)

### Video demonstration ###
https://youtu.be/l5X7xixCLCI


# Project 4 (4-digit 7-segment display with joystick and shift register)
### Requirements ###
• Components: a joystick, a 4 digit 7-segment display, a 74hc595 shift register

• Task: First state: A joystick axis can be used to cycle through the 4 digits; using the other axis does nothing. A blinking decimal point shows the current digit position. When pressing the button, it locks in on the selected digit and enter the second state. In this state, the decimal point stays always on, no longer blinking and the axis can no longer be used to cycle through the 4 digits. Instead, the other axis can be used to increment or decrement the number on the current digit. Pressing the button again returns to the previous state.

### Picture of setup ###
![WhatsApp Image 2021-11-17 at 18 41 01 (1)](https://user-images.githubusercontent.com/62179598/142243895-c856dd5c-d2ed-43d4-893c-850c4c1784fe.jpeg)


### Video demonstration ###
https://www.youtube.com/watch?v=oXStTMpoZFs&ab_channel=AlexandruOana
