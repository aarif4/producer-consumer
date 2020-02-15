#include "semaphore.hpp"

void Semaphore::down()
{
    std::unique_lock<std::mutex> lck(m_mux);

    // check mutex value and wait if need be
    m_value = m_value - 1;
    if(m_value < 0)
    { /* make us wait until the mutex is unlocked */
        m_waitcond.wait(lck);
    }
}

void Semaphore::up()
{
    std::unique_lock<std::mutex> lck(m_mux);

    // check mutex value and wait if need be
    m_value = m_value + 1;
    if(m_value <= 0)
    { /* start a waiting thread if required */
        m_waitcond.notify_one();
    }
}

int Semaphore::get_value()
{
    return this->m_value;
}
