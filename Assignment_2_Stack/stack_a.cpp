#include <iostream>
#include <stdexcept>
#include "stack_a.h"

using namespace std;

Stack_A::Stack_A()
{
    size = 0;
}

void Stack_A::push(int data)
{
    if (size == 1024)
    {
        throw runtime_error("Stack Full");
    }
    else
    {
        stk[size] = data;
        size += 1;
    }
}

int Stack_A::pop()
{
    if (size == 0)
    {
        throw runtime_error("Empty Stack");
    }
    else
    {
        size -= 1;
        return stk[size];
    }
}

int Stack_A::get_element_from_top(int idx)
{
    if (idx > size - 1)
    {
        throw runtime_error("Index out of range");
    }
    else
    {
        return stk[size - 1 - idx];
    }
}

int Stack_A::get_element_from_bottom(int idx)
{
    if (idx > size - 1)
    {
        throw runtime_error("Index out of range");
    }
    else
    {
        return stk[idx];
    }
}

void Stack_A::print_stack(bool top_or_bottom)
{
    if (top_or_bottom == 1)
    {
        for (int i = size - 1; i >= 0; i--)
        {
            cout << stk[i] << "\n";
        }
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            cout << stk[i] << "\n";
        }
    }
}

int Stack_A::add()
{
    if (size < 2)
    {
        throw runtime_error("Not Enough Arguments");
    }
    else
    {
        int a = pop(), b = pop();
        int c = a + b;
        push(c);
        return c;
    }
}

int Stack_A::subtract()
{
    if (size < 2)
    {
        throw runtime_error("Not Enough Arguments");
    }
    else
    {
        int a = pop(), b = pop();
        int c = b - a;
        push(c);
        return c;
    }
}

int Stack_A::multiply()
{
    if (size < 2)
    {
        throw runtime_error("Not Enough Arguments");
    }
    else
    {
        int a = pop(), b = pop();
        int c = a * b;
        push(c);
        return c;
    }
}

int Stack_A::divide()
{
    if (size < 2)
    {
        throw runtime_error("Not Enough Arguments");
    }
    else
    {
        if (stk[size - 1] == 0)
        {
            throw runtime_error("Divide by Zero Error");
        }
        else
        {
            int a = pop(), b = pop();
            if ((a < 0 && b > 0) || (a > 0 && b < 0))
            {
                int c = b / a;
                c -= 1;
                push(c);
                return c;
            }
            else
            {
                int c = b / a;
                push(c);
                return c;
            }
        }
    }
}

int *Stack_A::get_stack()
{
    return stk;
}

int Stack_A::get_size()
{
    return size;
}