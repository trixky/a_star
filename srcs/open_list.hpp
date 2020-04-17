#ifndef OPEN_LIST_HPP
#define OPEN_LIST_HPP

#include "main.hpp"
#include "node.hpp"

class compareNode
{
public:
    bool operator() (const Node *first_node, const Node *second_node)
    {
        return (first_node->get_f_cost() >= second_node->get_f_cost() ? true : false);
    }
};

class OpenList
{
    private:
        std::priority_queue<Node *, std::vector<Node *>, compareNode>   queue;

    public:
        OpenList();
        ~OpenList();

        void    insert(Node *node);
        void    pop();
        Node    *top();
};

#endif