#pragma once
#include <iostream>
#include <cstddef>
#include <exception>

// стратегия изменения capacity
enum class ResizeStrategy {
    Additive,
    Multiplicative
};


template<typename T>
class MyVector
{
public:
    //TODO реализовать итераторы
    class VectorIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;

        VectorIterator(pointer ptr, size_t idx);
        
        VectorIterator(const VectorIterator& copy);
        VectorIterator& operator=(const VectorIterator& copy);

        reference operator*();
        pointer operator->();
        VectorIterator& operator++();
        VectorIterator operator++(int _);
        bool operator==(const VectorIterator& other);
        bool operator!=(const VectorIterator& other);
        difference_type operator-(const VectorIterator& other);

        size_t getIndex() const;
    private:
        pointer _ptr;
        size_t _index;
    };

    class ConstVectorIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = const T;
        using pointer           = const T*;
        using reference         = const T&;

        ConstVectorIterator(pointer ptr, size_t idx);
        
        ConstVectorIterator(const ConstVectorIterator& copy);
        ConstVectorIterator& operator=(const ConstVectorIterator& copy);

        reference operator*() const;
        pointer operator->() const;
        ConstVectorIterator& operator++();
        ConstVectorIterator operator++(int _);
        bool operator==(const ConstVectorIterator& other);
        bool operator!=(const ConstVectorIterator& other);
        difference_type operator-(const ConstVectorIterator& other);

        size_t getIndex() const;
    private:
        pointer _ptr;
        size_t _index;
    };

    // заполнить вектор значениями T()
    MyVector(size_t size = 0, 
             ResizeStrategy = ResizeStrategy::Multiplicative, 
             size_t coef = 2); // почему тут было float coef = 1.5f ?
    // заполнить вектор значениями value
    MyVector(size_t size, 
             T value, 
             ResizeStrategy = ResizeStrategy::Multiplicative, 
             size_t coef = 2); // почему тут было float coef = 1.5f ?
    
    MyVector(const MyVector& copy);
    MyVector& operator=(const MyVector& copy);
    
    MyVector(MyVector&& other) noexcept;
    MyVector& operator=(MyVector&& other) noexcept;
    ~MyVector();
    
    size_t capacity() const;
    size_t size() const;
    float loadFactor() const;
    bool isLoaded() const;
    
    VectorIterator begin();
    ConstVectorIterator begin() const;
    VectorIterator end();
    ConstVectorIterator end() const;

    // доступ к элементу, 
    // должен работать за O(1)
    T& at(const size_t idx);
	const T& at(const size_t idx) const;
    T& operator[](const size_t i);
    const T& operator[](const size_t i) const;
    
    // добавить в конец,
    // должен работать за amort(O(1))
    void pushBack(const T& value);
    // вставить,
    // должен работать за O(n)
    void insert(const size_t idx, const T& value);     // версия для одного значения
    void insert(const size_t idx, const MyVector& value);      // версия для вектора
    void insert(VectorIterator it, const T& value);  // версия для одного значения
    void insert(VectorIterator it, const MyVector& value);   // версия для вектора
    
    // удалить с конца,
    // должен работать за amort(O(1))
    void popBack();
    // удалить
    // должен работать за O(n)
    void erase(const size_t i);
    void erase(const size_t i, const size_t len);            // удалить len элементов начиная с i
    
    // найти элемент,
    // должен работать за O(n)
    // если isBegin == true, найти индекс первого элемента, равного value, иначе последнего
    // если искомого элемента нет, вернуть end
    ConstVectorIterator find(const T& value, bool isBegin = true) const;
    
    // зарезервировать память (принудительно задать capacity)
    void reserve(const size_t capacity);
    
    // изменить размер
    // если новый размер больше текущего, то новые элементы забиваются value
    // если меньше - обрезаем вектор
    void resize(const size_t size, const T& value = T());

    // реаллокация вектора в случае, если loadFactor превысит максимальное значение
    void reallocVector();
    
    // очистка вектора, без изменения capacity
    void clear();
private:
    T* _data;
    size_t _size;
    size_t _capacity;
    ResizeStrategy _strategy;
    float _resizeCoef;

    static const float MAX_LOAD;
    static const float MIN_LOAD;
    static const size_t CAPACITY_INIT;
};


template<typename T>
const float MyVector<T>::MAX_LOAD = 1;

template<typename T>
const float MyVector<T>::MIN_LOAD = 0.25;

