/*
此项目
1. 通过将用户输入的中缀表达式转换为后缀表达式
2. 计算后缀表达式的值来实现简单的计算器功能

注意：
1. 一切计算都是在假定用户输入格式正确的情况下进行的，如果输入的格式不是严格的中缀表达式，谁知道会发生什么
2. 支持的运算符：+、 -、 *、 /、 =（=代表运算的结束）以及（、）
3. 支持的数据类型：双精度浮点类型（注意不可以将0.3写成.3，但是可以将3.0写成3.）
4. 栈大小：1000*sizeof(char)，浮点数组大小：1000*sizeof(double)，用户需保证输入的计算式不会超出两者的限制，否则谁知道会发生什么
5. 用户输入的数据中可以在任意地方放入空白字符，比如用户输入1+1=或者1 + 1 = 都可以得到正确的结果
6. 所有运算都是浮点运算，所以最终结果可能与实际结果有微小的差异，但这也是不可避免的……，最终的运算结果输出形式与最终结果有关，有可能为E型或浮点型

项目分工：
- 架构设计及实现：徐震
- 主函数设计及实现：徐震
- stack.h设计及实现：徐震
- 部分stack.c函数设计及实现：徐震
- stack.c主体设计及实现：付仁泓
- 项目总体调试及初步测试运行：徐震
- 简单函数计算功能设计及实现：陈九润（待完成）
*/

#include <stdio.h>
#include <ctype.h>
#include <math.h> //现阶段还没用到函数
#include "stack.h"

int main()
{
    Stack infix = create();
    Stack postfix = create();
    double num[MAXSTACKSIZE] = {0}; //num数组用于储存读入的数字
    int cnt = 0;                    //cnt代表num的index

    //读入数据并直接转换为后缀表达式
    char ch;
    while ((ch = getchar()) != '=')
    {
        if (isspace(ch)) //跳过空格
            continue;
        switch (ch)
        {
        case '*':
        case '/':
        case '(':
            push(infix, ch); //低优先级的运算符直接压栈到infix
            break;
        case '+':
        case '-':
            while (peek(infix) == '*' || peek(infix) == '/')
                push(postfix, pop(infix)); //高优先级的运算符先将infix中低优先级的出栈到postfix再压栈到infix
            push(infix, ch);
            break;
        case ')':
            while (peek(infix) != '(') //将infix中的运算符出栈，直到遇到'('，注意'('也要出栈，但不进入postfix
                push(postfix, pop(infix));
            pop(infix);
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
            scanf("%lf", &num[cnt++]); //利用一个额外的数组进行数字的储存，以便double类型的实现，cnt是该数组的指针（也可以用栈直接进行实现）
            push(postfix, -cnt + 1);   //遇到数字直接进postfix
            break;
        }
    }
    while (peek(infix) != '0') //倒序postfix剩余元素进infix
        push(postfix, pop(infix));

    //计算结果
    double re; //用于储存每一次的结果
    int index = 0;
    double num1, num2;
    while ((ch = peekmid(postfix, index++)) != '0')
    {
        if (isspace(ch)) //跳过空格
            continue;
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
    printf("%.6g\n", num[-pop(infix)]); //输出infix的最后结果
    destroy(infix);
    destroy(postfix);
}