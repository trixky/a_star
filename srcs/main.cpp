#include "board.hpp"
#include "goal.hpp"
#include "open_list.hpp"
#include "closed_list.hpp"
#include "heuristics.hpp"

int		manhattan_distance_temp(int **board, Point *goal, int size) {
	int			result = 0;

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (board[i][j] && (goal[board[i][j]].x != i || goal[board[i][j]].y != j)) {
				result += abs(i - goal[board[i][j]].x) + abs(j - goal[board[i][j]].y);
			}
		}
	}
	return (result);
}

void	child_handle(Board *child, Goal *goal, OpenList &open_list, ClosedList &close_list, Heuristic *hrs)
{
	if (child != nullptr) {
		child->set_h_cost(manhattan_distance_temp(child->get_board(), goal->pos, child->get_size()));
		if (!close_list.already_exist(child)) {
			open_list.push(child);
		}
	}
}

void	algo_a_star(Goal *goal, OpenList &open_list, ClosedList &close_list, Heuristic *hrs)
{
	Board *child[4];
	while (!open_list.empty()) {
		usleep(100000);
		std::cout << open_list.top()->get_last_move() << std::endl;
		// open_list.top()->show();
		std::cout << "**************************************** move_up" << std::endl;
		child[0] = open_list.top()->move_up();
		std::cout << "**************************************** move_right" << std::endl;
		child[1] = open_list.top()->move_right();
		std::cout << "**************************************** move_down" << std::endl;
		child[2] = open_list.top()->move_down();
		std::cout << "**************************************** move_left" << std::endl;
		child[3] = open_list.top()->move_left();

		std::cout << "**************************************** CHILD HANDLE" << std::endl;

		child_handle(child[0], goal, open_list, close_list, hrs);
		child_handle(child[1], goal, open_list, close_list, hrs);
		child_handle(child[2], goal, open_list, close_list, hrs);
		child_handle(child[3], goal, open_list, close_list, hrs);

		std::cout << "**************************************** INSERT" << std::endl;

		close_list.insert(open_list.pop());
	}
	std::cout << "\n\n\n**************************************** ON SORT DE WHILE\n\n\n" << std::endl;
	if (!open_list.empty()) {
		std::cout << "open list vide !" << std::endl;
	}
}

int		usage() {
	std::cout << "N_Puzzle usage: n_puzzle [-0; -1; -2] [-g; -u] [file]" << std::endl;
	std::cout << "  Heuristics:" << std::endl;
	std::cout << "    -0: Manhattan Distance Heuristic." << std::endl;
	std::cout << "    -1: Hamming Distance Heuristic." << std::endl;
	std::cout << "    -2: Linear Conflict and Manhattan Distance Heuristic." << std::endl;
	std::cout << "  Algorithm:" << std::endl;
	std::cout << "    -g: Gready Search Algorithm." << std::endl;
	std::cout << "    -u: Uniform Cost Algorithm." << std::endl;
	return (1);
}

int		main(int args_count, char **args_value) {
	// Verify the number of arguments.
	if (args_count != 4) {
		return (usage());
	}

	// Verify if the heuristic is well chosen and set the pointer to the heuristic.
	if (strcmp(args_value[1], "-0") && strcmp(args_value[1], "-1") && strcmp(args_value[1], "-2")) {
		return (usage());
	}
	Heuristic	*hrs = new Heuristic(args_value[1]);

	// Verify if the algorithm is well chosen.
	if (strcmp(args_value[2], "-g") && strcmp(args_value[2], "-u")) {
		return (usage());
	}

	// Parsing of the file.
	Lexer	*lexer = new Lexer(args_value[3]);
	if (lexer->err == true) {
		std::cout << "The file is not well formated : Lexer Error" << std::endl;
		delete lexer;
		return (1);
	}
	Board	*board_start = new Board(lexer);
	delete lexer;
	if (board_start->get_err() == true) {
		std::cout << "The file is not well formated : Parser Error" << std::endl;
		delete board_start;
		return (1);
	}

	// Create a the goal as reversed puzzle.
	Goal	*goal = new Goal(board_start->get_size());

	// Verify if the board is solvable.
	if (board_start->is_solvable(goal->pos)) {
		std::cout << "The puzzle is solvable" << std::endl;
	}
	else {
		std::cout << "The puzzle is not solvable" << std::endl;
		delete goal;
		delete board_start;
		return (1);
	}

	OpenList	open_list;
	ClosedList	close_list;

	open_list.push(board_start);

	algo_a_star(goal, open_list, close_list, hrs);

	delete goal;
	delete board_start;
	return (0);
}
