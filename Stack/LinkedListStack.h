#pragma once

#include "StackImplementation.h"
#include "../LinkedList/LinkedListTemplate.h"

// вариант с использованием ранее написанного списка и множественного наследования
// если бы список не был реализован, то было бы наследование только от интерфейса
// множественное наследование можно заменить на композицию
template<typename T>
class ListStack : public StackImplementation<T>, public LinkedList<T>
{
public:
	///
	ListStack();

    ListStack(const ListStack<T>& other);
    ListStack(ListStack<T>&& other) noexcept;

	ListStack<T>& operator=(const ListStack& other);
    ListStack<T>& operator=(ListStack&& other) noexcept;

	~ListStack() = default;
	///

	// добавление в хвост
	void push(const T& value) override;
	// удаление с хвоста
	void pop() override;
	// посмотреть элемент в хвосте
	const T& top() const override;
	// проверка на пустоту
	bool isEmpty() const override;
	// размер 
	size_t size() const override;

private:
	LinkedList<T> _listStack;
};

///

template<typename T>
ListStack<T>::ListStack() :
	_listStack(LinkedList<T>())
{

}

template<typename T>
ListStack<T>::ListStack(const ListStack<T>& other) :
	_listStack(other._listStack)
{

}

template<typename T>
ListStack<T>& ListStack<T>::operator=(const ListStack<T>& other) {
	_listStack = other._listStack;
	return *this;
}

template<typename T>
ListStack<T>::ListStack(ListStack<T>&& other) noexcept :
	_listStack(std::move(other._listStack))
{
	
}

template<typename T>
ListStack<T>& ListStack<T>::operator=(ListStack&& other) noexcept {
	_listStack = std::move(other._listStack);
	return *this;
}

///

template<typename T>
void ListStack<T>::push(const T& value) {
	_listStack.pushBack(value);
}

template<typename T>
void ListStack<T>::pop() {
	_listStack.removeBack();
}

template<typename T>
const T& ListStack<T>::top() const {
	if (isEmpty()) {
		throw std::out_of_range("Stack is empty");
	}
	return _listStack[size() - 1];
}

template<typename T>
bool ListStack<T>::isEmpty() const {
	return _listStack.size() == 0;
}

template<typename T>
size_t ListStack<T>::size() const {
	return _listStack.size();
}