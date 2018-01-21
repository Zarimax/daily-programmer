// C99 (gcc 6.2.0)

// Codility Golden Award (Ferrum 2018) - #17
// https://app.codility.com/cert/view/certMCJYNM-B445A5YSM5PSQEN2/

int solution(int A[], int N) {
    int matching_sum_idx[N+1];  // maintains the last position in A of a given negative sum
    int sum_array[N];           // maintains the sum of element i and all subsequent elements
    int i, end;
    int len=0, result=0, sum=0;

    for (i = 0; i <= N; i++)    // init array to -1
        matching_sum_idx[i] = -1;

    for (i = N-1; i >= 0; i--)  // walk through A backwards, accumulating and storing the sum
    {
        sum += A[i];
        sum_array[i] = sum;
        // the first time that we encounter a given sum, store the position of that sum in
        // matching_sum_idx.
        if (sum < 0 && matching_sum_idx[sum * -1] == -1)
            matching_sum_idx[sum * -1] = i;
    }

    for (i = 0; i < N; i++)      // walk through A forwards
    {
        if (sum_array[i] >= 0)   // if the sum of this element and all subsequent elements is not
        {                        // negative, then we know this is the largest span for i. check
            if (N - i > result)  // if it is the largest overall and break out.
                result = N - i;
            break;
        }

        // find the position where the sum of this element and all subsequent elements is cancelled
        // out. that position minus the current position is the largest possible span for i.
        end = matching_sum_idx[sum_array[i] * -1];
        if (end > i)
        {
            len = end - i;
            if (len > result)
                result = len;
        }
    }

    if (result == 1)   // cannot have a span of 1
        result = 0;

    return result;
}
