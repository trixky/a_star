#ifndef HEURISTICS_HPP
# define HEURISTICS_HPP

#include "main.hpp"
#include "goal.hpp"

class Heuristic {
	public:
		int (Heuristic::*heuristic)(int **, Point *, int);

		Heuristic(char *arg);
	private:
		int		manhattan_distance(int **board, Point *goal, int size);
		int		hamming_distance(int **board, Point *goal, int size);
		int		linear_conflict_plus_manhattan_distance(int **board, Point *goal, int size);

};

#endif
