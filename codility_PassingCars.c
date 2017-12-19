// C99 (gcc 6.2.0)

int solution(int A[], int N) {
    int i;
    int num_zeros_seen = 0;
    double total_passing_pairs = 0;
    
    for (i = 0; i < N; i++)
    {
        if (A[i] == 0)
            num_zeros_seen++;
        else if (A[i] == 1)
            total_passing_pairs += num_zeros_seen;
            
        if (total_passing_pairs > 1000000000)
        {
            total_passing_pairs = -1;
            break;
        }
    }
    
    return total_passing_pairs;
}
