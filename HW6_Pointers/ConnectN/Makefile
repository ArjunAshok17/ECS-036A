connectn.out: connectn.o matrix_manipulation.o user_input.o
	gcc -g -Wall -Werror -o connectn.out connectn.o matrix_manipulation.o user_input.o

connectn.o: connectn.c
	gcc -g -Wall -Werror -c connectn.c

matrix_manipulation.o: matrix_manipulation.c matrix_manipulation.h
	gcc -g -Wall -Werror -c matrix_manipulation.c

user_input.o: user_input.c user_input.h
	gcc -g -Wall -Werror -c user_input.c

clean:
	rm -fr *.o *.out