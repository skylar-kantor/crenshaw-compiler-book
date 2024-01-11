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
    printf("\n%s\n", s);
}

void fatal(char *s)
{
    error(s);
    exit(1);
}

void expected(char *s)
{
    char *out = malloc((strlen(s) + 1) * sizeof(char));
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

void factor(void)
{
    char result[100];
    sprintf(result, "mov ebx, %c", get_num());
    emitln(result);
}

void multiply(void)
{
    match('*');
    factor();
    emitln("pop ecx");
    emitln("mul ebx, ecx");
}

void divide(void)
{
    match('/');
    factor();
    emitln("pop ecx");
    emitln("div ecx, ebx");
}

void term(void)
{
    factor();
    while (look == '*' || look == '/')
    {
        emitln("push ebx");
        if (look == '*')
        {
            multiply();
        }
        else if (look == '/')
        {
            divide();
        }
        else
        {
            expected("Mulop");
        }
        
    }
}

void add()
{
    match('+');
    term();
    emitln("pop ecx");
    emitln("add ebx, ecx");
}

void subtract()
{
    match('-');
    term();
    emitln("pop ecx");
    emitln("sub ebx, ecx");
    emitln("neg ebx");
}

void expression(void)
{
    term();
    while (look == '+' || look == '-')
    {
        emitln("push ebx");
        if (look == '+')
        {
            add();
        }
        else if (look == '-')
        {
            subtract();
        }
        else
        {
            expected("Addop");
        }
    }
}

int main()
{
    init();
    expression();
    return 0;
}
