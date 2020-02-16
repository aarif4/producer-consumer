#include "producer.hpp"

/// @brief this is the Producer's constructor
///
/// It essentially creates a unique ID for this producer obj and
/// holds reference to the shared resource Queue
///
/// @author aarif
/// @param[in]  id            unique identifier for this producer
/// @param[in]  queue         Queue object to put string messages to
/// @param[in]  sleep_sec     dur to sleep after adding msg to queue
/// @param[in]  verbose       flag to declare to show all msgs rcvd
/// @return Pointer to an instance of the Producer class
Producer::Producer(std::string id, 
                   Queue* queue, 
                   double sleep_sec, 
                   bool verbose) 
                  :id(id), 
                   queue(queue), 
                   sleep_dur_sec(sleep_sec), 
                   verbose(verbose)
{
    //fprintf(stderr, "In Producer %s's constructor\n", this->id.c_str());
}

/// @brief this is the Producer's destructor
///
/// For now, all it does is print a message to tell the user that 
/// this method has been reached
///
/// @author aarif
Producer::~Producer()
{
    //fprintf(stderr, "In Producer %s's destructor\n", this->id.c_str());
}


/// @brief adds messages to the Queue obj 
///
///this allows the Producer instance to run finitely (or indefinitely)
/// and keep adding message to the queue as long as there's space
/// in it
///
/// @author aarif
/// @param[in]   iterations   number of iterations to perform(<=0 means 
/// run indefinitely)
void Producer::run(int iterations)
{
    static long cnt = 0;
    std::string msg;
    while(iterations <= 0 || cnt <= iterations)
    {
        // make a message to put in the queue
        //std::string msg = "hi";
        msg = this->id + " Msg#" + std::to_string(cnt);
        // make the call
        this->queue->pushMsg(msg);
        // let the user know that you're about to put it in the queue
        if(this->verbose)
          fprintf(stderr, "\t%s: Putting this msg in queue:   \'%s\'\n", this->id.c_str(), msg.c_str());
        // sleep for a period of time
        sleep((unsigned int)this->sleep_dur_sec);

        // increment msg counter
        cnt++;
    }
    this->last_msg = msg;
}

/// @brief retrieves this Producer's last message 
///
/// gets the Producer's last successfully sent message
///
/// @author aarif
/// @return last message it made before it safely exited its run() fcn
std::string Producer::get_last_msg()
{
    return this->last_msg;
}

