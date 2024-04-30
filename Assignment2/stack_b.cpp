#include <iostream>
#include <stdexcept>
#include "stack_b.h"

using namespace std;

Stack_B::Stack_B()
{
    size = 0;
    capacity = 1024;
    try
    {
        stk = new int[capacity];
    }
    catch (const std::bad_alloc &)
    {
        delete[] stk;
        throw runtime_error("Out of Memory");
    }
}

Stack_B::~Stack_B()
{
    delete[] stk;
}

void Stack_B::push(int data)
{
    if (size == capacity)
    {
        capacity = capacity * 2;
        int *temp;
        try
        {
            temp = new int[capacity];
        }
        catch (const std::bad_alloc &)
        {
            delete[] temp;
            throw runtime_error("Out of Memory");
        }

        for (int i = 0; i < size; i++)
        {
            temp[i] = stk[i];
        }

        delete[] stk;
        stk = temp;
    }

    stk[size] = data;
    size += 1;
}

int Stack_B::pop()
{
    if (size == 0)
    {
        throw runtime_error("Empty Stack");
    }
    else
    {
        size -= 1;
        int x = stk[size];
        if (size <= capacity / 4 && capacity > 1024)
        {
            capacity = capacity / 2;
            int *temp;
            try
            {
                temp = new int[capacity];
            }
            catch (const std::bad_alloc &)
            {
                delete[] temp;
                throw runtime_error("Out of Memory");
            }

            for (int i = 0; i < size; i++)
            {
                temp[i] = stk[i];
            }

            delete[] stk;
            stk = temp;
        }

        return x;
    }
}

int Stack_B::get_element_from_top(int idx)
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

int Stack_B::get_element_from_bottom(int idx)
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

void Stack_B::print_stack(bool top_or_bottom)
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

int Stack_B::add()
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

int Stack_B::subtract()
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

int Stack_B::multiply()
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

int Stack_B::divide()
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

int *Stack_B::get_stack()
{
    return stk;
}

int Stack_B::get_size()
{
    return size;
}