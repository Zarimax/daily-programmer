// C99 (gcc 6.2.0)

int solution(int X, int A[], int N) {
    
    int *river = calloc(X+1, sizeof(int)); // build an array to track values which have been seen before
    double full_river = (((double)X) * ((double)X + 1)) / 2;  // get the sum of all integers between 1 and X
    int i;
    int cross_time = -1;
    
    for (i = 0; i < N; i++)
    {
        if (river[A[i]] == 0) // we have not seen this value before
        {
            river[A[i]] = 1;
            full_river -= A[i];
        }
        
        if (cross_time == -1 && full_river == 0)
        {
            cross_time = i;
            break;
        }
    }
    
    return cross_time;
}
