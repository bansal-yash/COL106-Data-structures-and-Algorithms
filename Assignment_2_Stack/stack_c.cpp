#include <iostream>
#include <stdexcept>
#include "stack_c.h"

using namespace std;

Stack_C::Stack_C()
{
    try
    {
        stk = new List();
    }
    catch (const std::bad_alloc &)
    {
        delete stk;
        throw runtime_error("Out of Memory");
    }
}

Stack_C::~Stack_C()
{
    delete stk;
}

void Stack_C::push(int data)
{
    stk->insert(data);
}

int Stack_C::pop()
{
    if (stk->get_size() == 0)
    {
        throw runtime_error("Empty Stack");
    }
    else
    {
        return stk->delete_tail();
    }
}

int Stack_C::get_element_from_top(int idx)
{
    int s = stk->get_size();
    if (idx > s - 1)
    {
        throw runtime_error("Index out of range");
    }
    else
    {
        Node *x = stk->get_head();
        int a = s - 1 - idx;
        for (int i = 0; i < a; i++)
        {
            x = x->next;
        }
        return x->next->get_value();
    }
}

int Stack_C::get_element_from_bottom(int idx)
{
    int s = stk->get_size();
    if (idx > s - 1)
    {
        throw runtime_error("Index out of range");
    }
    else
    {
        Node *x = stk->get_head();
        int a = idx;
        for (int i = 0; i < a; i++)
        {
            x = x->next;
        }
        return x->next->get_value();
    }
}

void Stack_C::print_stack(bool top_or_bottom)
{
    int s = stk->get_size();
    if (top_or_bottom == 1)
    {
        Node *x = stk->get_head();

        while (x->next != nullptr)
        {
            x - x->next;
        }

        for (int i = s - 1; i >= 0; i--)
        {
            x = x->prev;
            cout << x->get_value() << "\n";
        }
    }
    else
    {
        Node *x = stk->get_head();
        for (int i = 0; i < s; i++)
        {
            x = x->next;
            cout << x->get_value() << "\n";
        }
    }
}

int Stack_C::add()
{
    int s = stk->get_size();
    if (s < 2)
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

int Stack_C::subtract()
{
    int s = stk->get_size();
    if (s < 2)
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

int Stack_C::multiply()
{
    int s = stk->get_size();
    if (s < 2)
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

int Stack_C::divide()
{
    int s = stk->get_size();
    if (s < 2)
    {
        throw runtime_error("Not Enough Arguments");
    }
    else
    {
        if (get_element_from_top(0) == 0)
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

List *Stack_C::get_stack()
{
    return stk;
}

int Stack_C::get_size()
{
    return stk->get_size();
}