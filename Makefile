shelly: shelly.o main.o
	gcc -o $@ $^

clean: 
	-rm *.o
	-rm *.lst
