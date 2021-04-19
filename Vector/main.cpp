#include "Vector.h"

int main() {
	Vector a;
	for (size_t i = 1; i <= 10; ++i) {
		a.pushBack(i);
	}
	a.pushBack(9);

	for (size_t i = 0; i < a.size(); ++i) {
		std::cout << a[i] << ' ';
	}
	std::cout << std::endl;

	std::cout << a.find(9) << std::endl;

	return 0;
}