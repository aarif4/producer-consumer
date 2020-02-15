///
/// @file queue.hpp
/// @author aarif
///

#ifndef __queue_h__
#define __queue_h__

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <mutex>

#include "semaphore.hpp"

#define DEBUG false

/// @brief this class that defines a resource (FIFO queue) that's 
/// shared by several Producer&Consumer objects
/// @author aarif
class Queue
{
    private:
        uint32_t MAX_SIZE;
        std::mutex access_buffer;
        Semaphore* empty_count;
        Semaphore* fill_count;
        std::vector<std::string> buffer;

    public:
        Queue(uint32_t queue_max_size);
        ~Queue();
        void pushMsg(std::string msg);
        std::string pullMsg();
};

#endif
