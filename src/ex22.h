#ifndef _ex22_h_
#define _ex22_h_

// makes THE_SIZE in ex22.c available to other .c files
extern int THE_SIZE;

// gets and sets an internal static variable in ex22.c
int get_age();
void set_age();

// updates a static variable that's inside update_ratio, returns
// previous value
double update_ratio(double ratio);

void print_size();

#endif
