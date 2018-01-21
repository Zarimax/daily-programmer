// C99 (gcc 6.2.0)

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int slow_solution(int A[], int N);
int fast_solution(int A[], int N);

unsigned int rand_interval(unsigned int min, unsigned int max)
{
    int r;
    const unsigned int range = 1 + max - min;
    const unsigned int buckets = RAND_MAX / range;
    const unsigned int limit = buckets * range;

    /* Create equal size buckets all in a row, then fire randomly towards
     * the buckets until you land in one of them. All buckets are equally
     * likely. If you land off the end of the line of buckets, try again. */
    do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}

void TEST(char *test_name, int *test_array, int N)
{
    int slow = slow_solution(test_array, N);
    int fast = fast_solution(test_array, N);
    char result[4 + 1];
    int i;

    if (slow == fast)
        strcpy(result, "pass");
    else
        strcpy(result, "FAIL");

    printf("%s: received %02d (expected %02d) -- %s\n\n",
           test_name, fast, slow, result);
}

int main(int argc, char **argv)
{
    #define Z -1
    int T1[]  = {1,1,1,1,1};
    int T2[]  = {0,0,0,0,0};
    int T3[]  = {Z,Z,Z,Z,Z};
    int T4[]  = {0,0};
    int T5[]  = {1,1};
    int T6[]  = {Z,Z};
    int T7[]  = {Z,0};
    int T8[]  = {Z,Z,1,1,Z,Z,Z,1,1};
    int T9[]  = {1,1,Z,Z,Z,Z,Z,1,1};
    int T10[] = {Z,1,1,Z,1,Z,Z,1,1,Z,Z,1,Z,1,1,Z,1,Z,Z,1,Z,1,1,Z,Z,1,1,Z,1,Z,Z,1};
    int T11[] = {1,1,Z,0,0,0,Z,1,Z,Z,1,Z,1,0,1,Z,Z,1,0,Z,0,0,0,0,0,Z,0,0};
    #undef Z

    int *random_array;
    int random_array_size;
    int i;

    /* Intializes random number generator */
    srand(time(0));
    random_array_size = rand_interval(2, 100000);
    printf("\n... building random string of length: %d\n", random_array_size);

    random_array = malloc(random_array_size * sizeof(int));
    for (i = 0; i < random_array_size; i++)
    {
        int x = rand_interval(1, 3);
        random_array[i] = x - 2;
    }

    TEST("T01", T1, sizeof(T1)/sizeof(int));
    TEST("T02", T2, sizeof(T2)/sizeof(int));
    TEST("T03", T3, sizeof(T3)/sizeof(int));
    TEST("T04", T4, sizeof(T4)/sizeof(int));
    TEST("T05", T5, sizeof(T5)/sizeof(int));
    TEST("T06", T6, sizeof(T6)/sizeof(int));
    TEST("T07", T7, sizeof(T7)/sizeof(int));
    TEST("T08", T8, sizeof(T8)/sizeof(int));
    TEST("T09", T9, sizeof(T9)/sizeof(int));
    TEST("T10", T10, sizeof(T10)/sizeof(int));
    TEST("T11", T11, sizeof(T11)/sizeof(int));

    TEST("R01", random_array, random_array_size);

    free(random_array);
    return 0;
}

// O(n*2) - for each element, check the sum of all elements after it
int slow_solution(int A[], int N) {

    int M = 0;
    int len, sum, i, j;
    int start = 0, end = 0;

    for (i = 0; i < N; i++)
    {
        for (len=0, sum=0, j = i; j < N; j++)
        {
            sum += A[j];
            if (sum >= 0)
                len = j - i + 1;

            if (len > M)
            {
                M = len;
                start = i;
                end = j;
            }
        }
    }

    if (M == 1)
        M = 0;

    printf("start: %d  end: %d\n", start, end);

    return M;
}

// O(n) solution
int fast_solution(int A[], int N) {

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
