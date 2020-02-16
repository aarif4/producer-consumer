///
/// @file main.cpp
/// @author aarif
///

#include "main.hpp"



int main(int argc, char* argv[])
{
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // INIT CONFIGURATION TO RUN SYSTEM
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // default values
    uint32_t queue_size       = 10; // queue will be of size 10 msgs
    size_t num_producers      = 1;  // no. of producers to make
    double producer_sleep_sec = 1;
    size_t num_consumers      = 1;  // no. of consumers to make
    double consumer_sleep_sec = 5; 
    int iterations            = 0; // 0 means run infinite
    bool verbose              = true;
    std::vector<std::string> args(argv+1, argv+argc + !argc);
    int exit = parse_args(queue_size, 
                          num_producers, 
                          producer_sleep_sec,
                          num_consumers,
                          consumer_sleep_sec,
                          verbose,
                          iterations,
                          args);
    if (exit)
    {
      return 0;
    }
    else
    {
        fprintf(stderr,"==============================================================================================\n");
        fprintf(stderr,"pushpull: Going to run %zu producer(s) and %zu consumer(s) with a %d-element shared queue.\n", num_producers, num_consumers, (int)queue_size);
        fprintf(stderr, "          Producers and Consumers will sleep for %gsec and %gsec, respectively.\n", producer_sleep_sec, consumer_sleep_sec);
        if (iterations)
        {
            fprintf(stderr, "          Producers and Consumers will run %d time(s) before the program halts\n", iterations);
        }
        else
        {
            fprintf(stderr, "          Producers and Consumers will run indefinitely. Use Ctrl+C to exit this program\n");
        }
        if (verbose)
            fprintf(stderr, "          Producers and Consumers will be verbose\n");
        else
            fprintf(stderr, "          Producers and Consumers will be silent\n");
        fprintf(stderr,"==============================================================================================\n\n");
    }
    
    
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // MAKE QUEUE
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    Queue queue(queue_size);

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // MAKE PRODUCER & CONSUMER THREADS
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    std::vector<std::thread> p_threads(num_producers);
    for (size_t i = 0; i < num_producers; i++)
    {
        std::string id= "Producer " + std::to_string(i+1);
        QueueHandlerType type = PRODUCER;

        p_threads[i] = std::thread(
                           queue_handler,
                           type,
                           id,
                           &queue,
                           producer_sleep_sec,
                           verbose,
                           iterations);
    }

    std::vector<std::thread> c_threads(num_consumers);
    for (size_t i = 0; i < num_consumers; i++)
    {
        std::string id= "Consumer " + std::to_string(i+1);
        QueueHandlerType type = CONSUMER;

        c_threads[i] = std::thread(
                           queue_handler,
                           type,
                           id,
                           &queue,
                           consumer_sleep_sec,
                           verbose,
                           iterations);
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

    fprintf(stderr, "pushpull: exiting application safely\n");

    return 0;
}

