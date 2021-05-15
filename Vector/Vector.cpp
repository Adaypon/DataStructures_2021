#include "Vector.h"

Vector::Vector(const size_t size) : 
	_size(size),
	_data(nullptr)
{
	if (_size > 0) {
		_data = new ValueType[_size];
		for (size_t i = 0; i < _size; ++i) {
            _data[i] = 0;
        }
	}
}

Vector::Vector(const Vector& other) : 
	_size(other._size),
	_data(nullptr)
{
	if (_size > 0) {
		_data = new ValueType[_size];
		for (size_t i = 0; i < size(); ++i) {
			_data[i] = other[i];
		}
	}
}

Vector::Vector(Vector&& other) noexcept :
	_size(other._size),
    _data(other._data)
{
	other._data = nullptr; 
    other._size = 0;
}


Vector& Vector::operator=(const Vector& other) {
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

Vector& Vector::operator=(Vector&& other) noexcept {
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

Vector::~Vector() {
	delete[] _data;
	_data = nullptr;
    _size = 0;
}

ValueType& Vector::at(const size_t idx) {
	if (idx < size()) {
		return _data[idx];
	}
	throw std::out_of_range("idx >= size");
}


const ValueType& Vector::at(const size_t idx) const {
	if (idx < size()) {
		return _data[idx];
	}
	throw std::out_of_range("idx >= size");
}

ValueType& Vector::operator[](const size_t i) {
	return at(i);
}

const ValueType& Vector::operator[](const size_t i) const {
	return at(i);
}

void Vector::pushBack(const ValueType& value) {
	this->insert(value, size());
}

void Vector::pushFront(const ValueType& value) {
	this->insert(value, 0);
}

void Vector::insert(const ValueType& value, size_t idx) {
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

void Vector::clear() {
	//this->erase(0, size());
	delete[] _data;
    _data = nullptr;
    _size = 0;
}

void Vector::erase(size_t pos) {
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

void Vector::erase(size_t pos, size_t len) {
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

void Vector::popBack() {
	if (size() == 0) {
		throw std::out_of_range("Called at popBack(): Vector is empty");
	}
	this->erase(size()-1);
}

size_t Vector::size() const {
	return _size;
}

size_t Vector::find(const ValueType& value) const {
	size_t res = -1;
	for (size_t i = 0; i < size(); ++i) {
		if (this->at(i) == value) {
			res = i;
			break;
		}
	}
	return res;
}