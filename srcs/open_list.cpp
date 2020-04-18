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

Board    *OpenList::pop()
{
	Board    *top_board = this->queue.top();

    this->queue.pop();

	return (top_board);
}

bool	OpenList::empty() const
{
	return (this->queue.empty());
}

int		OpenList::size() const
{
	return (this->queue.size());
}