#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include <cstring>

class simple_library
{
    public:
        std::string name;
        int public_val;
    private:
        int private_val;

    public:
        simple_library(std::string newname);
        ~simple_library();

        void set_public_val(int num);
        int  get_public_val();
        void set_private_val(int num);
        int  get_private_val();

        char * to_string();
};
