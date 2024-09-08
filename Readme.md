# Learning C++ Programming through Raylib
This respository is intended to help teach students how to program using C++ while still making an interactive game built on the Raylib C library.

At this stage in development, students should really be focusing on getting code up and running and should not be 
bogged down in details about setting up the environment. As such, this CMake project was built using Visual Studio 
2022 and should work "out of the box." Behind the scenes, vcpkg is used to load an appropriate version of all 
dependencies including raylib, libxml, tmx, and fmt.

Included in this project is a custom `Toolkit` library that aims to reduce the complexity of making games while 
learning C++. `Toolkit` serves a couple of purposes. First, Raylib itself is a C Library. We largely want our students 
focusing on an Object Oriented Style of programming. `Toolkit` allows us to abstract some of the Raylib library into 
an OOP Paradigm. Second, there is a ton of complexity that goes into making some reusable components. We can't and 
don't want to throw everything at students all at once, so `Toolkit` makes it easier to build some components for 
them while still giving them the freedom to make their own games. Elements like a Dialog box and Map loading support are among the components that `Toolkit` will be used for.

## Setup

### Prerequisites
Students will need:
- git
- cmake (3.15+)
- Visual Studio 2022

Follow these steps to setup a project
1. Clone this repository
2. Initialize git submodules (Necessary for dependencies)

    `git submodule update --init --recursive`
3. Open the CMakeLists.txt file from within Visual Studio

## Notes
When this is presented to students, we will want them to fork this repository. That will allow them to clone their own 
copy, make changes, and keep their own revision control stored on GitHub. Additionally, this will allow the 
maintainers (i.e. @arch1t3ct) to make updates to the teaching library that students can then bring into their own 
forks from the upstream

### Dependencies
#### Raylib
Core library providing the necessary elements to making a game including Graphics, Audio, and Input.

#### Tiled Map support (tmx, libxml2)
Allows us to load a 2D tilemap created in Tiled.

#### fmt
Useful for formatting text output rather than using streams
Mostly used for library development. Students should familiarize themselves with traditional streams first before 
using this