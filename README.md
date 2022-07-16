# Bitaala
Source code for Embedded System of traffic lights

**Description of the smart traffic assignment**

Design and simulate smart traffic lights at a junction which serves 6 roads that is 1, 2, 3, 4, 5 and 6. The following lines can move in parallel that is at the same time and each has a set of traffic lights controlling it.

1 and 2

3 and 4

5 and 6

Each pair is given 10 seconds to move (green lights) and 3 seconds warning (Umber) the line to stop after which the lights turn to red (stop). Only one pair of traffic lights can light green at a given time. The order of the car movement can be altered by a person pressing the number with the biggest traffic. This gives the actively moving lines 4 seconds of warning (amber) so that the new line starts moving. The new line will be accompanied by its paired line.

**Steps undertaken.**

On interpreting the assignment, we discovered that the system involves an interrupt to a normal flow of events. The normal flow of events involves traffic lights lighting in a certain order. And the interrupt arrives if a number is pressed to alter the movement of the cars.

We decided the sequence of lighting to be 1, 2 then 34 then 5, 6.

The state of the system is, while the green and orange of a pair of lights are on, only the red of the other pairs is on.

The state for a particular set of traffic lights is, while one color is on, the other colors should be off.

We agreed that this system needed the following components.

- 1 AT89C51 processor.
- 6 traffic lights for the required lighting sequence
- A phone keypad for generation of interrupts
- An LCD screen to display the action in the system (which lines are moving, switching of lines when a key on the keypad is pressed.
- An AND gate to send a bit to the interrupt pin on the processor, when a key is pressed. This is so as to connect all the keypad columns to the interrupt pin.
- 8 10KΩ resistors for interfacing port 0 of the processor.
- Ground
- Power

In order to program this system, we required functions or a function to do the following.

1. Initialize traffic lights
2. Light the traffic lights
3. Initialize the LCD
4. Send words to the LCD screen.
5. To handle the interrupt
6. Initialize the keypad
7. To check whether a key of the keypad has been pressed
