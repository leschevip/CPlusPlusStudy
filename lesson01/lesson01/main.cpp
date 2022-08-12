
#include <iostream>
#include "Power.h"
#include "RGBA.h"
#include "Stack.h"

void Task1()
{
    cout << "Task1:" << endl;
    Power p1;
    p1.calucate();

    p1.set(2, 4);
    p1.calucate();

    p1.set(1.2, 2.2);
    p1.calucate();

    cout << endl;
}

void Task2()
{
    cout << "Task2:" << endl;
    RGBA c1;
    c1.print();

    RGBA c2(134, 255, 12, 44);
    c2.print();

    cout << endl;
}

void Task3()
{
    cout << "Task3:" << endl;
    Stack<int> stack;
    stack.reset();
    stack.print();

    stack.push(3);
    stack.push(7);
    stack.push(5);
    stack.print();

    stack.pop();
    stack.print();

    stack.pop();
    stack.pop();
    stack.print();

    cout << endl;

    Stack<RGBA*> sptr;
    RGBA c1;
    RGBA c2(12, 32, 44, 255);
    sptr.push(&c1);
    sptr.push(&c2);
    sptr.print();
    RGBA* с3 = sptr.pop();
    sptr.print();

    cout << endl;

    Stack<RGBA> sv;
    sv.push(c1);
    sv.push(c2);
    sv.print();
    RGBA c4 = sv.pop();
    sv.print();

    cout << endl;
}

// внутри stack.h есть несколько вопросов, которые хочется понять / разобрать
int main()
{
    Task1();
    Task2();
    Task3();
}