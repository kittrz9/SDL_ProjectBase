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

`resourceManager.h` lets you use a resource without constantly loading it into memory. currently only supports loading textures since that's all this kinda example uses, but it is easy to add support for other resource types.

`main.c` is just the main function, pretty much just SDL initialization stuff and calling the game loop function, not really much reason to change it when just making games.<br>

`renderer.h` has the pointers to the current SDL_Renderer and SDL_Window. This should be included when drawing to the screen.

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

To compile for windows from linux you need to install mingw (most linux package managers have it I think), get all of the SDL libraries linked below, install them and put all the dlls needed for them to work in the directory the executable will be in (I should probably start using a build directory at this point lmao) and run `make windows`. I've gotten it to work running through Wine but the framerate seeems pretty much halved and idk if that's because of running it through Wine or if I'm just compiling it wrong or something. I have not tested this on actual Windows or even through a VM or anything yet, but I'm assuming it will work.<br>

links to all the SDL libraries:<br>
https://www.libsdl.org/download-2.0.php <br>
https://www.libsdl.org/projects/SDL_image/ <br>
https://www.libsdl.org/projects/SDL_ttf/ <br>
https://www.libsdl.org/projects/SDL_mixer/ <br>

---

## Todo:

`make stuff not as dependant on SDL in case I want to be able to use other graphics libraries or port to other platforms that don't have SDL2`<br>
`Add music playing`<br>
`Better synthesizer`<br>
`ciumgui integration (https://github.com/cimgui/cimgui)`<br>
`Sequencer and file format or whatever to play music with the synthesizer`<br>
`Optimize text rendering`<br>
`change the name to something better`<br>
`Fix entityNOP compiler errors when actually used`<br>
`Add a config file thing (Probably with like XML or something)`<br>
`Multithreading?`<br>
`maybe be able to build for the web with emscriptem lmao`<br>
`More types in types.h`<br>
`Maybe start using CMake?`<br>
`Controller support`<br>
`Maybe just move to just regular OpenGL lmao`<br>
