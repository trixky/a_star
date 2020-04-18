#ifndef CLOSED_LIST_HPP
#define CLOSED_LIST_HPP

#include "main.hpp"
#include "board.hpp"

class ClosedList
{
    private:
        std::unordered_map<std::string, Board *>   map;

    public:
        ClosedList();
        ~ClosedList();

        void    insert(Board *board);
        bool    already_exist(Board *board);
        int	    size() const;
};

#endif