// C99 (gcc 6.2.0)

int solution(int A[], int N) {
    
    short *B = calloc(N+1, sizeof(short));
    int i;
    int smallest_missing = 1;
    
    for (i = 0; i < N; i++)
    {
        if (A[i] > 0 && A[i] <= N)
            B[A[i]] = 1;
    }
    
    for (i = 1; i <= N; i++)
    {
        if (B[i] == 0)
        {
            smallest_missing = i;
            break;
        }
    }
    
    if (i > N)
        smallest_missing = i;

    free(B);
    
    return smallest_missing;
}
