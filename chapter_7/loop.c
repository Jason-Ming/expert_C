#include <stdio.h>
#include <unistd.h>

void main()
{
    int count = 0;

    while(1)
    {
        printf("I'm alive! %d.\n", count++);
        sleep(3);
    }
}

