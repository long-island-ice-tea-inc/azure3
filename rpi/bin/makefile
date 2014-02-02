clean:
	rm -f test;

compile: clean
	gcc -Wall -o test -I ../src ../src/tlc5940.c ../src/cube.c test.c -lwiringPi 
#	gcc -Wall -o test -I ./azure3/rpi/src  test.c -lwiringPi 

run: compile
	sudo ./test
