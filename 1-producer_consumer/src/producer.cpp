#include "producer.hpp"

/// @brief this is the Producer's constructor
///
/// It essentially creates a unique ID for this producer obj and
/// holds reference to the shared resource Queue
///
/// @author aarif
/// @param[in]  id            unique identifier for this producer
/// @param[in]  queue         Queue object to put string messages to
/// @param[in]  sleep_dur_sec dur to sleep after adding msg to queue
/// @return Pointer to an instance of the Producer class
Producer::Producer(std::string id, 
                   Queue* queue, double sleep_sec) 
                  :id(id),queue(queue),sleep_dur_sec(sleep_sec)
{
    if (DEBUG)
    {
        fprintf(stderr, "In Producer %s's constructor\n", this->id.c_str());
    }
}

/// @brief this is the Producer's destructor
///
/// For now, all it does is print a message to tell the user that 
/// this method has been reached
///
/// @author aarif
Producer::~Producer()
{
    if(DEBUG)
    {
        fprintf(stderr, "In Producer %s's destructor\n", this->id.c_str());
    }
}


/// @brief this allows the Producer instance to run indefinitely
/// and keep adding message to the queue as long as there's space
/// in it
/// @author aarif
void Producer::run()
{
#if 0
#endif
    fprintf(stderr, "in producer %s's run() fcn\n", this->id.c_str());
    static int cnt = 0;
    while(true)
    {
        if (DEBUG)
        {
            fprintf(stderr, "in producer %s's while\n",this->id.c_str());
        }
        // make a message to put in the queue
        //std::string msg = "hi";
        std::string msg = this->id + " Msg#" + std::to_string(cnt);
        // let the user know that you're about to put it in the queue
        fprintf(stderr, "%s: Putting this msg in queue: \'%s\'\n", this->id.c_str(), msg.c_str());
        // make the call
        this->queue->pushMsg(msg);
        // let user know that it was successful TODO:time elapsed?
        if (DEBUG)
        {
            fprintf(stderr, "%s: Done.\n", this->id.c_str());
        }
        // sleep for a period of time
        sleep((unsigned int)this->sleep_dur_sec);

        // increment msg counter
        cnt++;
    }
}


