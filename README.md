# towerofthedead
### Nice name: Tower of the Dead

# Well, what is it?
Tower of the Dead is actually mostly a game engine I created called dragoness. It is interfaced directly with C functions. The engine itself isn't fully featured... Not even close. Support for custom models... There is no support, nor textures. Movement is possible via WASD keys, shift, space, and left ctrl. To exit, esc is used. The project hasn't seen much attention as of late besides me adding an autobuild system, Windows amd64 support, and adding the git repo.

# How to build
I will no longer offer out of the box configure scripts after the disaster that was xz and I might even switch to cmake in the future. So what needs to be done:
```Bash
aclocal
autoconf
automake --add-missing
```
This will create all the files necessary to configure the project. In order to build on linux for linux, you will need OpenGL, GLEW, GLFW, and CGLM. To build for Windows but building on Linux, you need the headers but don't need to provide any DLLs as the project handles that for you unless you are compiling for x86 Windows. As for building on Windows, that isn't supported yet but the builds do work on Windows. For now, Windows will complain that the software is potentially unsafe. There is an option to trust to application when you click settings when right clicking the exe. 

### To build on Linux
```Bash
./configure && make && make install
# To change default install prefix from /usr/local
./configure --prefix=[yourprefixhere]
```
### To build on Linux for Windows
```Bash
./configure --host=[architecture(either x86_64 or i686)]-w64-mingw32 && make && make install
# To change default install prefix from /usr/local
./configure --prefix=[yourprefixhere] --host=[architecture(either x86_64 or i686)]-w64-mingw32
# Making a DESTDIR install is recommended as all necessary DLLs will be installed in same dir
make DESTDIR=$PWD/[yourchosendirname] install
```
