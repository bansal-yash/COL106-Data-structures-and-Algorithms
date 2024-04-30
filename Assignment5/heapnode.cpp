#include "heapnode.h"

HeapNode::HeapNode()
{
    val = NULL;
}

HeapNode::HeapNode(int _val)
{
    val = _val;
}

HeapNode::~HeapNode()
{
    delete left;
    delete right;
}