

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

// GAME 1 -- BROKEN CALCULATOR  (By HARSHVARDHAN [2201EE30] & LAKSHYA SINGH [2201CE30])

typedef struct stack1 // creating stack1 for postfix conversion
{
    char arr[35];
    int top;
} st1;

void push1(st1 *s, char item)
{
    s->arr[++s->top] = item;
}
char pop1(st1 *s)
{
    return s->arr[s->top--];
}

typedef struct stack2 // creating stack for postfix solving
{
    int arr[35];
    int top;
} st2;

void push2(st2 *s, int item)
{
    s->arr[++s->top] = item;
}

int pop2(st2 *s)
{
    s->top--;
    return s->arr[s->top + 1];
}

int prec(char a) // function for precedence
{
    if (a == '+' || a == '-')
        return 0;
    if (a == '*' || a == '/')
        return 1;
    if (a == '^')
        return 2;
    if (a == '(')
        return -1;
}

char *infixtopostfix(char a[], char arr[])
{
    st1 sck1;
    st1 *stack1 = &sck1; // stack1 for expressison conversion
    stack1->top = -1;    // initializing staack
    int index = 0;

    for (int i = 0; i < 100 && a[i] != '\0'; i++)
    {
        switch (a[i])
        {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
        {
            arr[index++] = a[i];
            break;
        }

        case '*':
        case '/':
        case '+':
        case '-':
        {
            if (stack1->arr[stack1->top] == '(')
            {
                push1(stack1, a[i]);
                break;
            }
            while (prec(a[i]) <= prec(stack1->arr[stack1->top]) && stack1->top != -1)
            {
                arr[index++] = pop1(stack1);
            }
            push1(stack1, a[i]);
            break;
        }

        case '(':
        case '^':
        {
            push1(stack1, a[i]);
            break;
        }

        case ')':
        {
            while (stack1->arr[stack1->top] != '(')
            {
                arr[index++] = pop1(stack1);
            }
            pop1(stack1);
            break;
        }
        }
    }
    while (stack1->top != -1)
        arr[index++] = pop1(stack1);

    return arr;
}

int postfixsolve(char *a)
{
    st2 sck2;
    st2 *stack2 = &sck2; // stack2 for solving expression
    stack2->top = -1;    // initializing stack

    for (int i = 0; i < 100 && a[i] != '\0'; i++)
    {
        switch (a[i])
        {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
        {
            push2(stack2, a[i] - 48);
            break;
        }

        case '+':
        {
            push2(stack2, (pop2(stack2) + pop2(stack2)));
            break;
        }
        case '*':
        {
            push2(stack2, (pop2(stack2) * pop2(stack2)));
            break;
        }
        case '-':
        {
            int a = pop2(stack2);
            push2(stack2, (pop2(stack2) - a));
            break;
        }
        case '/':
        {
            int a = pop2(stack2);
            push2(stack2, (pop2(stack2) / a));
            break;
        }
        case '^':
        {
            int a = pop2(stack2);
            push2(stack2, (int)pow(pop2(stack2), a));
            break;
        }
        }
    }
    return stack2->arr[stack2->top];
}

int notincheck(char a, char arr[])
{
    int flag = 1;
    for (int j = 0; j < strlen(arr); j++)
    {
        if (a == arr[j])
        {
            flag = 0;
            break;
        }
    }
    return flag;
}
// LEVELS

