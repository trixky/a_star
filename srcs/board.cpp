#include "board.hpp"
#include "goal.hpp"

Board::Board(Lexer *lexer)
{
	if (!(err = parse_file(lexer)))
	{
		this->find_my_empty_case();
		this->refresh_hash();
		this->set_last_move(HERE);
		this->parent_board = nullptr;
		this->g_cost = 0;
	}
}

Board::Board(Board *clone)
{
	this->g_cost = clone->g_cost;
	this->h_cost = clone->h_cost;
	this->size = clone->size;
	init_board();
	this->err = clone->err;
	this->x_empty_case = clone->x_empty_case;
	this->y_empty_case = clone->y_empty_case;
	this->parent_board = clone;
	this->hash = clone->hash;
	this->set_last_move(clone->get_last_move());

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			board[i][j] = clone->board[i][j];
		}
	}
}

Board::~Board()
{
	if (this->board)
	{
		// std::cout << "kill a board" << std::endl;
		for (int i = 0; i < size; ++i)
		{
			delete[] this->board[i];
		}
		delete[] this->board;
		this->board = nullptr;
	}
	else
	{
		std::cout << "kill a null" << std::endl;
	}
	// std::cout << "end kill a board" << std::endl;
}

bool Board::verif_number_size(int number, int power)
{
	int ten_power = 1;
	while (number /= 10)
	{
		ten_power++;
	}
	if (ten_power != power)
	{
		return (true);
	}
	return (false);
}

void Board::init_board()
{
	this->board = new int *[size];
	for (int i = 0; i < size; ++i)
	{
		board[i] = new int[size];
		for (int j = 0; j < size; ++j)
		{
			board[i][j] = -1;
		}
	}
}

bool Board::check_value(int actual_row, int actual_col, int max)
{
	if (board[actual_row][actual_col] > max)
	{
		return (true);
	}
	for (int row = 0; row < size; ++row)
	{
		for (int col = 0; col < size; ++col)
		{
			if (row == actual_row && col == actual_col)
			{
				return (false);
			}
			if (board[actual_row][actual_col] == board[row][col])
			{
				return (true);
			}
		}
	}
	return (false);
}

bool Board::parse_file(Lexer *lexer)
{
	char *test;
	int characters;
	int i = 0;
	int col;
	int row;
	int max;

	while (i < lexer->length && lexer->lexem->at(i) != NUMBER)
	{
		++i;
	}
	size = strtol(&lexer->buffer[i], &test, 10);
	size_square = size * size;
	if (size <= 2 || size >= 4096)
	{
		return (true);
	}
	std::cout << "The size of the board is : " << size << std::endl;
	characters = test - &lexer->buffer[i];
	if (verif_number_size(size, characters))
	{
		return (true);
	}
	i += characters;
	row = 0;
	while (i < lexer->length && lexer->lexem->at(i) != NUMBER)
	{
		if (lexer->lexem->at(i) == ENDLINE)
			row = 1;
		++i;
	}
	if (i == lexer->length)
	{
		return (true);
	}
	if (!row)
	{
		return (true);
	}
	init_board();
	max = size_square - 1;
	row = 0;
	while (i < lexer->length && row < size)
	{
		col = 0;
		while (i < lexer->length && col < size)
		{
			board[row][col] = strtol(&lexer->buffer[i], &test, 10);
			characters = test - &lexer->buffer[i];
			if (verif_number_size(board[row][col], characters))
			{
				return (true);
			}
			if (check_value(row, col, max))
			{
				return (true);
			}
			i += characters;
			++col;
			while (i < lexer->length && lexer->lexem->at(i) != NUMBER && lexer->lexem->at(i) != ENDLINE)
			{
				++i;
			}
			if (i != lexer->length)
			{
				if (col != size && lexer->lexem->at(i) == ENDLINE)
				{
					return (true);
				}
				if (col == size && lexer->lexem->at(i) == NUMBER)
				{
					return (true);
				}
			}
		}
		while (i < lexer->length && lexer->lexem->at(i) != NUMBER)
		{
			++i;
		}
		++row;
	}
	if (row != size || col != size)
	{
		return (true);
	}
	while (i < lexer->length)
	{
		if (lexer->lexem->at(i) == NUMBER)
		{
			return (true);
		}
		++i;
	}
	return (false);
}

