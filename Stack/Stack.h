#pragma once

#include "StackImplementation.h"
#include "LinkedListStack.h"
#include "MyVectorStack.h"

// Уровень абстракции
// клиентский код подключает именно этот хедер

// на основе какого контейнера работает стек
enum class StackContainer {
	Vector = 0,
	List,
	// можно дополнять другими контейнерами
};

// декларация класса с реализацией
template<typename T>
class StackImplementation;

template<typename T>
class Stack
{
public:
	// Большая пятерка
	///
	Stack(StackContainer container = StackContainer::Vector);
	// элементы массива последовательно подкладываются в стек
	Stack(const T* valueArray, const size_t arraySize, 
		  StackContainer container = StackContainer::Vector);

	explicit Stack(const Stack& copyStack);
	Stack& operator=(const Stack& copyStack);
	
	Stack(Stack&& moveStack) noexcept;
	Stack& operator=(Stack&& moveStack) noexcept;

	~Stack();
	///

	// добавление в хвост
	void push(const T& value);
	// удаление с хвоста
	void pop();
	// посмотреть элемент в хвосте
	T& top();
	const T& top() const;
	// проверка на пустоту
	bool isEmpty() const;
	// размер 
	size_t size() const;
private:
	StackImplementation<T>* _pimpl = nullptr; // указатель на имплементацию (уровень реализации)
	StackContainer _containerType; // тип контейнера, наверняка понадобится
};

///

template<typename T>
Stack<T>::Stack(StackContainer container) :
	_containerType(container)
{
	switch (_containerType) {
		case StackContainer::Vector:
			_pimpl = new VectorStack<T>();
			break;
		case StackContainer::List:
			_pimpl = new ListStack<T>();
			break;
		default:
			throw std::invalid_argument("Invalid container type");
	}
}

template<typename T>
Stack<T>::Stack(const T* valueArray, const size_t arraySize, StackContainer container) {
	switch (_containerType) {
		case StackContainer::Vector:
			_pimpl = new VectorStack<T>();
			break;
		case StackContainer::List:
			_pimpl = new ListStack<T>();
			break;
		default:
			throw std::invalid_argument("Invalid container type");
	}

	for (size_t i = 0; i < arraySize; ++i) {
		_pimpl->push(valueArray[i]);
	}
}

template<typename T>
Stack<T>::Stack(const Stack& copyStack) :
	_containerType(copyStack._containerType)
{
	switch (_containerType) {
		case StackContainer::Vector:
			_pimpl = new VectorStack<T>((VectorStack<T>&)(*copyStack._pimpl));
			break;
		case StackContainer::List:
			_pimpl = new ListStack<T>((ListStack<T>&)(*copyStack._pimpl));
			break;
		default:
			throw std::invalid_argument("Invalid container type");
	}
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack& copyStack) {
	if (this != &copyStack) {
		_containerType = copyStack._containerType;
		switch (_containerType) {
		case StackContainer::Vector:
			_pimpl = new VectorStack<T>((VectorStack<T>&)(*copyStack._pimpl));
			break;
		case StackContainer::List:
			_pimpl = new ListStack<T>((ListStack<T>&)(*copyStack._pimpl));
			break;
		default:
			throw std::invalid_argument("Invalid container type");
		}
	}
	return *this;
}

template<typename T>
Stack<T>::Stack(Stack&& moveStack) noexcept {
	std::swap(_pimpl, moveStack._pimpl);
	std::swap(_containerType, moveStack._containerType);
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack&& moveStack) noexcept {
	if (this != &moveStack) {
		_pimpl = nullptr;
		std::swap(_pimpl, moveStack._pimpl);
		std::swap(_containerType, moveStack._containerType);
	}
	return *this;
}

template<typename T>
Stack<T>::~Stack() {
	delete _pimpl;
}

template<typename T>
void Stack<T>::push(const T& value) {
	_pimpl->push(value);
}

template<typename T>
void Stack<T>::pop() {
	_pimpl->pop();
}

template<typename T>
T& Stack<T>::top() {
	return _pimpl->top();
}

template<typename T>
const T& Stack<T>::top() const {
	return _pimpl->top();
}

template<typename T>
bool Stack<T>::isEmpty() const {
	return _pimpl->isEmpty();
}

template<typename T>
size_t Stack<T>::size() const {
	return _pimpl->size();
}