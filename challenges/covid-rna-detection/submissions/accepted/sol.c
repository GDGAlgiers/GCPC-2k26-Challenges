#include <stdio.h>
#include <string.h>

int main(void)
{
    char rna[1010];
    scanf("%1009s", rna);

    const char *markers[] = {"ACGUAUGC", "AUGCGUAG", "UGCUAGCU"};
    for (int i = 0; i < 3; i++)
    {
        if (strstr(rna, markers[i]) != NULL)
        {
            printf("True\n");
            return 0;
        }
    }
    printf("False\n");
    return 0;
}
