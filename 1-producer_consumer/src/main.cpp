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
                   double sleep_dur_sec,
                   bool verbose,
                   int iterations);

int parse_args( uint32_t &queue_size,
                size_t   &num_producers,
                double   &producer_sleep_sec,
                size_t   &num_consumers,
                double   &consumer_sleep_sec,
                bool     &verbose,
                int      &iterations,
                std::vector<std::string> &args);

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


/// @brief: generic Producer/Consumer thread 
///
/// this is a generic function used to instantiate a Producer 
/// or a Consumer object and have them run while viewing the same 
/// shared queue
///
/// @author: aarif
/// @param[in]   type           Enum value to indicate whether we want to create a Consumer or Publisher
/// @param[in]   id             Unique Identifier for this thread (if it's meant to be verbose)
/// @param[in]   queue          Shared resource object that has the FIFO queue
/// @param[in]   sleep_dur_sec  Amount of time to sleep after performing and action (i.e. send/receive)
/// @param[in]   verbose        Flag to determine whether thread should be verbose or not
/// @param[in]   iterations     Number of actions the Producer/Consumer should perform (0 means run indefinitely)
void queue_handler(QueueHandlerType type,
                   std::string id,
                   Queue * queue,
                   double sleep_dur_sec, 
                   bool verbose,
                   int iterations)
{
    switch(type)
    {
        case PRODUCER:
        {
            Producer pobj(id, queue, sleep_dur_sec, verbose);
            pobj.run(iterations);
        }
        break;
        case CONSUMER:
        {
            Consumer cobj(id, queue, sleep_dur_sec, verbose);
            cobj.run(iterations);
        }
        break;
        default:
            std::cerr << "queue_handler: Invalid QueueHandlerType for ID(" 
                      << id << "). Exiting thread" << std::endl;
            return;
    }
}


