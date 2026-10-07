TAGS = -DDAY_LENGTH=$(day_length) -DDRYOUT_TIME=$(dryout_time) -DTEMP_TIME=$(temp_time)
day_length = 100
dryout_time = 1
temp_time = 2

fsm: main.c greenhouse.c greenhouse.h
	gcc $(TAGS) main.c greenhouse.c -lncurses -o fsm 

clean:
	rm fsm
