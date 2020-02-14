///
/// @file producer.hpp
/// @author aarif
///

#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include <cstring>

/// @brief this is the Consumer class that can get data from a shared queue
/// this class gets direction to the semaphore it's supposed to check to see if
/// the queue is available to be read from. Once it is available, the object
/// reads a message from the queue (assuming that the queue isn't empty)
class Consumer
{
    private:
        int public_val;

    public:
        Consumer();
        ~Consumer();
        void set_public_val(int num);
        int get_public_val();
};
