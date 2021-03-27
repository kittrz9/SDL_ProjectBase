CC = gcc
SHELL = /bin/bash
LIBS = -lSDL2 -lSDLmain -lSDL2_ttf -lSDL2_mixer
CFLAGS = -Wall -Wpedantic -Wextra -O2 
INCLUDE = -Isrc/game -Isrc/game/gameStates -Isrc/engine
NAME = SDL-thing
SOURCES = ${wildcard src/game/*.c} ${wildcard src/engine/*.c} ${wildcard src/game/gameStates/*.c}
OBJS = ${subst src/, obj/, ${subst .c,.o,${SOURCES}}}

${NAME}: ${SOURCES} ${OBJS}
	# This is probably a very stupid way to get this to work
	-rm ${subst src/,obj/,${subst .c,.o,$?}}
	make ${subst src/,obj/,${subst .c,.o,$?}}
	${CC} ${CFLAGS} ${INCLUDE} ${LIBS} -o $@ ${OBJS}

debug: ${SOURCES}
	$(CC) $(CFLAGS) $(INCLUDE) -g $(SOURCES) $(LDFLAGS) -o ${NAME}-debug $(LIBS)

all: ${NAME} debug

clean:
	-rm -rf obj
	-rm ./${NAME}*

%.o:
	# Probably not good to constantly try to create the folders for the object files 
	# Probably should just add those folders to the repository
	if ! [ -d obj/game/gameStates ] || ! [ -d obj/engine ]; then \
		mkdir -p obj/game/gameStates obj/engine; \
	fi
	${CC} ${CFLAGS} ${LIBS} ${INCLUDE} -c ${subst obj/,src/,$*.c} -o ${subst src/,obj/,$*.o}
