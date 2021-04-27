#include "LinkedList.h"


LinkedList::Node::Node(const ValueType& value, Node* next) : 
	_value(value),
	_next(next)
{

}


LinkedList::LinkedList() :
	_head(nullptr),
	_size(0)
{

}

LinkedList::LinkedList(const LinkedList& copyList) {
	_size = copyList._size;
	if (!copyList._head) {
		_head == nullptr;
	}
	else {
		_head = new Node(copyList._head->_value);
		Node* cur = _head;
		Node* curCopy = copyList._head;
		while (curCopy->_next) {
			cur->_next = new Node(curCopy->_next->_value);
			curCopy = curCopy->_next;
			cur = cur->_next;
		}
	}	
}

LinkedList& LinkedList::operator=(const LinkedList& copyList) {
	//TODO delete old list before ?
	if (this != &copyList) {
		LinkedList tmpList(copyList);
		_head = tmpList._head;
		_size = tmpList._size;
	}
	return *this;
}


LinkedList::LinkedList(LinkedList&& moveList) noexcept :
	_head(nullptr),
	_size(0)
{
	std::swap(_head, moveList._head);
	std::swap(_size, moveList._size);
}

LinkedList& LinkedList::operator=(LinkedList&& moveList) noexcept {
	if (this != &moveList) {
		std::swap(_head, moveList._head);
		std::swap(_size, moveList._size);
	}
	return *this;
}


LinkedList::~LinkedList() {
	while (_head) {
		this->removeFront();
	}
};




const ValueType& LinkedList::at(const size_t pos) const {
	if (pos >= size()) {
		throw std::out_of_range("Called at at(): pos >= size");
	}
	Node* cur = _head;
	for (size_t i = 0; i < pos && cur; ++i) {
		cur = cur->_next;
	}
	if (cur) {
		return cur->_value;
	}
	else {
		throw std::out_of_range("Called at at(): nullptr"); //TODO подумать над формулировкой исключения
	}
}

const ValueType& LinkedList::operator[](const size_t pos) const {
	return at(pos);
}

ValueType& LinkedList::at(const size_t pos) {
	if (pos >= size()) {
		throw std::out_of_range("Called at at(): pos >= size");
	}
	Node* cur = _head;
	for (size_t i = 0; i < pos && cur; ++i) {
		cur = cur->_next;
	}
	if (cur) {
		return cur->_value;
	}
	else {
		throw std::out_of_range("Called at at(): nullptr"); //TODO подумать над формулировкой исключения
	}
}

ValueType& LinkedList::operator[](const size_t pos) {
	return at(pos);
}

//TODO insert
void LinkedList::insert(const size_t pos, const ValueType& value) {
	if (pos > size()) {
		throw std::out_of_range("Called at insert(): pos > size");
	}
	Node* node = new Node(value);

	if (!_head) {
		_head = node;
	}
	else {
		Node* cur = _head;
		for (size_t i = 0; i < pos && cur; ++i) {
			cur = cur->_next;
		}
		Node* next = cur->_next;
		cur = node;
		node->_next = next;
	}
}




void LinkedList::pushBack(const ValueType& value) {
	Node* node = new Node(value);
	if (!_head) {
		_head = node;
	}
	else {
		Node* cur = _head;
		while (cur->_next) {
			cur = cur->_next;
		}
		cur->_next = node;
	}
	++_size;
}


void LinkedList::pushFront(const ValueType& value) {
	Node* node = new Node(value);
	if (_head) {
		node->_next = _head;
	}
	_head = node;
	++_size;
}

void LinkedList::print() const {
	if (!_head) {
		std::cout << "(nullptr)" << std::endl;
		return;
	}
	Node* cur = _head;
	do {
		std::cout << cur->_value << " -> ";
	} while(cur = cur->_next);
	std::cout << "(nullptr)" << std::endl;
}

void LinkedList::forEach(void (*fn)(ValueType&)) {
	Node* cur = _head;
	while(cur) {
		fn(cur->_value);
		cur = cur->_next;
	}
}

void LinkedList::map(ValueType (*fn)(ValueType)) {
	Node* cur = _head;

	while(cur) {
		cur->_value = fn(cur->_value);
		cur = cur->_next;
	}
}


void LinkedList::filter(bool (*fn)(ValueType)) {
	Node* cur = _head;
	Node* prev = nullptr;
	
	while (cur) {
		if (!fn(cur->_value)) {
			if (!prev) { // in head
				this->removeFront();
				cur = _head->_next;
				prev = _head;
			}
			else {
				prev->_next = cur->_next;
				delete cur;
				
				//для следующей итерации
				cur = prev->_next;
			}
		}
		else {
			prev = cur;
			cur = cur->_next;
		}
	}	
}

void LinkedList::removeFront() {
	Node* tmp = _head;
	_head = _head->_next;
	delete tmp;
	--_size;
}



void LinkedList::reverse() {
	Node* cur = _head;
	Node* prev = nullptr;
	Node* next = nullptr;

	while (cur) {
		next = cur->_next;
		cur->_next = prev; //swap pointer to prev node
		prev = cur;
		cur = next; // moving to the next node
	}
	_head = prev; // set new movement
}

/*
void LinkedList::reverse() {
	this->reverseSubList(0, size()-1);
}
*/
void LinkedList::reverseSubList(unsigned int start, unsigned int end) {
	if (start >= end) {
		return;
	}

	std::cout << "tmp\n";

	
	Node* cur = _head;
	Node* prev = nullptr;
	Node* next = nullptr;

	for (size_t i = 0; i < start && cur; ++i) {
		prev = cur;
		cur = cur->_next;
	}

	Node* startNode = cur;
	Node* endNode = nullptr;
	for (size_t i = 0; i < end - start + 1 && cur; ++i) {
		next = cur->_next;
		cur->_next = endNode; // swap pointer to end node
		endNode = cur;
		cur = next; // moving to the next node
	}
	
	// set new movement
	startNode->_next = cur; 
	if (prev) {
		prev->_next = endNode;
	}
	else {
		_head = prev;
	}
}


size_t LinkedList::size() const {
	return _size;
}