#include <stdio.h>
#include <stdlib.h>

int STRLEN (char *s)
{
    unsigned count = 0;
    while (*s++) {
        count++;
    }
    return count;
}

int STRCMP (char *s1, char *s2)
{
    while (*s1 == *s2 && *s1) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

int STRCMPR (char *s1, char *s2, int r)
{
    int i = 0;
    while (*s1 == *s2 && *s1 && ++i != r) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

char *STRCPY (char *s1, const char *s2) //копировать
{
    while ((*s1++ = *s2++) != 0);
    return s1;
}

char *STRCAT (char *s1, const char *s2) //копировать
{
    char *s = s1;
    while (*s++);
    while (*s2++){
        *s = *s2;
        s++;
        s2++;
    }
    return s1;
}

char *STRCHR (const char *s, int c)
{
    char *s1 = 0;
    while (*s++) {
        s1 = (char *) s;
    }
    return s1;
}

int main(void)
{
    char s[100];
    char *s1 = "wersgsrydh";
    char s2[100] = "wers";
    printf ("%d\n", STRLEN("frtwgyedhs"));
    printf ("%d\n", STRCMP("rfdqcdd", "tgyahs"));
    printf ("%d\n", STRCMPR("rfdqcdd", "rfdqjgtr", 4));
    STRCPY(s, s1);
    printf ("%s\n", s);
    char *s3 = STRCAT(s2, s);
    printf ("%s\n", s3);
    printf ("%s\n", STRCHR("wefrefdg", 'w'));
    return 0;
}
