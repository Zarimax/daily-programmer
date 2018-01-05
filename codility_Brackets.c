// C99 (gcc 6.2.0)

// define a data structure to map open brackets to closing brackets
struct char_mapping {
    char open;
    char close;
};

struct char_mapping MAP[] = 
{
  {'{', '}'},
  {'[', ']'},
  {'(', ')'},
  {'\0', '\0'}
};

int pop(char *stack, int *sp, char value)
{
    int j;
    int result = 0;
    
    if (*sp >= 0) // we cannot pop from an empty stack
    {
        for (j = 0; MAP[j].open != '\0'; j++)
        {
            if (value == MAP[j].close)
                result = (MAP[j].open == stack[*sp] ? 1 : 0);
        }
        stack[(*sp)--] = '\0';
    }
    
    return result;
}

int push(char *stack, int *sp, char value)
{
    stack[++(*sp)] = value;
    return 1;
}

int solution(char *S) {
    int N = strlen(S);
    int i, j;
    int result = 1; // default to true in case string is empty
    char *S2 = calloc(N, sizeof(char));
    int sp = -1; // init to -1 so that first push goes to element 0
    
    for (i = 0; i < N && result == 1; i++)
    {
        for (j = 0; MAP[j].open != '\0'; j++)
        {
            if (S[i] == MAP[j].open)
                result = push(S2, &sp, S[i]);
            else if (S[i] == MAP[j].close)
                result = pop(S2, &sp, S[i]);
        }
    }
    
    if (sp != -1) // if stack is not fully popped, there were unmatched open brackets
        result = 0;
    
    free(S2);
    return result;
}
