#include<simple_library.hpp>
#include <gtest/gtest.h>

TEST(SimpleLibraryTest, Init)
{
    simple_library* obj = new simple_library("dumb_name");
    ASSERT_EQ(0, obj->get_private_val());
    ASSERT_EQ(0, obj->get_public_val());
}

TEST(SimpleLibraryTest, ValCheck)
{
    simple_library* obj = new simple_library("dumb_name");
    obj->set_private_val(44);
    obj->set_public_val(45);
    ASSERT_EQ(44, obj->get_private_val());
    ASSERT_EQ(45, obj->get_public_val());
}

int main(int argc, char **argv)
    {
    testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
