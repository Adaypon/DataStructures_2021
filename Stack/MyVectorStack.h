#pragma once

#include "StackImplementation.h"
#include "../Vector/MyVectorTemplate.h"

// вариант с использованием ранее написанного вектора и множественного наследования
// если бы вектор не был реализован, то было бы наследование только от интерфейса
// множественное наследование можно заменить на композицию
template<typename T>
class VectorStack : public StackImplementation<T>, public MyVector<T>
{
public:
	///
	VectorStack();

    VectorStack(const VectorStack<T>& other);
    VectorStack(VectorStack<T>&& other) noexcept;

	VectorStack<T>& operator=(const VectorStack& other);
    VectorStack<T>& operator=(VectorStack&& other) noexcept;

	~VectorStack() = default;
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
	MyVector<T> _vectorStack;
};

///

template<typename T>
VectorStack<T>::VectorStack() :
	_vectorStack(MyVector<T>())
{

}

template<typename T>
VectorStack<T>::VectorStack(const VectorStack<T>& other) :
	_vectorStack(other._vectorStack)
{

}

template<typename T>
VectorStack<T>& VectorStack<T>::operator=(const VectorStack<T>& other) {
	_vectorStack = other._vectorStack;
	return *this;
}

template<typename T>
VectorStack<T>::VectorStack(VectorStack<T>&& other) noexcept :
	_vectorStack(std::move(other._vectorStack))
{
	
}

template<typename T>
VectorStack<T>& VectorStack<T>::operator=(VectorStack&& other) noexcept {
	_vectorStack = std::move(other._vectorStack);
	return *this;
}

///

template<typename T>
void VectorStack<T>::push(const T& value) {
	_vectorStack.pushBack(value);
}

template<typename T>
void VectorStack<T>::pop() {
	_vectorStack.popBack();
}

template<typename T>
const T& VectorStack<T>::top() const {
	if (isEmpty()) {
		throw std::out_of_range("Stack is empty");
	}
	return _vectorStack[size() - 1];
}

template<typename T>
bool VectorStack<T>::isEmpty() const {
	return _vectorStack.size() == 0;
}

template<typename T>
size_t VectorStack<T>::size() const {
	return _vectorStack.size();
}