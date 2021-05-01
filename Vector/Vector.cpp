#include "MyVector.h"

const float MyVector::MAX_LOAD = 1;
const float MyVector::MIN_LOAD = 0.25;

/// Iterators section

// VectorIterator

MyVector::VectorIterator::VectorIterator(ValueType *ptr, size_t idx) :
	_ptr(ptr),
	_index(idx)
{

}

MyVector::VectorIterator::VectorIterator(const MyVector::VectorIterator& copy) :
	_ptr(copy._ptr),
	_index(copy._index)
{

}

MyVector::VectorIterator& MyVector::VectorIterator::operator=(const MyVector::VectorIterator& copy) {
	if (this != &copy) {
		_ptr = copy._ptr;
		_index = copy._index;
	}
	return *this;
}

ValueType& MyVector::VectorIterator::operator*() {
	return *(_ptr);
}
ValueType* MyVector::VectorIterator::operator->() {
	return _ptr;
}

MyVector::VectorIterator& MyVector::VectorIterator::operator++() {
	++_ptr;
	++_index;
	return *this;
}

MyVector::VectorIterator MyVector::VectorIterator::operator++(int _) {
	VectorIterator tmp = *this;
	++(*this);
	return tmp;
}

bool MyVector::VectorIterator::operator==(const MyVector::VectorIterator& other) {
	return _ptr == other._ptr;
}

bool MyVector::VectorIterator::operator!=(const MyVector::VectorIterator& other) {
	return !(*this == other);
}

std::ptrdiff_t MyVector::VectorIterator::operator-(const MyVector::VectorIterator& other) {
	return _ptr - other._ptr;
}

size_t MyVector::VectorIterator::getIndex() const {
	return _index;
}

// ConstVectorIterator

MyVector::ConstVectorIterator::ConstVectorIterator(ValueType *ptr) :
	_ptr(ptr)
{

}

MyVector::ConstVectorIterator::ConstVectorIterator(const MyVector::ConstVectorIterator& copy) :
	_ptr(copy._ptr)
{

}

MyVector::ConstVectorIterator& MyVector::ConstVectorIterator::operator=(const MyVector::ConstVectorIterator& copy) {
	if (this != &copy) {
		_ptr = copy._ptr;
	}
	return *this;
}

ValueType& MyVector::ConstVectorIterator::operator*() {
	return *(_ptr);
}

ValueType* MyVector::ConstVectorIterator::operator->() {
	return _ptr;
}

MyVector::ConstVectorIterator& MyVector::ConstVectorIterator::operator++() {
	++_ptr;
	return *this;
}

MyVector::ConstVectorIterator MyVector::ConstVectorIterator::operator++(int _) {
	ConstVectorIterator tmp = *this;
	++(*this);
	return tmp;
}

bool MyVector::ConstVectorIterator::operator==(const MyVector::ConstVectorIterator& other) {
	return _ptr == other._ptr;
}

bool MyVector::ConstVectorIterator::operator!=(const MyVector::ConstVectorIterator& other) {
	return !(*this == other);
}

std::ptrdiff_t MyVector::ConstVectorIterator::operator-(const MyVector::ConstVectorIterator& other) {
	return _ptr - other._ptr;
}

///

MyVector::MyVector(size_t size, ResizeStrategy strategy, size_t coef) : 
	_size(size),
	_capacity(size),
	_strategy(strategy),
	_resizeCoef(coef),
	_data(nullptr)
{
	if (_size > 0) {
		switch (_strategy) {
			case ResizeStrategy::Additive:
				_capacity += _resizeCoef;
				break;
			case ResizeStrategy::Multiplicative:
				_capacity *= _resizeCoef;
				break;
		}
		_data = new ValueType[_capacity];
		for (size_t i = 0; i < _size; ++i) {
            _data[i] = ValueType();
        }
	}
}

MyVector::MyVector(size_t size, ValueType value, ResizeStrategy strategy, size_t coef) :
	_size(size),
	_capacity(size),
	_strategy(strategy),
	_resizeCoef(coef),
	_data(nullptr)
{
	if (_size > 0) {
		switch (_strategy) {
			case ResizeStrategy::Additive:
				_capacity += _resizeCoef;
				break;
			case ResizeStrategy::Multiplicative:
				_capacity *= _resizeCoef;
				break;
		}
		_data = new ValueType[_capacity];
		for (size_t i = 0; i < _size; ++i) {
            _data[i] = value;
        }
	}
}