template<typename T>
const size_t MyVector<T>::CAPACITY_INIT = 20;


/// Iterators section

// VectorIterator
template<typename T>
MyVector<T>::VectorIterator::VectorIterator(T* ptr, size_t idx) :
	_ptr(ptr),
	_index(idx)
{

}

template<typename T>
MyVector<T>::VectorIterator::VectorIterator(const MyVector::VectorIterator& copy) :
	_ptr(copy._ptr),
	_index(copy._index)
{

}

template<typename T>
typename MyVector<T>::VectorIterator& MyVector<T>::VectorIterator::operator=(const MyVector<T>::VectorIterator& copy) {
	if (this != &copy) {
		_ptr = copy._ptr;
		_index = copy._index;
	}
	return *this;
}

template<typename T>
T& MyVector<T>::VectorIterator::operator*() {
	return *(_ptr);
}

template<typename T>
T* MyVector<T>::VectorIterator::operator->() {
	return _ptr;
}

template<typename T>
typename MyVector<T>::VectorIterator& MyVector<T>::VectorIterator::operator++() {
	++_ptr;
	++_index;
	return *this;
}

template<typename T>
typename MyVector<T>::VectorIterator MyVector<T>::VectorIterator::operator++(int _) {
	auto tmp = *this;
	++(*this);
	return tmp;
}

template<typename T>
bool MyVector<T>::VectorIterator::operator==(const MyVector<T>::VectorIterator& other) {
	return _ptr == other._ptr;
}

template<typename T>
bool MyVector<T>::VectorIterator::operator!=(const MyVector<T>::VectorIterator& other) {
	return !(*this == other);
}

template<typename T>
std::ptrdiff_t MyVector<T>::VectorIterator::operator-(const MyVector<T>::VectorIterator& other) {
	return _ptr - other._ptr;
}

template<typename T>
size_t MyVector<T>::VectorIterator::getIndex() const {
	return _index;
}

// ConstVectorIterator

template<typename T>
MyVector<T>::ConstVectorIterator::ConstVectorIterator(const T* ptr, size_t idx) :
	_ptr(ptr),
	_index(idx)
{

}

template<typename T>
MyVector<T>::ConstVectorIterator::ConstVectorIterator(const MyVector<T>::ConstVectorIterator& copy) :
	_ptr(copy._ptr),
	_index(copy._index)
{

}

template<typename T>
typename MyVector<T>::ConstVectorIterator& MyVector<T>::ConstVectorIterator::operator=(const MyVector<T>::ConstVectorIterator& copy) {
	if (this != &copy) {
		_ptr = copy._ptr;
		_index = copy._index;
	}
	return *this;
}

template<typename T>
const T& MyVector<T>::ConstVectorIterator::operator*() const {
	return *(_ptr);
}

template<typename T>
const T* MyVector<T>::ConstVectorIterator::operator->() const {
	return _ptr;
}

template<typename T>
typename MyVector<T>::ConstVectorIterator& MyVector<T>::ConstVectorIterator::operator++() {
	++_ptr;
	++_index;
	return *this;
}

template<typename T>
typename MyVector<T>::ConstVectorIterator MyVector<T>::ConstVectorIterator::operator++(int _) {
	auto tmp = *this;
	++(*this);
	return tmp;
}

template<typename T>
bool MyVector<T>::ConstVectorIterator::operator==(const MyVector<T>::ConstVectorIterator& other) {
	return _ptr == other._ptr;
}

template<typename T>
bool MyVector<T>::ConstVectorIterator::operator!=(const MyVector<T>::ConstVectorIterator& other) {
	return !(*this == other);
}

template<typename T>
std::ptrdiff_t MyVector<T>::ConstVectorIterator::operator-(const MyVector<T>::ConstVectorIterator& other) {
	return _ptr - other._ptr;
}

template<typename T>
size_t MyVector<T>::ConstVectorIterator::getIndex() const {
	return _index;
}

///

template<typename T>
MyVector<T>::MyVector(size_t size, ResizeStrategy strategy, size_t coef) : 
	_size(size),
	_capacity(CAPACITY_INIT),
	_strategy(strategy),
	_resizeCoef(coef),
	_data(nullptr)
{
	if (_size > 0) {
		switch (_strategy) {
			case ResizeStrategy::Additive:
				_capacity = _size + _resizeCoef;
				break;
			case ResizeStrategy::Multiplicative:
				_capacity = _size * _resizeCoef;
				break;
		}
	}
	_data = new T[_capacity];
	for (size_t i = 0; i < _size; ++i) {
        _data[i] = T();
    }
}

