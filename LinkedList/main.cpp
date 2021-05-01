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

	list.reverseSubList(1, 3);
	list.print();

	return 0;	
}