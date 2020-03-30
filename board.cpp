#include <cstdlib>
#include <fstream>
#include <vector>
#include <iostream>
#include <string.h>
using namespace std;

#define START	0
#define NUMBER	1
#define HASHTAG	2
#define ENDLINE	3
#define SPACE	4

class Lexer {
	public:
		char	*buffer = nullptr;
		int		length;
		bool	err;
		vector<int> *lexem = new vector<int>;

		// Constructor
		Lexer(string path) {
			ifstream file(path, ifstream::binary);
			if (!file) {
				cout << "File cannot be loaded" << endl;
			}
			else {
				file.seekg(0, file.end);
				length = file.tellg();
				file.seekg(0, file.beg);
				buffer = new char [length];
				file.read(buffer, length);
				if (!file) {
					err = true;
				}
				else {
					err = create_lexem();
				}
				file.close();
			}
		}

		// Destructor
		~Lexer() {
			delete lexem;
			if (buffer) {
				delete buffer;
			}
		}

	private:
		bool create_lexem() {
			int state = START;
			for (int i = 0; i < length; ++i) {
				if (state == HASHTAG) {
					if (buffer[i] == '\n') {
						lexem->push_back(ENDLINE);
						state = ENDLINE;
					}
					else if (buffer[i] == '#') {
						lexem->push_back(SPACE);
						state = SPACE;
					}
					else {
						lexem->push_back(HASHTAG);
					}
				}
				else {
					if (buffer[i] == '#') {
						lexem->push_back(HASHTAG);
						state = HASHTAG;
					}
					else if (isdigit(buffer[i])) {
						lexem->push_back(NUMBER);
						state = NUMBER;
					}
					else if (buffer[i] == '\n') {
						lexem->push_back(ENDLINE);
						state = ENDLINE;
					}
					else if (isspace(buffer[i])) {
						lexem->push_back(SPACE);
						state = SPACE;
					}
					else {
						return (true);
					}
				}
			}
			return (false);
		}
};

class Board {
	public:
		int size;
		int **board = nullptr;
		bool err;
		// Constructor
		Board(Lexer *lexer) {
			err = parse_file(lexer);
		}

		// Destructor
		~Board() {
			if (board) {
				for (int i = 0; i < size; ++i) {
					delete board[i];
				}
				delete board;
			}
		}

	private:
		bool verif_number_size(int number, int power) {
			int ten_power = 1;
			while (number /= 10) {
				ten_power++;
			}
			if (ten_power != power) {
				return (true);
			}
			return (false);
		}

		void init_board() {
			board = new int*[size];
			for (int i = 0; i < size; ++i) {
				board[i] = new int[size];
				for (int j = 0; j < size; ++j) {
					board[i][j] = -1;
				}
			}
		}

		bool check_value(int actual_row, int actual_col, int max) {
			if (board[actual_row][actual_col] > max) {
				return (true);
			}
			for (int row = 0; row < size; ++row) {
				for (int col = 0; col < size; ++col) {
					if (row == actual_row && col == actual_col) {
						return (false);
					}
					if (board[actual_row][actual_col] == board[row][col]) {
						return (true);
					}
				}
			}
			return (false);
		}

		bool parse_file(Lexer *lexer) {
			char	*test;
			int		characters;
			int		i = 0;
			int		col;
			int		row;
			int		max;

			while (i < lexer->length && lexer->lexem->at(i) != NUMBER) {
				++i;
			}
			size = strtol(&lexer->buffer[i], &test, 10);
			if (size <= 1 || size >= 4096) {
				return (true);
			}
			cout << "The size of the board is : " << size << endl;
			characters = test - &lexer->buffer[i];
			if (verif_number_size(size, characters)) {
				return (true);
			}
			i += characters;
			row = 0;
			while (i < lexer->length && lexer->lexem->at(i) != NUMBER) {
				if (lexer->lexem->at(i) == ENDLINE)
					row = 1;
				++i;
			}
			if (i == lexer->length) {
				return (true);
			}
			if (!row) {
				return (true);
			}
			init_board();
			max = size * size - 1;
			row = 0;
			while (i < lexer->length && row < size) {
				col = 0;
				while (i < lexer->length && col < size) {
					board[row][col] = strtol(&lexer->buffer[i], &test, 10);
					characters = test - &lexer->buffer[i];
					if (verif_number_size(size, characters)) {
						return (true);
					}
					if (check_value(row, col, max)) {
						return (true);
					}
					i += characters;
					++col;
					while (i < lexer->length && lexer->lexem->at(i) != NUMBER && lexer->lexem->at(i) != ENDLINE) {
						++i;
					}
					if (i != lexer->length) {
						if (col != size && lexer->lexem->at(i) == ENDLINE) {
							return (true);
						}
						if (col == size && lexer->lexem->at(i) == NUMBER) {
							return (true);
						}
					}
				}
				while (i < lexer->length && lexer->lexem->at(i) != NUMBER) {
					++i;
				}
				++row;
			}
			if (row != size || col != size) {
				return (true);
			}
			while (i < lexer->length) {
				if (lexer->lexem->at(i) == NUMBER) {
					return (true);
				}
				++i;
			}
			return (false);
		}
};

int main(int args_count, char **args_value) {
	if (args_count <= 1) {
		cout << "You should write at least one argument" << endl;
		return (1);
	}
	Lexer	*lexer = new Lexer(args_value[1]);
	if (lexer->err == true) {
		cout << "The file is not well formated : Lexer Error" << endl;
		delete lexer;
		return (1);
	}
	Board	*board = new Board(lexer);
	delete lexer;
	if (board->err == true) {
		cout << "The file is not well formated : Parser Error" << endl;
		delete board;
		return (1);
	}
	return (0);
}
