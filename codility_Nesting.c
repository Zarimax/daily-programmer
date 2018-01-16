// C99 (gcc 6.2.0)

int solution(char *S) {
    int stack = 0, i;
    
    // +1 for open paren, -1 for close paren. 
    // if the count ever goes below zero, that is not a properly nested string, e.g., ')('
    for (i = 0; i < strlen(S) && stack >= 0; i++)
        stack += (S[i] == '(' ? 1 : -1);
    
    return (stack == 0 ? 1 : 0);
}
