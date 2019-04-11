#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAXSTACKSIZE 10000 //用于创建栈和double数组

//用于清空以保守的方式清空stdin
#define CLEARSTDIN                                    \
    {                                                 \
        int ch;                                       \
        while ((ch = getchar()) != '\n' && ch != EOF) \
            ;                                         \
    }

typedef struct _Stack
{
    char array[MAXSTACKSIZE];
    int top; //栈顶index
} * Stack;

Stack create(void);             //初始化栈（array和top都变为零）
char pop(Stack stack);          //栈为空时返回'0'
void push(Stack stack, char c); //达到最大值后报错并结束程序
char peek(Stack stack);         //栈为空时返回'0'
void destroy(Stack stack);      //清空该栈的内容（其实没啥用因为C里面没有对象或者析构函数）
char peekmid(Stack stack, int index);
double npl(void);

int wrong;
double output;

int main()
{
    while (1)
    {
        do
        {
            wrong = 0;
            output = npl();
            CLEARSTDIN
        } while (wrong);
        printf("%g\n", output);
    }
}

Stack create(void)
{
    Stack S;
    S = (Stack)malloc(sizeof(*S));
    int i = 0;
    S->top = 0;
    return S;
}

char pop(Stack stack)
{
    if (stack->top == 0)
        return '0';
    else
    {
        char a = stack->array[--stack->top];
        return a;
    }
}

void push(Stack stack, char c)
{
    if (stack->top == MAXSTACKSIZE - 1)
    {
        printf("Stack is FULL");
        exit(1);
    }
    else
        stack->array[stack->top++] = c;
}

char peek(Stack stack)
{
    if (stack->top <= 0)
        return '0';
    else
    {
        return stack->array[stack->top - 1];
    }
}

void destroy(Stack stack)
{
    free(stack);
    stack = NULL;
}

char peekmid(Stack stack, int index)
{
    if (index >= stack->top)
        return '0';
    return stack->array[index];
}

double func()
{
    //读入用于表达函数的字符串
    char ch = getchar();
    if (isdigit(ch))
    {
        double re;
        ungetc(ch, stdin);
        scanf("%lf", &re);
        return re;
    }
    else if (isalpha(ch))
    {
        char c;
        int i = 0;
        char temp[MAXSTACKSIZE];
        while (!wrong && isalpha(c = getchar()))
        {
            temp[i++] = ch;
            ch = c;
        }
        temp[i++] = ch;
        temp[i] = 0;

        if (!strcmp(temp, "pi") || !strcmp(temp, "PI") || !strcmp(temp, "Pi"))
        {
            ungetc(c, stdin);
            return 3.1415926535;
        }
        if (!strcmp(temp, "e"))
        {
            ungetc(c, stdin);
            return 2.71828;
        }
        if (!strcmp(temp, "ANS") || !strcmp(temp, "Ans") || !strcmp(temp, "ans"))
        {
            ungetc(c, stdin);
            return output;
        }

        if (wrong)
            return 1;

        //跳过空格
        while (isspace(c))
            c = getchar();

        double tempNum;
        //确定function应该计算的值是什么（这里会发生一系列函数的多次递归）
        if (c != '(') //上面的getchar读入了空格后面的一个东西
        {
            ungetc(c, stdin);
            tempNum = func();
        }
        else
            tempNum = npl();
        if (wrong)
            return 1;
        //这一段算灵活性比较高的，想要的话甚至可以把能调用的系统里所有的计算型的double函数都添加进去
        //如果用比较高级的方式，比如哈希表？或许会大幅度提高性能？或者考虑函数指针，用switch建立类似的哈希表？但这里包含的函数实在太少……利用哈希表提高的性能或许还满足不了complexity的常数项对性能的拖累
        //对于pow这种函数，有两个参数，不会出现后面不加括号的情况
        if (!strcmp(temp, "pow"))
        {
            double
                temp1 = tempNum,
                temp2 =
                    npl(); //最好不要直接在pow函数中调用两个npl，执行顺序是个变数。
            return pow(temp1, temp2);
        }
        else if (!strcmp(temp, "sin"))
            return sin(tempNum);
        else if (!strcmp(temp, "cos"))
            return cos(tempNum);
        else if (!strcmp(temp, "sqrt"))
            return sqrt(tempNum);
        else if (!strcmp(temp, "fabs"))
            return fabs(tempNum);
        else if (!strcmp(temp, "tan"))
            return tan(tempNum);
        else if (!strcmp(temp, "atan"))
            return atan(tempNum);
        else if (!strcmp(temp, "asin"))
            return asin(tempNum);
        else if (!strcmp(temp, "acos"))
            return acos(tempNum);
        else if (!strcmp(temp, "exp"))
            return exp(tempNum);
        else if (!strcmp(temp, "log"))
            return log(tempNum);
        else if (!strcmp(temp, "floor"))
            return floor(tempNum);
        else
        {
            printf("Bad input. Try again.\n");
            CLEARSTDIN
            wrong = 1;
            return 1;
        }
    }
    return 1; //这种情况一般不会发生。
}

