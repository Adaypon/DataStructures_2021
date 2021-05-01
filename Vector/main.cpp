#include "MyVector.h"

int main() {
	MyVector a(5);
	for (int i = 0; i < a.size(); ++i) {
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "size = " << a.size() << " capacity = " << a.capacity() << std::endl;

	for (int i = 0; i < 8; ++i) {
		a.pushBack(9);
	}
	for (int i = 0; i < a.size(); ++i) {
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "size = " << a.size() << " capacity = " << a.capacity() << std::endl;
	return 0;
}