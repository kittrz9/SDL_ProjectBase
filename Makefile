CC = gcc
SHELL = /bin/bash
LIBS = -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image -lm
CFLAGS = -Wall -Wpedantic -Wextra -O2
INCLUDE = -Isrc/game -Isrc/game/gameStates -Isrc/engine
NAME = SDL-thing
SOURCES = ${wildcard src/game/*.c} ${wildcard src/engine/*.c} ${wildcard src/game/gameStates/*.c}
OBJS = ${subst src/, obj/, ${subst .c,.o,${SOURCES}}}

# creates the main executable
${NAME}: obj-dir ${OBJS}
	${CC} ${CFLAGS} ${INCLUDE} ${LIBS} -o $@ ${OBJS}

# creates an executable with debug symbols and stuff
debug: ${SOURCES}
	$(CC) $(CFLAGS) $(INCLUDE) -g $(SOURCES) $(LDFLAGS) -o ${NAME}-debug $(LIBS)

# why the fuck does cross compiling have to be such a nightmare lmao this doesn't even fully work
windows: ${SOURCES}
	i686-w64-mingw32-gcc $(CFLAGS) $(INCLUDE) -g $(SOURCES) $(LDFLAGS) -o ${NAME}-windows.exe -lmingw32 $(LIBS)

all: ${NAME} debug

clean:
	-rm -rf obj
	-rm ./${NAME}*

# creates the directory for all the object files
obj-dir:
	mkdir -p obj/game/gameStates obj/engine

# rule to make object files
# https://stackoverflow.com/questions/14639794/getting-make-to-create-object-files-in-a-specific-directory
${OBJS}: obj/%.o : src/%.c
	${CC} ${CFLAGS} ${INCLUDE} -c src/$*.c -o obj/$*.o
