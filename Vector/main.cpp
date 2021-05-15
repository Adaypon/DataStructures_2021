#include "MyVector.h"

int main() {
	MyVector a;
	for (int i = 0; i < a.size(); ++i) {
		std::cout << i << ": "<< a[i] << std::endl;
	}
	std::cout << std::endl;

	std::cout << "size = " << a.size() << " capacity = " << a.capacity() << std::endl;
	a.reserve(30);
	for (int i = 0; i < a.size(); ++i) {
		std::cout << i << ": "<< a[i] << std::endl;
	}
	std::cout << std::endl;
	std::cout << "size = " << a.size() << " capacity = " << a.capacity() << std::endl;
	a.resize(50);
	std::cout << "size = " << a.size() << " capacity = " << a.capacity() << std::endl;
	for (int i = 0; i < a.size(); ++i) {
		std::cout << i << ": "<< a[i] << std::endl;
	}
	std::cout << std::endl;

	return 0;	
}