# Simple CMake Project

## Overview
This project is pretty simple. I made a class called `simple_library` and stored its .hpp and .cpp files in `inc/` and `src/`, respectively. Next, I made a `main.cpp` that used this library.

## Project Structure
These are the reasons why the filesystem is like so:
* inc --- folder to hold the projects header files (.hpp)
* src --- folder to hold the projects source files (.cpp)
* libs --- folder to hold external libraries that we need to use in this project, if applicable
* tests --- folder to hold unit testing modules
* spike --- folder to hold temporary small-scale tests 

## Requirements
This was done on Ubuntu 18.04 VM, but this will probably work on Ubuntu 14.04+. Here are the dependencies needed in order to build this project:

```
sudo apt-get install build-essential g++ cmake
```

## How To Build

Just perform the following commands to build the project:
```
cd 0-simple_cmake_project
mkdir build
cd build
cmake ..
make
```
## How To Run

To run the project, execute the `main` executable in your `build/bin/` folder:

```
cd 0-simple_cmake_project/build/bin
./main
```

You should see this output when you run that executable:
```
main: starting application
main: instantiating simple_library object
main: setting public_val to 5
main: setting private_val to 15
main: going to display content of simple_library object:
        name       : dumb_name
        public_val : 5
        private_val: 15

main: stopping application
```
