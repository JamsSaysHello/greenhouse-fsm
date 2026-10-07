#include <time.h>
#include <ncursesw/curses.h>
#ifndef GREENHOUSE_H
    #define GREENHOUSE_H

    #ifndef DAY_LENGTH
    #define DAY_LENGTH 100
    #endif

    #ifndef DRYOUT_TIME
    #define DRYOUT_TIME 1
    #endif

    #ifndef TEMP_TIME
    #define TEMP_TIME 2
    #endif

    enum greenhouse_states {
        MONITOR,
        HEAT,
        COOL,
        WATER,
        EXIT
    };

    /*
    * Function to increase the moisture in the greenhouse to 90. Would turn sprinklers on.
    */
    void hydrate();

    /*
    * Function to increase the temperature of the greenhouse by 1 degree F.
    */
    void heatersOn();

    /*
    * Function to decrease the temperature of the greenhouse by 1 degree F.
    */
    void coolingOn();

	extern int temperature;       // Temperature in Fahrenheit
	extern int moisture;          // % out of 100% watered
	extern time_t hourCycle;
	extern time_t moistureDecay;
	extern int day;
	extern int night;
	extern time_t saved_time;
	extern time_t saved_2time;
	extern time_t g_time;
	
	void dayTrack();    // Function to swap day and night after specified time.  (default 100 seconds)
	void dryTrack();    // Function to decrease moisture after a specified time. (default 1 second)
	void tempTrack();   // Function to increment temperature dependent on day/night after a specified time (default 2 seconds)
    
#endif // GREENHOUSE_H


