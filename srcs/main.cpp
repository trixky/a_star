#include "board.hpp"
#include "goal.hpp"
#include "open_list.hpp"


int main(int args_count, char **args_value) {
	if (args_count <= 1) {
		std::cout << "You should write at least one argument" << std::endl;
		return (1);
	}
	Lexer	*lexer = new Lexer(args_value[1]);
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
	board_start->show();
	Goal	*goal = new Goal(board_start->get_size());

	if (board_start->is_solvable(goal->pos)) {
		std::cout << "The puzzle is solvable" << std::endl;
	}
	else {
		std::cout << "The puzzle is not solvable" << std::endl;
		delete board_start;
		return (1);
	}

	OpenList	openlist;

	board_start->show();
	board_start->set_g_cost(10);
	board_start->set_h_cost(10);

	Board *board_1 = board_start->move_up();
	board_1->set_g_cost(20);
	board_1->set_h_cost(20);

	board_1->show();

	openlist.push(board_1);
	openlist.push(board_start);

	std::cout << openlist.top()->get_f_cost() << std::endl;

	return (0);
}
