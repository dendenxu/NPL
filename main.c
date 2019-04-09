/*


url:https://github.com/dendenxu/npl
git command:git clone https://github.com/dendenxu/npl.git

Ϊ�˺��ڷ�����ԣ������ļ����汾�н�stack.c stack.h
main.c�����ļ������˺ϲ�������û�з���ʵ�ʱ䶯��

����Ŀ
1. ͨ�����û��������׺���ʽת��Ϊ��׺���ʽ
2. �����׺���ʽ��ֵ��ʵ�ּ򵥵ļ���������

ע�⣺
1.
һ�м��㶼���ڼٶ��û������ʽ��ȷ������½��еģ��������ĸ�ʽ�����ϸ����׺���ʽ��˭֪���ᷢ��ʲô
2. ֧�ֵ��������+�� -�� *�� /�� =       =��������Ľ����Լ�     ��������     ��
��������
3. ֧�ֵ��������ͣ�˫���ȸ������ͣ�ע�ⲻ���Խ�0.3д��.3�����ǿ��Խ�3.0д��3.��
4.
ջ��С��1000*sizeof(char)�����������С��1000*sizeof(double)���û��豣֤����ļ���ʽ���ᳬ�����ߵ����ƣ�����˭֪���ᷢ��ʲô
5. �û�����������п���������ط�����հ��ַ��������û�����1+1=����1 + 1 =
�����Եõ���ȷ�Ľ������Ȼ����������ԭ��Ӧ��������ĺ����в�����ֵĿհ��ַ�������s
i n��
6.
�������㶼�Ǹ������㣬�������ս��������ʵ�ʽ����΢С�Ĳ��죬����Ҳ�ǲ��ɱ���ġ��������յ������������ʽ�����ս���йأ��п���ΪE�ͻ򸡵���

��Ŀ�ֹ���
- �ܹ���Ƽ�ʵ�֣�����
- ��������Ƽ�ʵ�֣�����
- stack.h��Ƽ�ʵ�֣�����
- ����stack.c������Ƽ�ʵ�֣�����
- stack.c������Ƽ�ʵ�֣�������
- ��Ŀ������Լ������������У�����
- �򵥺������㹦����Ƽ�ʵ�֣��¾��󣨴���ɣ�
- �Һ��ˣ��ҵݹ��˼򵥺�������-����
- �ҰѲ������ŵĵ�ֵ����Ҳʵ�����£���ʱ��ֻ�ܶԵ�����һ�������в�����...-����
- �����ܶԵ���������һ��������������д���-����
*/

//ԭ��Ŀreadme.md����ճ�����£�
/*
# �沨�����ʽ

# �����ߣ�

1. ���� 3180105504
2. ������  3180102072
3. �¾��� 3180105488



## ����Ǯ��C�������ר�⣨2019-03-12������

��Ա�����𣬳¾��󣬸�����

## 03-26-16-30 �ڲ�������ɣ����������Ѿ߱�
1. �����ļӼ��˳�����
2. ���������ֵ�����
3. �����������ʵ��

## ��������ʵ��cos sin pow�ȼ򵥺����Ĺ��� �ֶ�����.jpg

# �Һ�����д���˺���

- �����ó��������·������C�����е����к�������ʵ���ͼ�һ���жϵ���������

- �ɹ�ʵ���˺�����ֻ��һ�������������ŵ����
- �ɹ�ʵ���˺����ڵ������������һ�����������

- ���Գ���ṹ�������ع���������func()����

## ������Ҫ���������鹦�ܵ�������

- hhh�а��Ҳ������ˣ��޸��ˡ���hin��hin��bug��������������

  -
������stdin����շ�ʽ����fflush��֪��Ϊɶ����Щ����ֵֹĴ�������ֱ���ú��ˣ�

  - �����޷�ʶ�����Ĵ��������
  - �����޷�ʶ���ַ��Ĵ��������
  - �������ʱ�Ķ�ջ����ʽ�����ǹ�goto��������ѡ��һ����˳���
  - ���Ĳ�����Ȼ����Ĳ�����main��������������
  - ���Ӳ������ݵ�ע�ͣ������������߼�
  - �޼��˲����ʵĴ�����
  - �������ϡ�������

- ��ʵ�Ⱥ����Ծ���Ҫ����Ĳ��Ե���й��ܼ���
*/

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTACKSIZE 10000 //���ڴ���ջ��double����

#define CLEARSTDIN                                    \
    {                                                 \
        int ch;                                       \
        while ((ch = getchar()) != '\n' && ch != EOF) \
            ;                                         \
    }