template<typename T>
MyVector<T>::MyVector(size_t size, T value, ResizeStrategy strategy, size_t coef) :
	_size(size),
	_capacity(CAPACITY_INIT),
	_strategy(strategy),
	_resizeCoef(coef),
	_data(nullptr)
{
	if (_size > 0) {
		switch (_strategy) {
			case ResizeStrategy::Additive:
				_capacity = _size + _resizeCoef;
				break;
			case ResizeStrategy::Multiplicative:
				_capacity = _size * _resizeCoef;
				break;
		}
	}
	_data = new T[_capacity];
	for (size_t i = 0; i < _size; ++i) {
        _data[i] = value;
	}
}

template<typename T>
MyVector<T>::MyVector(const MyVector<T>& other) : 
	_size(other._size),
	_capacity(other._capacity),
	_strategy(other._strategy),
	_resizeCoef(other._resizeCoef),
	_data(nullptr)
{
	if (_size > 0) {
		_data = new T[_capacity];
		for (size_t i = 0; i < size(); ++i) {
			_data[i] = other[i];
		}
	}
}

template<typename T>
MyVector<T>::MyVector(MyVector<T>&& other) noexcept :
	_size(other._size),
	_capacity(other._capacity),
	_strategy(other._strategy),
	_resizeCoef(other._resizeCoef),
    _data(other._data)
{
	other._data = nullptr;
    other._size = 0;
	other._capacity = 0;
	other._resizeCoef = 0;
}


