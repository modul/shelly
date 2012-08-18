shelly: shelly.o shelly_extra.o main.o
	gcc -o $@ $^

clean: 
	-rm *.o
	-rm *.lst
