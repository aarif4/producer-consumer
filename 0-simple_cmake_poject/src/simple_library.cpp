#include "simple_library.hpp"

simple_library::simple_library(std::string newname)
{
    name        = newname;
    public_val  = 0;
    private_val = 0;
}

simple_library::~simple_library()
{
    // do nothing
}


void simple_library::set_public_val(int num)
{
    public_val = num;
}

int simple_library::get_public_val()
{
    return public_val;
}

void simple_library::set_private_val(int num)
{
    private_val = num;
}

int simple_library::get_private_val()
{
    return private_val;
}

char * simple_library::to_string()
{
    std::string s = "";
    s.append("\tname       : " + name + "\n");
    s.append("\tpublic_val : " + std::to_string(public_val)  + "\n");
    s.append("\tprivate_val: " + std::to_string(private_val) + "\n");

    char * ch = new char[s.size()+1];
    memcpy(ch, s.c_str(), s.size());

    return ch;
}
