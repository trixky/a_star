#include <vector>
#include <string.h>
using namespace std;

#define UP		0 // The 0 goes up
#define RIGHT	1 // The 0 goes right
#define DOWN	2 // The 0 goes down
#define LEFT	3 // The 0 goes left

class Lists {
	public:
		int		*board;
		int		*parent;
		long	hash;
		int		cost;
		int		past;
		int		total_cost;

		// Constructor
		Lists(int **actual_board, int move, int actual_cost, int actual_past, int size) {
			parent = new int[size * size];
			board = new int[size * size];
			int	position[2];

			for (int i = 0; i < size; ++i) {
				for (int j = 0; j < size; ++j) {
					if (actual_board[i][j] == 0) {
						position[0] = i;
						position[1] = j;
					}
					board[i * size + j] = actual_board[i][j];
					parent[i * size + j] = actual_board[i][j];
				}
			}
			if (move == UP) {
				board[position[0] * size + position[1]] = actual_board[position[0] - 1][position[1]];
				board[(position[0] - 1) * size + position[1]] = 0;
			}
			else if (move == RIGHT) {
				board[position[0] * size + position[1]] = actual_board[position[0]][position[1] + 1];
				board[position[0] * size + position[1] + 1] = 0;
			}
			else if (move == DOWN) {
				board[position[0] * size + position[1]] = actual_board[position[0] + 1][position[1]];
				board[(position[0] + 1) * size + position[1]] = 0;
			}
			else if (move == LEFT) {
				board[position[0] * size + position[1]] = actual_board[position[0]][position[1] - 1];
				board[position[0] * size + position[1] - 1] = 0;
			}
			//hash = hash_function((char*)board);
			cost = actual_cost;
			past = actual_past;
			total_cost = cost + past;
		}

		// Destructor
		~Lists() {
			delete board;
			delete parent;
		}
};

// Class for the priority queue (opened list)

class OpenedList {
	public:
		int				size;
		vector<Lists>	*elem = new vector<Lists>;

		// Constructor
		OpenedList() {
			size = 0;
		}

		// Destructor
		~OpenedList() {
			int		i = 0;

			while (i < size) {
				delete elem->at(i).board;
				i++;
			}
			delete elem;
		}

		void	insert(Lists item) {
			int		i = 0;
			while (i < size) {
				if (elem->at(i).total_cost < item.total_cost) {
					elem->insert(elem->begin() + i, item);
					break ;
				}
				i++;
			}
			if (i == size)
				elem->push_back(item);
			size++;
		}
};

// Class for the closed list

class ClosedList {
	public:
		vector<Lists>	*elem = new vector<Lists>;
		int				size;

		ClosedList() {
			size = 0;
		}

		~ClosedList() {
			int		i = 0;

			while (i < size) {
				delete elem->at(i).board;
				i++;
			}
			delete elem;
		}

		// Return true if it s already done
		bool	already_done(Lists item, int size_square) {
			for (int i = 0; i < size; ++i) {
				if (elem->at(i).hash == item.hash) {
					if (!memcmp(elem->at(i).board, item.board, 4 * size_square)) {
						if (elem->at(i).total_cost > item.total_cost) {
							elem->erase(elem->begin() + i);
							return (false);
						}
						return (true);
					}
				}
			}
			return (false);
		}

		// Add a new elem to the closed list
		void	add_elem(Lists item) {
			elem.push_back(item);
		}
};
