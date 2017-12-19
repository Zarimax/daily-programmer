// C99 (gcc 6.2.0)

int solution(int A, int B, int K) {
    int divisors = 0;

    if ((A % K) == 0)
        divisors++;

    divisors += ((B / K) - (A / K));

    return divisors;
}
