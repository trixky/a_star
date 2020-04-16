#ifndef BOARD_HPP
#define BOARD_HPP

#include "main.hpp"
#include "lexer.hpp"

class Board {
	public:
		int size;
		int **board = nullptr;
		bool err;

		Board(Lexer *lexer);
		~Board();

	private:
		bool verif_number_size(int number, int power);

		void init_board();

		bool check_value(int actual_row, int actual_col, int max);

		bool parse_file(Lexer *lexer);
};

#endif