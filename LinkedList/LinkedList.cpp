#include "LinkedList.h"


LinkedList::Node::Node(const ValueType& value, Node* next) : 
	_value(value),
	_next(next)
{

}

/// Iterators section

LinkedList::ListIterator::ListIterator(Node* ptr, size_t idx) :
	_ptr(ptr),
	_index(idx)
{

}

LinkedList::ListIterator::ListIterator(const LinkedList::ListIterator& copy) :
	_ptr(copy._ptr),
	_index(copy._index)
{

}

LinkedList::ListIterator& LinkedList::ListIterator::operator=(const LinkedList::ListIterator& copy) {
	if (this != &copy) {
		_ptr = copy._ptr;
		_index = copy._index;
	}
	return *this;
}

ValueType& LinkedList::ListIterator::operator*() {
	return _ptr->_value;
}
ValueType* LinkedList::ListIterator::operator->() {
	return &(_ptr->_value);
}

LinkedList::ListIterator& LinkedList::ListIterator::operator++() {
	_ptr = _ptr->_next;
	++_index;
	return *this;
}

LinkedList::ListIterator LinkedList::ListIterator::operator++(int _) {
	auto tmp = *this;
	++(*this);
	return tmp;
}

bool LinkedList::ListIterator::operator==(const LinkedList::ListIterator& other) {
	return _ptr == other._ptr;
}

bool LinkedList::ListIterator::operator!=(const LinkedList::ListIterator& other) {
	return !(*this == other);
}	

std::ptrdiff_t LinkedList::ListIterator::operator-(const LinkedList::ListIterator& other) {
	return _ptr - other._ptr;
}

size_t LinkedList::ListIterator::getIndex() const {
	return _index;
}

///

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
	if (this != &copyList) {
		if (_head) {
			clear();
		}
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
		if (_head) {
			clear();
		}
		std::swap(_head, moveList._head);
		std::swap(_size, moveList._size);
	}
	return *this;
}


LinkedList::~LinkedList() {
	clear();
};


LinkedList::ListIterator LinkedList::begin() const {
	return LinkedList::ListIterator(_head, 0);
}

LinkedList::ListIterator LinkedList::end() const {
	return LinkedList::ListIterator(nullptr, size());
}

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

LinkedList::ListIterator LinkedList::getNode(const size_t pos) const {
	if (pos >= size()) {
		throw std::out_of_range("Called at getNode(): pos >= size");
	}
	auto it = begin();
	for (; it != end(); ++it) {
		if (it.getIndex() == pos) {
			break;
		}
	}
	return it;
}


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
		Node* prev = nullptr;
		for (size_t i = 0; i < pos; ++i) {
			if (!prev) { // in head
				prev = _head;
			}
			else {
				prev = cur;
			}
			cur = cur->_next;
		}

		if (!prev) { // pos == 0
			node->_next = cur;
			_head = node;
		}
		else {
			prev->_next = node;
			node->_next = cur;
		}
	}
	++_size;
}

void LinkedList::pushBack(const ValueType& value) {
	this->insert(size(), value);
}


void LinkedList::pushFront(const ValueType& value) {
	this->insert(0, value);
}


void LinkedList::insertAfterNode(LinkedList::ListIterator it, const ValueType& value) {
	insert(it.getIndex() + 1, value);
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


void LinkedList::remove(const size_t pos) {
	if (pos >= size()) {
		throw std::out_of_range("Called at remove(): pos >= size");
	}

	Node* cur = _head;
	Node* prev = nullptr;
	for (size_t i = 0; i < pos; ++i) {
		if (!prev) { // in head
			prev = _head;
		}
		else {
			prev = cur;
		}
		cur = cur->_next;
	}

	if (!prev) { // pos == 0
		_head = _head->_next;
	}
	else {
		prev->_next = cur->_next;
	}
	delete cur;

	--_size;
}

void LinkedList::removeFront() {
	this->remove(0);
}

void LinkedList::removeBack() {
	this->remove(size()-1);
}

void LinkedList::clear() {
	while (_head) {
		this->removeFront();
	}
}


//TODO findIndex
//TODO findNode


void LinkedList::reverse() {
	this->reverseSubList(0, size()-1);
}

void LinkedList::reverseSubList(const unsigned int start, const unsigned int end) {
	if (start >= end) {
		return;
	}

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
		_head = endNode;
	}
}

LinkedList LinkedList::getReverseList() const {
	LinkedList reversedList = *this;
	reversedList.reverse();
	return reversedList;
}

LinkedList LinkedList::getReverseList(const unsigned int start, const unsigned int end) const {
	LinkedList reversedList = *this;
	reversedList.reverseSubList(start, end);
	return reversedList;
}


size_t LinkedList::size() const {
	return _size;
}