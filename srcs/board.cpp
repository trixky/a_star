#include "board.hpp"
#include "goal.hpp"

Board::Board(Lexer *lexer)
{
	if (!(err = parse_file(lexer))) {
		this->find_my_empty_case();
	}
}

Board::Board(const Board &clone)
{
	size = clone.size;
	board = new int *[size];
	err = clone.err;
	x_empty_case = clone.x_empty_case;
	y_empty_case = clone.y_empty_case;

	for (int i = 0; i < size; ++i)
	{
		board[i] = new int[size];
		for (int j = 0; j < size; ++j)
		{
			board[i][j] = clone.board[i][j];
		}
	}
}

Board::~Board()
{
	if (board)
	{
		for (int i = 0; i < size; ++i)
		{
			delete board[i];
		}
		delete board;
	}
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
	board = new int *[size];
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
	if (size <= 1 || size >= 4096)
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
	max = size * size - 1;
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

bool Board::is_solvable() {
	return (true);
}

void	Board::show()
{
	char c;

	for (int i(0); i < this->size; i++) {
		std::cout << "\\\\\\\\\\\\\\\\";
	}
	std::cout << " show start :" << std::endl;
	for (int y(0); y < this->size; y++)
	{
		for (int x(0); x < this->size; x++)
		{
			std::cout << "   ";
			if (this->board[y][x] != 0) {
				std::cout << this->board[y][x];
			}
			else {
				std::cout << '~';
			}
			std::cout << '\t';
		}
		std::cout << std::endl;
	}
	for (int i(0); i < this->size; i++) {
		std::cout << "////////";
	}
	std::cout << " show end." << std::endl;
}

void	Board::find_my_empty_case()
{
	for (int y(0); y < this->size; y++)
	{
		for (int x(0); x < this->size; x++)
		{
			if (this->board[y][x] == 0) {
				this->x_empty_case = x;
				this->y_empty_case = y;
				return ;
			}
		}
	}
}

// ==================================================== MOVE
// ================
// ======

// ====== UP
Board *Board::move_up()
{
	if (this->y_empty_case == 0) {
		return (nullptr);
	}

	Board	*board_cpy = new Board(*this);
	int		temp_case;

	temp_case = board_cpy->board[board_cpy->y_empty_case - 1][board_cpy->x_empty_case];
	board_cpy->board[board_cpy->y_empty_case - 1][board_cpy->x_empty_case] = 0;
	board_cpy->board[board_cpy->y_empty_case][board_cpy->x_empty_case] = temp_case;

	board_cpy->y_empty_case--;

	return (board_cpy);
}

// ====== DOWN
Board *Board::move_down()
{
	if (this->y_empty_case == this->size - 1) {
		return (nullptr);
	}

	Board	*board_cpy = new Board(*this);
	int		temp_case;

	temp_case = board_cpy->board[board_cpy->y_empty_case + 1][board_cpy->x_empty_case];
	board_cpy->board[board_cpy->y_empty_case + 1][board_cpy->x_empty_case] = 0;
	board_cpy->board[board_cpy->y_empty_case][board_cpy->x_empty_case] = temp_case;

	board_cpy->y_empty_case++;

	return (board_cpy);
}

// ====== RIGHT
Board *Board::move_right()
{
	if (this->x_empty_case == this->size - 1) {
		return (nullptr);
	}

	Board	*board_cpy = new Board(*this);
	int		temp_case;

	temp_case = board_cpy->board[board_cpy->y_empty_case][board_cpy->x_empty_case + 1];
	board_cpy->board[board_cpy->y_empty_case][board_cpy->x_empty_case + 1] = 0;
	board_cpy->board[board_cpy->y_empty_case][board_cpy->x_empty_case] = temp_case;

	board_cpy->x_empty_case++;

	return (board_cpy);
}

// ====== LEFT
Board *Board::move_left()
{
	if (this->x_empty_case == 0) {
		return (nullptr);
	}

	Board	*board_cpy = new Board(*this);
	int		temp_case;

	temp_case = board_cpy->board[board_cpy->y_empty_case][board_cpy->x_empty_case - 1];
	board_cpy->board[board_cpy->y_empty_case][board_cpy->x_empty_case - 1] = 0;
	board_cpy->board[board_cpy->y_empty_case][board_cpy->x_empty_case] = temp_case;

	board_cpy->x_empty_case--;

	return (board_cpy);
}

// ==================================================== OPERATOR
// ================
// ======


// ====== [ == ]
bool	Board::operator==(const Board &board) const
{
	for (int y(0); y < this->size; y++)
	{
		for (int x(0); x < this->size; x++)
		{
			if (this->board[y][x] != board.board[y][x]) {
				return (false);
			}
		}
	}
	return (true);
}
