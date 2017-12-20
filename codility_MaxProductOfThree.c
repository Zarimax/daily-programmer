// C99 (gcc 6.2.0)

int comp (const void * elem1, const void * elem2) 
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

int solution(int A[], int N) {
    int max_product = 0;
    int low_test = 0;
   
    qsort(A, N, sizeof(int), comp);
    
    // for positive numbers, the three biggest values will yield the biggest product
    max_product = A[N-1] * A[N-2] * A[N-3];
    
    // it is possible for two negative numbers and a positive number to be bigger than 3 positive numbers
    low_test = A[0] * A[1] * A[N-1];
    if (low_test > max_product)
        max_product = low_test;
    
    return max_product;
}
