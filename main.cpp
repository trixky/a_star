#include "board.hpp"

int main(int args_count, char **args_value) {
	if (args_count <= 1) {
		cout << "You should write at least one argument" << endl;
		return (1);
	}
	Lexer	*lexer = new Lexer(args_value[1]);
	if (lexer->err == true) {
		cout << "The file is not well formated : Lexer Error" << endl;
		delete lexer;
		return (1);
	}
	Board	*board = new Board(lexer);
	delete lexer;
	if (board->err == true) {
		cout << "The file is not well formated : Parser Error" << endl;
		delete board;
		return (1);
	}
	return (0);
}
