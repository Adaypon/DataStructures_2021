#include "LinkedList.h"

int main() {
	LinkedList list;
	list.print();
	
    list.pushBack(1);
	list.pushBack(2);
	list.pushBack(3);
	list.print();
	try	{
		list.insert(0, 9);
	}
	catch(std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << list.size() << std::endl;
	list.print();
	/*
	LinkedList l2 = list;
	l2.print();
	list.removeFront();
	list.print();
	l2.print();
	std::cout << list.size() << " " << l2.size() << std::endl;
	*/
	return 0;	
}