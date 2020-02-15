///
/// @file producer.hpp
/// @author aarif
///

#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include <cstring>
#include <mutex>
#include "semaphore.hpp"

/// @brief this is the Producer class that can add data to a shared queue
/// this class gets direction to the semaphore it's supposed to check to see if
/// the queue is available to be written to. Once it is available, the object
/// writes a message to the queue (assuming that the queue isn't full)
class Producer
{
    private:
        std::string id;
        uint32_t queue_size;
        Semaphore * EmptySlotsInQueue;
        Semaphore * FilledSlotsInQueue;
        std::mutex * QueueAccess;
        std::vector<std::string>* queue;

    public:
        Producer(std::string, std::mutex*, Semaphore*, Semaphore*, std::vector<std::string>*);
        ~Producer();
        void run();
};
