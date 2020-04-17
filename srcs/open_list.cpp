#include "open_list.hpp"

OpenList::OpenList()
{

}

OpenList::~OpenList()
{
    while (!this->queue.empty()) {
        this->queue.pop();
    }
}

void    OpenList::insert(Node *node)
{
    this->queue.push(node);
}

Node    *OpenList::top()
{
    return (this->queue.top());
}

void    OpenList::pop()
{
    this->queue.pop();
}
