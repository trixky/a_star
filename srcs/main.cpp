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
	Board	*board = new Board(lexer);
	delete lexer;
	if (board->err == true) {
		std::cout << "The file is not well formated : Parser Error" << std::endl;
		delete board;
		return (1);
	}
	Goal	*goal = new Goal(board->size);
	board->show();

	if (board->is_solvable()) {
		std::cout << "The board is solvable" << std::endl;
	}
	else {
		std::cout << "The board is not solvable" << std::endl;
		return (1);
	}

	OpenList	openlist;

	return (0);
}
