#include "MyVector.h"

int main() {
	MyVector a(5, 3);
	for (int i = 0; i < a.size(); ++i) {
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "size = " << a.size() << " capacity = " << a.capacity() << std::endl;

	a.pushBack(9);
	for (int i = 0; i < a.size(); ++i) {
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "size = " << a.size() << " capacity = " << a.capacity() << std::endl;
	return 0;
}