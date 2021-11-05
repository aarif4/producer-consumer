#include "consumer.hpp"

/// @brief this is the Consumer's constructor
///
/// It essentially creates a unique ID for this consumer obj and
/// holds reference to the shared resource Queue
///
/// @author aarif
/// @param[in]  id            unique identifier for this consumer
/// @param[in]  queue         Queue object to put string messages to
/// @param[in]  sleep_sec     dur to sleep after adding msg to queue
/// @param[in]  verbose       flag to declare to show all msgs rcvd
/// @return Pointer to an instance of the Consumer class
Consumer::Consumer(std::string id, 
                   Queue* queue, 
                   double sleep_sec, 
                   bool verbose) 
                  :id(id), 
                   queue(queue), 
                   sleep_dur_sec(sleep_sec), 
                   verbose(verbose)
{
    //fprintf(stderr, "In Consumer %s's constructor\n", this->id.c_str());
}

/// @brief this is the Consumer's destructor
///
/// For now, all it does is print a message to tell the user that 
/// this method has been reached
///
/// @author aarif
Consumer::~Consumer()
{
    //fprintf(stderr, "In Consumer %s's destructor\n", this->id.c_str());
}


/// @brief subtracts messages from Queue obj
///
/// this allows the Consumer instance to run finitely (or indefinitely)
/// and keep adding message to the queue as long as there's space
/// in it
///
/// @author aarif
/// @param[in]   iterations   number of iterations to perform(<=0 means 
/// run indefinitely)
void Consumer::run(int iterations)
{
    static long cnt = 0;
    std::string msg;
    while(iterations <= 0 || cnt <= iterations)
    {
        // make the call to get a message from the queue
        msg = this->queue->pullMsg();
        // let the user know the message 
        if(this->verbose)
            fprintf(stderr, "\t%s: Got this msg from the queue: \'%s\'\n",this->id.c_str(), msg.c_str());

        // sleep for a period of time
        sleep((unsigned int)this->sleep_dur_sec);

        // increment the counter
        cnt++;
    }
    this->last_msg = msg;
}


/// @brief retrieves this Consumer's last message 
///
/// gets the Consumer's last successfully received message
///
/// @author aarif
/// @return last message it got before it safely exited its run() fcn
std::string Consumer::get_last_msg()
{
    return this->last_msg;
}

