# towerofthedead
### Nice name: Tower of the Dead

# Well, what is it?
Tower of the Dead is actually mostly a game engine I created called dragoness. It is interfaced directly with C functions. The engine itself isn't fully featured... Not even close. Support for custom models... There is no support, nor textures. Movement is possible via WASD keys, shift, space, and left ctrl. To exit, esc is used.

# How to build
I now have incorporated CMake for this project and removed it from autoconf and automake in an effort to make things more simple and less obfuscated. In order to build on linux for linux, you will need OpenGL, GLEW, GLFW, and CGLM. To build for Windows but building on Linux, you need the headers but don't need to provide any DLLs as the project handles that for you unless you are compiling for x86 Windows. As for building on Windows, that isn't supported yet but the builds do work on Windows. For now, Windows will complain that the software is potentially unsafe. There is an option to trust to application when you click settings when right clicking the exe. 

### To build on Linux
```Bash
# Please run in the top directory
cmake . && make && make install
# To change the default prefix from /usr/local to whatever of your choosing:
cmake -DCMAKE_INSTALL_PREFIX=[prefix]
```
### To build on Linux for Windows
```Bash
cmake . -DCMAKE_TOOLCHAIN_FILE=w[32 or 64, only 64 is supported] && make && make install
# To change the default prefix from /usr/local to whatever of your choosing:
cmake -DCMAKE_INSTALL_PREFIX=[prefix] -DCMAKE_TOOLCHAIN_FILE=w64
# Making a DESTDIR install is recommended as all necessary DLLs will be installed in same dir
make DESTDIR=$PWD/[dirname] install
```
