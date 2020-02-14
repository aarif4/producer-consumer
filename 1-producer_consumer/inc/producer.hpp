///
/// @file producer.hpp
/// @author aarif
///

#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include <cstring>

/// @brief this is the Producer class that can add data to a shared queue
/// this class gets direction to the semaphore it's supposed to check to see if
/// the queue is available to be written to. Once it is available, the object
/// writes a message to the queue (assuming that the queue isn't full)
class Producer
{
    private:
        int public_val;

    public:
        Producer();
        ~Producer();
        void set_public_val(int num);
        int get_public_val();
};
