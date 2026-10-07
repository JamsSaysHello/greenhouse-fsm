**Greenhouse Manager Finite State Machine**
A finite state machine to manage a greenhouse temperature and soil mositure using the ncurses library.

## OVERVIEW
This finite state machine program simulates an automatic greenhouse manager. It tracks the soil moisture, and the internal temperature of the greenhouse. It also keeps track of whether it is day or night, and will adjust its target parameters based upon the state of the sun cycle. Temperature is measured in degrees Fahrenheit, and moisture is a percentage of 100% moist. 

The target moisture percentage is 90%, to prevent the soil from always being too wet, and will be allowed to dry up to 20% before sprinklers turn on again and raise the moisture levels back to 90%.

The target temperature is 70 during the day, and 60 during the nighttime. It temperatures will be allowed to within a +- 10 degree range before the heat or A/C turn on to prevent the machines turning on and off every minute. 


## COMMANDS
A command line argument of "-h" or "--help" can be added after the command ./fsm to list available keys to modify the system while the machine is running. The buttons available are as follow.
q : quit the program
h : Raise temperature to 100 degrees
c : Lower temperature to 20 degrees
d : Set to daytime
n : Set to nighttime
w : Lower moisture to 20%

The program will take these modifications and switch states, changing these values to recover and return to it's comfortable state. 

## BUILDING
It is necessary for ncurses to be installed on the system for this FSM to function.

This program can be built using the command
`gcc main.c greenhouse.c -lncurses -o fsm`

To adjust the length of the day in seconds, the rate of the soil drying out in seconds, and the rate of the temperature change, add this line right after gcc. Replace day_length, dryout_time, and temp_time with your desired value in seconds.
`-DDAY_LENGTH=$(day_length) -DDRYOUT_TIME=$(dryout_time) -DTEMP_TIME=$(temp_time)`
