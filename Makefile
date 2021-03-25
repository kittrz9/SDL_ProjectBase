CC = gcc
SHELL = /bin/bash
LIBS = -lSDL2 -lSDLmain -lSDL2_ttf
CFLAGS = -Wall -Wpedantic -Wextra -O2 
NAME = SDL-thing
SOURCES = ${wildcard src/*.c} ${wildcard src/gameStates/*.c}
OBJS = ${subst src/, obj/, ${subst .c,.o,${SOURCES}}}

${NAME}: ${SOURCES} ${OBJS}
	# This is probably a very stupid way to get this to work
	-rm ${subst src/,obj/,${subst .c,.o,$?}}
	make ${subst src/,obj/,${subst .c,.o,$?}}
	${CC} ${CFLAGS} ${LIBS} -o $@ ${OBJS}

debug: ${SOURCES}
	$(CC) $(CFLAGS) -g $(SOURCES) $(LDFLAGS) -o ${NAME}-debug $(LIBS)

all: ${NAME} debug

clean:
	-rm obj/*.o obj/gameStates/*.o
	-rm ./${NAME}*

%.o:
	# Probably not good to constantly try to create the folders for the object files 
	# Probably should just add those folders to the repository
	mkdir -p obj/gameStates
	${CC} ${CFLAGS} ${LIBS} -c ${subst obj/,src/,$*.c} -o ${subst src/,obj/,$*.o}
