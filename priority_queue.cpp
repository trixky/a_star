#include <vector>
#include <string.h>
using namespace std;

typedef struct	Lists {
	int		*board;
	long	hash;
	int		cost;
	int		remaining;
	int		total_cost;
}				Lists;

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
						return (true);
					}
				}
			}
			return (false);
		}
};