bool Board::is_solvable(Point *pos)
{
	int *goal = new int[size_square];
	int *board_1d = new int[size_square];
	int index = 0;
	int transversion = 0;
	int even_odd = (std::abs(pos[0].x - x_empty_case) + std::abs(pos[0].y - y_empty_case)) % 2;

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			board_1d[index++] = board[i][j];
		}
	}
	for (int i = 0; i < size_square; ++i)
	{
		goal[pos[i].x * size + pos[i].y] = i;
	}
	for (int i = 0; i < size_square; ++i)
	{
		for (int j = i + 1; j < size_square; ++j)
		{
			if (goal[board_1d[i]] > goal[board_1d[j]])
			{
				transversion++;
			}
		}
	}
	transversion %= 2;
	delete[] goal;
	delete[] board_1d;
	if (transversion - even_odd)
	{
		return (false);
	}
	return (true);
}

bool Board::is_success(Point *goal)
{
	for (int i = 0; i < size_square; ++i)
	{
		if (i != board[goal[i].x][goal[i].y])
		{
			return (false);
		}
	}
	return (true);
}

void Board::show() const
{
	for (int y(0); y < this->size; y++)
	{
		std::cout << "|\t";
		for (int x(0); x < this->size; x++)
		{
			if (this->board[y][x] != 0)
			{
				std::cout << this->board[y][x];
			}
			else
			{
				std::cout << '~';
			}
			std::cout << '\t';
		}
		std::cout << "|" << std::endl;
	}
	std::cout << "\n"
			  << std::endl;
}

void Board::show_more() const
{
	for (int i(0); i < this->size; i++)
	{
		std::cout << "\\\\\\\\\\\\\\\\";
	}
	std::cout << " show start :" << std::endl;
	std::cout << "   g_cost = " << this->get_g_cost() << std::endl;
	std::cout << "   h_cost = " << this->get_h_cost() << std::endl;
	std::cout << "   f_cost = " << this->get_f_cost() << std::endl;
	for (int y(0); y < this->size; y++)
	{
		for (int x(0); x < this->size; x++)
		{
			std::cout << "   ";
			if (this->board[y][x] != 0)
			{
				std::cout << this->board[y][x];
			}
			else
			{
				std::cout << '~';
			}
			std::cout << '\t';
		}
	}
	for (int i(0); i < this->size; i++)
	{
		std::cout << "////////";
	}
	std::cout << " show end." << std::endl;
	std::cout << "\n"
			  << std::endl;
}

void Board::find_my_empty_case()
{
	for (int y(0); y < this->size; y++)
	{
		for (int x(0); x < this->size; x++)
		{
			if (this->board[y][x] == 0)
			{
				this->x_empty_case = x;
				this->y_empty_case = y;
				return;
			}
		}
	}
}

Board *Board::get_parent_board()
{
	return (this->parent_board);
}

std::string Board::get_hash() const
{
	return (this->hash);
}

bool Board::get_err()
{
	return (this->err);
}

int Board::get_size()
{
	return (this->size);
}

int Board::get_g_cost() const
{
	return (this->g_cost);
}

int Board::get_h_cost() const
{
	return (this->h_cost);
}

int Board::get_f_cost() const
{
	return (this->g_cost + this->h_cost);
}

int Board::get_last_move() const
{
	return (this->last_move);
}

int **Board::get_board() const
{
	return (this->board);
}

void Board::set_g_cost(int cost)
{
	this->g_cost = cost;
}

void Board::set_h_cost(int cost)
{
	this->h_cost = cost;
}

