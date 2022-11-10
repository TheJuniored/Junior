# Makefile

CC = gcc
CPPFLAGS =
CFLAGS = -Wall -Wextra
LDFLAGS =
LDLIBS = -lm

SRC = main.c xor.c learn.c save.c vector.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

main: ${OBJ}

-include ${DEP}

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} main

# END

