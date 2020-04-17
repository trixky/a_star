#ifndef BOARD_HPP
#define BOARD_HPP

#include "main.hpp"
#include "lexer.hpp"
#include "goal.hpp"

class Board {
	private:

		Board   *parent_board;
        int     g_cost;
        int     h_cost;

		int		size;
		int		**board = nullptr;
		bool	err;

		int		x_empty_case;
		int		y_empty_case;

		bool	verif_number_size(int number, int power);
		void	init_board();
		bool	check_value(int actual_row, int actual_col, int max);
		bool	parse_file(Lexer *lexer);
		void	find_my_empty_case();

	public:
		Board(Lexer *lexer);
		Board(const Board &board);
		~Board();

		void show();

		Board *move_up();
		Board *move_down();
		Board *move_right();
		Board *move_left();

		bool	operator==(const Board &board) const;

		bool	is_solvable(Point *pos);

	
};

#endif
