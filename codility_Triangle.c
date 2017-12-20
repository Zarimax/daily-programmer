// C99 (gcc 6.2.0)

// implement merge sort
void merging(int A[], int B[], int low, int mid, int high) {
   int l1, l2, i;

   for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
      if(A[l1] <= A[l2])
         B[i] = A[l1++];
      else
         B[i] = A[l2++];
   }
   
   while(l1 <= mid)    
      B[i++] = A[l1++];

   while(l2 <= high)   
      B[i++] = A[l2++];

   for(i = low; i <= high; i++)
      A[i] = B[i];
}

void sort(int A[], int B[], int low, int high) {
   int mid;
   
   if(low < high) {
      mid = (low + high) / 2;
      sort(A, B, low, mid);
      sort(A, B, mid+1, high);
      merging(A, B, low, mid, high);
   } else { 
      return;
   }   
}

int solution(int A[], int N) {
    int *B = calloc(N, sizeof(int));
    int i;
    int triplet = 0;
    double P, Q, R;
    
    sort(A, B, 0, N-1);
    for (i = 0; i < N-2; i++)
    {
        P = A[i];
        Q = A[i+1];
        R = A[i+2];
        
        if (P + Q > R &&
            Q + R > P &&
            R + P > Q)
        {
            triplet = 1;
            break;
        }
    }
 
    free(B);   
    return triplet;
}
