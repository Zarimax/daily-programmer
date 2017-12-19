// C99 (gcc 6.2.0)

int solution(int A[], int N) {
    double full_sum = (((double)N+1) * ((double)N+2)) / 2;
    double array_sum = 0;
    int i;
    
    for (i = 0; i < N; i++)
    {
        array_sum += A[i];
    }
    
    return (full_sum - array_sum);
}
