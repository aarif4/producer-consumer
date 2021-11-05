///
/// @file consumer.hpp
/// @author aarif
///

#ifndef __consumer_h__
#define __consumer_h__

#include<stdio.h>
#include<iostream>
#include<string>
#include "queue.hpp"

/// @brief this is the Producer class that adds messages to a shared FIFO Queue until it's full. In that situation, the Producer hangs until the Queue has an available slot to store a new message
class Consumer
{
    private:
        std::string id;
        Queue* queue;
        double sleep_dur_sec;
        std::string last_msg;
        bool verbose;
    public:
        Consumer(std::string id, Queue * queue, double sleep_sec, bool verbose);
        ~Consumer();
        void run(int iterations);
        std::string get_last_msg();
};

#endif
