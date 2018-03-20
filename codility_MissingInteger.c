// C99 (gcc 6.2.0)

#include <stdio.h>
#include <stdlib.h>

int solution(int A[], int N) {

    int result = 1;
    
    // allocate space for a checklist of integers that we have seen
    // we only care about yes/no values, so the char type is fine for this
    char *checklist = calloc(N+1, sizeof(char)); // N+1 here to allow checklist[N]
    if (checklist == NULL)
        return 0; // error condition - memory allocation failed
    
    // for each element in the given array, set the corresponding character value
    // in the checklist to true
    for (int i = 0; i < N; i++) {
        // we only care about values between 1 and N. if there exists and integer value
        // greater than N we can safely disregard it, (because that tells us that the
        // range is not contigious and the smallest missing positive integer must be less
        // than N)
        if (A[i] > 0 && A[i] <= N) {
            checklist[A[i] - 1] = 1;
        }
    }

    // walk through the checklist looking for the first char value that is set to zero.
    // this is our missing value
    for(int i = 0; i <= N; i++)
    {
        if (checklist[i] == 0)
        {
            result = i+1;
            break;
        }
    }
    
    free(checklist);
    return result;
}

int main()
{
    int test_1[] = {1, 2, 3};
    int test_2[] = {-1, -3};
    int test_3[] = {1, 2, 10};
    int test_4[] = {2, 2, 2, 2, 2, 2};
    int test_5[] = {1};
    int test_6[] = {1, 1, 2, 2, 2, 3, 3, 5, 5, 5, 6, 6};
    int test_7[] = {1000000, 2, 1, 4};

    printf("test 1: should be 4, got: %d\n", solution(test_1, sizeof(test_1)/sizeof(int)));
    printf("test 2: should be 1, got: %d\n", solution(test_2, sizeof(test_2)/sizeof(int)));
    printf("test 3: should be 3, got: %d\n", solution(test_3, sizeof(test_3)/sizeof(int)));
    printf("test 4: should be 1, got: %d\n", solution(test_4, sizeof(test_4)/sizeof(int)));
    printf("test 5: should be 2, got: %d\n", solution(test_5, sizeof(test_5)/sizeof(int)));
    printf("test 6: should be 4, got: %d\n", solution(test_6, sizeof(test_6)/sizeof(int)));
    printf("test 7: should be 3, got: %d\n", solution(test_7, sizeof(test_7)/sizeof(int)));                        

    return 0;
}
