#include <ncursesw/curses.h>
#include "greenhouse.h"

// Global Variables initialized

int temperature = 50;       // Temperature in Fahrenheit
int moisture = 75;          // % out of 100% watered
extern time_t hourCycle;
extern time_t moistureDecay;
extern time_t tempDecay;
int day = 1;
int night = 0;
extern time_t saved_time;
extern time_t saved_2time;
extern time_t saved_3time;
extern time_t g_time;
int temp;

// Function to water the greenhouse -> Maximizing moisture
void hydrate(){
    moisture++;
}

// Function to increase the temperature per call of the function.
void heatersOn(){
    temperature++;
}

// Function to decrease the temperature per call of the function. 
void coolingOn(){
    temperature--;
}

// Function to swap day and night after a specified time (default 100 seconds)
void dayTrack(){
    if (hourCycle >= DAY_LENGTH) {
        temp = day;
        day = night;
        night = temp;
        saved_time = g_time;
    }
}

// Function to decrease soil moisture after a specified time (default 1 second)
void dryTrack(){
    if (moistureDecay >= DRYOUT_TIME) {
        moisture--;
        saved_2time = g_time;
    }
}

// Function to increment temperature dependent on day/night after a specified time (default 2 seconds)
void tempTrack(){
	if ((tempDecay >= TEMP_TIME) && day) {
		temperature++;
		saved_3time = g_time;
	}
	if ((tempDecay >= TEMP_TIME) && night) {
		temperature--;
		saved_3time = g_time;
	}
}
