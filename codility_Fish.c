// C99 (gcc 6.2.0)

int solution(int A[], int B[], int N) {
    int DOWN[N], dtop=-1, living=0, i;
    
    for (i = 0; i < N; i++)
    {
        if (B[i] == 0) // if it is an UP, try to chew through DOWN stack
        {
            while (dtop > -1 && A[i] > DOWN[dtop])
                dtop--;
            if (dtop == -1)
                living++;
        }
        else // if it is a DOWN, add to the DOWN stack
        {
            DOWN[++dtop] = A[i];    
        }
    }
    
    living += (dtop + 1);
    return living;
}
