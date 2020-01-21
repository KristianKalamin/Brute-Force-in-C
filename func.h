#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

char *createPass(int len)
{
    char *password = (char *)malloc(len * sizeof(char) + 1);
    time_t t;
    srand((unsigned)time(&t));
    int i;
    for (i = 0; i < len; i++)
        password[i] = rand() % 26 + 'A';

    password[i] = 0;
    return password;
}

char *createBreakString(int len)
{
    char *breakString = (char *)malloc(len * sizeof(char));
    int i;
    for (i = 0; i < len; i++)
    {
        breakString[i] = 'Z';
    }
    breakString[i] = 0;
    return breakString;
}

char *stepUp(char *bruteForce, int len)
{
    int i = len - 2;
    if (bruteForce[i] < (int)'Z')
    {
        bruteForce[i]++;
    }
    else if (bruteForce[i] == (int)'Z')
    {
        int b = 1;
        int j = i;
        while (b)
        {
            if (bruteForce[j] < (int)'Z')
            {
                bruteForce[j]++;
                b = 0;
            }
            else
            {
                bruteForce[j] = 'A';
            }
            j--;
        }
    }
    return bruteForce;
}
