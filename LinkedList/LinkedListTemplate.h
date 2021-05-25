#pragma once

#include <iostream>

// потом поменяем на шаблоны
// using ValueType = int;

template<typename T>
class LinkedList
{
	// класс узла списка
	// по своей сути, может содержать любые данные,
	// можно реализовать и ассоциативный массив, просто добавив 
	// поле с ключем в узел и, с учетом этого, поменять методы LinkedList 
	// (доступ по ключу, поиск по ключу и т.д.)
	struct Node {
		Node(const T& value, Node* next = nullptr) : _value(value),	_next(next) {}
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

		ListIterator(Node* ptr, size_t idx) : _ptr(ptr), _index(idx) {}
        
        ListIterator(const ListIterator& copy) : _ptr(copy._ptr), _index(copy._index) {}
        ListIterator& operator=(const ListIterator& copy) {
			if (this != &copy) {
				_ptr = copy._ptr;
				_index = copy._index;
			}
			return *this;
		}

        reference operator*() { return _ptr->_value; }
        pointer operator->() { return &(_ptr->_value); }
        ListIterator& operator++() {
			_ptr = _ptr->_next;
			++_index;
			return *this;
		}
        ListIterator operator++(int _) {
			auto tmp = *this;
			++(*this);
			return tmp;
		}
        bool operator==(const ListIterator& other) { return _ptr == other._ptr; }
        bool operator!=(const ListIterator& other) { return !(*this == other); }
        difference_type operator-(const ListIterator& other) { return _ptr - other._ptr; }

        size_t getIndex() const { return _index; }
		Node* getPtr() const { return _ptr; }
	private:
		Node* _ptr;
		size_t _index;
	};

public:
	////
	LinkedList() : _head(nullptr), _size(0) {}
	LinkedList(const LinkedList& copyList) {
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
	LinkedList& operator=(const LinkedList& copyList) {
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

	LinkedList(LinkedList&& moveList) noexcept : _head(nullptr), _size(0)
	{
		std::swap(_head, moveList._head);
		std::swap(_size, moveList._size);
	}
	LinkedList& operator=(LinkedList&& moveList) noexcept {
		if (this != &moveList) {
			if (_head) {
				clear();
			}
			std::swap(_head, moveList._head);
			std::swap(_size, moveList._size);
		}
		return *this;
	}

	~LinkedList() { clear(); }
	////

	ListIterator begin() const { return LinkedList::ListIterator(_head, 0); }
    ListIterator end() const { return LinkedList::ListIterator(nullptr, size()); }

	// доступ к значению элемента по индексу
	const T& at(const size_t pos) const {
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

	T& at(const size_t pos) {
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

	const T& operator[](const size_t pos) const { return at(pos); }
	T& operator[](const size_t pos) { return at(pos); }

	// доступ к узлу по индексу
	LinkedList::Node* getNode(const size_t pos) const {
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
	
	// вставка элемента по индексу, сначала ищем, куда вставлять (О(n)), потом вставляем (O(1))
	void insert(const size_t pos, const T& value) {
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

	// вставка элемента после узла, (O(1))
	void insertAfterNode(ListIterator it, const T& value) { insert(it.getIndex() + 1, value); }
	// вставка в конец (О(n))
	void pushBack(const T& value) { this->insert(size(), value); }
	// вставка в начало (О(1))
	void pushFront(const T& value) { this->insert(0, value); }


	// вывод списка
	void print() const {
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

	// выполнение функции для каждого из элементов списка
	void forEach(void (*fn)(T&)) {
		Node* cur = _head;
		while(cur) {
			fn(cur->_value);
			cur = cur->_next;
		}
	}

	// трансформирование каждого элемента связанного списка с помощью функции
	void map(int (*fn)(T)) {
		Node* cur = _head;
		while(cur) {
			cur->_value = fn(cur->_value);
			cur = cur->_next;
		}
	}

	// фильтрация связанного списка
	void filter(bool (*fn)(T)) {
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

	// удаление
	void remove(const size_t pos) {
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

	void removeNextNode(ListIterator it) { remove(it.getIndex() + 1); }
	void removeFront() { this->remove(0); }
	void removeBack() { this->remove(size()-1); }
	void clear() {
		while (_head) {
			this->removeFront();
		}
	}

	// поиск, О(n)
	size_t findIndex(const T& value) const {
		for (auto it = begin(); it != end(); ++it) {
			if (*it == value) {
				return it.getIndex();
			}
		}
		return -1;
	}
	Node* findNode(const T& value) const {
		for (auto it = begin(); it != end(); ++it) {
			if (*it == value) {
				return it.getPtr();
			}
		}
		return nullptr;
	}

	// разворот списка
	// изменение текущего списка
	void reverse() { this->reverseSubList(0, size()-1); }
	// изменение списка с позиции start по end						
	void reverseSubList(const unsigned int start, const unsigned int end) {
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

	// чтобы неконстантный объект тоже мог возвращать новый развернутый список
	LinkedList getReverseList() const {
		LinkedList reversedList = *this;
		reversedList.reverse();
		return reversedList;
	}
	LinkedList getReverseList(const unsigned int start, const unsigned int end) const {
		LinkedList reversedList = *this;
		reversedList.reverseSubList(start, end);
		return reversedList;
	}

	

	size_t size() const { return _size; }
private:
	Node*	_head;
	size_t	_size;

	void forceNodeDelete(Node* node);
};