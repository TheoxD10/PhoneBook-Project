#include <stdio.h>
#include <stdlib.h>

char s[101];

int main()
{
    FILE *f = fopen("contact_list.in","r");

    while(fscanf(f, "%s", &s) == 1)
    {
        printf("%s\n",s);
    }
    return 0;
}