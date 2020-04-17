#include "board.hpp"
#include "goal.hpp"
#include "open_list.hpp"
#include "node.hpp"


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

	Node *node_1 = new Node(nullptr, nullptr);
	node_1->set_g_cost(10);
	node_1->set_h_cost(10);

	Node *node_2 = new Node(nullptr, nullptr);
	node_2->set_g_cost(20);
	node_2->set_h_cost(20);

	openlist.insert(node_2);
	openlist.insert(node_1);

	std::cout << openlist.top()->get_f_cost() << std::endl;

	return (0);
}
