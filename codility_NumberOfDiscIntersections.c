// C99 (gcc 6.2.0)

int solution(int A[], int N) {
    int result = 0;
    int *d_s = calloc(N, sizeof(int));
    int *d_e = calloc(N, sizeof(int));
    int i, t;
    
    for (i = 0; i < N; i++)
    {
        // how many discs have opened in position i?
        d_s[i > A[i] ? i - A[i] : 0]++;
        // how many discs have closed in position i?
        d_e[N - 1 - i > A[i] ? i + A[i] : N - 1]++;
    }

    for (i = 0, t = 0; i < N; i++)
    {
        if (d_s[i] > 0) // at least 1 disc has started by this position
        {
            // multiply number of already-open discs by number of newly-opening discs, add to result
            result += t * d_s[i];
            
            // if 3 discs are newly-opening, there are 1 + 2 + 3 new intersections
            // use the n * (n-1) / 2 formula to compute this amount and add it to the result
            result += d_s[i] * (d_s[i] - 1) / 2;

            if (result > 10000000) // too many results were found - abort
            {
                result = -1;
                goto EXIT;
            }
            
            // add the count of newly-opening discs to the total of already-open discs
            t += d_s[i];     
        }
        // subtract the count of newly-closing discs from the total of already-open discs
        t -= d_e[i];
    }

 EXIT:   
    free(d_s);
    free(d_e);
    return(result);
}
