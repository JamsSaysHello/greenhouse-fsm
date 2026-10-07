#include <time.h>
#include <ncursesw/curses.h>
#include "greenhouse.h"
#include <string.h>
#include <stdint.h>

enum greenhouse_states current_state;
enum greenhouse_states next_state;

extern int temperature;       // Temperature in Fahrenheit
extern int moisture;          // % out of 100% watered
time_t hourCycle;
time_t moistureDecay;
time_t tempDecay;
extern int day;               // 1 for true, 0 for false
extern int night;             // 1 for true, 0 for false - Always opposite of day
time_t saved_time;
time_t saved_2time;
time_t saved_3time;
time_t g_time;

/*
* Provided by Professor to initalize ncurses to work.
*/
void init_ncurses() {
    initscr();
    cbreak();
    noecho();
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    set_escdelay(0);
}

/*
* Modified from Professor's example code to start the FSM program. 
*/
void init_fsm(){
    current_state = MONITOR;
    next_state = MONITOR;
    init_ncurses();
    g_time = time(NULL);
}

uint64_t get_time_ms() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000) + (ts.tv_nsec / 1000000);
}

int main(int argv, char* argc[]) {

    // Code to allow "-h" and "--help"
    if (argv > 1) {
        if (strcmp(argc[1], "-h") == 0 || strcmp(argc[1], "--help") == 0) {
           printf("This program will run on its own, attempting to maintain a state of good moisture and temperature.\n"
			"To directly influence the program, testing its ability to adapt, the following keys can be hit.\n"
			"q : quit the program\n"
			"d : set the program to day\n"
			"n : set the program to night\n"
			"w : set the moisture to 20 \n"
			"h : set the temperature to 100\n"
			"c : set the temperature to 20\n ");
        }
        return 0;
    }

    // Times
    saved_time = g_time;
    saved_2time = g_time;
    saved_3time = g_time;

    uint64_t last_run = 0;
    uint64_t interval = 50;

	init_fsm();

    // While loop for the FSM state control.
    while (1) {

        uint64_t now = get_time_ms();               // CODE NEEDED TO BE SLOWED DOWN
            if (now - last_run >= interval) {       // Was running so fast it would cause the program to be unable to continue
                last_run = now;                     // Now will run whenever the time since last run is greater than the interval.

	        int key = getch();
	        hourCycle = g_time - saved_time;
	        moistureDecay = g_time - saved_2time;
	        tempDecay = g_time - saved_3time;
	        g_time = time(NULL);

	        dayTrack();
	        dryTrack();
	        tempTrack();

	        if (key == 'w') {
	            moisture = 20; 
	        }
			if (key == 'c') {
				temperature = 20;
			}
	        if (key == 'h') {
	        	temperature = 100;
	        }
	        if (key == 'd') {
	            day = 1;
	            night = 0;
	        }
	        if (key == 'n') {
	            day = 0;
	            night = 1;
	        }
	        if (key == 'q') {
	            next_state = EXIT;
	        }

			printw("Temp : %d  |   Moisture : %d  |  Day = %d  |   Night = %d         ", temperature, moisture, day, night);

	        current_state = next_state;
	        switch (current_state) {
	            case MONITOR:
	                if (moisture < 40) {
	                    printw("REQUIRE WATER -> ACTIVATE SPRINKLERS\n");
	                    next_state = WATER;
	                }
	                else if (temperature < 50 && night) {
	                    printw("COLD NIGHTTIME -> ACTIVATE HEATERS\n");
	                    next_state = HEAT;
	                }
	                else if (temperature < 60 && day) {
	                    printw("COLD DAYTIME -> ACTIVATE HEATERS\n");
	                    next_state = HEAT;
	                }
	                else if (temperature > 70 && night) {
	                    printw("HOT NIGHTTIME -> ACTIVATE A/C\n");
	                    next_state = COOL;
	                } 
	                else if (temperature > 80 && day) {
	                    printw("HOT DAYTIME -> ACTIVATE A/C\n");
	                    next_state = COOL;
	                }
	                else {
	                    printw("ACTIVELY MONITORING -> ALL GOOD\n");
	                    next_state = MONITOR; 
	                }
	                break;

	            case HEAT:
	                heatersOn();
	                if (moisture < 40) {
	                    printw("REQUIRE WATER -> ACTIVATE SPRINKLERS\n");
	                    next_state = WATER;
	                }
	                else if (temperature > 60 && night) {
	                    printw("ACTIVELY MONITORING -> ALL GOOD\n");
	                    next_state = MONITOR;
	                } 
	                else if (temperature > 70 && day) {
	                    printw("ACTIVELY MONITORING -> ALL GOOD\n");
	                    next_state = MONITOR;
	                }
	                else if (day) {
	                	printw("COLD DAYTIME -> ACTIVATE HEATERS\n");
	                	next_state = HEAT;
	                } 
	                else {
	                    printw("COLD NIGHTTIME -> ACTIVATE HEATERS\n");
	                    next_state = HEAT; 
	                }
	                break;

	            case COOL:
	                coolingOn();
	                if (moisture < 40) {
	                    printw("REQUIRE WATER -> ACTIVATE SPRINKLERS\n");
	                    next_state = WATER;
	                }
	                else if (temperature < 60 && night) {
	                    printw("ACTIVELY MONITORING -> ALL GOOD\n");
	                    next_state = MONITOR;
	                } 
	                else if (temperature < 70 && day) {
	                    printw("ACTIVELY MONITORING -> ALL GOOD\n");
	                    next_state = MONITOR;
	                }
	                else if (day){
	                    printw("HOT DAYTIME -> ACTIVATE A/C\n");
	                    next_state = COOL; 
	                }
	                else {
	                	printw("HOT NIGHTTIME -> ACTIVATE A/C\n");
	                	next_state = COOL;
	                }
	                break;

	            case WATER:
	                hydrate();
	                if (moisture > 90) {
	                	printw("ACTIVELY MONITORING -> ALL GOOD\n");
	                	next_state = MONITOR;
	                }
	                else {
	                    printw("REQUIRE WATER -> ACTIVATE SPRINKLERS\n");
	                    next_state = WATER;
	                }
	                break;
	                
	            case EXIT:
	                endwin();
	                return 0;
	                break;
	                }
		}
    }
}
