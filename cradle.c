#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
char look = '\0';

void getch()
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

char get_name()
{
    if (!isalpha(look))
    {
        expected("name");
    }
    char new_name = look;
    getch();
    return new_name;
}

char get_num()
{
    if (isdigit(look) == 0)
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

void init()
{
    getch();
   
}

void add()
{
    match('+');
    term();
    //emitln("pop rcx");
    emitln("a = a + b;");
}

void subtract()
{
    match('-');
    term();
    emitln("a = a - b;");
    emitln("a *= -1;");
}
int is_addop(char c)
{
    if (c == '-' || c == '+')
    {
        return 1;
    }
    return 0;
}
void expression()
{
    if (is_addop(look) == 1)
    {
        emitln("CLR D0");
    }
    else
    {
        term();
    }

    while (is_addop(look) == 1)
    {
        emitln("b = a;");
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

void assignment()
{
    char name = get_name();
    match('=');
    expression();
    char output[100];
    sprintf(output, "int %c = a;", name);
    emitln(output);
}

void factor()
{
    char result[100];
    if (look == '(')
    {
        match('(');
        expression();
        match(')');
    }
    else
    {
        sprintf(result, "a = %c;", get_num());
        emitln(result);
    }
}

void term()
{
    factor();
    while (look == '*' || look == '/')
    {
        emitln("b = a;");
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

void multiply()
{
    match('*');
    factor();
    emitln("a = a * b;");
}

void divide()
{
    match('/');
    factor();
    emitln("a = b / a;");
}

int main()
{
    init();
    emitln("int main(){");
    emitln("int a = 0;");
    emitln("int b = 0;");
    assignment();
    emitln("return 0;");
    emitln("}");
    if (look != '\n')
    {
        expected("Newline");
    }

    return 0;
}
