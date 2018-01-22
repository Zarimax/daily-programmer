// C99 (gcc 7.2.0)

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// slow test - baseline
int slow_branches = 0;
int slow_solution(int X[], int Y[], int N, char *T);
int slow_find_capture_value(int X[], int Y[], int N, char *T, int x, int y);
int slow_search(int X[], int Y[], int N, char *T, int x, int y, int dir, int ceiling, int capture_score);

// fast test - challenge problem
int fast_solution(int X[], int Y[], int N, char *T);

/***********************************************************/

void TEST(char *test_name, int *X, int *Y, char *T)
{
    int slow = slow_solution(X, Y, strlen(T), T);
    int fast = fast_solution(X, Y, strlen(T), T);
    char result[4 + 1];

    if (slow == fast)
        strcpy(result, "pass");
    else
        strcpy(result, "FAIL");

    printf("%s: received %02d (expected %02d) -- %s\n",
            test_name, fast, slow, result);
    printf("%d branches explored in the slow solution\n\n", slow_branches);
    slow_branches = 0; // reset
}

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

int main(int argc, char **argv)
{
    int  T01_X[] = {3, 5, 1, 6};
    int  T01_Y[] = {1, 3, 3, 8};
    char T01_T[] = "Xpqp";
    
    int  T02_X[] = {0, 3, 5, 1, 6};
    int  T02_Y[] = {4, 1, 3, 3, 8};
    char T02_T[] = "pXpqp";
    
    int  T03_X[] = {0, 6, 2, 5, 3, 0};
    int  T03_Y[] = {4, 8, 2, 3, 1, 6};
    char T03_T[] = "ppqpXp";
    
    // no captures - queen positioned above all other pieces
    int  T04_X[] = {3, 5, 1, 6};
    int  T04_Y[] = {9, 3, 3, 8};
    char T04_T[] = "Xpqp";
    
    // no captures - no other pieces
    int  T05_X[] = {3};
    int  T05_Y[] = {1};
    char T05_T[] = "X";
    
    int  *random_X;
    int  *random_Y;
    char *random_T;
    int random_array_size;
    int random_density;
    bool player_placed = false;
    
    /* Intializes random number generator */
    #define RANDOM_SCALE 100
    srand(time(0));
    random_array_size = rand_interval(1, RANDOM_SCALE);
    random_density = rand_interval(1, 2);
    random_density *= RANDOM_SCALE;
    
    random_X = calloc(random_array_size, sizeof(int));
    random_Y = calloc(random_array_size, sizeof(int));
    random_T = calloc(random_array_size + 1, sizeof(char));
    
    printf("... building random game board with (%d) pieces at density (%d)\n", random_array_size, random_density);
    for (int i = 0; i < random_array_size; i++)
    {
        int x, y, p;
        char c;

        do {
            // set random y
            y = rand_interval(0, random_density);
        
            // set random x based on y
            x = rand_interval(0, random_density);
            // if y is even, x must be even
            // if y is odd, x must be odd
            while ((y % 2 == 1 && x % 2 == 0) || (y % 2 == 0 && x % 2 == 1))
                x = rand_interval(0, random_density);
        
            // if there is already a piece in this location, we cant place it
        } while (slow_find_capture_value(random_X, random_Y, random_array_size, random_T, x, y) != 0);
            
        // set random piece value
        if (player_placed) // do not place the player piece twice
            p = rand_interval(1, 2);
        else
            p = rand_interval(1, 3);
        
        switch(p)
        {
            case 1:
                c = 'p';
                break;
            case 2:
                c = 'q';
                break;
            case 3:
                c = 'X';
                player_placed = true;
                break;
        }
        
        random_X[i] = x;
        random_Y[i] = y;
        random_T[i] = c;
        printf("placed %c on (%d,%d)\n", c, x, y);
    }
    printf("... game board complete\n");
    
    // ************ START TESTS ************
    TEST("T01", T01_X, T01_Y, T01_T);
    TEST("T02", T02_X, T02_Y, T02_T);
    TEST("T03", T03_X, T03_Y, T03_T);
    TEST("T04", T04_X, T04_Y, T04_T);
    TEST("T05", T05_X, T05_Y, T05_T);
    TEST("R01", random_X, random_Y, random_T);
    // ************ FINISH TESTS ************
    
    free(random_X);
    free(random_Y);
    free(random_T);
    
    return 0;
}

/***********************************************************/
int slow_find_capture_value(int X[], int Y[], int N, char *T, int x, int y)
{
    int capture_score = 0;
    
    for (int i = 0; i < N; i++)
    {
        if (X[i] == x && Y[i] == y)
        {
            switch(T[i])
            {
                case 'p':
                    capture_score = 1;
                    break;
                case 'q':
                    capture_score = 10;
                    break;
            }
            break; // out of for loop
        }
    }
    
    return capture_score;
}

int slow_search(int X[], int Y[], int N, char *T, int x, int y, int dir, int ceiling, int capture_score)
{
        bool did_capture = false;
        int M=0, B=0, best_branch=0;
        
        slow_branches++; // increment global branch count
        
        while (y < ceiling) // while below ceiling, move in specified direction
        {
            y++;
            x += dir;
        
            // is there a piece here?
            M = slow_find_capture_value(X, Y, N, T, x, y);
            if (M > 0)
            {
                // can i get behind it?
                if (slow_find_capture_value(X, Y, N, T, x+dir, y+1) == 0)
                {
                    // yes - i can get behind it. capture this piece
                    capture_score += M;
                    did_capture = true;
                    y++;
                    x += dir;
                }
                else // there is a blocking piece beind it - this branch is dead
                    break; // break out of while loop
            }

            if (did_capture) // start a search on the perpendicular axis
                B = slow_search(X, Y, N, T, x, y, dir * -1, ceiling, capture_score);
            
            if (B > best_branch)
                best_branch = B;
        }
        
        if (best_branch > capture_score)
            capture_score = best_branch;
        
        return capture_score;
}

int slow_solution(int X[], int Y[], int N, char *T)
{
    int result=0, x=0, y=0, ceiling=0;

    for (int i = 0; i < N; i++)
    {
        // find ceiling, (max Y)
        if (Y[i] > ceiling)
            ceiling = Y[i];
        
        // find coordinates of queen piece 'X'
        if (T[i] == 'X')
        {
            x = X[i];
            y = Y[i];
        }
    }

    // left  = x-1, y+1
    // right = x+1, y+1

    // sum score of captures on left axis up to ceiling
    int L = slow_search(X, Y, N, T, x, y, -1, ceiling, 0);
    // sum score of captures on right axis up to ceiling
    int R = slow_search(X, Y, N, T, x, y, 1, ceiling, 0);
    
    // greatest score wins
    result = (L > R ? L : R);
    
    return result;
}

int fast_solution(int X[], int Y[], int N, char *T)
{
    int result = 0;
    
    return result;
}
