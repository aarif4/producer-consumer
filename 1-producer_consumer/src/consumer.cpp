#include "Consumer.hpp"

/// @brief this is the Consumer's constructor
///
/// This is a not-so-simple constructor of a Consumer. 
///
/// @author aarif
/// @param[in]   newid                 id used when printing stuff for this producer
/// @param[in]   queue_access          mutex that tells us when it's ok to access queue
/// @param[in]   empty_slot_counter    semaphore to dec no. of empty slots
/// @param[in]   filled_slot_counter   semaphore to inc. no of empty slots
/// @param[in]    queue_var            actual queue
/// @return Pointer to Consumer class
Consumer::Consumer(std::string newid, 
                   std::mutex* queue_access, 
                   Semaphore* empty_slot_counter, 
                   Semaphore* filled_slot_counter, 
                   std::vector<std::string>* queue_var)
{
    id                 = newid;
    printf("In Consumer %s's constructor\n", id);
    queue_size         = (*queue_var).size();
    QueueAccess        = queue_access;
    EmptySlotsInQueue  = empty_slot_counter;
    FilledSlotsInQueue = filled_slot_counter;
    queue              = queue_var;
}

/// @brief this is the Consumer's destructor
///
/// This is a simple destructor of a Consumer. For now, all it does is print
/// a string to signify that this destructor is called
///
/// @author aarif
Consumer::~Consumer()
{
    printf("In Consumer %s's destructor\n", id);
}


/// @brief this is the run function that will indefinitely keep removing data from the queue
/// @author aarif
void Consumer::run()
{
    static int cnt = 0;
    while(true)
    {
        FilledSlotsInQueue->down();
        QueueAccess->lock();

        std::string msg = (*queue)[cnt];
        printf("Cons %s: Got this msg in queue: \'%s\'\n",msg.c_str());

        QueueAccess->unlock();
        EmptySlotsInQueue->up();
        cnt++;
        if (cnt > (*queue).size())
        {
            break;
        }
    }
}
