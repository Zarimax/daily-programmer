// C99 (gcc 6.2.0)
int solution(int A[], int N) {
    int unpaired_value = 0;
    int i;
    
    for (i = 0; i < N; i++)
    {
        unpaired_value ^= A[i];
    }
    
    return unpaired_value;        
}
