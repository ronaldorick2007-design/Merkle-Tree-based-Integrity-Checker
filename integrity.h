#ifndef INTEGRITY_H  //  it will manage the multiple declaration 
#define INTEGRITY_H  // Defines the header guard

#include "common.h"  // includes the Chain structure 

int check_integrity(const Chain *c);  //  will   It Declares the integrity-checking function

#endif  //  end
// purpose of this integrity is to check wheather the entered inputs are matched with stored hash or not
