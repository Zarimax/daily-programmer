// C99 (gcc 6.2.0)

int comp (const void * elem1, const void * elem2) 
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

int solution(int A[], int N) {
    int i;
    int num_distinct = 0;
    
    qsort(A, N, sizeof(int), comp);
    
    // account for first value and N == 1 scenario
    if (N > 0)
        num_distinct = 1;

    for (i = 1; i < N; i++)
    {
        if (A[i] != A[i-1])
        {
            num_distinct++;
        }            
    }
    
    return num_distinct;
}
