// C99 (gcc 6.2.0)

int solution(int A[], int N) {
    int i, pos = 0, stack = 0, top = 0, count = 0;
    
    // achieve O(n) time complexity and O(1) space complexity by ignoring pairs of elements
    // which do not match. ignoring pairs of elements which do not match leaves the array with
    // the same leader, (if a leader exists).
    for (i = 0; i < N; i++)
    {
        if (top == 0) // the stack is empty...
        {
            // push to stack
            top++;
            stack = A[i];
        }
        else // there is already something on the stack...
        {
            if (stack != A[i])
                top--; // pop from stack - this has the effect of ignoring a pair of mismatching elements
            else
                top++; // push to stack. note: we do not actually need to store the value.
                // because it is identical to the last value.
        }   
    }

    if (top > 0) // we have a saved value on the stack to check...
    {
        for (i = 0; i < N; i++) // walk through the array and count up instances of our saved value
        {
            if (A[i] == stack)
            {
                pos = i;
                count++;
            }
        }
    }
    
    // if a value appears more than half the time, it is the leader
    // return the last position of that leader value
    return (count > (N / 2) ? pos : -1);
}
