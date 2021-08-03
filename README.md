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

`types.h` has really basic types defined that can be useful like `vec2f`.<br>

`animation.h` has stuff for really basic animation using texture rects<br>

`main.c` is just the main function, pretty much just SDL initialization stuff and calling the game loop function, not really much reason to change it when just making games.<br>

`defines.h` is where defines that can be used in other files are.<br>

### src/game/ directory
`gameLoop.c` is where the while loop that always runs while the game is running. Probably should be renamed since the game state thing handles game loops instead of this, while this handles actually calling the function for the game state.<br>

The `gameStates` directory is where source files with functions that will be called every game loop will be. The game states will need to be included in the `gameStates.h` file to be used. (Should probably be changed somehow to be a bit easier to use)<br>

`controls.h` and `controls.c` are where the controls used in game are defined (in `controls.h`) and initialized (in `contorls.c`).

`player.c` and `player.h` are just example source files for a simple entity to show how entities work. should probably eventually move entities into their own directory like how the game states are.

### res/ directory
the `res` directory is just where resources used in game are (Like images and stuff). It just has the Terminus TTF font (https://files.ax86.net/terminus-ttf/) and a placeholder graphic to test texture rect animations for now.

---

## Compiling
I think the only thing you really need is SDL2 and other SDL2 libraries like SDL_ttf and SDL_mixer to compile it, which you should be able to get just from whatever package manager you're using on linux. If you're on windows it's probably on the libsdl.org site but idk<br>
It should work by just doing `make` in the command line since it's not a really complex project lmao<br>
`make debug` includes debug stuff for stuff like gdb<br>

There is kinda linux to windows cross compiling but it's not 100% working right now I think (I tried testing it with wine and the synth doesn't seem to work properly, it's like slowed down a ton. also the framerate was like halved but idk if that's because of how it was compiled or because of running it through wine) but it's there. To compile to windows you'll need to install mingw, find all the weird files and move them to your lib and include directories for mingw, and then find all the dlls you need for those to work, move all those dlls into wherever the exe is being build (should probably have a build directory at this point lmao), compile with `make windows` and MAYBE it will work. I cannot guarentee it. Getting it to compile felt like a nightmare.<br>

links to all the SDL libraries:<br>
https://www.libsdl.org/download-2.0.php <br>
https://www.libsdl.org/projects/SDL_image/ <br>
https://www.libsdl.org/projects/SDL_ttf/ <br>
https://www.libsdl.org/projects/SDL_mixer/ <br>

---

## Todo:

`fix Linux to Windows cross compiling`<br>
`Add music playing`<br>
`Better synthesizer`<br>
`ciumgui integration (https://github.com/cimgui/cimgui)`<br>
`Sequencer and file format or whatever to play music with the synthesizer`<br>
`Optimize text rendering`<br>
`Fix entityNOP compiler errors when actually used`<br>
`Make the makefile not garbage`<br>
`Add a config file thing (Probably with like XML or something)`<br>
`Multithreading?`<br>
`maybe be able to build for the web with emscriptem lmao`<br>
`More types in types.h`<br>
`Maybe start using CMake?`<br>
`Controller support`<br>
`Maybe just move to just regular OpenGL lmao`<br>
