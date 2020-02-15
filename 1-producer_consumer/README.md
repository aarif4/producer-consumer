# Producer-Consumer Problem

## Overview
The **Producer-Consumer Problem** defines the classic concurrency problem of two processes that are attempting to share a fixed-sized buffer/queue. The Producer is a process that generates data and adds it to the queue. On the other hand, the Consumer is a process that removes data from the queue and "consumes" the data. This problem requires that the Producer does not add data when the queue is full nor does the Consumer remove data from the queue when it's empty.

This project attempts to solve this problem by defining a set of classes that mimic the Producer and Consumer behavior. By using semaphores to schedule all queue-related manipulations (i.e. add or remove), we can have multiple Producers and Consumers running and safely adding and removing data from the queue, respectively. The header files for the Producer-Consumer class can be found in `inc/` folder and their source files are located in `src/` folder. Moreover, all test cases are exercised in `tests/` folder.

## Requirements
This project was compiled on an Ubuntu VM, however it should work on all Ubuntu OSes beyond Ubuntu 16.04. In order to properly go through these requirements, it is assumed that you have `sudo` privledges to download and install certain libraries. In this project, we need to configure the system so that our build tool can be used, our unit testing framework can run safely, and API generation can occur at compilation. Here are the dependencies that need to be installed:

### CMake (Build Tool)
In order to use **CMake** to build the project, run the following command in the terminal (assuming you have sudo credentials)
```
sudo apt-get install build-essential g++ cmake
```

### GoogleTest (Unit Testing)
In order to use **GoogleTest** to run the test cases for this project:
1. Run the following command in the terminal:
```
sudo apt-get install googletest
```
2. Compile GoogleTest's static libraries (`.lib`) and place them in the right area:
```
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo cp *.a /usr/lib
```

### Doxygen (Documentation)
Getting **Doxygen** is pretty easy, all you need to is run this command in your terminal and that's it:
```
sudo apt-get install doxygen graphviz
```

## Build Process
Build this project like any other CMake project; make a build folder and run CMake's build commands to build the project. To build this project, perform the following steps in your terminal (assuming you're inside the project):
```
mkdir build
cd build
cmake ..
make
make doc # to generate API
```
That last command `make doc` prompts Doxygen to traverse through this project and stitch together an API based on comments in the source code.

## How To Run
All relevant executables can be found in `build/bin/` folder. The API Documentation generation is located in `build/doc/` folder.

### Running Executable
The main executable demonstrates a solution to this concurrency problem by running one Consumer and one Producer in their own individual threads. As the Producer keeps adding data to the queue, the Consumer handles the messages. To run this executable, do:

```
./build/bin/main
```

You should see the following output:
```
main: starting application
Creating Queue obj
Queue Max Size = 10
In Producer P0's constructor
WEARE STARTING PROD THREAD
in producer P0's run() fcn
in producer P0's while
P0: Putting this msg in queue: 'P0 Msg#0'
P0: Done.
In Consumer C0's constructor
WEARE STARTING CONS THREAD
in consumer C0's run() fcn
in consumer C0's while
C0: Going to get message from queue.
C0: Got this msg from the queue: 'P0 Msg#0'
in producer P0's while
P0: Putting this msg in queue: 'P0 Msg#1'
P0: Done.
in consumer C0's while
C0: Going to get message from queue.
C0: Got this msg from the queue: 'P0 Msg#1'
in producer P0's while
P0: Putting this msg in queue: 'P0 Msg#2'
P0: Done.
in consumer C0's while
C0: Going to get message from queue.
C0: Got this msg from the queue: 'P0 Msg#2'
in producer P0's while
P0: Putting this msg in queue: 'P0 Msg#3'
P0: Done.
in consumer C0's while
C0: Going to get message from queue.
C0: Got this msg from the queue: 'P0 Msg#3'
in producer P0's while
P0: Putting this msg in queue: 'P0 Msg#4'
P0: Done.
in consumer C0's while
C0: Going to get message from queue.
C0: Got this msg from the queue: 'P0 Msg#4'
in producer P0's while
P0: Putting this msg in queue: 'P0 Msg#5'
P0: Done.
in consumer C0's while
C0: Going to get message from queue.
C0: Got this msg from the queue: 'P0 Msg#5'
```

### Running Test Cases
The test cases that are run are the following

==TODO== make a table with the name and what that test case does

```
./build/bin/executeTests
```
You should see the following output:
==TODO==

### View API Documentation
The documentation generated is an HTML file that's located in the following path:
```
build/doc/producer_consumer_problem/html/index.html
```
Open this file in a web browser of your choice.

## Final Thoughts


