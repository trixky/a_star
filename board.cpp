#include <cstdlib>
#include <fstream>
#include <vector>
#include <iostream>
#include <string.h>
using namespace std;

#define HASHTAG 0
#define NUMBER 1
#define ENDLINE 2
#define START 3
#define SPACE 4

class Lexer {
public:
	Lexer(string path) {
		ifstream file(path, ifstream::binary);
		if (!file) {
			cout << "File cannot be loaded" << endl;
		}
		else {
			file.seekg(0, file.end);
			length = file.tellg();
			cout << length << endl;
			file.seekg(0, file.beg);
			buffer = new char [length];
			file.read(buffer, length);
			if (!file) {
				cout << "File cannot be read" << endl;
			}
			else {
				if (create_lexem()) {
					cout << "File is not well formated" << endl;
				}
			}
			file.close();
		}
	}

private:
	char	*buffer;
	int		length;

	bool create_lexem() {
		int state = START;
		for (int i; i < length; ++i) {
			if (state == START) {
				if (isdigit(buffer[i]))
					state = NUMBER;
				else if (buffer[i] == '#')
					state = HASHTAG;
				else if (isspace(buffer[i]))
					state = SPACE;
				else
					return (true);
			}
			else if (state == HASHTAG) {
				if (buffer[i] == '\n')
					state = ENDLINE;
				else if (buffer[i] == '#')
					state = SPACE;
			}
			else if (state == NUMBER) {
				if (isdigit(buffer[i]))
					state = NUMBER;
				else if (buffer[i] == '\n')
					state = ENDLINE;
				else if (isspace(buffer[i]))
					state = SPACE;
				else if (buffer[i] == '#')
					state = HASHTAG;
				else
					return (true);
			}
			else {
				if (buffer[i] == '#')
					state = HASHTAG;
				else if (isdigit(buffer[i]))
					state = NUMBER;
				else if (buffer[i] == '\n')
					state = ENDLINE;
				else if (isspace(buffer[i]))
					state = SPACE;
				else
					return (true);
			}
		}
		return (false);
	}
};

class Board {
	public:
		// Constructor
		Board(size_t rowcol) {
			size = rowcol;
			board = new int*[size];
			for (int i = 0; i < size; ++i) {
				board[i] = new int[size];
			}
		}

		// Destructor
		~Board() {
			for (int i = 0; i < size; ++i) {
				delete board[i];
			}
			delete board;
		}

	private:
		size_t size;
		int **board;
};

int main(int args_count, char **args_value) {
	if (args_count <= 1) {
		cout << "You should write at least one argument" << endl;
		return (1);
	}
	Lexer *lexer = new Lexer(args_value[1]);
	Board *board = new Board(2);
	delete board;
	return (0);
}
