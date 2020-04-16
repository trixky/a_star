#include <cmath>
using namespace std;

typedef struct	Point {
	int		x;
	int		y;
}				Point;

int		manhattan_distance(int **board, Point *goal, int size) {
	int			result = 0;

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (board[i][j] && (goal[board[i][j]].x != i || goal[board[i][j]].y != j)) {
				result += abs(i - goal[board[i][j]].x) + abs(j - goal[board[i][j]].y);
			}
		}
	}
	return (result);
}

int		hamming_distance(int **board, Point *goal, int size) {
	int			result = 0;

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (board[i][j] && (goal[board[i][j]].x != i || goal[board[i][j]].y != j)) {
				result++;
			}
		}
	}
	return (result);
}

int		linear_conflict_plus_manhattan_distance(int **board, Point *goal, int size) {
	int		manhattan_result = 0;
	int		linear_result = 0;

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (board[i][j] && (goal[board[i][j]].x != i || goal[board[i][j]].y != j)) {
				manhattan_result += abs(i - goal[board[i][j]].x) + abs(j - goal[board[i][j]].y);
				if (goal[board[i][j]].x == i) {
					for (int k = j + 1; k < size; k++) {
						if (board[i][k] && goal[board[i][k]].y == k) {
							linear_result += 2;
						}
					}
				}
				else {
					for (int k = i + 1; k < size; k++) {
						if (board[k][j] && goal[board[k][j]].x == k) {
							linear_result += 2;
						}
				}
			}
		}
	}
	return (manhattan_result + linear_result);
}
