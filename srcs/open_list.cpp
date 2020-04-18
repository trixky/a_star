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

void    OpenList::push(Board *board)
{
    this->queue.push(board);
}

Board    *OpenList::top()
{
    return (this->queue.top());
}

void    OpenList::pop()
{
    this->queue.pop();
}

bool	OpenList::empty() const
{
	return (this->queue.empty());
}