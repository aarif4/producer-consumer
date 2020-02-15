#include "Producer.hpp"

/// @brief this is the Producer's constructor
///
/// This is a not-so-simple constructor of a Producer. 
///
/// @author aarif
/// @param[in]   newid                 id used when printing stuff for this producer
/// @param[in]   queue_access          mutex that tells us when it's ok to access queue
/// @param[in]   empty_slot_counter    semaphore to dec no. of empty slots
/// @param[in]   filled_slot_counter   semaphore to inc. no of empty slots
/// @param[in]    queue_var            actual queue
/// @return Pointer to Producer class
Producer::Producer(std::string newid, 
                   std::mutex* queue_access, 
                   Semaphore* empty_slot_counter, 
                   Semaphore* filled_slot_counter, 
                   std::vector<std::string>* queue_var)
{
    printf("In Producer's constructor\n");
    id                 = newid;
    queue_size         = (uint32_t) (*queue_var).size();
    QueueAccess        = queue_access;
    EmptySlotsInQueue  = empty_slot_counter;
    FilledSlotsInQueue = filled_slot_counter;
    queue              = queue_var;
}

/// @brief this is the Producer's destructor
///
/// This is a simple destructor of a Producer. For now, all it does is print
/// a string to signify that this destructor is called
///
/// @author aarif
Producer::~Producer()
{
    printf("In Producer's destructor\n");
}


/// @brief this is the run function that will indefinitely keep adding data to the queue
/// @author aarif
void Producer::run()
{
    static int cnt = 0;
    while(true)
    {
        EmptySlotsInQueue->down();
        QueueAccess->lock();

        (*queue)[cnt] = id + " #" + std::to_string(cnt);
        printf("Prod %s: Putting this msg in queue: \'%s\'\n",(*queue)[cnt].c_str());

        QueueAccess->unlock();
        FilledSlotsInQueue->up();
        cnt++;
        if (cnt > (*queue).size())
        {
            break;
        }
    }
}


