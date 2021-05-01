#include "MyVector.h"

int main() {
	MyVector a;
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
	a.resize(30);
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