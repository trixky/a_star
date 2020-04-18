#include "board.hpp"
#include "goal.hpp"
#include "open_list.hpp"
#include "closed_list.hpp"

void	algo_a_star(Goal *goal, OpenList &open_list, ClosedList &close_list)
{
	while (!open_list.empty() && !open_list.top()->is_success(goal->pos)) {
		break;
	}
}

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

	OpenList	open_list;
	ClosedList	close_list;
	
	open_list.push(board_start);

	algo_a_star(goal, open_list, close_list);

	return (0);
}
