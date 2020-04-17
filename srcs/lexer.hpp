#ifndef LEXER_HPP
#define LEXER_HPP

#include "main.hpp"

class Lexer {
	public:
		char	*buffer = nullptr;
		int		length;
		bool	err;
		std::vector<int> *lexem = new std::vector<int>;

		Lexer(std::string path);
		~Lexer();

	private:
		bool create_lexem();
};

#endif