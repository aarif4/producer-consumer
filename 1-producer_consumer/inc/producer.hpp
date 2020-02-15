///
/// @file producer.hpp
/// @author aarif
///

#ifndef __producer_h__
#define __producer_h__

#include<stdio.h>
#include<iostream>
#include<string>
#include "queue.hpp"

#define DEBUG true

/// @brief this is the Producer class that adds messages to a shared FIFO Queue until it's full. In that situation, the Producer hangs until the Queue has an available slot to store a new message
class Producer
{
    private:
        std::string id;
        Queue* queue;
        double sleep_dur_sec;
    public:
        Producer(std::string id, Queue * queue, double sleep_sec);
        ~Producer();
        void run();
};

#endif
