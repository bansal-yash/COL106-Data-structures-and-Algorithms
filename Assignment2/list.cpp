#include <iostream>
#include <stdexcept>
#include "list.h"

using namespace std;

List::List()
{
    try
    {
        sentinel_head = new Node(true);
    }
    catch (const std::bad_alloc &)
    {
        delete sentinel_head;
        throw runtime_error("Out of Memory");
    }

    try
    {
        sentinel_tail = new Node(true);
    }
    catch (const std::bad_alloc &)
    {
        delete sentinel_tail;
        throw runtime_error("Out of Memory");
    }

    sentinel_head->next = sentinel_tail;
    sentinel_head->prev = nullptr;
    sentinel_tail->prev = sentinel_head;
    sentinel_tail->next = nullptr;
    size = 0;
}

List::~List()
{
    Node *x = get_head();
    while (x != nullptr)
    {
        Node *y = x->next;
        delete x;
        x = y;
    }
}

void List::insert(int v)
{
    Node *a;
    try
    {
        a = new Node(v, nullptr, nullptr);
    }
    catch (const std::bad_alloc &)
    {
        delete a;
        throw runtime_error("Out of Memory");
    }
    a->next = sentinel_tail->prev->next;
    sentinel_tail->prev->next = a;
    a->prev = sentinel_tail->prev;
    sentinel_tail->prev = a;
    size += 1;
}

int List::delete_tail()
{
    if (size == 0)
    {
        throw runtime_error("Empty Stack");
    }
    else
    {
        sentinel_tail->prev->prev->next = sentinel_tail;
        Node *temp = sentinel_tail->prev;
        sentinel_tail->prev = temp->prev;
        int c = temp->get_value();
        delete temp;
        size -= 1;
        return c;
    }
}

int List::get_size()
{
    return size;
}

Node *List::get_head()
{
    return sentinel_head;
}