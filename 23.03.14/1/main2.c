#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void stringify(int n, char t[10])
{
    int dim = 0;

    while(n)
    {
        t[dim++] = n % 10 + '0';
        n /= 10;
    }
    t[dim] = '\0';

    return;
}

void printStringWithoutIndex(t, i)
{

}
void removeDigit(int n)
{
    char t[10];
    stringify(n, t);
    
    int firstIndexFound = -1;

    for(int i = 1; i < strlen(t); ++i)
    {
        if(t[i - 1] < t[i])
        {
            
        }
    }

}
int main()
{
    int n;
    scanf("%d", &n);

    removeDigit(n);
}