#include "consumer.hpp"

/// @brief this is the Consumer's constructor
///
/// It essentially creates a unique ID for this consumer obj and
/// holds reference to the shared resource Queue
///
/// @author aarif
/// @param[in]  id            unique identifier for this consumer
/// @param[in]  queue         Queue object to put string messages to
/// @param[in]  sleep_dur_sec dur to sleep after adding msg to queue
/// @return Pointer to an instance of the Consumer class
Consumer::Consumer(std::string id, 
                   Queue* queue, double sleep_sec) 
                  :id(id),queue(queue),sleep_dur_sec(sleep_sec)
{
    if (DEBUG)
    {
        fprintf(stderr, "In Consumer %s's constructor\n", this->id.c_str());
    }
}

/// @brief this is the Consumer's destructor
///
/// For now, all it does is print a message to tell the user that 
/// this method has been reached
///
/// @author aarif
Consumer::~Consumer()
{
    if(DEBUG)
    {
        fprintf(stderr, "In Consumer %s's destructor\n", this->id.c_str());
    }
}


/// @brief this allows the Consumer instance to run indefinitely
/// and keep adding message to the queue as long as there's space
/// in it
/// @author aarif
void Consumer::run()
{
    fprintf(stderr, "in consumer %s's run() fcn\n",this->id.c_str());
    while(true)
    {
        fprintf(stderr, "in consumer %s's while\n",this->id.c_str());
        // make a message to put in the queue
        // let the user know that you're about to put it in the queue
        if (DEBUG)
        {
            fprintf(stderr, "%s: Going to get message from queue.\n",this->id.c_str());
        }
        // make the call
        std::string msg = this->queue->pullMsg();
        // let the user know the message TODO: time elapsed?
        fprintf(stderr, "%s: Got this msg from the queue: \'%s\'\n",this->id.c_str(), msg.c_str());

        // sleep for a period of time
        sleep((unsigned int)this->sleep_dur_sec);

        // increment msg counter
    }
}


