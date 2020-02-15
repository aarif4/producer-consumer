///
/// @file main.cpp
/// @author aarif
///

#include <thread>
#include <iostream>
#include <stdio.h>

#include "producer.hpp"
#include "consumer.hpp"
#include "queue.hpp"

enum QueueHandlerType { PRODUCER, CONSUMER };

void queue_handler(QueueHandlerType type,
                   std::string id,
                   Queue * queue,
                   double sleep_dur_sec);

int main()
{
    fprintf(stderr, "main: starting application\n");

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // MAKE QUEUE
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    uint32_t buffer_size = 10; // queue will be of size 10 msgs
    double sleep_dur_sec = 1;  // 1 second
    size_t num_producers = 1;  // no. of producers to make
    size_t num_consumers = 1;  // no. of consumers to make

    Queue queue(buffer_size);

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // MAKE PRODUCER & CONSUMER THREADS
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    std::vector<std::thread> p_threads(num_producers);
    for (size_t i = 0; i < num_producers; i++)
    {
        std::string id= "P" + std::to_string(i);
        QueueHandlerType type = PRODUCER;

        p_threads[i] = std::thread(
                           queue_handler,
                           type,
                           id,
                           &queue,
                           sleep_dur_sec);
    }

    std::vector<std::thread> c_threads(num_consumers);
    for (size_t i = 0; i < num_consumers; i++)
    {
        std::string id= "C" + std::to_string(i);
        QueueHandlerType type = CONSUMER;

        c_threads[i] = std::thread(
                           queue_handler,
                           type,
                           id,
                           &queue,
                           sleep_dur_sec);
    }


    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // JOIN THREADS AT EXIT
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    for (size_t i=0; i<p_threads.size(); i++)
    {
        p_threads[i].join();
    }
    for (size_t i=0; i<c_threads.size(); i++)
    {
        c_threads[i].join();
    }

    fprintf(stderr, "main: exiting application safely\n");

    return 0;
}


void queue_handler(QueueHandlerType type,
                   std::string id,
                   Queue * queue,
                   double sleep_dur_sec)
{
    switch(type)
    {
        case PRODUCER:
        {
            Producer pobj(id, queue, sleep_dur_sec);
fprintf(stderr,"WEARE STARTING PROD THREAD\n");
            pobj.run();
        }
        break;
        case CONSUMER:
        {
            Consumer cobj(id, queue, 10*sleep_dur_sec);
fprintf(stderr,"WEARE STARTING CONS THREAD\n");
            cobj.run();
        }
        break;
        default:
            std::cerr << "queue_handler: Invalid QueueHandlerType for ID(" 
                      << id << "). Exiting thread" << std::endl;
            return;
    }
}

