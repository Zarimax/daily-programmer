// C99 (gcc 6.2.0)

int solution(int N) {
    unsigned char *ptr = (unsigned char *)&N;
    unsigned char bit;
    int size = sizeof(int);
    int i, j;
    int longest_gap = 0;
    int current_gap = 0;
    int start_counting = 0;
    
    for (i = size-1; i >= 0; i--)
    {
        for (j = 7; j >= 0; j--)
        {
            bit = (ptr[i] >> j) & 1;
            if (bit == 1)
            {
                if (current_gap > longest_gap)
                    longest_gap = current_gap;
                current_gap = 0;
                start_counting = 1;
            }
            else if (bit == 0 && start_counting)
            {
                current_gap++;      
            }
        }  
    }
    
    return longest_gap;
}
