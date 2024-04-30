#include "node.h"
using namespace std;

Node::Node(bool sentinel)
{
    is_sentinel = sentinel;
}

Node::Node(int v, Node *nxt, Node *prv)
{
    is_sentinel = false;
    value = v;
    next = nxt;
    prev = prv;
}

bool Node::is_sentinel_node()
{
    return is_sentinel;
}

int Node::get_value()
{
    return value;
}