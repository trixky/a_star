#ifndef OPEN_LIST_HPP
#define OPEN_LIST_HPP

#include "main.hpp"
#include "board.hpp"

class compareBoard
{
public:
    bool operator() (const Board *first_board, const Board *second_board)
    {
        return (first_board->get_f_cost() >= second_board->get_f_cost() ? true : false);
    }
};

class OpenList
{
    private:
        std::priority_queue<Board *, std::vector<Board *>, compareBoard>   queue;

    public:
        OpenList();
        ~OpenList();

        void    push(Board *board);
        void    pop();
        Board    *top();
		bool	empty() const;
};

#endif