#include <gtest/gtest.h>
#include<Producer.hpp>
#include<Consumer.hpp>

TEST(Producer, Init)
{
    Producer* obj = new Producer();
    ASSERT_EQ(0, obj->get_public_val());
    obj->set_public_val(23);
    ASSERT_EQ(23, obj->get_public_val());
}

TEST(Consumer, Init)
{
    Consumer* obj = new Consumer();
    ASSERT_EQ(0, obj->get_public_val());
    obj->set_public_val(25);
    ASSERT_EQ(25, obj->get_public_val());
}

int main(int argc, char **argv)
    {
    testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
