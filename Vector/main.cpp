#include "MyVector.h"

int main() {
	MyVector a(1, 12);
	for (int i = 0; i < a.size(); ++i) {
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "size = " << a.size() << " capacity = " << a.capacity() << std::endl;

	a.pushBack(1);
	for (int i = 0; i < a.size(); ++i) {
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "size = " << a.size() << " capacity = " << a.capacity() << std::endl;
	/*
	for (int i = 0; i < 10; ++i) {
		a.pushBack(i);
	}
	for (int i = 0; i < a.size(); ++i) {
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "size = " << a.size() << " capacity = " << a.capacity() << std::endl;

	*/
}