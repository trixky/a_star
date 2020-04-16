#ifndef LEXER_HPP
#define LEXER_HPP

#include "main.hpp"

class Lexer {
	public:
		char	*buffer = nullptr;
		int		length;
		bool	err;
		vector<int> *lexem = new vector<int>;

		Lexer(string path);
		~Lexer();

	private:
		bool create_lexem();
};

#endif