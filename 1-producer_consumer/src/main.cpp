///
/// @file main.cpp
/// @author aarif
///

#include "producer.hpp"
#include "consumer.hpp"
#include "semaphore.hpp"
#include <thread>

void producer_thread(std::string id, 
                     std::mutex* access, 
                     Sempahore* emptycnt, 
                     Semaphore* fillcnt, 
                     std::vector<std::string>* queue)
{
    Producer obj(id, access, emptycnt, fillcnt, queue);
    obj.run();
}
void consumer_thread(std::string id, 
                     std::mutex* access, 
                     Sempahore* emptycnt, 
                     Semaphore* fillcnt, 
                     std::vector<std::string>* queue)
{
    Consumer obj(id, access, emptycnt, fillcnt, queue);
    obj.run();
}

int main()
{
    printf("main: starting application\n");
    int buffer_size = 100;
    std::mutex access;
    Semaphore fillcnt(0);
    Semaphore emptycnt(buffer_size);
    std::vector<std::string> queue(buffer_size);

    int num_producers = 1;
    std::vector<std::thread> producerthreads(num_producers);
    for (int i=0; i<num_producers; i++)
    {
        std::string id= "P"+std::to_string(i);
        producerthreads[i] = std::thread(producer_thread, 
                                         id,
                                         &access,
                                         &emptycnt,
                                         &fillcnt,
                                         &queue);

    }
    int num_consumers = 1;
    std::vector<std::thread> consumerthreads(num_consumers);
    for (int i=0; i<num_consumers; i++)
    {
        std::string id= "C"+std::to_string(i);
        consumerthreads[i] = std::thread(consumer_thread, 
                                         id,
                                         &access,
                                         &emptycnt,
                                         &fillcnt,
                                         &queue);

    }
    for (int i=0; i<producerthreads.size(); i++)
    {
        producerthreads[i].join();
    }
    for (int i=0; i<consumerthreads.size(); i++)
    {
        consumerthreads[i].join();
    }

    printf("main: stopping application\n");

    return 0;
}
