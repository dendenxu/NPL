/*
����Ŀ
1. ͨ�����û��������׺���ʽת��Ϊ��׺���ʽ
2. �����׺���ʽ��ֵ��ʵ�ּ򵥵ļ���������

ע�⣺
1. һ�м��㶼���ڼٶ��û������ʽ��ȷ������½��еģ��������ĸ�ʽ�����ϸ����׺���ʽ��˭֪���ᷢ��ʲô
2. ֧�ֵ��������+�� -�� *�� /�� =��=��������Ľ������Լ�������
3. ֧�ֵ��������ͣ�˫���ȸ������ͣ�ע�ⲻ���Խ�0.3д��.3�����ǿ��Խ�3.0д��3.��
4. ջ��С��1000*sizeof(char)�����������С��1000*sizeof(double)���û��豣֤����ļ���ʽ���ᳬ�����ߵ����ƣ�����˭֪���ᷢ��ʲô
5. �û�����������п���������ط�����հ��ַ��������û�����1+1=����1 + 1 = �����Եõ���ȷ�Ľ��
6. �������㶼�Ǹ������㣬�������ս��������ʵ�ʽ����΢С�Ĳ��죬����Ҳ�ǲ��ɱ���ġ��������յ������������ʽ�����ս���йأ��п���ΪE�ͻ򸡵���

��Ŀ�ֹ���
- �ܹ���Ƽ�ʵ�֣�����
- ��������Ƽ�ʵ�֣�����
- stack.h��Ƽ�ʵ�֣�����
- ����stack.c������Ƽ�ʵ�֣�����
- stack.c������Ƽ�ʵ�֣�������
- ��Ŀ������Լ������������У�����
- �򵥺������㹦����Ƽ�ʵ�֣��¾��󣨴���ɣ�
*/

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
    printf("%.6g\n", num[-pop(infix)]); //���infix�������
    destroy(infix);
    destroy(postfix);
}