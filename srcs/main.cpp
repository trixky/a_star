#include "board.hpp"
#include "goal.hpp"
#include "open_list.hpp"
#include "closed_list.hpp"
#include "heuristics.hpp"

void	algo_a_star(Goal *goal, OpenList &open_list, ClosedList &close_list)
{
	Board *temp_board;

	while (!open_list.empty()) {

		temp_board = open_list.top()->move_up();
		if (temp_board != nullptr) {
			temp_board->set_h_cost(333);
			if (!close_list.already_exist(temp_board)) {
				open_list.push(temp_board);
			}
		}

		temp_board = open_list.top()->move_right();
		if (temp_board != nullptr) {
			temp_board->set_h_cost(333);
			if (!close_list.already_exist(temp_board)) {
				open_list.push(temp_board);
			}
		}

		temp_board = open_list.top()->move_down();
		if (temp_board != nullptr) {
			temp_board->set_h_cost(333);
			if (!close_list.already_exist(temp_board)) {
				open_list.push(temp_board);
			}
		}

		temp_board = open_list.top()->move_left();
		if (temp_board != nullptr) {
			temp_board->set_h_cost(333);
			if (!close_list.already_exist(temp_board)) {
				open_list.push(temp_board);
			}
		}


		close_list.insert(open_list.pop());
		open_list.pop();
	}
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

	board_start->show();

	OpenList	open_list;
	ClosedList	close_list;

	open_list.push(board_start);

	algo_a_star(goal, open_list, close_list);

	delete goal;
	delete board_start;
	return (0);
}
