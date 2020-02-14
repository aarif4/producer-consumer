# Simple CMake Project

## Overview
This project is pretty simple. I made a class called `simple_library` and stored its .hpp and .cpp files in `inc/` and `src/`, respectively. Next, I made a `main.cpp` that used this library.

## Project Structure
These are the reasons why the filesystem is like so:
* doc --- folder to hold configuration for how/where to get documentation info
* inc --- folder to hold the projects header files (.hpp)
* src --- folder to hold the projects source files (.cpp)
* libs --- folder to hold external libraries that we need to use in this project, if applicable
* tests --- folder to hold unit testing modules
* spike --- folder to hold temporary small-scale tests 

## Requirements
This was done on Ubuntu 18.04 VM, but this will probably work on Ubuntu 14.04+. Here are the dependencies needed in order to build this project:

```
sudo apt-get install build-essential g++ cmake doxygen
```
### How to install GoogleTest
1. download these dependencies:
```
sudo apt-get install libgtest-dev googletest
```
2. Compile GTest's static libraries (`.lib`) and put it in the right area:
```
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo cp *.a /usr/lib
```
That's it. You now have GoogleTest
## How To Build
### Build Tests and Binaries
Just perform the following commands to build the project:
```
cd 0-simple_cmake_project
mkdir build
cd build
cmake ..
make
```

### Build Documentation
Just perform the following commands to build the documentation (I've already littered this repo with doc strings)
```
cd build
make doc
```
The documentation can be found in `build/doc/simple_project/html/index.html`. Open that.
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