MyVector::MyVector(const MyVector& other) : 
	_size(other._size),
	_capacity(other._capacity),
	_strategy(other._strategy),
	_resizeCoef(other._resizeCoef),
	_data(nullptr)
{
	if (_size > 0) {
		_data = new ValueType[_capacity];
		for (size_t i = 0; i < size(); ++i) {
			_data[i] = other[i];
		}
	}
}

MyVector::MyVector(MyVector&& other) noexcept :
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


MyVector& MyVector::operator=(const MyVector& other) {
	if (this != &other) {
		if (_data) {
			delete[] _data;
		}
		_size = other._size;
		_capacity = other._capacity;
		_resizeCoef = other._resizeCoef;
		_data = new ValueType[_capacity];
		for (size_t i = 0; i < size(); ++i) {
				_data[i] = other[i];
		}
	}
    return *this;
}

MyVector& MyVector::operator=(MyVector&& other) noexcept {
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

MyVector::~MyVector() {
	delete[] _data;
	_data = nullptr;
    _size = 0;
	_capacity = 0;
	_resizeCoef = 0;
}

MyVector::VectorIterator MyVector::begin() {
	return MyVector::VectorIterator(&_data[0], 0);
}

MyVector::ConstVectorIterator MyVector::begin() const {
	return MyVector::ConstVectorIterator(&_data[0]);
}

MyVector::VectorIterator MyVector::end() {
	return MyVector::VectorIterator(&_data[size()], size());
}

MyVector::ConstVectorIterator MyVector::end() const {
	return MyVector::ConstVectorIterator(&_data[size()]);
}

ValueType& MyVector::at(const size_t idx) {
	if (idx >= size()) {
		throw std::out_of_range("Called at at(): idx >= size");
	}
	return _data[idx];
}

const ValueType& MyVector::at(const size_t idx) const {
	if (idx >= size()) {
		throw std::out_of_range("Called at at(): idx >= size");
	}
	return _data[idx];
}

ValueType& MyVector::operator[](const size_t i) {
	return at(i);
}

const ValueType& MyVector::operator[](const size_t i) const {
	return at(i);
}


void MyVector::reallocVector() {
	std::cout << "\tReallocating vector" << std::endl;
	switch (_strategy) {
		case ResizeStrategy::Additive:
			_capacity += _resizeCoef;
			break;
		case ResizeStrategy::Multiplicative:
			_capacity *= _resizeCoef;
			break;
	}
	ValueType* tmpVector = new ValueType[capacity()];
	for (size_t i = 0; i < size(); ++i) {
		tmpVector[i] = _data[i];
	}
	delete[] _data;
	_data = tmpVector;
}


void MyVector::pushBack(const ValueType& value) {
	this->insert(size(), value);
}


void MyVector::insert(const size_t idx, const ValueType& value) {
	if (idx > size()) {
		throw std::out_of_range("Called at insert(): idx > size");
	}

	++_size;
	if (isLoaded()) {
		reallocVector();
	}

	ValueType* tmpVector = new ValueType[_capacity];

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

void MyVector::clear() {
	//this->erase(0, size());
	delete[] _data;
    _data = nullptr;
    _size = 0;
	_capacity = 0;
	_resizeCoef = 0;
}

void MyVector::erase(size_t pos) {
	if (pos >= size()) {
		throw std::out_of_range("Called at erase(): pos >= size");
	}
	
	size_t tmpSize = _size - 1;
	ValueType* tmpVector = new ValueType[tmpSize];
	
	for (size_t i = 0; i < pos; ++i) {
		tmpVector[i] = _data[i];
	}
	for (size_t i = pos; i < tmpSize; ++i) {
		tmpVector[i] = _data[i+1];
	}
	delete[] _data;
	_data = tmpVector;
	_size = tmpSize;
}

void MyVector::erase(size_t pos, size_t len) {
	if (pos >= size()) {
		throw std::out_of_range("Called at erase(): pos >= size");
	}
	
	if (len > _size - pos) {
		len = _size - pos;
	}

	size_t tmpSize = _size - len;
	ValueType* tmpVector = new ValueType[tmpSize];
	
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

void MyVector::popBack() {
	if (size() == 0) {
		throw std::out_of_range("Called at popBack(): Vector is empty");
	}
	this->erase(size()-1);
}

size_t MyVector::size() const {
	return _size;
}

size_t MyVector::capacity() const {
	return _capacity;
}

float MyVector::loadFactor() const {
	return (static_cast<float>(size()) / capacity());
}

bool MyVector::isLoaded() const {
	return (loadFactor() >= MAX_LOAD);
}
/*
size_t MyVector::find(const ValueType& value) const {
	size_t res = -1;
	for (size_t i = 0; i < size(); ++i) {
		if (this->at(i) == value) {
			res = i;
			break;
		}
	}
	return res;
}
*/