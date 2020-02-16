# Producer-Consumer Problem

## Overview
The **Producer-Consumer Problem** defines the classic concurrency problem of two processes that are attempting to share a fixed-sized buffer/queue. The Producer is a process that generates data and adds it to the queue. On the other hand, the Consumer is a process that removes data from the queue and "consumes" the data. This problem requires that the Producer does not add data when the queue is full nor does the Consumer remove data from the queue when it's empty.

This project attempts to solve this problem by defining a set of classes that mimic the producer (Producer) and consumer (Consumer) behavior as well as a single class that keeps track of all of the important semaphores needed to both push and pop messages to and from the queue safely (Queue). So, the shared resource is a **Queue object** and the `main()` function spins several threads that initalize a single **Producer object** or **Consumer object**. Every Producer/Consumer object is given a reference to the original Queue object we've initialized in `main()` function. The Queue object's buffer is modeled as a vector of strings and the messages that Producers/Consumers send/receive are strings as well.

As a result, these Producer/Consumer threads are continually request to push/pull messages to/from the shared Queue object while they run in their own while loops. If Producer objects have messages to push to the Queue object and the Queue object has available space in its buffer, the Queue object allows this action to happen safely. If Consumer objects requests to pull messages from the Queue object and the Queue object has messages in its buffer, then the Queue object allows this action to occur safely. However, if the Queue object's buffer is empty and say a Consumer object requests to pull a message from it, then the Queue object blocks that thread because it wants to wait until it has a message to give that Consumer object. Similarly, if the Queue object's buffer is full and a Producer object requests to push a message to the Queue object's buffer, the Queue object will block until a Consumer object has freed a slot in the Queue object's buffer. This behavior is desired and solves the Producer-Consumer problem outlined above; By using semaphores to schedule all queue-related manipulations (i.e. add or remove), we can have multiple Producers and multiple Consumers running and safely adding and removing data from the queue, respectively.

This project relied heavily on standard libraries like `<thread>`, `<vector>`, and `<mutex>`. Since I couldn't find a semaphore library in the standard library, I made one. CMake was used to build this project and Doxygen comments are all over the source code. More importantly, GoogleTest has been used to test certain features of this problem. The header files for this project can be found in `inc/` folder and their source files are located in `src/` folder. Moreover, all test cases are exercised in `tests/` folder.

## Requirements

**OS:** Ubuntu 18.04 (Although it should work for 16.04 as well)

In order to properly go through these requirements, it is assumed that you have `sudo` privledges to download and install certain libraries. In this project, we need to configure the system so that not only our build tool can generate the binaries, but also our unit testing framework and API generation can occur safely. 

The following subsections describe the dependencies of this project and how to install them on a Debian system.

### CMake (Build Tool)
In order to use **CMake** to build the project, run the following command in the terminal:
```
sudo apt-get install build-essential g++ cmake
```

### GoogleTest (Unit Testing)
In order to use **GoogleTest** to run the test cases for this project, do the following two steps:
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
Build this project like any other CMake project; make a build folder and run CMake's build commands to build the project. 

Here are the commands you'd run in your terminal to build this project (assuming you're already inside the project's area):
```
mkdir build
cd build
cmake ..
make
make doc # to generate API
```

> **NOTE**: That last command `make doc` prompts Doxygen to *traverse through this project and stitch together an API based on comments in the source code.*

## How To Run
* All relevant executables can be found in `build/bin/` folder in the project area. 
  * The executable to run is called **pushpull** (`build/bin/pushpull`) 
* The API Documentation generation is located in `build/doc/` folder in the project area.
  * More specifically, to see the API, open the following HTML file: `build/doc/producer_consumer_problem/html/index.html`
* The test cases are grouped into a single executable in `build/bin` folder in the project area.
  * The executable to run is called **executeTests** (`build/bin/executeTests`)

### Running Executable
The main executable demonstrates a solution to this concurrency problem by running one Consumer and one Producer in their own individual threads. As the Producer keeps adding data to the queue, the Consumer handles the messages. Nore that the Producer object has an idle period of 1 sec while the Consumer object has an idle period of 5 seconds. To run this executable, run the following command in the terminal whilst being in this project's directory:

```
./build/bin/pushpull
```

You should see the following output (Use Ctrl-C to quit because it'll run indefinitely):
```
==============================================================================================
pushpull: Going to run 1 producer(s) and 1 consumer(s) with a 10-element shared queue.
          Producers and Consumers will sleep for 1sec and 5sec, respectively.
          Producers and Consumers will run indefinitely. Use Ctrl+C to exit this program
          Producers and Consumers will be verbose
==============================================================================================

        Producer 1: Putting this msg in queue:   'Producer 1 Msg#0'
        Consumer 1: Got this msg from the queue: 'Producer 1 Msg#0'
        Producer 1: Putting this msg in queue:   'Producer 1 Msg#1'
        Producer 1: Putting this msg in queue:   'Producer 1 Msg#2'
        Producer 1: Putting this msg in queue:   'Producer 1 Msg#3'
        Producer 1: Putting this msg in queue:   'Producer 1 Msg#4'
        Consumer 1: Got this msg from the queue: 'Producer 1 Msg#1'
        Producer 1: Putting this msg in queue:   'Producer 1 Msg#5'
        Producer 1: Putting this msg in queue:   'Producer 1 Msg#6'
        Producer 1: Putting this msg in queue:   'Producer 1 Msg#7'
        Producer 1: Putting this msg in queue:   'Producer 1 Msg#8'
        Producer 1: Putting this msg in queue:   'Producer 1 Msg#9'
        Consumer 1: Got this msg from the queue: 'Producer 1 Msg#2'
        Producer 1: Putting this msg in queue:   'Producer 1 Msg#10'
        Producer 1: Putting this msg in queue:   'Producer 1 Msg#11'
        Producer 1: Putting this msg in queue:   'Producer 1 Msg#12'
        Consumer 1: Got this msg from the queue: 'Producer 1 Msg#3'
        Producer 1: Putting this msg in queue:   'Producer 1 Msg#13'
^C
```

> **Don't like how "limited" it is? Try this out:**
> ```
> ./build/bin/pushpull --help
> ```
> This program can handle CLI arguments so that users can modify certain parameters so that they can exercise this program in different ways. I've limited the range of acceptable values because bounded values were easier to validate.
> **NOTE:** When using options, DO **NOT** FORGET THE EQUAL SIGN!

### View API Documentation
The documentation generated is an HTML file that's located in the following path:
```
build/doc/producer_consumer_problem/html/index.html
```
Open this file in a web browser of your choice.

### Running Test Cases
The test cases that are run are the following

==TODO== make a table with the name and what that test case does

```
./build/bin/executeTests
```
You should see the following output:
==TODO==



## Final Thoughts

Overall, encapsulating the semaphores required to store and expunge packets of data was the right thing to do because 
it limited the need for Producer and Consumer classes to handle semaphores and mutexes.
