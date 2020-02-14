///
/// @file simple_library.hpp
/// @author Me myself and I
///

#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include <cstring>

/// @brief this is a simple library class for you to learn how to incorporate safely
/// here's some more info
/// I have three private vars: name (public), public_val (public int), and private_val (private)
/// I have a constructor and destructor. Ultimately I use the to_string() fcn to see waht those values are
/// @author this guy
///
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
