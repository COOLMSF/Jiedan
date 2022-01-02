#include <stdio.h>
int main()
{
    char str[80];
    int i, w = 0;
    printf("Enter a string: ");

    // format input
    scanf("%[^\n]",str);

    for (i = 0; str[i] != '\0'; i++)
    {
        // get word
        if((str[i]!=' ' && str[i+1]==' ')||(str[i+1]=='\0' && str[i]!=' '))
        {
            // counter add
            w++;
        }
        
    }
    printf("The number of words = %d", w );

    return 0;
}
