#pragma once

#include <iostream>

template<typename T>
class LinkedList
{
	// класс узла списка
	// по своей сути, может содержать любые данные,
	// можно реализовать и ассоциативный массив, просто добавив 
	// поле с ключем в узел и, с учетом этого, поменять методы LinkedList 
	// (доступ по ключу, поиск по ключу и т.д.)
	struct Node {
		Node(const T& value, Node* next = nullptr);
		~Node() = default;

		T _value;
		Node* _next;
	};

	class ListIterator {
	public:
		using iterator_category = std::forward_iterator_tag;
		using difference_type   = std::ptrdiff_t;
		using value_type        = T;
		using pointer           = T*;
		using reference         = T&;

		ListIterator(Node* ptr, size_t idx);
        
        ListIterator(const ListIterator& copy);
        ListIterator& operator=(const ListIterator& copy);

        reference operator*();
        pointer operator->();
        ListIterator& operator++();
        ListIterator operator++(int _);
        bool operator==(const ListIterator& other);
        bool operator!=(const ListIterator& other);
        difference_type operator-(const ListIterator& other);

        size_t getIndex() const;
		Node* getPtr() const;
	private:
		Node* _ptr;
		size_t _index;
	};

public:
	////
	LinkedList();
	LinkedList(const LinkedList& copyList);
	LinkedList& operator=(const LinkedList& copyList);

	LinkedList(LinkedList&& moveList) noexcept;
	LinkedList& operator=(LinkedList&& moveList) noexcept;

	~LinkedList();
	////

	ListIterator begin() const;
    ListIterator end() const;

	// доступ к значению элемента по индексу
	const T& at(const size_t pos) const;
	T& at(const size_t pos);
	const T& operator[](const size_t pos) const;
	T& operator[](const size_t pos);
	// доступ к узлу по индексу
	LinkedList::Node* getNode(const size_t pos) const;
	
	// вставка элемента по индексу, сначала ищем, куда вставлять (О(n)), потом вставляем (O(1))
	void insert(const size_t pos, const T& value);
	// вставка элемента после узла, (O(1))
	void insertAfterNode(ListIterator it, const T& value);
	// вставка в конец (О(n))
	void pushBack(const T& value);
	// вставка в начало (О(1))
	void pushFront(const T& value);


	// вывод списка
	void print() const;	

	// выполнение функции для каждого из элементов списка
	void forEach(void (*fn)(T&));

	// трансформирование каждого элемента связанного списка с помощью функции
	void map(T (*fn)(T));

	// фильтрация связанного списка
	void filter(bool (*fn)(T));

	// удаление
	void remove(const size_t pos);
	void removeNextNode(ListIterator it);
	void removeFront();
	void removeBack();
	void clear();

	// поиск, О(n)
	size_t findIndex(const T& value) const;
	Node* findNode(const T& value) const;

	// разворот списка
	void reverse();						// изменение текущего списка
	void reverseSubList(const unsigned int start, const unsigned int end); // изменение списка с позиции start по end
	LinkedList<T> getReverseList() const;	// чтобы неконстантный объект тоже мог возвращать новый развернутый список
	LinkedList<T> getReverseList(const unsigned int start, const unsigned int end) const;

	

	size_t size() const;
private:
	Node*	_head;
	size_t	_size;

	void forceNodeDelete(Node* node);
};


template<typename T>
LinkedList<T>::Node::Node(const T& value, Node* next) : 
	_value(value),
	_next(next)
{

}

/// Iterators section

template<typename T>
LinkedList<T>::ListIterator::ListIterator(Node* ptr, size_t idx) :
	_ptr(ptr),
	_index(idx)
{

}

template<typename T>
LinkedList<T>::ListIterator::ListIterator(const LinkedList<T>::ListIterator& copy) :
	_ptr(copy._ptr),
	_index(copy._index)
{

}

template<typename T>
typename LinkedList<T>::ListIterator& LinkedList<T>::ListIterator::operator=(const LinkedList<T>::ListIterator& copy) {
	if (this != &copy) {
		_ptr = copy._ptr;
		_index = copy._index;
	}
	return *this;
}

template<typename T>
T& LinkedList<T>::ListIterator::operator*() {
	return _ptr->_value;
}
template<typename T>
T* LinkedList<T>::ListIterator::operator->() {
	return &(_ptr->_value);
}

template<typename T>
typename LinkedList<T>::ListIterator& LinkedList<T>::ListIterator::operator++() {
	_ptr = _ptr->_next;
	++_index;
	return *this;
}

template<typename T>
typename LinkedList<T>::ListIterator LinkedList<T>::ListIterator::operator++(int _) {
	auto tmp = *this;
	++(*this);
	return tmp;
}

template<typename T>
bool LinkedList<T>::ListIterator::operator==(const LinkedList<T>::ListIterator& other) {
	return _ptr == other._ptr;
}

