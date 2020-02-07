#include "simple_library.hpp"

int main()
{
    printf("main: starting application\n");
    int num;

    printf("main: instantiating simple_library object\n");
    simple_library* obj = new simple_library("dumb_name");

    num = 5;
    printf("main: setting public_val to %d\n", num);
    obj->set_public_val(num);

    num = 15;
    printf("main: setting private_val to %d\n", num);
    obj->set_private_val(num);

    printf("main: going to display content of simple_library object:\n%s\n", obj->to_string());

    printf("main: stopping application\n");
    return 0;
}
