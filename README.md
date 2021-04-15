# SDL Project Base
A really basic SDL thing to just kinda make more stuff off of.

Pretty much the same thing as the CSFML project base but in SDL (This time mainly to learn SDL)<br>

---

## Basic structure
The `engine` directory in the `src` directory is where all of the main non-game related source files that don't really need to be edited for games are, and the `game` directory is where the game related source files are.<br>

### src/engine/ directory
Entities (defined in `entity.h` and `entity.c`) are things that will be drawn and/or updated every game loop. You can set the functions to be called for drawing and updating. There is an entityNOP function that does nothing that can be used for if your entity doesn't need to be updated/drawn (Like maybe a box that checks whether a player is inside a box or something idk) but gives compiler warnings when used due to the function parameters not being the same as the draw and update functions. (Should probably be fixed but idk how without just having 2 seperate functions lmao)<br>

`audio.c` and `audio.h` has an audio synthesizer. `audio.h` shows how to use the synthesizer, idk how to actually like explain how it works lmao.<br>

`text.c` and `text.h` is where text rendering is implemeneted.<br>

`types.h` has really basic types defined that can be useful like `vec2f`. It also has `UNUSED` defined but is used to tell the compiler when a variable isn't used. Should probably move it to a seperate file or something.<br>

`main.c` is just the main function, pretty much just SDL initialization stuff and calling the game loop function, not really much reason to change it when just making games.<br>

`defines.h` is where defines that can be used in other files are.<br>

### src/game/ directory
`gameLoop.c` is where the while loop that always runs while the game is running. Probably should be renamed since the <br>

The `gameStates` directory is where source files with functions that will be called every game loop. The game states will need to be included in the `gameStates.h` file to be used. (Should probably be changed somehow to be a bit easier to use)<br>

`controls.h` and `controls.c` are where the controls used in game are defined (in `controls.h`) and initialized (in `contorls.c`).

`player.c` and `player.h` are just example source files for a simple entity to show how entities work.

### res/ directory
the `res` directory is just where resources used in game are (Like images and stuff). It just has the Terminus TTF font (https://files.ax86.net/terminus-ttf/) for now.

---

## Compiling
I think the only thing you really need is SDL2 and other SDL2 libraries like SDL_ttf and SDL_mixer to compile it, which you should be able to get just from whatever package manager you're using on linux. If you're on windows it's probably on the libsdl.org site but idk<br>
It should work by just doing `make` in the command line since it's not a really complex project lmao<br>
`make debug` includes debug stuff for stuff like gdb<br>

---

## Todo:

`Add music playing`<br>
`Better synthesizer`<br>
`Sequencer and file format or whatever to play music with the synthesizer`<br>
`Optimize text rendering`<br>
`Move UNUSED define to a different file`<br>
`Fix entityNOP compiler errors when actually used`<br>
`Make the makefile not garbage`<br>
`Move stuff like headers into an include directory`<br>
`Add a config file thing (Probably with like XML or something)`<br>
`Multithreading?`<br>
`More types in types.h`<br>
`Maybe start using CMake?`<br>
`Controller support`<br>
`Animation system or something`<br>
`Maybe just move to just regular OpenGL lmao`<br>
