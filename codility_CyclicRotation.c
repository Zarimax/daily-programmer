// C99 (gcc 6.2.0)
#include <string.h>

struct Results solution(int A[], int N, int K) {
    struct Results result;

    int next_pos = 0;
    int i;
    int *B = (int *)0;
    
    B = calloc(N, sizeof(int));
    memcpy(B, A, sizeof(int) * N);

    for(i = 0; i < N; i++)
    {
        next_pos = (i + K) % N;
        B[next_pos] = A[i];
    }
    
    result.A = B;
    result.N = N;
    return result;
}
