// C99 (gcc 6.2.0)
#include <float.h>

int solution(int A[], int N) {
    int i = 0;
    int min_pos = 0;
    double min_avg = DBL_MAX;
    double cur_avg;
    
    // the trick here is that a minimal-average slice will either be 2 or 3 values - not longer
    // this is because longer slices can be decomposed into slices of length 2 or 3
    
    // walk through the array and check slices of length 2 and 3
    for (i = 0; i < N-2; i++)
    {
        cur_avg = (A[i] + A[i+1])/2.0;
        if (cur_avg < min_avg) {
            min_avg = cur_avg;
            min_pos = i;
        }
        
        cur_avg = (cur_avg + A[i+2])/2.0;
        if (cur_avg < min_avg) {
            min_avg = cur_avg;
            min_pos = i;
        }
    }
    
    // check final slice of length 2 which was skipped by the loop above
    cur_avg = (A[i] + A[i+1])/2.0;
    if (cur_avg < min_avg) {
        min_avg = cur_avg;
        min_pos = i;
    }
    
    return min_pos;
}
