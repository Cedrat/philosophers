#include "philosophers.h"

typedef struct test
{
    int vide;
    int i;
}test;

void * i_pair(void * in)
{
    int *i;
    test *yo;

    yo = (test *) in;
    i =  &yo->i;
    while (*i < 100)
    {
        if ((*i % 2))
        {
            (*i)++;
            printf("pair = %d\n", *i);
        }
    }
    return ((void *) 1);
}

void * i_impair(void * in)
{
    int *i;
    test *yo;

    yo = (test *) in;
    i =  &yo->i;
    while (*i < 100)
    {
        if ((*i % 2) == 0)
        {
            (*i)++;
            printf("impair = %d\n", *i);
        }
    }
    return ((void *) 1);
}

int main()
{
    test yo;
    yo.i = 98;
    // i = malloc(sizeof(int));
    pthread_t impair;
    pthread_t pair;

    pthread_create(&impair, NULL, i_impair, (void *)&yo);
    pthread_create(&pair, NULL, i_pair, (void *)&yo);
    while (1)
    ;
}