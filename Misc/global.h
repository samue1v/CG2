#ifndef GLOBAL_H
#define GLOBAL_H
#include <math.h>


#define PI M_PI
#define DOUBLE_INFINITY INFINITY
#define SCREEN_W 500
#define SCREEN_H 500
#define WINDOW_WIDTH 60
#define WINDOW_HEIGHT 60
#define WINDOW_DISTANCE 20
#define REALLY_SMALLF 1e-15f
#define REALLY_SMALLD 1e-15
#define MIN_DIST 1e-4;
#define MAX_DIST 1e10;

inline bool isReallySmall(double n){
    if(abs(n) < REALLY_SMALLD){
        return true;
    }
    return false;
}

inline bool isReallySmall(float n){
    if(abs(n) < REALLY_SMALLF){
        return true;
    }
    return false;
}

#endif