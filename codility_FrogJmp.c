// C99 (gcc 6.2.0)
#include <math.h>

int solution(int X, int Y, int D) {    
    double distance = (double)(Y - X) / D;
    return ceil(distance);
}
