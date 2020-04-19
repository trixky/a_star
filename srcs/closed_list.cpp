#include "closed_list.hpp"

ClosedList::ClosedList(){}

ClosedList::~ClosedList()
{
    // this->map.clear();
}


void    ClosedList::insert(Board *board)
{
    this->map.insert({board->get_hash(), board});
}

bool    ClosedList::already_exist(Board *open_list_board)
{
    std::unordered_map<std::string, Board *>::iterator it = this->map.find(open_list_board->get_hash());
    if (it != this->map.end()) {
        if (it->second->get_f_cost() < open_list_board->get_f_cost()) {
            return (true);
        }
		// delete it->second;
        this->map.erase(it);
    }
    return (false);
}

int	    ClosedList::size() const
{
	return (this->map.size());
}

