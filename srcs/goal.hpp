#ifndef GOAL_HPP
#define GOAL_HPP

#include "main.hpp"

typedef struct	Point {
	int	x;
	int	y;
}				Point;

class Goal {
	public:
		Point *pos;
		bool err;

		Goal(int size);
		~Goal();
};

#endif
