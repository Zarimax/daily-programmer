// C99 (gcc 6.2.0)
int solution(int A[], int N) {
    int i, j, stack = 0, top = 0, count = 0, result = 0;
    
    // leader-finding algorithm is from codility_Dominator.c
    for (i = 0; i < N; i++)
    {
        if (top == 0)
        {
            top++;    
            stack = A[i];
        }
        else
        {
            if (stack != A[i])
                top--;
            else
                top++;
        }
    }
    
    if (top > 0)
    {
        for (i = 0; i < N; i++)
        {
            if (A[i] == stack)
                count++;
        }       
    }
    
    if (count > (N / 2)) // if we have a leader
    {
        int L[N], R[N], Lcnt = 0, Rcnt = 0;
        
        // build two new arrays - L and R - which represent the number of instances of the leader
        // on the Left side and the Right side of any position within A
        for (i=0, j=N-1; i < N && j > 0; i++, j--)
        {
            // this loop will build both L and R in a single pass
            L[i] = R[j] = 0;
            
            if (A[i] == stack)
                Lcnt++;
            if (Lcnt > ((i+1) / 2))
                L[i] = 1;
            
            if (A[j] == stack)
                Rcnt++;                
            if (Rcnt > ((N-j) / 2))
                R[j] = 1;
        }
        
        // walk through the Left side and Right side arrays looking for positions which satisfy the
        // criteria for an equi leader
        for (i = 0; i < (N-1); i++)
        {
            if (L[i] == 1 && R[i+1] == 1)
                result++;
        }
    }
    
    return result;   
}