template<typename T>
bool LinkedList<T>::ListIterator::operator!=(const LinkedList<T>::ListIterator& other) {
	return !(*this == other);
}	

template<typename T>
std::ptrdiff_t LinkedList<T>::ListIterator::operator-(const LinkedList<T>::ListIterator& other) {
	return _ptr - other._ptr;
}

template<typename T>
size_t LinkedList<T>::ListIterator::getIndex() const {
	return _index;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::ListIterator::getPtr() const {
	return _ptr;
}

///

template<typename T>
LinkedList<T>::LinkedList() :
	_head(nullptr),
	_size(0)
{

}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& copyList) {
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

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& copyList) {
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


template<typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& moveList) noexcept :
	_head(nullptr),
	_size(0)
{
	std::swap(_head, moveList._head);
	std::swap(_size, moveList._size);
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& moveList) noexcept {
	if (this != &moveList) {
		if (_head) {
			clear();
		}
		std::swap(_head, moveList._head);
		std::swap(_size, moveList._size);
	}
	return *this;
}

template<typename T>
LinkedList<T>::~LinkedList() {
	clear();
};


template<typename T>
typename LinkedList<T>::ListIterator LinkedList<T>::begin() const {
	return LinkedList<T>::ListIterator(_head, 0);
}

template<typename T>
typename LinkedList<T>::ListIterator LinkedList<T>::end() const {
	return LinkedList<T>::ListIterator(nullptr, size());
}

template<typename T>
const T& LinkedList<T>::at(const size_t pos) const {
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

template<typename T>
const T& LinkedList<T>::operator[](const size_t pos) const {
	return at(pos);
}

template<typename T>
T& LinkedList<T>::at(const size_t pos) {
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

template<typename T>
T& LinkedList<T>::operator[](const size_t pos) {
	return at(pos);
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::getNode(const size_t pos) const {
	if (pos >= size()) {
		throw std::out_of_range("Called at getNode(): pos >= size");
	}
	auto it = begin();
	for (; it != end(); ++it) {
		if (it.getIndex() == pos) {
			break;
		}
	}
	return it.getPtr();
}


template<typename T>
void LinkedList<T>::insert(const size_t pos, const T& value) {
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

template<typename T>
void LinkedList<T>::pushBack(const T& value) {
	this->insert(size(), value);
}


template<typename T>
void LinkedList<T>::pushFront(const T& value) {
	this->insert(0, value);
}


template<typename T>
void LinkedList<T>::insertAfterNode(LinkedList<T>::ListIterator it, const T& value) {
	insert(it.getIndex() + 1, value);
}

template<typename T>
void LinkedList<T>::print() const {
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

template<typename T>
void LinkedList<T>::forEach(void (*fn)(T&)) {
	Node* cur = _head;
	while(cur) {
		fn(cur->_value);
		cur = cur->_next;
	}
}


template<typename T>
void LinkedList<T>::map(T (*fn)(T)) {
	Node* cur = _head;

	while(cur) {
		cur->_value = fn(cur->_value);
		cur = cur->_next;
	}
}


template<typename T>
void LinkedList<T>::filter(bool (*fn)(T)) {
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

template<typename T>
void LinkedList<T>::remove(const size_t pos) {
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

template<typename T>
void LinkedList<T>::removeNextNode(LinkedList<T>::ListIterator it) {
	remove(it.getIndex() + 1);
}

template<typename T>
void LinkedList<T>::removeFront() {
	this->remove(0);
}

template<typename T>
void LinkedList<T>::removeBack() {
	this->remove(size()-1);
}

template<typename T>
void LinkedList<T>::clear() {
	while (_head) {
		this->removeFront();
	}
}


template<typename T>
size_t LinkedList<T>::findIndex(const T& value) const {
	for (auto it = begin(); it != end(); ++it) {
		if (*it == value) {
			return it.getIndex();
		}
	}
	return -1;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::findNode(const T& value) const {
	for (auto it = begin(); it != end(); ++it) {
		if (*it == value) {
			return it.getPtr();
		}
	}
	return nullptr;
}

template<typename T>
void LinkedList<T>::reverse() {
	this->reverseSubList(0, size()-1);
}

template<typename T>
void LinkedList<T>::reverseSubList(const unsigned int start, const unsigned int end) {
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

template<typename T>
LinkedList<T> LinkedList<T>::getReverseList() const {
	LinkedList<T> reversedList = *this;
	reversedList.reverse();
	return reversedList;
}

template<typename T>
LinkedList<T> LinkedList<T>::getReverseList(const unsigned int start, const unsigned int end) const {
	LinkedList<T> reversedList = *this;
	reversedList.reverseSubList(start, end);
	return reversedList;
}


template<typename T>
size_t LinkedList<T>::size() const {
	return _size;
}