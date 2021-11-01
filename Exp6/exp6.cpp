//
// Created by zjh15 on 2021/10/20.
//
#include <bits/stdc++.h>
using namespace std;

// 扩充数组容量
template <class T>
void changeLength1D(T *&a, int oldLength, int newLength)
{
    if (newLength < 0)
    { // 容量范围出错
        cout << "the length must be > 0" << endl;
        return;
    }
    T *temp = new T[newLength];             // 开辟新数组
    int number = min(oldLength, newLength); // 需要复制的元素
    copy(a, a + number, temp);
    delete[] a; // 释放原数组
    a = temp;
}

// 定义栈类
template <class T>
class arrayStack
{
public:
    arrayStack(int initialCapacity = 10);         // 构造函数
    ~arrayStack() { delete[] stack; }             // 析构函数
    bool empty() const { return stackTop == -1; } // 判断栈是否为空
    int size() const { return stackTop + 1; }     // 栈的元素数量
    T top()                                       // 返回栈顶元素
    {
        if (stackTop == -1)
        { // 如果栈为空
            // cout << "the stack is empty" << endl;
            return NULL;
        }
        return stack[stackTop]; // 返回栈顶元素
    }

    void pop() // 出栈
    {
        if (stackTop == -1)
        { // 如果栈为空
            // cout << "the stack is empty" << endl;
            return;
        }
        stack[stackTop--].~T(); // 删除栈顶元素
    }

    void push(const T &theElement); // 压栈

    // 数据成员
    int stackTop;    // 栈顶指针
    int arrayLength; // 栈的容量
    T *stack;        // 元素数组
};

template <class T>
arrayStack<T>::arrayStack(int initialCapacity)
{ // 栈的构造函数
    if (initialCapacity < 1)
    { // 栈的容量出错
        // cout << "the arrayLength of stack must be > 0" << endl;
        return;
    }
    arrayLength = initialCapacity;
    stackTop = -1;
    stack = new T[arrayLength];
}

template <class T>
void arrayStack<T>::push(const T &theElement)
{ // 栈中压入元素
    if (stackTop + 1 == arrayLength)
    { // 如果栈已满，则扩充栈的容量
        changeLength1D(stack, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }
    // 加入元素
    stack[++stackTop] = theElement;
}

void calculate(arrayStack<char>& Operator,arrayStack<double>& number)
{ // 计算操作，将结果压栈
    double res = 0;

    char op = Operator.top(); // 操作符栈
    Operator.pop();

    double a = number.top(); // 弹出操作数
    number.pop();
    double b = number.top();
    number.pop();

    switch (op)
    { // 根据运算符进行计算,结果入栈
    case '+':
    {
        res = b + a;
        number.push(res);
        break;
    }
    case '-':
    {
        res = b - a;
        number.push(res);
        break;
    }
    case '*':
    {
        res = b * a;
        number.push(res);
        break;
    }
    case '/':
    {
        res = b / a;
        number.push(res);
        break;
    }
    }
}

void eval(string str)
{// 计算输入表达式的值
    arrayStack<double> number;    // 记录表达式中数字
    arrayStack<char> Operator; // 记录运算符

    bool flag = false; // 标志前一个字符是否为数字
    for (int i = 0; i < str.size(); i++) // 遍历表达式
    {
        // cout << "str[" << i << "] = " << str[i] << endl;

        if(str[i] == '+' || str[i] == '-')
        {// 如果当前字符是 '+',' -' ,当Operator栈非空且栈顶元素不是 '(',否则直接运算
            flag = false;
            while(Operator.top() != '(' && !Operator.empty())
            {
                calculate(Operator,number);
            }
            Operator.push(str[i]);
            continue;
        }
        else if(str[i] == '*' || str[i] == '/')
        {// 如果当前字符是 * /，当栈不空且当前栈顶元素为* /时计算，否则入栈
            flag = false;
            if(!Operator.empty() && (Operator.top() == '/' || Operator.top() == '*'))
            {
                calculate(Operator,number);
            }
            Operator.push(str[i]);
            continue;
        }
        else if(str[i] == '(')
        {// 遇到左括号则直接进栈
            flag = false;
            Operator.push(str[i]);
            continue;
        }
        else if(str[i] == ')')
        {// 如果遇到右括号，计算直到遇到左括号
            while(Operator.top() != '(')
            {
                calculate(Operator,number);
            }
            Operator.pop(); // 弹出左括号
            continue;
        }
        else if(str[i] >= '0' && str[i] <= '9')
        {// 遇到数字则计算后入栈
            double temp = 0.0;
            if (flag == true)//判断前一个字符是否为数字,如果是，弹出乘10加下一位
            {
                temp = number.top();
                number.pop();
            }
            else
                temp = 0;
            temp = temp * 10 + str[i] - '0';
            flag = true;
            // 重新入栈
            number.push(temp);
            continue;
        }
    }
    while (!Operator.empty())
    {// 判断是否计算完全
        calculate(Operator,number);
    }
    printf("%.2f\n",number.top());
}

int main(void)
{
    int n; // 输入操作数
    cin >> n;
    string str;
    for (int i = 0; i < n; i++)
    {
        cin >> str;
        eval(str); // 计算表达式的值
    }
    return 0;
}
/*
3
1+6/1*7+2*1*4+9/1+2*0*9+9+7/(9*5)-1*6-0*8-7-9*2+6-(0-5-2*8-7-9*5*(6-5*5*2*6-2-7-5+6*7+6*9-1*0*0+3*0+2/1-6/6+5))
0-4-1/6*(1-(6/7)-4+6+2+6*1)-1*7+2-8*2+0-(4+6-6*1+(3-8*6/4-6-5)*6/4/8+7-1*4/9*5)-0/6+1-0-2+7-2+6*4-3*6+2/8+6+1*6*2
5-3*9+5/1*5-9+1*8-6-8-4*1+5-2+9/3*2-2/5/(2-6)*2/7-9*0-2+4/6*6*7*8-8-8*6+8*9*(3+0*1/5/2*7*8+0-8*8-5+8/5*2-0)
 */
