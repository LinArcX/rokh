# why creating new gui widgets
- for satisfying the curiousity :)
- need for changel always stay in your development lifecycle.
- for special use cases like embeded programming, we need a more strim altrenative.

# Prerequisites
## optional
- os: void linux
- editor: nvim
- file manager: lf
- windows manager: dwm
- c compiler: gcc (or clang, MSVC for windows)
- debugger: seergdb (or gdb, visualSutdio debugger for windows)

## mandatory
- git
- fzf
- SDL2_ttf-devel
- SDL-devel

## How graphics works?
- at the lowest level, you can send bytes directly to your graphihc card(0x88884423), if you os suppport this :)
  cons: your os should support this.
- in linux, we have technology called: framebuffer that is supported by kernel.
  cons: this works only on linux.
- opengl(partially cross-platform), vulkan(cross-platform), metal(IOS, macOs), direct3dx(windows), ... --> unified interface.
  it's just for graphics. nothing more.
  for example: rectangle, line, ..
- SDL --> we are using this option.
  for graphics, you can use it for audio management, controller(joystick) management, font management, and other stuff.