double npl()
{
    Stack infix = create();
    Stack postfix = create();
    double num[MAXSTACKSIZE] = {0}; // num数组用于储存读入的数字
    int cnt = 0;                    // cnt代表num的index

    //读入数据并直接转换为后缀表达式
    char ch;

    int flag = 1;
    int flag2 = 0;
    int prefix = 1;
    while ((!wrong && flag && (ch = getchar()) != '='))
    {
        if (isspace(ch)) //跳过空格
            continue;
        if (isalpha(ch))
        {
            ungetc(ch, stdin);
            num[cnt++] = func();
            push(postfix, -cnt + 1);
            continue;
        }
        switch (ch)
        {
        case '*':
        case '/':
            push(infix, ch); //高优先级的运算符直接压栈到infix
            break;
        case '(':
            prefix = 0;
            push(infix, ch); //低优先级的运算符直接压栈到infix
            flag2 = 1;       // flag2用于判断是否处于合法的括号当中（便于递归函数的实现）
            break;
        case '+':
            while (peek(infix) == '*' || peek(infix) == '/')
                push(postfix, pop(infix)); //低优先级的运算符先将infix中高优先级的出栈到postfix再压栈到infix
            push(infix, ch);
            break;
        case '-':
            if (prefix)
            {
                ungetc(ch, stdin);
                scanf("%lf", &num[cnt++]); //利用一个额外的数组进行数字的储存，以便直接利用scanf读入double类型功能的实现，cnt是该数组的指针（也可以用栈直接进行实现）
                push(postfix, -cnt + 1);   //遇到数字直接进postfix
                break;
            }
            while (peek(infix) == '*' || peek(infix) == '/')
                push(postfix, pop(infix)); //低优先级的运算符先将infix中高优先级的出栈到postfix再压栈到infix
            push(infix, ch);
            break;
        case ')':
            if (flag2)
            {
                while (peek(infix) != '(') //将infix中的运算符出栈，直到遇到'('，注意'('也要出栈，但不进入postfix
                    push(postfix, pop(infix));
                pop(infix);
                flag2 = 0;
            }
            else
                flag = 0;
            break;
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
            ungetc(ch, stdin);
            scanf("%lf", &num[cnt++]); //利用一个额外的数组进行数字的储存，以便直接利用scanf读入double类型功能的实现，cnt是该数组的指针（也可以用栈直接进行实现）
            push(postfix, -cnt + 1);   //遇到数字直接进postfix
            break;

        case ',':
            flag = 0;
            break;
        default:
            //输入格式有误，清空所有堆栈
            printf("Bad input. Try again.\n");
            CLEARSTDIN
            wrong = 1;
            break;
        }
        prefix = 0;
    }

    if (wrong)
        return 1;

    while (peek(infix) != '0') //倒序postfix剩余元素进infix
        push(postfix, pop(infix));

    //计算结果
    double re; //用于储存每一次的结果
    int index = 0;
    double num1, num2;
    while ((ch = peekmid(postfix, index++)) != '0')
    {
        if (ch <= 0) //数字直接压栈到infix
        {
            push(infix, ch);
            continue;
        }
        switch (ch) //对postfix加减乘除直接进行运算，并将运算结果压栈到infix
        {
        case '+':
            re = num[-pop(infix)] + num[-pop(infix)];
            num[cnt++] = re;
            push(infix, -cnt + 1);
            break;
        case '-':
            num1 = num[-pop(infix)];
            num2 = num[-pop(infix)];
            re = num2 - num1;
            num[cnt++] = re;
            push(infix, -cnt + 1);
            break;
        case '*':
            re = num[-pop(infix)] * num[-pop(infix)];
            num[cnt++] = re;
            push(infix, -cnt + 1);
            break;
        case '/':
            num1 = num[-pop(infix)];
            num2 = num[-pop(infix)];
            re = num2 / num1;
            num[cnt++] = re;
            push(infix, -cnt + 1);
            break;
        }
    }
    double result = num[-pop(infix)]; //输出infix的最后结果
    destroy(infix);
    destroy(postfix);
    wrong = 0;
    return result;
}