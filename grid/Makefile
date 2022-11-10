# Makefile

CC=gcc
CPPFLAGS=
CFLAGS= -Wall -Wextra -O3 `pkg-config --cflags sdl2 SDL2_image`
LDFLAGS=
LDLIBS= `pkg-config --libs sdl2 SDL2_image`
LDLIBS += -lm

OBJ=  blob.o 
DEP= ${OBJ:.o=.o}

all: blob

blob: ${OBJ}

clean:
	${RM} ${OBJ} ${DEP} blob