void Board::set_last_move(int move)
{
	this->last_move = move;
}

void Board::refresh_hash()
{
	this->hash.clear();
	for (int y(0); y < this->size; y++)
	{
		for (int x(0); x < this->size; x++)
		{
			this->hash += this->board[y][x];
		}
	}
}

// ==================================================== MOVE
// ================
// ======

// ====== UP
Board *Board::move_up(int algo_type)
{
	if (this->last_move == DOWN || this->y_empty_case == 0)
	{
		return (nullptr);
	}

	Board *board_cpy = new Board(this);
	int temp_case;

	temp_case = board_cpy->board[board_cpy->y_empty_case - 1][board_cpy->x_empty_case];
	board_cpy->board[board_cpy->y_empty_case - 1][board_cpy->x_empty_case] = 0;
	board_cpy->board[board_cpy->y_empty_case][board_cpy->x_empty_case] = temp_case;

	board_cpy->y_empty_case--;
	board_cpy->refresh_hash();
	board_cpy->set_last_move(UP);
	if (algo_type != GREADY)
	{
		board_cpy->g_cost++;
	}

	return (board_cpy);
}

// ====== DOWN
Board *Board::move_down(int algo_type)
{
	if (this->last_move == UP || this->y_empty_case == this->size - 1)
	{
		return (nullptr);
	}

	Board *board_cpy = new Board(this);
	int temp_case;

	temp_case = board_cpy->board[board_cpy->y_empty_case + 1][board_cpy->x_empty_case];
	board_cpy->board[board_cpy->y_empty_case + 1][board_cpy->x_empty_case] = 0;
	board_cpy->board[board_cpy->y_empty_case][board_cpy->x_empty_case] = temp_case;

	board_cpy->y_empty_case++;
	board_cpy->refresh_hash();
	board_cpy->set_last_move(DOWN);
	if (algo_type != GREADY)
	{
		board_cpy->g_cost++;
	}

	return (board_cpy);
}

// ====== RIGHT
Board *Board::move_right(int algo_type)
{
	if (this->last_move == LEFT || this->x_empty_case == this->size - 1)
	{
		return (nullptr);
	}

	Board *board_cpy = new Board(this);
	int temp_case;

	temp_case = board_cpy->board[board_cpy->y_empty_case][board_cpy->x_empty_case + 1];
	board_cpy->board[board_cpy->y_empty_case][board_cpy->x_empty_case + 1] = 0;
	board_cpy->board[board_cpy->y_empty_case][board_cpy->x_empty_case] = temp_case;

	board_cpy->x_empty_case++;
	board_cpy->refresh_hash();
	board_cpy->set_last_move(RIGHT);
	if (algo_type != GREADY)
	{
		board_cpy->g_cost++;
	}

	return (board_cpy);
}

// ====== LEFT
Board *Board::move_left(int algo_type)
{
	if (this->last_move == RIGHT || this->x_empty_case == 0)
	{
		return (nullptr);
	}

	Board *board_cpy = new Board(this);
	int temp_case;

	temp_case = board_cpy->board[board_cpy->y_empty_case][board_cpy->x_empty_case - 1];
	board_cpy->board[board_cpy->y_empty_case][board_cpy->x_empty_case - 1] = 0;
	board_cpy->board[board_cpy->y_empty_case][board_cpy->x_empty_case] = temp_case;

	board_cpy->x_empty_case--;
	board_cpy->refresh_hash();
	board_cpy->set_last_move(LEFT);
	if (algo_type != GREADY)
	{
		board_cpy->g_cost++;
	}

	return (board_cpy);
}

// ==================================================== OPERATOR
// ================
// ======

// ====== [ == ]
bool Board::operator==(const Board &board) const
{
	for (int y(0); y < this->size; y++)
	{
		for (int x(0); x < this->size; x++)
		{
			if (this->board[y][x] != board.board[y][x])
			{
				return (false);
			}
		}
	}
	return (true);
}
