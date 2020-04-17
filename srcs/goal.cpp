#include "goal.hpp"

Goal::Goal(int size) {
	int		i = 0;
	int		j = 0;
	Point	sens;
	int		top = 1;
	int		bottom = 0;
	int		right = 0;
	int		left = 0;
	int		actual = 1;
	int		max = size * size;
	int		size_minus_one = size - 1;

	sens.x = 0;
	sens.y = 1;
	pos = new Point[max];
	while (actual < max) {
		pos[actual].x = i;
		pos[actual].y = j;
		if (sens.y == 1 && j + right == size_minus_one) {
			sens.x = 1;
			sens.y = 0;
			right++;
		}
		else if (sens.x == 1 && i + bottom == size_minus_one) {
			sens.x = 0;
			sens.y = -1;
			bottom++;
		}
		else if (sens.y == -1 && j == left) {
			sens.x = -1;
			sens.y = 0;
			left++;
		}
		else if (sens.x == -1 && i == top) {
			sens.x = 0;
			sens.y = 1;
			top++;
		}
		i += sens.x;
		j += sens.y;
		actual++;
	}
	pos[0].x = i;
	pos[0].y = j;
}

Goal::~Goal() {
	delete pos;
}