int source(int numbers[], int elements, char operands[], char operators[], int level)
{
    char both[15];
    strcat(both, operands);
    strcat(both, operators);
    int result = 0;
    char *expression;
    char *postexpression;

    while (elements != 0)

    {
        expression = (char *)malloc(200);
        postexpression = (char *)malloc(200);
        printf("\n \033[1;34m     [         \033[0m");
        printf("\033[1;33m%d\033[0m", result);
        printf("\033[1;34m         ]\033[0m", result); // Format
        printf("\n\n\n\033[1;36m      Numbers Avaialable\033[0m \033[1;34m :\033[0m  ");
        for (int i = 0; i < strlen(operands); i++)
            printf("\033[1;35m  %c  \033[0m", operands[i]);
        printf("\n\n\n ");
        printf("\033[1;36m     Operators Available\033[0m \033[1;34m: \033[0m  ");
        for (int i = 0; i < strlen(operators); i++)
            printf("\033[1;35m  %c  \033[0m", operators[i]);
        printf("   \n\n\n ");
        printf(" \033[1;36m    Numbers remaining\033[0m \033[1;34m : \033[0m  \033[1;35m");

        for (int i = 0; i < elements; i++)
        {
            printf(" %d  ", numbers[i]);
        }
        printf("\033[0m\n\n\n\033[1;36m      ENTER your expresssion\033[0m \033[1;32mpress c to confirm/clear\033[0m \033[1;34m : \033[0m ");
        scanf("%s", expression);
        system("cls");

        if (expression[0] == 'c')
        {
            for (int i = 0; i < elements; i++)
            {
                if (result == numbers[i])
                {
                    for (int j = i; j < elements - 1; j++)
                        numbers[j] = numbers[j + 1];
                    elements--;
                }
            }
            result = 0;
            // free(expression);
        }
        else
        {
            int flag1 = 0;
            for (int i = 0; i < strlen(expression); i++)
            {
                if (notincheck(expression[i], both))
                {
                    flag1 = 1;
                    break;
                }
            }
            if (flag1 == 1)
            {
                printf("\033[1;31m      INVALID OPERATOR or OPERAND\033[0m\n");
                // free(expression);
            }
            else
            {
                result = postfixsolve(infixtopostfix(expression, postexpression));
            }
        }
    }
}

void level1()
{
    int numbers[] = {6, 18, 12, 29, 43, 91};
    int elements = 6;
    int level = 1;
    char operands[5] = "23";
    char operator[5] = "+*";
    source(numbers, elements, operands, operator, level);
    printf(" \n\n\n\n YOu have passed level %d \n\n\n", level);
}

void level2()
{
    int numbers[] = {3, 19, 41, 99, 200};
    int elements = 5;
    int level = 2;
    char operands[5] = "457";
    char operator[5] = "-*/";
    source(numbers, elements, operands, operator, level);
    printf(" \n\n\n\n YOu have passed level %d \n\n\n", level);
}
void level3()
{
    int numbers[] = {21, 69, 146, 169, 231};
    int elements = 5;
    int level = 3;
    char operands[9] = "256";
    char operator[8] = "+-*()";
    source(numbers, elements, operands, operator, level);
    printf(" \n\n\n\n YOu have passed level %d \n\n\n", level);
}
void level4()
{
    int numbers[] = {69, 97, 294, 784, 3969};
    int elements = 5;
    int level = 4;
    char operands[9] = "237";
    char operator[9] = "+-^()";
    source(numbers, elements, operands, operator, level);
    printf(" \n\n\n\n YOu have passed level %d \n\n\n", level);
}

int main()
{

    printf(" \n\n\n\n \033[1;34mSam's calculator got smashed , but some of it still works.\033[0m\n");
    printf(" \033[1;34mCan you help Sam get the answers?\033[0m\n\n\n");

    int n;
    printf("\033[1;35m Enter lever 1 - 4 : \033[0m");
    scanf("%d", &n);
    system("cls");
    do
    {
        switch (n)
        {
        case 1:
        {
            level1();
            break;
        }
        case 2:
        {
            level2();
            break;
        }
        case 3:
        {
            level3();
            break;
        }
        case 4:
        {
            level4();
            break;
        }
        }
        printf("\033[1;35mwanna play other level ? (Enter it or enter 0 to quit ) : \033[0m");
        scanf("%d", &n);
    } while (n);
}
