# IntroductionToRobotics
Repo for Introduction to Robotics course


Introduction to Robotics laboratory homeworks, taken in the 3rd year at the Faculty of Mathematics and Computer Science, University of Bucharest. Each homework includes requirements, implementation details, code and image files.


# Homework 1 (RGB LED)

### Requirements ###

Use a separate potentiometer in controlling each of the color of the RGB led (Red, Green and Blue). The control must be done with digital electronics (aka you must read the value of the potentiometer with Arduino, and write a mapped value to each of the pins connected to the led).

Components: RBG led (1 minimum), potentiometers (3 minimum), resistors and wires (per logic)

### Picture of setup ###
![WhatsApp Image 2021-10-27 at 15 31 20 (1)](https://user-images.githubusercontent.com/62179598/139066010-7fd1b010-e98d-4ef9-a28a-83d60500d9c3.jpeg)


### Video demonstration ###
https://youtu.be/kEyHzu88KyY

# Homework 2 (TRAFFIC LIGHTS FOR PEOPLE AND CARS)
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

# Homework 3

