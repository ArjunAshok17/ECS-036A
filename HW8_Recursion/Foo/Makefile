foo.out: foo.o
	gcc -g -Wall -Werror -o foo.out foo.o

foo.o: foo.c
	gcc -g -Wall -Werror -c foo.c

clean:
	rm -fr *.o *.out