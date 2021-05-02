#include "LinkedList.h"

int main() {
	LinkedList list;
	list.print();
	
    list.pushBack(1);
	list.pushBack(2);
	list.pushBack(3);
	list.pushBack(4);
	list.pushBack(5);
	std::cout << list.size() << std::endl;
	list.print();

	//list.clear();
	//std::cout << list.size() << std::endl;
	//list.print();
	LinkedList l2;
	l2.pushBack(3);

	try {
		l2 = list;
		l2.removeBack();
		std::cout << "LIST 2\n";
		std::cout << l2.size() << std::endl;
		l2.print();
		std::cout << "LIST 2 END\n";
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	return 0;	
}