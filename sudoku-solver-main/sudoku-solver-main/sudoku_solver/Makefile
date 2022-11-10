
CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3


SRC = main.c filetab.c already.c is_solved.c solve.c
OBJ = ${SRC:.c=.o}

solver: ${OBJ}
	$(CC) -o solver ${OBJ} $(LDFLAGS)
clean:
	${RM} ${OBJ}   # remove object files
	${RM} solver     # remove main program
	${RM} *.result

#END