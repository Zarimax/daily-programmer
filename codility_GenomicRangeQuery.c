// C99 (gcc 6.2.0)

// map A, C, G, and T to impact factors
int get_impact_factor(char nucleotide)
{
    switch(nucleotide)
    {
        case 'A': return 1;
        case 'C': return 2;
        case 'G': return 3;
        case 'T': return 4;
    }
    return 0;
}

#define NUM_OF_IMPACT_FACTORS 4

// define a lookback history structure to track the last position that each impact factor was seen
struct Lookback {
    int impact_factor;
    int last_pos[NUM_OF_IMPACT_FACTORS];
};

struct Results solution(char *S, int P[], int Q[], int M) {
    struct Results result;
    
    int len = strlen(S);
    struct Lookback *LB = calloc(len, sizeof(struct Lookback));
    int i,j;
    
    for (i = 0; i < len; i++) // loop through each character in the nucleotide string
    {
        // build lookback array
        LB[i].impact_factor = get_impact_factor(S[i]);
        for(j = 0; j < NUM_OF_IMPACT_FACTORS; j++) // set all of the "last pos" values
            LB[i].last_pos[j] = (i > 0 ? LB[i-1].last_pos[j] : -1);
        LB[i].last_pos[LB[i].impact_factor - 1] = i;
    }
    
    int *A = calloc(M, sizeof(int));
    
    for (i = 0; i < M; i++) // for endposition in Q[i], look at corresponding lookback structure
    {
        for (j = 0; j < NUM_OF_IMPACT_FACTORS; j++)
        {
            if (LB[Q[i]].last_pos[j] >= P[i]) // where does P[i] fit in?
            {
                A[i] = j+1; // update A[i] with that result
                break;
            }
        }
    }
    
    free(LB);
    
    result.A = A;
    result.M = M;
    return result;
}
