// C99 (gcc 6.2.0)

// this is a 3-pass solution.

#include <string.h>

int solution(int A[], int N) {
    int M = 0;
    int i;
    char X[N], Y[N];
    
    memset(X, ' ', sizeof(X));
    memset(Y, ' ', sizeof(Y));

    // pass #1: left-to-right
    int sum = 0, total_sum = 0;
    int len = 0;    
    for (i = 0; i < N; i++)
    {
        sum += A[i];
        total_sum += A[i];
        if (sum >= 0)
        {
            X[i] = 'x';
            len++;
        }
        
        if (len > M)
            M = len;        
        
        if (sum < 0)
        {
            sum = 0;
            len = 0;
        }
    }
    
    if (total_sum >= 0)
        return N;
    
    // pass #2: right-to-left
    sum = 0;
    len = 0;
    for (i = N-1; i >= 0; i--)
    {
        sum += A[i];
        if (sum >= 0)
        {
            Y[i] = 'y';
            len++;
        }
        
        if (len > M)
            M = len;        
    
        if (sum < 0)
        {
            sum = 0;
            len = 0;
        }
    }
    
    // pass #3: left-to-right while flipping back-and-forth
    int xside = 0, yside = 0;
    for (i = 0; i < N; i++)
    {
        if (X[i] != ' ')
            xside++;
        else
        {
            if (Y[i] != ' ' && Y[i-1] == ' ')
                yside = xside;
            xside = 0;
        }
        
        if (Y[i] != ' ')
            yside++;
        else
        {
            if (X[i] != ' ' && X[i-1] == ' ')
                xside = yside;
            yside = 0;
        }
            
        if (xside > M)
            M = xside; 
        if (yside > M)
            M = yside;
    }  
    
    if (M == 1)
        M = 0;
        
    return M;
}
