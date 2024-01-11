#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
char look = '\0';


void getch(void) 
{
    look = getchar();
}
void error(char *s)
{
    printf("\n%s.", s);
}

void fatal(char *s)
{
    error(s);
    exit(1);
}

void expected(char *s)
{
    char *out = malloc((strlen(s)+1)*sizeof(char));
    sprintf(out, "%s expected", s);
    fatal(out);
}

void match(char x)
{
    if (look == x)
    {
        getch(); /*Not getchar, but using the lookahead*/
    }
    else
    {
        expected(&x);
    }
}

char get_name(void) 
{
    if (!isalpha(look))
    {
        expected("name");
    }
    char new_name = look;
    getch();
    return new_name;
}

char get_num(void) 
{
    if (!isdigit(look))
    {
        expected("Integer");
    }

    char new_number = look;
    getch();
    return new_number;
}

void emit(char *s)
{
    printf("\t%s", s);
}

void emitln(char *s)
{
    emit(s);
    printf("\n");
}

void init(void)
{
    getch();
}

int main()
{
    init();
    return 0;
}
