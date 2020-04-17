#include "node.hpp"

Node::Node(Board *parent_board, Board *actual_board): parent_board(parent_board), actual_board(actual_board){}

Node::~Node()
{

}

int Node::get_g_cost() const
{
    return (this->g_cost);
}

int Node::get_h_cost() const
{
    return (this->h_cost);
}

int Node::get_f_cost() const
{
    return (this->g_cost + this->h_cost);
}

void Node::set_g_cost(int cost)
{
    this->g_cost = cost;
}

void Node::set_h_cost(int cost)
{
    this->h_cost = cost;
}

