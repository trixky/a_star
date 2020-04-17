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
    this->insert(node);
}

Node    *OpenList::top() const
{
    
}

void    OpenList::pop()
{

}
