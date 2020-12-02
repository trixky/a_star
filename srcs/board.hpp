#ifndef BOARD_HPP
#define BOARD_HPP

#include "main.hpp"
#include "lexer.hpp"
#include "goal.hpp"

class Board {
	private:

		Board		*parent_board;
        std::string	hash;
		int			g_cost;
        int			h_cost;

		int			size;
		int			size_square;
		int			**board = nullptr;
		bool		err;

		int			x_empty_case;
		int			y_empty_case;

		short		last_move;

		bool		verif_number_size(int number, int power);
		void		init_board();
		bool		check_value(int actual_row, int actual_col, int max);
		bool		parse_file(Lexer *lexer);
		void		find_my_empty_case();
		void		refresh_hash();

	public:
		Board(Lexer *lexer);
		Board(Board *board);
		~Board();

		void show() const;
		void show_more() const;

		Board			*move_up(int algo_type);
		Board			*move_down(int algo_type);
		Board			*move_right(int algo_type);
		Board			*move_left(int algo_type);

		bool			operator==(const Board &board) const;

		bool			is_solvable(Point *pos);
		bool			is_success(Point *pos);

		bool			get_err();
		int				get_size();

        Board			*get_parent_board();

		std::string     get_hash() const;

		int     		get_g_cost() const;
        int     		get_h_cost() const;
        int     		get_f_cost() const;
		int				get_last_move() const;
		int				**get_board() const;

        void    		set_g_cost(int cost);
        void    		set_h_cost(int cost);
		void			set_last_move(int move);
};

#endif
