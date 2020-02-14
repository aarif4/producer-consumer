#include "Consumer.hpp"

/// @brief this is the Consumer's constructor
///
/// This is a simple constructor of a Consumer. All it does for now is sets an
/// attribute in the Consumer class (public_val) to zero
///
/// @author aarif
/// @return Pointer to Consumer class
Consumer::Consumer()
{
    printf("In Consumer's constructor\n");
    public_val  = 0;
}

/// @brief this is the Consumer's destructor
///
/// This is a simple destructor of a Consumer. For now, all it does is print
/// a string to signify that this destructor is called
///
/// @author aarif
Consumer::~Consumer()
{
    printf("In Consumer's destructor\n");
}


/// @brief this is the Consumer's attribute setter (public_val)
/// @author aarif
/// @param[in]   num   a number to set Consumer's public_val attribute to
void Consumer::set_public_val(int num)
{
    public_val = num;
}

/// @brief this is the Consumer's attribute getter (public_val)
/// @author aarif
/// @return returns Consumer's attribute's (public_val) value
int Consumer::get_public_val()
{
    return public_val;
}

