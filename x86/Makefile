CFLAGS = -I.. -I.
VPATH += ..

shelly: shelly.o shelly_extra.o main.o
	gcc $(CFLAGS) -o $@ $^

shelly-strict.o: shelly.c
	gcc $(CFLAGS) -c -Dstrict $^ -o $@

shelly-strict: shelly-strict.o main.o
	gcc $(CFLAGS) -o $@ $^

clean: 
	-rm *.o
	-rm *.lst
