// C99 (gcc 6.2.0)

int solution(int A[], int N) {
    int perm_xor = 0;
    int array_xor = 0;
    int i;
    
    for (i = 0; i < N; i++)
    {
        perm_xor  ^= (i+1);
        array_xor ^= A[i];
    }
    
    return(perm_xor == array_xor ? 1 : 0);
}
