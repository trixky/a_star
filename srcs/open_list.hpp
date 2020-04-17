#ifndef OPEN_LIST_HPP
#define OPEN_LIST_HPP

#include "main.hpp"
#include "node.hpp"

class compareNode
{
public:
    bool operator() (Node *first_node, const Node *second_node)
    {
        return true;
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
        Node    *top() const;
};

#endif