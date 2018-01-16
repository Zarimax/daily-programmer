// C99 (gcc 6.2.0)
int solution(int H[], int N) {
    int stack[N], top=-1, count = 0, i;
    
    for (i = 0; i < N; i++)
    {
        if (top == -1)
        {
            // there are no entries on the wall height stack - we must add one
            stack[++top] = H[i];    // push to stack
            count++;                // increment block count
        }
        else
        {
            if (H[i] > stack[top])
            {
                // if the wall height increases, we must add a new block
                stack[++top] = H[i];    // push to stack
                count++;                // increment block count
            }
            else
            {
                // if the wall height descreases, chew through the stack to see
                // if an identical wall height was already placed
                while (top != -1 && H[i] < stack[top])
                {
                    top--;  // pop from stack
                }

                // if an identical wall height exits, we do not need to add a new block
                // if it does not, however, then we do
                if (top == -1 || H[i] != stack[top])
                {
                    stack[++top] = H[i];    // push to stack
                    count++;                // increment block count
                }
            }
        }
    }
    
    return count;
}
