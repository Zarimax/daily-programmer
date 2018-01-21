// C99 (gcc 6.2.0)

// this is a 4-pass solution.

#include <string.h>

int solution(int A[], int N) {
    int M = 0;
    int i;
    char X[N], Y[N];
    
    memset(X, ' ', sizeof(X));
    memset(Y, ' ', sizeof(Y));

    // pass #1: left-to-right
    int sum = 0;
    int len = 0;    
    for (i = 0; i < N; i++)
    {
        sum += A[i];
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
    
    // pass #3: left-to-right while flipping back-and-forth, with a preference for track X
    char *current_track = X;
    char *other_track = Y;
    len = 0;
    for (i = 0; i < N; i++)
    {
        if (current_track[i] != ' ')
            len++;
        else
        {
            if ((i - 1 >= 0) && other_track[i] != ' ' && other_track[i-1] == ' ')
            {
                char * temp = current_track;
                current_track = other_track;
                other_track = temp;
                len++;
            }
            else
            {
                len = 0;
                current_track = X;
                other_track = Y;
            }
        }
            
        if (len > M)
            M = len; 
    }
    
    // pass #4: right-to-left while flipping back-and-forth, with a preference for track Y
    current_track = Y;
    other_track = X;
    len = 0;
    for (i = N-1; i >= 0; i--)
    {
        if (current_track[i] != ' ')
            len++;
        else
        {
            if ((i + 1 < N - 1) && other_track[i] != ' ' && other_track[i+1] == ' ')
            {
                char * temp = current_track;
                current_track = other_track;
                other_track = temp;
                len++;
            }
            else
            {
                current_track = Y;
                other_track = X;
                len = 0;
            }
        }
            
        if (len > M)
            M = len;  
    }    
    
    if (M == 1)
        M = 0;
        
    return M;
}
