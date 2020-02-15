#ifndef __semaphore_h__
#define __semaphore_h__
#include <mutex>
#include <condition_variable>


// cpp doesn't have semaphores, but it has mutexes and cond varas, which can be used to make a semaphore
class Semaphore {
    public:
        Semaphore(int init): m_value(init)
        {
        }
        void down();
        void up();

    private:
        int m_value; // value of semaphore
        std::mutex m_mux; // controls access
        std::condition_variable m_waitcond; // control waiting and restart
};
#endif // __semaphore_h__

