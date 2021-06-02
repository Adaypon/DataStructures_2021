#pragma once
#include <iostream>
#include <cstddef>
#include <exception>

// стратегия изменения capacity
enum class ResizeStrategy {
    Additive,
    Multiplicative
};

// тип значений в векторе
// потом будет заменен на шаблон
// using ValueType = double;


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

        VectorIterator(pointer ptr, size_t idx) : _ptr(ptr), _index(idx) {}
        
        VectorIterator(const VectorIterator& copy) : _ptr(copy._ptr), _index(copy._index) {}
        VectorIterator& operator=(const VectorIterator& copy) {
			if (this != &copy) {
				_ptr = copy._ptr;
				_index = copy._index;
			}
			return *this;
		}

        reference operator*() { return *(_ptr); }
        pointer operator->() { return _ptr; }
        VectorIterator& operator++() {
			++_ptr;
			++_index;
			return *this;
		}
        VectorIterator operator++(int _) {
			auto tmp = *this;
			++(*this);
			return tmp;
		}
        bool operator==(const VectorIterator& other) { return _ptr == other._ptr; }
        bool operator!=(const VectorIterator& other) { return !(*this == other); }
        difference_type operator-(const VectorIterator& other) { return _ptr - other._ptr; }

        size_t getIndex() const { return _index; };
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

        ConstVectorIterator(pointer ptr, size_t idx) : _ptr(ptr), _index(idx) {}
        
        ConstVectorIterator(const ConstVectorIterator& copy) : _ptr(copy._ptr), _index(copy._index) {}
        ConstVectorIterator& operator=(const ConstVectorIterator& copy) {
			if (this != &copy) {
				_ptr = copy._ptr;
				_index = copy._index;
			}
			return *this;
		}

        reference operator*() const { return *(_ptr); };
        pointer operator->() const { return _ptr; }
        ConstVectorIterator& operator++() {
			++_ptr;
			++_index;
			return *this;
		}
        ConstVectorIterator operator++(int _) {
			auto tmp = *this;
			++(*this);
			return tmp;
		}
        bool operator==(const ConstVectorIterator& other) { return _ptr == other._ptr; }
        bool operator!=(const ConstVectorIterator& other) { return !(*this == other); }
        difference_type operator-(const ConstVectorIterator& other) { return _ptr - other._ptr; }

        size_t getIndex() const { return _index; };
    private:
        pointer _ptr;
        size_t _index;
    };

    // заполнить вектор значениями T()
    MyVector(size_t size = 0, ResizeStrategy strategy = ResizeStrategy::Multiplicative, size_t coef = 2) : // почему тут было float coef = 1.5f ?
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

    // заполнить вектор значениями value
    MyVector(size_t size, T value, ResizeStrategy strategy = ResizeStrategy::Multiplicative, size_t coef = 2) : // почему тут было float coef = 1.5f ?
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

    MyVector(const MyVector& other) :
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

    MyVector& operator=(const MyVector& other) {
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
    
    MyVector(MyVector&& other) noexcept :
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

    MyVector& operator=(MyVector&& other) noexcept {
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

    ~MyVector() {
		delete[] _data;
		_data = nullptr;
		_size = 0;
		_capacity = 0;
		_resizeCoef = 0;
	}
    
    size_t capacity() const { return _capacity; }
    size_t size() const { return _size; }
    float loadFactor() const { return (static_cast<float>(size()) / capacity()); }
    bool isLoaded() const { return (loadFactor() >= MAX_LOAD); }
    
    VectorIterator begin() { return MyVector::VectorIterator(&_data[0], 0); }
    ConstVectorIterator begin() const { return MyVector::ConstVectorIterator(&_data[0], 0); }
    VectorIterator end() { return MyVector::VectorIterator(&_data[size()], size()); }
    ConstVectorIterator end() const { return MyVector::ConstVectorIterator(&_data[size()], size()); }

    // доступ к элементу, 
    // должен работать за O(1)
    T& at(const size_t idx) {
		if (idx >= size()) {
			throw std::out_of_range("Called at at(): idx >= size");
		}
		return _data[idx];
	}
	const T& at(const size_t idx) const {
		if (idx >= size()) {
			throw std::out_of_range("Called at at(): idx >= size");
		}
		return _data[idx];
	}
    T& operator[](const size_t i) { return at(i); }
    const T& operator[](const size_t i) const { return at(i); };
    
    // добавить в конец,
    // должен работать за amort(O(1))
    void pushBack(const T& value) { this->insert(size(), value); }
    
	// вставить,
    // должен работать за O(n)

	// версия для одного значения
    void insert(const size_t idx, const T& value) {
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
	
	// версия для вектора
    void insert(const size_t idx, const MyVector& value) {
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
    
	void insert(VectorIterator it, const T& value) { this->insert(it.getIndex(), value); }  // версия для одного значения
    void insert(VectorIterator it, const MyVector& value) { this->insert(it.getIndex(), value); }   // версия для вектора
    
    // удалить с конца,
    // должен работать за amort(O(1))
    void popBack() {
		if (size() == 0) {
			throw std::out_of_range("Called at popBack(): Vector is empty");
		}
		this->erase(size()-1);
	}

    // удалить
    // должен работать за O(n)
    void erase(const size_t pos) { this->erase(pos, 1); }

	// удалить len элементов начиная с i
    void erase(const size_t pos, size_t len) {            
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

    // найти элемент,
    // должен работать за O(n)
    // если isBegin == true, найти индекс первого элемента, равного value, иначе последнего
    // если искомого элемента нет, вернуть end
    ConstVectorIterator find(const T& value, bool isBegin = true) const {
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
    
    // зарезервировать память (принудительно задать capacity)
    void reserve(const size_t newCapacity) {
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
    
    // изменить размер
    // если новый размер больше текущего, то новые элементы забиваются value
    // если меньше - обрезаем вектор
	// TODO try to fix (may work unstable, still idk why)
    void resize(const size_t size, const T& value = T()) {
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

    // реаллокация вектора в случае, если loadFactor превысит максимальное значение
    void reallocVector() {
		std::cout << "\tdebug: Reallocating vector" << std::endl;
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
    
    // очистка вектора, без изменения capacity
    void clear() {
		//this->erase(0, size());
		delete[] _data;
		_data = nullptr;
		_size = 0;
	}


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