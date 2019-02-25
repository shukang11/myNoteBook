#include <stdio.h>

int sumZeroToMaxFunc(int max) {
    int sum = 0;
    for(int i = 0; i <= max; i++)
    {
        sum += i;
    }
    return sum;
}

int main(int argc, char const *argv[])
{
    int x = sumZeroToMaxFunc(100);
    printf("%d", x);
    return 0;
}

