// C99 (gcc 6.2.0)

struct Results solution(int N, int A[], int M) {
    struct Results result;
    
    int *C = calloc(N, sizeof(int));
    int current_max_value = 0;
    int saved_max_value = 0;
    int i,j;
    
    for (i = 0; i < M; i++) // loop through instruction array
    {
        if (A[i] == N+1) // max counter instruction
        {
            saved_max_value = current_max_value;        
        }
        else // instruction to incrememt a specific counter
        {
            if (C[A[i]-1] < saved_max_value)
               C[A[i]-1] = saved_max_value;
            C[A[i]-1]++;
            if (C[A[i]-1] > current_max_value)
                current_max_value = C[A[i]-1];
        }    
    }
    
    if (saved_max_value > 0)
    {
        for (j = 0; j < N; j++)
        {
            if (C[j] < saved_max_value)
                C[j] = saved_max_value;
        }
    }
    
    result.C = C;
    result.L = N;
    return result;
}
