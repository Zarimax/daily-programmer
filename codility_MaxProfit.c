// C99 (gcc 6.2.0)

#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

int solution(int A[], int N) {
    int max_ending = 0, max_slice = 0, i;
    
    // for each position, we compute the largest sum that ends in that position. if we
    // assume that the maximum sum of a slice ending in position i equals max_ending, then
    // the maximum slice ending in position i+1 equals MAX(0, max_ending+A[i+1])
    for (i = 0; i < (N-1); i++)
    {
        max_ending = MAX(0, max_ending + (A[i+1] - A[i]));
        max_slice = MAX(max_slice, max_ending);
    }
    
    return (max_slice > 0 ? max_slice : 0);
}
