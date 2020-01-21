#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "func.h"

typedef struct param
{
    char *pass;
    char firstChar;
} Params;

int len = 5;

DWORD WINAPI BruteForce(LPVOID lpParams)
{
    Params *params = (Params *)lpParams;
    char firstChar;
    char *pass = (char *)malloc(len * sizeof(char) + 1);
    char *breakString = (char *)malloc(len * sizeof(char));
    firstChar = params->firstChar;
    strcpy(pass, params->pass);
    printf("%c\n", firstChar);
    char *bruteForce = (char *)malloc(len * sizeof(char) + 1);
    char *p;
    bruteForce[0] = (char)firstChar;
    for (int i = len - 1; i > 0; i--)
    {
        bruteForce[i] = 'A';
    }
    bruteForce[len] = '\0';
    breakString = createBreakString(len - 1);
    while (1)
    {
        int i = len - 1;

        bruteForce[i]++;
        if (strcmp(pass, bruteForce) == 0)
        {
            printf("Found password is: %s", bruteForce);
            exit(0);
        }

        p = strstr(bruteForce, breakString); //"ZZZ"
        if (p != NULL)
        {
            printf("Break -- End of thread\n");
            break;
        }

        if ((int)bruteForce[i] == (int)'Z')
        {
            bruteForce = stepUp(bruteForce, len);
            bruteForce[i] = 'A';
        }
    }
    return 0;
}

int main()
{
    Params *params = (Params *)malloc(sizeof(Params));
    params->pass = (char *)malloc(len * sizeof(char) + 1);
    char *pass = (char *)malloc(len * sizeof(char) + 1);
    pass = createPass(len);
    strcpy(params->pass, pass);

    printf("Passoword is: %s\n", pass);
    int nThreads='Z'-'A'+1;
    DWORD threadId[nThreads];
    HANDLE thread[nThreads];
    int firstChar = 65;
    int i = 0;
    for (i = 0; i < nThreads; i++)
    {
        params->firstChar = (char)(i + 65);
        thread[i] = CreateThread(
            NULL,
            0,
            BruteForce,
            (LPVOID)params,
            0,
            &threadId[i]);
        Sleep(200);
    }

    WaitForMultipleObjects(nThreads, thread, TRUE, INFINITE);
    for (int i = 0; i < nThreads; i++)
        CloseHandle(thread[i]);
    free(params);
    free(pass);

    return 0;
}
