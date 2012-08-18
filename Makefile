shelly: shelly.o shelly_extra.o main.o
	gcc -o $@ $^

shelly-strict.o: shelly.c
	gcc -c -Dstrict $^ -o $@

shelly-strict: shelly-strict.o main.o
	gcc -o $@ $^

clean: 
	-rm *.o
	-rm *.lst
