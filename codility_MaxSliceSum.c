// C99 (gcc 6.2.0)
// Kadane's algorithm

int solution(int A[], int N) {
	int sum = 0, M = 0x80000000;

	for (int i = 0; i < N; i++)
	{
		sum += A[i];
		if (sum > M)
			M = sum;

		if (sum < 0)
			sum = 0;
	}
	return M;
}
