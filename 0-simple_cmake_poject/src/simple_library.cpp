#include "simple_library.hpp"

/// @brief this is a constructor
///
/// here's a longer description. 
///
/// @author me
/// @param[in]   newname   input string
/// @return Returns a pointer object becasue it does
simple_library::simple_library(std::string newname)
{
    name        = newname;
    public_val  = 0;
    private_val = 0;
}

/// @brief this is the destructor
///
/// here's a longer description. 
///
/// @author me
simple_library::~simple_library()
{
    // do nothing
}


/// @brief this is a setter for public_val
///
/// here's a longer description. 
///
/// @author me
/// @param[in]   num   a number
void simple_library::set_public_val(int num)
{
    public_val = num;
}

/// @brief this is a getter for public_val
///
/// here's a longer description. 
///
/// @author me
// here's a longer description. Put the name you want it to have
/// @return Returns public_val's value
int simple_library::get_public_val()
{
    return public_val;
}

/// @brief this is a setter for private_val
///
/// here's a longer description. 
///
/// @author me
/// @param[in]   num   a number
void simple_library::set_private_val(int num)
{
    private_val = num;
}
/// @brief this is a getter for private_val
///
/// here's a longer description. 
///
/// @author me
/// @return Returns private_val's value
int simple_library::get_private_val()
{
    return private_val;
}

/// @brief this is a to_string() fcn
///
/// here's a longer description. 
///
/// @author me
/// @return Returns a string that tells us the state of the object
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
