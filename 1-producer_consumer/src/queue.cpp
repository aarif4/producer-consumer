#include "queue.hpp"

Queue::Queue(uint32_t queue_max_size)
{
    this->MAX_SIZE = queue_max_size;
    this->empty_count = new Semaphore(this->MAX_SIZE);
    this->fill_count  = new Semaphore(0);
}

Queue::~Queue()
{
}

void Queue::pushMsg(std::string msg)
{
    bool DEBUG = false;
    if (DEBUG)
    {
        fprintf(stderr, "Queue(push) => Pushing msg \'%s\' to the queue\n", msg.c_str());
    }
    if (DEBUG)
    {
        fprintf(stderr, "Queue(push) => Queue empty counter was at %d/%d\n", this->empty_count->get_value(), this->MAX_SIZE);
    }
    // decrement emptiness counter (will block when we're past 0)
    this->empty_count->down();
    if (DEBUG)
    {
        fprintf(stderr, "Queue(push) => Queue empty counter is  at %d/%d\n", this->empty_count->get_value(), this->MAX_SIZE);
    }
    // lock mutex so that the buffer can be added
    this->access_buffer.lock();
    // add producer's message to the buffer
    if (DEBUG)
    {
        fprintf(stderr, "Queue(push) => Adding message to queue now\n");
    }
    this->buffer.push_back(msg);
    // done adding msg to buffer. unlock mutex
    this->access_buffer.unlock();
    // increment the filler count
    if (DEBUG)
    {
        fprintf(stderr, "Queue(push) => Queue fill  counter was at %d/%d\n", this->fill_count->get_value(), this->MAX_SIZE);
    }
    this->fill_count->up();
    if (DEBUG)
    {
        fprintf(stderr, "Queue(push) => Queue fill  counter is  at %d/%d\n", this->fill_count->get_value(), this->MAX_SIZE);
    }
}

std::string Queue::pullMsg()
{
    bool DEBUG = false;
    if (DEBUG)
    {
        fprintf(stderr, "Queue(pull) => Pulling msg from the queue\n");
    }
     // decrement fullness counter (will block when we're past 0)
    if (DEBUG)
    {
        fprintf(stderr, "Queue(pull) => Queue fill  counter was at %d/%d\n", this->fill_count->get_value(), this->MAX_SIZE);
    }
    this->fill_count->down();
    if (DEBUG)
    {
        fprintf(stderr, "Queue(pull) => Queue fill  counter is  at %d/%d\n", this->fill_count->get_value(), this->MAX_SIZE);
    }
    // lock mutex so that the msg can be acquired
    this->access_buffer.lock();
    // add producer's message to the buffer
    if (DEBUG)
    {
        fprintf(stderr, "Queue(pull) => Getting message to queue now\n");
    }
    std::string msg = this->buffer[0];
    this->buffer.erase(this->buffer.begin());
    // done adding msg to buffer. unlock mutex
    this->access_buffer.unlock();
    // increment the filler count
   if (DEBUG)
    {
        fprintf(stderr, "Queue(pull) => Queue empty counter was at %d/%d\n", this->empty_count->get_value(), this->MAX_SIZE);
    }
    // decrement emptiness counter (will block when we're past 0)
    this->empty_count->up();
    if (DEBUG)
    {
        fprintf(stderr, "Queue(pull) => Queue empty counter is  at %d/%d\n", this->empty_count->get_value(), this->MAX_SIZE);
    }

    return msg;
}



