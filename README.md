<h1 align="center">
    <img src="assets/cave.jpg" align="center" width="700" height="350"/>
    <br/>
    <h4 align="center">Is it hard to make your own GUI? why nobody talks about it anymore?! <a href="https://en.wikipedia.org/wiki/Allegory_of_the_cave">[more]</a></h4>
</h1>

# Cave
A gui library based on C, SDL2 and Plato Ideas!

# Prerequisites
## libs
- SDL2_ttf-devel
- SDL-devel

## tools
- git
- gcc(or clang)
- gdb(or seergdb)
- fzf

# Build/Run/Clean
## Linux
First source **project.sh** file:
`. project.sh`

And then call `p`(it's a bash function).

Now you can see a list of commands, like:
- run
- clean
- debug
- generate tags
- valgrind
- find strings in the binary
- list symbols from object files

# Architecture
There are two main directories:
- lib
  - In this directory, you can find graphical widgets(https://en.wikipedia.org/wiki/Graphical_widget).
  - there is a special widget that acts as a main container and it's **app.c**. this file contains 3 important functions:
    - `initialize()`: All initializations happen here.
    - `render()`: The main loop of the program when all top-level events come here. and then we use function pointers to dispatch them to a local widget.
      Actually, events do not process here. if you look carefully, for each event we call a function: `callFunctions()` and we pass it as a __Node*__. actually, we delegate event handling to every widget.
    - `cleanup()`: Free all the resource allocated for the application(including dynamically allocated memories, SDL specific memories, etc..)
  - If you need some widgets that do not exist, feel free to raise an issue.
- example
  - **main.c**: the `main()` function resides here. it just calls other functions from `app.c`. also it pass __initWidgets()__ function to **app.c**.
    if you add any new widget in your application, you should put it's init() function here.
  - sample widgets: there are some widgets like __btnTest__, __lblTest__, __txtInputTest__, etc..
    you can see how they are implemented if you need ideas about widget creation.

## How to use Cave in my own project?
1. put **lib/** directory in your project.
2. start designing your scene by creating different widgets. you should follow some rules:
  2.1. for every widget that you create, you should provide an init() function for it in its header file.(look at `txtInputTest.h`)
  2.2. in the equivalent `.c` file, you should implement that init function.
    2.2.1. inside this function, you should set the properties of each widget.(most Cave widgets have a structure that you need to initialize)
    2.2.2. you should register callback functions to handle events.(look at `txtInputTest.c`, if you need some ideas)
3. finally, call your init function in `initWidgets()` that you can find it in **main.c**.

# Why Cave?
Plato has an allegory called: [Allegory of the cave](https://en.wikipedia.org/wiki/Allegory_of_the_cave). In there, he's talking about people who in their whole life, they watched the projection of the reality
and they didn't try to believe that maybe reality is something else.

Once some of them escaped their calm life and start exploring, they realize that reality is totally different from their perception. Finally, they came back to the cave, but no one believed them...

I think the same scenario happened in our computer world. No one wants to know about underlying stuff anymore. They think all the **buttons** should come from HTML world or C# window forms!
They don't even bother themselves to search, explore or even try to make something from scratch.

I created the Cave:
1. to satisfy my curiosity and make my knowledge deeper in GUI development.
2. encouraging that you can start exploring too.
3. and maybe someone uses CaveGui in his/her own project. who knows? :)

## License
![License](https://img.shields.io/github/license/LinArcX/cave.svg)
