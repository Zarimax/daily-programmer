// C99 (gcc 6.2.0)
#include <float.h>

int solution(int A[], int N) {
    double left_side = 0;
    double right_side = 0;
    double current_diff = 0;
    double lowest_diff = DBL_MAX;
    int i;
    
    for (i = 0; i < N; i++)
    {
        right_side += A[i];
    }
    
    for (i = 0; i < (N-1); i++)
    {
        left_side += A[i];
        right_side -= A[i];
        current_diff = abs(left_side - right_side);
        if (current_diff < lowest_diff)
            lowest_diff = current_diff;
    }    
    
    return lowest_diff;
}
