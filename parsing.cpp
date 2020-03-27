#include <cstdlib>
using namespace std;

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

int main() {
	Board board = Board(2);
	return (0);
}
