#pragma once

#include <iostream>

// потом поменяем на шаблоны
using ValueType = int;

class LinkedList
{
	// класс узла списка
	// по своей сути, может содержать любые данные,
	// можно реализовать и ассоциативный массив, просто добавив 
	// поле с ключем в узел и, с учетом этого, поменять методы LinkedList 
	// (доступ по ключу, поиск по ключу и т.д.)
	struct Node {
		Node(const ValueType& value, Node* next = nullptr);
		~Node() = default;

		void insertNext(const ValueType& value);
		void removeNext();

		ValueType _value;
		Node* _next;
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

	// доступ к значению элемента по индексу
	const ValueType& at(const size_t pos) const;
	ValueType& at(const size_t pos);
	const ValueType& operator[](const size_t pos) const;
	ValueType& operator[](const size_t pos);
	// доступ к узлу по индексу
	//LinkedList::Node* getNode(const size_t pos) const;
	
	// вставка элемента по индексу, сначала ищем, куда вставлять (О(n)), потом вставляем (O(1))
	void insert(const size_t pos, const ValueType& value);
	// вставка элемента после узла, (O(1))
	void insertAfterNode(Node* node, const ValueType& value);
	// вставка в конец (О(n))
	void pushBack(const ValueType& value);
	// вставка в начало (О(1))
	void pushFront(const ValueType& value);


	// вывод списка
	void print() const;	

	// выполнение функции для каждого из элементов списка
	void forEach(void (*fn)(ValueType&));

	// трансформирование каждого элемента связанного списка с помощью функции
	void map(int (*fn)(ValueType));

	// фильтрация связанного списка
	void filter(bool (*fn)(ValueType));

	// удаление
	void remove(const size_t pos);
	void removeNextNode(Node* node);
	void removeFront();
	void removeBack();
	
	// поиск, О(n)
	long long int findIndex(const ValueType& value) const;
	Node* findNode(const ValueType& value) const;

	// разворот списка
	void reverse();						// изменение текущего списка
	LinkedList reverse() const;			// полчение нового списка (для константных объектов)
	LinkedList getReverseList() const;	// чтобы неконстантный объект тоже мог возвращать новый развернутый список

	void reverseSubList(const unsigned int start, const unsigned int end);

	size_t size() const;
private:
	Node*	_head;
	size_t	_size;

	void forceNodeDelete(Node* node);
};