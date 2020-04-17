#ifndef NODE_HPP
#define NODE_HPP

#include "main.hpp"
#include "board.hpp"

class Node
{
    private:
        Board   *parent_board;
        Board   *actual_board;
        int     g_cost;
        int     h_cost;

    public:
        Node(Board *parent_board, Board *actual_board);
        ~Node();

        Board   *get_parent_board();
        Board   *get_actual_board();

        int     get_g_cost() const;
        int     get_h_cost() const;
        int     get_f_cost() const;

        void    set_g_cost(int cost);
        void    set_h_cost(int cost);
};

#endif