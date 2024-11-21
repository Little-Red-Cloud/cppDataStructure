#ifndef TimeCounting
#define TimeCounting

#include <functional>


/*
 * @brief Count the time cosumed by function
 *
 * @param n The function run n times. 
 * n should be bigger than zero.
 * @param func Test function
 * no parameter and no return type
 *
 * @return the seconds that the function cosumed
 */
double timeCounting(int n,std::function<void()> func);

#endif