typedef struct _Stack
{
    char array[MAXSTACKSIZE];
    int top; //ջ��index
} * Stack;

Stack create(void);             //��ʼ��ջ��array��top����Ϊ�㣩
char pop(Stack stack);          //ջΪ��ʱ����'0'
void push(Stack stack, char c); //�ﵽ���ֵ�󱨴���������
char peek(Stack stack);         //ջΪ��ʱ����'0'
void destroy(
    Stack stack); //��ո�ջ�����ݣ���ʵûɶ������ΪC����û�ж����������������
char peekmid(Stack stack, int index);
double npl(void);

int wrong;

int main()
{
    double output;
    do
    {
        wrong = 0;
        output = npl();
    } while (wrong);
    printf("%g", output);
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
    //�������ڱ�ﺯ�����ַ���
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
        temp[i] = NULL;

        if (wrong)
            return 1;

        //�����ո�
        while (isspace(c))
            c = getchar();

        double tempNum;
        //ȷ��functionӦ�ü����ֵ��ʲô������ᷢ��һϵ�к����Ķ�εݹ飩
        if (c != '(') //�����getchar�����˿ո�����һ������
        {
            ungetc(c, stdin);
            tempNum = func();
        }
        else
            tempNum = npl();
        if (wrong)
            return 1;
        //��һ��������ԱȽϸߵģ���Ҫ�Ļ��������԰��ܵ��õ�ϵͳ�����еļ����͵�double��������ӽ�ȥ
        //����ñȽϸ߼��ķ�ʽ�������ϣ�����������������ܣ����߿��Ǻ���ָ�룬��switch�������ƵĹ�ϣ������������ĺ���ʵ��̫�١������ù�ϣ����ߵ����ܻ������㲻��complexity�ĳ���������ܵ�����
        //����pow���ֺ�����������������������ֺ��治�����ŵ����
        if (!strcmp(temp, "pow"))
        {
            double
                temp1 = tempNum,
                temp2 =
                    npl(); //��ò�Ҫֱ����pow�����е�������npl��ִ��˳���Ǹ�������
            return pow(temp1, temp2);
        }
        else if (!strcmp(temp, "sin"))
            return sin(tempNum);
        else if (!strcmp(temp, "cos"))
            return cos(tempNum);
        else if (!strcmp(temp, "sqrt"))
            return sqrt(tempNum);
        else if (!strcmp(temp, "abs"))
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
}

double npl()
{
    Stack infix = create();
    Stack postfix = create();
    double num[MAXSTACKSIZE] = {0}; // num�������ڴ�����������
    int cnt = 0;                    // cnt����num��index

    //�������ݲ�ֱ��ת��Ϊ��׺���ʽ
    char ch;

    int flag = 1;
    int flag2 = 0;
    while (flag)
    {
        while ((!wrong && flag && (ch = getchar()) != '='))
        {
            if (isspace(ch)) //�����ո�
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
                push(infix, ch); //�����ȼ��������ֱ��ѹջ��infix
                break;
            case '(':
                push(infix, ch); //�����ȼ��������ֱ��ѹջ��infix
                flag2 = 1;       // flag2�����ж��Ƿ��ںϷ������ŵ��У����ڵݹ麯����ʵ�֣�
                break;
            case '+':
            case '-':
                while (peek(infix) == '*' || peek(infix) == '/')
                    push(postfix, pop(infix)); //�����ȼ���������Ƚ�infix�е����ȼ��ĳ�ջ��postfix��ѹջ��infix
                push(infix, ch);
                break;
            case ')':
                if (flag2)
                {
                    while (peek(infix) != '(') //��infix�е��������ջ��ֱ������'('��ע��'('ҲҪ��ջ����������postfix
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
                scanf("%lf", &num[cnt++]); //����һ�����������������ֵĴ��棬�Ա�ֱ������scanf����double���͹��ܵ�ʵ�֣�cnt�Ǹ������ָ�루Ҳ������ջֱ�ӽ���ʵ�֣�
                push(postfix, -cnt + 1);   //��������ֱ�ӽ�postfix
                break;

            case ',':
                flag = 0;
                break;
            default:
                //�����ʽ����������ж�ջ
                printf("Bad input. Try again.\n");
                CLEARSTDIN
                wrong = 1;
                break;
            }
        }
        flag = 0;
    }

    if (wrong)
        return 1;

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
        switch (
            ch) //��postfix�Ӽ��˳�ֱ�ӽ������㣬����������ѹջ��infix
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
    double result = num[-pop(infix)]; //���infix�������
    destroy(infix);
    destroy(postfix);
    wrong = 0;
    return result;
}