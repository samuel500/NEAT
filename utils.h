
#ifndef DEF_UTILS
#define DEF_UTILS

#include <cstdlib>

#include<ctime>




extern inline int randint(int min, int max){
    return rand() % (max-min+1)+min;
}


extern inline double randdouble(double min, double max){
    return min + (double)rand()/RAND_MAX * (max - min);
}



#endif