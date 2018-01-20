// C99 (gcc 6.2.0)

// the overall strategy here is to track groups of values which sum to zero and push
// potential subsets to the stack for later review

void push(int value, int *stack, int *top)
{
    (*top)++;
    stack[*top] = value;
}

int pop(int *stack, int *top)
{
    if (*top == -1)
        return -1;
    return (stack[(*top)--]);
}

int solution(int A[], int N) {
    int left_bound = 0, right_bound = N-1;
    int longest_slice = 0;
    int i, j;
    int left_last = 0, left_sum = 0, left_slice = 0;
    int right_last = 0, right_sum = 0, right_slice = 0;
    int left_last_neg = 0, right_last_neg = 0;  
    int stack[N];
    int top = -1;
    
    // trim left-most negative values
    while (left_bound < N && A[left_bound] < 0)
        left_bound++;
    
    // trim rightmost negative values
    while (right_bound >= 0 && A[right_bound] < 0)
        right_bound--;
    
    if (right_bound < 0) // no non-negative values exist - we can't have a non-negative sum so return 0
        return 0;
    if (right_bound == left_bound) // only 1 non-negative value exists
    {
        if (A[left_bound] == 0 || N < 2)
            return 0; // the one value is a 0
        else
            return 2; // the one value is a 1, which creates a span of 2 when paired with a trimmed -1
    }
    
    while (left_bound != -1 && right_bound != -1 && left_bound < right_bound)
    {
        left_last = left_bound;
        right_last = right_bound;
        
        left_sum = right_sum = left_slice = right_slice = 0;
        
        // walk the array from both ends at the same time
        for (i = left_bound, j = right_bound; (i < N-1) || (j >= 0); i++, j--)
        {
            if (i < N-1) // if we have a new value going from left to right...
            {
                left_sum +=  A[i];
    
                if (left_sum == 0)
                {
                    left_slice += i - left_last + 1;
                    left_last = i+1;
                    if (left_last_neg)
                        push(i, stack, &top);
                }
                
                if (left_sum < 0)
                    left_last_neg = 1;
                else
                    left_last_neg = 0;
    
                if (left_slice > longest_slice)
                    longest_slice = left_slice;
            }
            
            if (j >= 0) // if we have a new value going from right to left...
            {
                right_sum += A[j];
    
                if (right_sum == 0)
                {
                    right_slice += right_last - j + 1;
                    right_last = j-1;
                    if (right_last_neg)
                        push(j, stack, &top);
                }
                
                if (right_sum < 0)
                    right_last_neg = 1;
                else
                    right_last_neg = 0;
            
                if (right_slice > longest_slice)
                    longest_slice = right_slice;
            }
        }
 
        right_bound = pop(stack, &top);
        left_bound = pop(stack, &top);       
        while (left_bound > right_bound)
        {
            right_bound = pop(stack, &top);
            left_bound = pop(stack, &top);
        }
    }
    
    return longest_slice;
}