template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other) {
	if (this != &other) {
		if (_data) {
			delete[] _data;
		}
		_size = other._size;
		_capacity = other._capacity;
		_resizeCoef = other._resizeCoef;
		_data = new T[_capacity];
		for (size_t i = 0; i < size(); ++i) {
				_data[i] = other[i];
		}
	}
    return *this;
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(MyVector<T>&& other) noexcept {
	if (this != &other) {
		if (_data) {
			delete[] _data;
		}
		_size = other._size;
		_capacity = other._capacity;
		_resizeCoef = other._resizeCoef;
		_data = other._data;
		other._data = nullptr;
	    other._size = 0;
		other._capacity = 0;
		other._resizeCoef = 0;
	}
	return *this;
}

template<typename T>
MyVector<T>::~MyVector<T>() {
	delete[] _data;
	_data = nullptr;
    _size = 0;
	_capacity = 0;
	_resizeCoef = 0;
}

template<typename T>
typename MyVector<T>::VectorIterator MyVector<T>::begin() {
	return MyVector<T>::VectorIterator(&_data[0], 0);
}

template<typename T>
typename MyVector<T>::ConstVectorIterator MyVector<T>::begin() const {
	return MyVector<T>::ConstVectorIterator(&_data[0], 0);
}

template<typename T>
typename MyVector<T>::VectorIterator MyVector<T>::end() {
	return MyVector<T>::VectorIterator(&_data[size()], size());
}

template<typename T>
typename MyVector<T>::ConstVectorIterator MyVector<T>::end() const {
	return MyVector<T>::ConstVectorIterator(&_data[size()], size());
}

template<typename T>
T& MyVector<T>::at(const size_t idx) {
	if (idx >= size()) {
		throw std::out_of_range("Called at at(): idx >= size");
	}
	return _data[idx];
}

template<typename T>
const T& MyVector<T>::at(const size_t idx) const {
	if (idx >= size()) {
		throw std::out_of_range("Called at at(): idx >= size");
	}
	return _data[idx];
}

template<typename T>
T& MyVector<T>::operator[](const size_t i) {
	return at(i);
}

template<typename T>
const T& MyVector<T>::operator[](const size_t i) const {
	return at(i);
}


template<typename T>
void MyVector<T>::reserve(const size_t newCapacity) {
	if (newCapacity <= _capacity) {
		return;
	}
	_capacity = newCapacity;
	T* tmpVector = new T[capacity()];
	for (size_t i = 0; i < size(); ++i) {
		tmpVector[i] = _data[i];
	}
	delete[] _data;
	_data = tmpVector;
}

// TODO try to fix (works unstable, still idk why)
template<typename T>
void MyVector<T>::resize(const size_t size, const T& value) {
	if (size > _size) {
		while (size > _capacity) {
        	reallocVector();
		}
        for (size_t i = _size; i < size; ++i) {
            _data[i] = value;
        }
    }
	_size = size;
}

template<typename T>
void MyVector<T>::reallocVector() {
	//std::cout << "\tdebug: Reallocating vector" << std::endl;
	switch (_strategy) {
		case ResizeStrategy::Additive:
			_capacity += _resizeCoef;
			break;
		case ResizeStrategy::Multiplicative:
			_capacity *= _resizeCoef;
			break;
	}
	T* tmpVector = new T[capacity()];
	for (size_t i = 0; i < size(); ++i) {
		tmpVector[i] = _data[i];
	}
	delete[] _data;
	_data = tmpVector;
}


template<typename T>
void MyVector<T>::pushBack(const T& value) {
	this->insert(size(), value);
}


template<typename T>
void MyVector<T>::insert(const size_t idx, const T& value) {
	if (idx > size()) {
		throw std::out_of_range("Called at insert(): idx > size");
	}

	++_size;
	if (isLoaded()) {
		reallocVector();
	}

	T* tmpVector = new T[_capacity];

	for (size_t i = 0; i < idx; ++i) {
		tmpVector[i] = _data[i];
	}
	tmpVector[idx] = value;
	for (size_t i = idx + 1; i < size(); ++i) {
		tmpVector[i] = _data[i-1];
	}

	delete[] _data;
	_data = tmpVector;
}

template<typename T>
void MyVector<T>::insert(const size_t idx, const MyVector<T>& value) {
	if (idx > size()) {
		throw std::out_of_range("Called at insert(): idx > size");
	}
	size_t i = 0, j = 0;
	const size_t insertVectorSize = value.size();

	_size += insertVectorSize;
	while (isLoaded()) {
		reallocVector();
	}

	T* tmpVector = new T[_capacity];

	for (; i < idx; ++i) {
		tmpVector[i] = _data[i];
	}
	for (; j < insertVectorSize; ++i, ++j) {
		tmpVector[i] = value[j];
	}
	for (j = idx; i < size(); ++i, ++j) {
		tmpVector[i] = _data[j];
	}

	delete[] _data;
	_data = tmpVector;
}

template<typename T>
void MyVector<T>::insert(MyVector<T>::VectorIterator it, const T& value) {
	this->insert(it.getIndex(), value);
}

template<typename T>
void MyVector<T>::insert(MyVector<T>::VectorIterator it, const MyVector<T>& value) {
	this->insert(it.getIndex(), value);
}

template<typename T>
void MyVector<T>::clear() {
	//this->erase(0, size());
	delete[] _data;
    _data = nullptr;
    _size = 0;
}

template<typename T>
void MyVector<T>::popBack() {
	if (size() == 0) {
		throw std::out_of_range("Called at popBack(): Vector is empty");
	}
	this->erase(size()-1);
}

template<typename T>
void MyVector<T>::erase(size_t pos) {
	this->erase(pos, 1);
}

template<typename T>
void MyVector<T>::erase(size_t pos, size_t len) {
	if (pos >= size()) {
		throw std::out_of_range("Called at erase(): pos >= size");
	}
	
	if (len > _size - pos) {
		len = _size - pos;
	}

	size_t tmpSize = _size - len;
	T* tmpVector = new T[_capacity];
	
	for (size_t i = 0; i < pos; ++i) {
		tmpVector[i] = _data[i];
	}
	for (size_t i = pos; i < tmpSize; ++i) {
		tmpVector[i] = _data[i + len];
	}

	delete[] _data;
	_data = tmpVector;
	_size = tmpSize;
}


template<typename T>
size_t MyVector<T>::size() const {
	return _size;
}

template<typename T>
size_t MyVector<T>::capacity() const {
	return _capacity;
}

template<typename T>
float MyVector<T>::loadFactor() const {
	return (static_cast<float>(size()) / capacity());
}

template<typename T>
bool MyVector<T>::isLoaded() const {
	return (loadFactor() >= MAX_LOAD);
}

template<typename T>
typename MyVector<T>::ConstVectorIterator MyVector<T>::find(const T& value, bool isBegin) const {
	auto res = begin();
	for (auto it = begin(); it != end(); ++it) {
		if (*it == value) {
			res = it;
			if (isBegin) {
				break;
			}
		}
	}
	if (*res != value) {
		return end();
	}
	return res;
}