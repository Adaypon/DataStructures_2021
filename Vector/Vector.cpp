#include "MyVector.h"

MyVector::MyVector(size_t size, ResizeStrategy strategy, float coef) : 
	_size(size),
	_capacity(size),
	_strategy(strategy),
	_resizeCoef(coef),
	_data(nullptr)
{
	if (_size > 0) {
		_data = new ValueType[_size];
		for (size_t i = 0; i < _size; ++i) {
            _data[i] = 0;
        }
	}
}

MyVector::MyVector(const MyVector& other) : 
	_size(other._size),
	_capacity(other._size),
	_strategy(other._strategy),
	_resizeCoef(other._resizeCoef),
	_data(nullptr)
{
	if (_size > 0) {
		_data = new ValueType[_size];
		for (size_t i = 0; i < size(); ++i) {
			_data[i] = other[i];
		}
	}
}

MyVector::MyVector(MyVector&& other) noexcept :
	_size(other._size),
	_capacity(other._size),
	_strategy(other._strategy),
	_resizeCoef(other._resizeCoef),
    _data(other._data)
{
	other._data = nullptr;
    other._size = 0;
}


MyVector& MyVector::operator=(const MyVector& other) {
	if (this != &other) {
		if (_data) {
			delete[] _data;
		}
		_size = other._size;
		_data = new ValueType[_size];
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
		_data = other._data;
		other._data = nullptr;
	    other._size = 0;
	}
	return *this;
}

MyVector::~MyVector() {
	delete[] _data;
	_data = nullptr;
    _size = 0;
}
/*
ValueType& MyVector::at(const size_t idx) {
	if (idx < size()) {
		return _data[idx];
	}
	throw std::out_of_range("idx >= size");
}


const ValueType& MyVector::at(const size_t idx) const {
	if (idx < size()) {
		return _data[idx];
	}
	throw std::out_of_range("idx >= size");
}
*/

/*
ValueType& MyVector::operator[](const size_t i) {
	return at(i);
}

const ValueType& MyVector::operator[](const size_t i) const {
	return at(i);
}
*/

void MyVector::pushBack(const ValueType& value) {
	this->insert(value, size());
}
/*
void MyVector::insert(const ValueType& value, size_t idx) {
	if (idx > size()) {
		throw std::out_of_range("Called at insert(): idx > size");
	}
	
	size_t tmpSize = _size + 1;
	ValueType* tmpVector = new ValueType[tmpSize];
	
	for (size_t i = 0; i < idx; ++i) {
		tmpVector[i] = _data[i];
	}
	tmpVector[idx] = value;
	for (size_t i = idx+1; i < tmpSize; ++i) {
		tmpVector[i] = _data[i-1];
	}

	delete[] _data;
	_data = tmpVector;
	_size = tmpSize;
}
*/
void MyVector::clear() {
	//this->erase(0, size());
	delete[] _data;
    _data = nullptr;
    _size = 0;
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