/// @brief: user-defined input arg parser
///
/// this function parses the user arguments (if they exist and defined properly) and adjusts the default values that this program uses (1Producer-1Consumer 1sec delay run indefinitely)
///
/// @author: aarif
/// @param[in]   queue_size           No. of elements in the queue (must be b/w 1-99) [DEFAULT 10]
/// @param[in]   num_producers        No. of Producer threads to run (must be b/w 1-10) [DEFAULT 1]
/// @param[in]   producer_sleep_sec   After Producer performs an action, it sleeps for this requested period of time (must be b/w 0-60sec) [DEFAULT 1]
/// @param[in]   num_consumers        No. of Producer threads to run (must be b/w 1-10) [DEFAULT 1]
/// @param[in]   consumer_sleep_sec   After Producer performs an action, it sleeps for this requested period of time (must be b/w 0-60sec) [DEFAULT 1]
/// @param[in]   verbose              Flag to determine whether the Producer/Consumer threads should be verbose [DEFAULT true]
/// @param[in]   iterations           No. of actions that each Producer/Consumer thread should perform before exiting their thread (0 means run indefinitely) [DEFAULT 0]
/// @param[in]   args                 Vector of input arguments passed in by the user. Can be empty if no arguments given, which just means that the default values are used.
/// @returns flag that describes whether we should exit the program prematurely or not (happens if use want to just see help menu)
int parse_args( uint32_t &queue_size,
                size_t   &num_producers,
                double   &producer_sleep_sec,
                size_t   &num_consumers,
                double   &consumer_sleep_sec,
                bool     &verbose,
                int      &iterations,
                std::vector<std::string> &args)
{
    if (args.size() == 0)
    {
        return 0;// use defaults
    }
    if (args.size() == 1 && (args[0].compare("-h") == 0 || args[0].compare("--help") == 0))
    {
         std::cerr << "Usage" << std::endl;
         std::cerr << "\t./pushpull [--option] [--flags]" << std::endl << std::endl;
         std::cerr << "This is a solution to the producer-consumer problem that allows you to define\n"
                 <<   "  the number of producers/consumers and their respective idle durations.\n" << std::endl;
         std::cerr << "Options [OPTIONAL]" << std::endl;
         std::cerr << "\t-q\t--queue_size=<value>\t\tsets the queue size to the requested size (b/w 1-99)\n";
         std::cerr << "\t-pnum\t--num_producers=<value>\t\tset number of producer to use (b/w 0-10)\n";
         std::cerr << "\t-cnum\t--num_consumers=<value>\t\tset number of consumers to use (b/w 0-10)\n";
         std::cerr << "\t-ps\t--producer_sleep_sec=<value>\tset idle period of the producer after it loads a message (b/w 0-60sec)\n";
         std::cerr << "\t-cs\t--consumer_sleep_sec=<value>\tset idle period of the consumer after it extracts a message (b/w 0-60sec)\n";
         std::cerr << "\t-lim\t--limit_iterations=<value>\tlimit the number of cycles that producers & consumers can run (b/w 0-100)\n";
         std::cerr << "Flags [OPTIONAL]" << std::endl;
         std::cerr << "\t-h\t--help\t\t\t\tdisplays this help menu and exits the program\n";
         std::cerr << "\t-s\t--silence\t\t\tsuppresses unnessary printouts from this program (useful during test cases)\n";

        return 1;
    }
    for (size_t i=0; i<args.size(); i++)
    {
        // make sure that it starts with a dash
        // see the text in between the dash and the equals sign
        //   if it dne, then don't do anything to it
        // see if this symbol works,
        //   if it doesn't exit, then ignore it
        // take the number after the equals sign
        //   if it doesn't work, throw error and tell the defualt val
        // if it works, then set the right arg and continue looping
        std::string str_shrt;
        std::string str_long;
        std::size_t found_shrt; 
        std::size_t found_long; 

        if (args[i].compare("-s") == 0 || args[i].compare("-silence") == 0)
        {
            verbose = false;
            continue;
        }
  

        //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        str_shrt = "-q=";
        str_long = "-queue_size=";
        found_shrt = args[i].find(str_shrt);
        found_long = args[i].find(str_long);
        if (found_shrt != std::string::npos && found_shrt == 0) 
        {
            int val = atoi(args[i].substr(found_shrt+str_shrt.size()).c_str());
            if (val > 0 && val < 100)
            {
                queue_size = val;
            }
            continue;
        }
        if (found_long != std::string::npos)
        {
            int val = atoi(args[i].substr(found_long+str_long.size()).c_str());
            if (val > 0 && val < 100)
            {
                queue_size = val;
            }
            continue;
        }
        //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        str_shrt = "-pnum=";
        str_long = "-num_producers=";
        found_shrt = args[i].find(str_shrt);
        found_long = args[i].find(str_long);
        if (found_shrt != std::string::npos && found_shrt == 0) 
        {
            int val = atoi(args[i].substr(found_shrt+str_shrt.size()).c_str());
            if (val >=0 && val <=10)
            {
                num_producers = val;
            }
            continue;
        }
        if (found_long != std::string::npos)
        {
            int val = atoi(args[i].substr(found_long+str_long.size()).c_str());
            if (val >=0 && val <=10)
            {
                num_producers = val;
            }
            continue;
        }
        //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        str_shrt = "-cnum=";
        str_long = "-num_consumers=";
        found_shrt = args[i].find(str_shrt);
        found_long = args[i].find(str_long);
        if (found_shrt != std::string::npos && found_shrt == 0) 
        {
            int val = atoi(args[i].substr(found_shrt+str_shrt.size()).c_str());
            if (val >=0 && val <=10)
            {
                num_consumers = val;
            }
            continue;
        }
        if (found_long != std::string::npos)
        {
            int val = atoi(args[i].substr(found_long+str_long.size()).c_str());
            if (val >=0 && val <=10)
            {
                num_consumers = val;
            }
            continue;
        }
        //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        str_shrt = "-ps=";
        str_long = "-producer_sleep_sec=";
        found_shrt = args[i].find(str_shrt);
        found_long = args[i].find(str_long);
        if (found_shrt != std::string::npos && found_shrt == 0) 
        {
            double val = atof(args[i].substr(found_shrt+str_shrt.size()).c_str());
            if (val >=0 && val <=60)
            {
                producer_sleep_sec = val;
            }
        }
        if (found_long != std::string::npos)
        {
            double val = atof(args[i].substr(found_long+str_long.size()).c_str());
            if (val >=0 && val <=60)
            {
                producer_sleep_sec = val;
            }
            continue;
        }
       //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        str_shrt = "-cs=";
        str_long = "-consumer_sleep_sec=";
        found_shrt = args[i].find(str_shrt);
        found_long = args[i].find(str_long);
        if (found_shrt != std::string::npos && found_shrt == 0) 
        {
            double val = atof(args[i].substr(found_shrt+str_shrt.size()).c_str());
            if (val >=0 && val <=60)
            {
                consumer_sleep_sec = val;
            }
            continue;
        }
        if (found_long != std::string::npos)
        {
            double val = atof(args[i].substr(found_long+str_long.size()).c_str());
            if (val >=0 && val <=60)
            {
                consumer_sleep_sec = val;
            }
            continue;
        }
       //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        str_shrt = "-lim=";
        str_long = "-limit_iterations=";
        found_shrt = args[i].find(str_shrt);
        found_long = args[i].find(str_long);
        if (found_shrt != std::string::npos && found_shrt == 0) 
        {
            int val = atoi(args[i].substr(found_shrt+str_shrt.size()).c_str());
            if (val >=0 && val <=100)
            {
                iterations = val;
            }
        }
        if (found_long != std::string::npos)
        {
            int val = atoi(args[i].substr(found_long+str_long.size()).c_str());
            if (val >=0 && val <=100)
            {
                iterations = val;
            }
        }
    }
    return 0;
}








