#include "board.hpp"
#include "goal.hpp"
#include "open_list.hpp"
#include "closed_list.hpp"
#include "heuristics.hpp"

void	show_ride_up(Board *board)
{
	while (board->get_parent_board() != nullptr)
	{
		board->show();
		board = board->get_parent_board();
	}
}

void	child_handle(Board *child, Goal *goal, OpenList &open_list, ClosedList &close_list, int (*hrs)(int **, Point *, int))
{
	if (child != nullptr) {
		child->set_h_cost(hrs(child->get_board(), goal->pos, child->get_size()));
		if (!close_list.already_exist(child)) {
			open_list.push(child);
		}
	}
}

void	algo_a_star(Goal *goal, OpenList &open_list, ClosedList &close_list, int (*hrs)(int **, Point *, int))
{
	Board *child[4];

	open_list.top()->set_h_cost(hrs(open_list.top()->get_board(), goal->pos, open_list.top()->get_size()));
	while (!open_list.empty() && open_list.top()->get_h_cost() != 0) {
		child[0] = open_list.top()->move_up();
		child[1] = open_list.top()->move_right();
		child[2] = open_list.top()->move_down();
		child[3] = open_list.top()->move_left();

		close_list.insert(open_list.pop());

		child_handle(child[0], goal, open_list, close_list, (*hrs));
		child_handle(child[1], goal, open_list, close_list, (*hrs));
		child_handle(child[2], goal, open_list, close_list, (*hrs));
		child_handle(child[3], goal, open_list, close_list, (*hrs));
	}
	show_ride_up(open_list.top());
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

	// Create the pointer for the heuristic.
	int		(*hrs)(int **, Point *, int);
	if (args_value[1][1] == '0') {
		hrs = &manhattan_distance;
	}
	else if (args_value[1][1] == '1') {
		hrs = &hamming_distance;
	}
	else {
		hrs = &linear_conflict_plus_manhattan_distance;
	}

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

	algo_a_star(goal, open_list, close_list, (*hrs));
	delete goal;
	delete board_start;
	return (0);
}
