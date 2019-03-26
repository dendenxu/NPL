#include <stdio.h>
#include <ctype.h>
#include <math.h> //�ֽ׶λ�û�õ�����
#include "stack.h"

int main()
{
    Stack infix = create();
    Stack postfix = create();
    double num[MAXSTACKSIZE] = {0}; //num�������ڴ�����������
    int cnt = 0;                    //cnt����num��index

    printf("I'm fine now.\n");
    //�������ݲ�ֱ��ת��Ϊ��׺���ʽ
    char ch;
    while ((ch = getchar()) != '=')
    {
        if (isspace(ch)) //�����ո�
            continue;
        switch (ch)
        {
        case '*':
        case '/':
        case '(':
            push(infix, ch); //�����ȼ��������ֱ��ѹջ��infix
            break;
        case '+':
        case '-':
            while (peek(infix) == '*' || peek(infix) == '/')
                push(postfix, pop(infix)); //�����ȼ���������Ƚ�infix�е����ȼ��ĳ�ջ��postfix��ѹջ��infix
            push(infix, ch);
            break;
        case ')':
            while (peek(infix) != '(') //��infix�е��������ջ��ֱ������'('��ע��'('ҲҪ��ջ����������postfix
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
        case '.':
            ungetc(ch, stdin);
            scanf("%lf", &num[cnt++]); //����һ�����������������ֵĴ��棬�Ա�double���͵�ʵ�֣�cnt�Ǹ������ָ�루Ҳ������ջֱ�ӽ���ʵ�֣�
            push(postfix, -cnt + 1);   //��������ֱ�ӽ�postfix
            break;
        }
    }
    while (peek(infix) != '0') //����postfixʣ��Ԫ�ؽ�infix
        push(postfix, pop(infix));

    //������
    double re; //���ڴ���ÿһ�εĽ��
    int index = 0;
    double num1, num2;
    while ((ch = peekmid(postfix, index++)) != '0')
    {
        if (isspace(ch)) //�����ո�
            continue;
        if (ch <= 0) //����ֱ��ѹջ��infix
        {
            push(infix, ch);
            continue;
        }
        switch (ch) //��postfix�Ӽ��˳�ֱ�ӽ������㣬����������ѹջ��infix
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
    printf("%.6f\n", num[-pop(infix)]); //���infix�������
    destroy(infix);
    destroy(postfix);
}