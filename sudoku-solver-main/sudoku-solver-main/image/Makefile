# Makefile

CC= gcc
CPPFLAGS=
CFLAGS= -Wall -g -Wextra -O3 `pkg-config --cflags sdl2 SDL2_image`
LDFLAGS=
LDLIBS= `pkg-config --libs sdl2 SDL2_image`
LDLIBS += -lm


OBJ= main.o
DEP= ${OBJ:.o=.o}

all: main

main: ${OBJ}

clean:
	${RM} ${OBJ} ${DEP} main output.png
