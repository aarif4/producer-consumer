#include <gtest/gtest.h>
#include "main.hpp"

TEST(Producer_Consumer, 1ThreadIter1_1ThreadIter1)
{
    Queue queue(2);
    double sleep = 0;
    int iter = 1;

    Producer pobj("producer1",&queue,sleep,false);
    pobj.run(iter);
    std::string pmsg = pobj.get_last_msg();

    Consumer cobj("consumer1",&queue,sleep,false);
    cobj.run(iter);
    std::string cmsg = cobj.get_last_msg();

    ASSERT_STREQ(pmsg.c_str(), cmsg.c_str());
}

TEST(Producer_Consumer, 1ThreadIter1Iter9_2ThreadIter1Iter9)
{
    Queue queue(10);
    double sleep = 0;

    Producer pobj("producer1",&queue,sleep,false);
    pobj.run(1);
    std::string pmsg1 = pobj.get_last_msg();
    pobj.run(9);
    std::string pmsg2 = pobj.get_last_msg();

    Consumer cobj1("consumer1",&queue,sleep,false);
    cobj1.run(1);
    std::string cmsg1 = cobj1.get_last_msg();

    Consumer cobj2("consumer2",&queue,sleep,false);
    cobj2.run(9);
    std::string cmsg2 = cobj2.get_last_msg();

    ASSERT_STREQ(pmsg1.c_str(), cmsg1.c_str());
    ASSERT_STREQ(pmsg2.c_str(), cmsg2.c_str());
}


int main(int argc, char **argv)
    {
    testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
