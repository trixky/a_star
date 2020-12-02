#include "board.hpp"
#include "goal.hpp"
#include "open_list.hpp"
#include "closed_list.hpp"
#include "heuristics.hpp"

void clear_board_vector(std::vector<Board *> &board_vector)
{
	std::vector<Board *>::iterator it(board_vector.begin());
	std::vector<Board *>::iterator it_end(board_vector.end());

	for (; it != it_end; ++it)
	{
		if (*it != nullptr)
		{
			delete (*it);
			*it = nullptr;
		}
	}
}

int show_ride_up(Board *board)
{
	int move = 0;

	while (board->get_parent_board() != nullptr)
	{
		board->show();
		board = board->get_parent_board();
		move++;
	}
	return (move);
}

int child_handle(Board *child, Goal *goal, OpenList &open_list, ClosedList &close_list, int (*hrs)(int **, Point *, int), int algo_type)
{
	if (child != nullptr)
	{
		if (algo_type != UNIFORM)
			child->set_h_cost(hrs(child->get_board(), goal->pos, child->get_size()));
		if (!close_list.already_exist(child))
		{
			open_list.push(child);
			return (1);
		}
	}
	return (0);
}

bool		resolved(int **board, Point *goal, int size) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (board[i][j] && (goal[board[i][j]].x != i || goal[board[i][j]].y != j)) {
				return (false);
			}
		}
	}
	return (true);
}

void algo(Goal *goal, OpenList &open_list, ClosedList &close_list, int (*hrs)(int **, Point *, int), int algo_type)
{
	Board *child[4];
	std::vector<Board *> board_vector;
	int time_complexity = 0;
	int memory_complexity = 0;
	int nbr_of_moves;

	if (algo_type != UNIFORM)
		open_list.top()->set_h_cost(hrs(open_list.top()->get_board(), goal->pos, open_list.top()->get_size()));
	board_vector.push_back(open_list.top());
	while (!open_list.empty() && ((algo_type != UNIFORM && open_list.top()->get_h_cost() != 0) || !resolved(open_list.top()->get_board(), goal->pos, open_list.top()->get_size())))
	{
		time_complexity++;
		board_vector.push_back((child[0] = open_list.top()->move_up(algo_type)));
		board_vector.push_back((child[1] = open_list.top()->move_right(algo_type)));
		board_vector.push_back((child[2] = open_list.top()->move_down(algo_type)));
		board_vector.push_back((child[3] = open_list.top()->move_left(algo_type)));

		close_list.insert(open_list.pop());

		memory_complexity += child_handle(child[0], goal, open_list, close_list, (*hrs), algo_type);
		memory_complexity += child_handle(child[1], goal, open_list, close_list, (*hrs), algo_type);
		memory_complexity += child_handle(child[2], goal, open_list, close_list, (*hrs), algo_type);
		memory_complexity += child_handle(child[3], goal, open_list, close_list, (*hrs), algo_type);
	}
	nbr_of_moves = show_ride_up(open_list.top());
	std::cout << "Complexity in time : [ " << time_complexity << " ]" << std::endl;
	std::cout << "Complexity in memory : [ " << memory_complexity << " ]" << std::endl;
	std::cout << "Number of moves from initial state : [ " << nbr_of_moves << " ]" << std::endl;
	std::cout << "board_vector size = " << board_vector.size() << std::endl;
	clear_board_vector(board_vector);
}

int usage()
{
	std::cout << "N_Puzzle usage: n_puzzle [-0; -1; -2] [-a; -g; -u] [file]" << std::endl;
	std::cout << "  Heuristics:" << std::endl;
	std::cout << "    -0: Manhattan Distance Heuristic." << std::endl;
	std::cout << "    -1: Hamming Distance Heuristic." << std::endl;
	std::cout << "    -2: Linear Conflict and Manhattan Distance Heuristic." << std::endl;
	std::cout << "  Algorithm:" << std::endl;
	std::cout << "    -a: A* (A Star)." << std::endl;
	std::cout << "    -g: Gready Search." << std::endl;
	std::cout << "    -u: Uniform Cost." << std::endl;
	return (1);
}

int main(int args_count, char **args_value)
{

	// Verify the number of arguments.
	// Verify if the heuristic is well chosen.
	// Verify if the algorithm is well chosen.
	if (args_count != 4 ||
		(strcmp(args_value[1], "-0") != 0 && strcmp(args_value[1], "-1") != 0 && strcmp(args_value[1], "-2") != 0) ||
		(strcmp(args_value[2], "-a") != 0 && strcmp(args_value[2], "-g") != 0 && strcmp(args_value[2], "-u") != 0))
	{
		return (usage());
	}

	std::cout << "youpilop 2" << std::endl;

	// Parsing of the file.
	Lexer *lexer = new Lexer(args_value[3]);
	if (lexer->err == true)
	{
		std::cout << "The file is not well formated : Lexer Error" << std::endl;
		delete lexer;
		return (1);
	}
	Board *board_start = new Board(lexer);
	delete lexer;
	if (board_start->get_err() == true)
	{
		std::cout << "The file is not well formated : Parser Error" << std::endl;
		delete board_start;
		return (1);
	}

	// Create the pointer for the heuristic.
	int algo_type;
	if (args_value[2][1] == 'a')
	{
		algo_type = A_STAR;
	}
	else if (args_value[2][1] == 'g')
	{
		algo_type = GREADY;
	}
	else
	{
		algo_type = UNIFORM;
	}

	// Create a the goal as reversed puzzle.
	Goal *goal = new Goal(board_start->get_size());

	// Create the pointer for the heuristic.
	int (*hrs)(int **, Point *, int);
	if (args_value[1][1] == '0')
	{
		hrs = &manhattan_distance;
	}
	else if (args_value[1][1] == '1')
	{
		hrs = &hamming_distance;
	}
	else
	{
		hrs = &linear_conflict_plus_manhattan_distance;
	}


	// Verify if the board is solvable.
	if (board_start->is_solvable(goal->pos))
	{
		std::cout << "The puzzle is solvable" << std::endl;
	}
	else
	{
		std::cout << "The puzzle is not solvable" << std::endl;
		delete goal;
		delete board_start;
		return (1);
	}

	OpenList open_list;
	ClosedList close_list;

	open_list.push(board_start);

	algo(goal, open_list, close_list, (*hrs), algo_type);

	delete goal;

	return (0);
}