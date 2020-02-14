#include "Producer.hpp"

/// @brief this is the Producer's constructor
///
/// This is a simple constructor of a Producer. All it does for now is sets an
/// attribute in the Producer class (public_val) to zero
///
/// @author aarif
/// @return Pointer to Producer class
Producer::Producer()
{
    printf("In Producer's constructor\n");
    public_val  = 0;
}

/// @brief this is the Producer's destructor
///
/// This is a simple destructor of a Producer. For now, all it does is print
/// a string to signify that this destructor is called
///
/// @author aarif
Producer::~Producer()
{
    printf("In Producer's destructor\n");
}


/// @brief this is the Producer's attribute setter (public_val)
/// @author aarif
/// @param[in]   num   a number to set Producer's public_val attribute to
void Producer::set_public_val(int num)
{
    public_val = num;
}

/// @brief this is the Producer's attribute getter (public_val)
/// @author aarif
/// @return returns Producer's attribute's (public_val) value
int Producer::get_public_val()
{
    return public_val;
}

