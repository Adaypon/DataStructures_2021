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
using ValueType = double;

class MyVector
{
public:
    //TODO реализовать итераторы
    class VectorIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = ValueType;
        using pointer           = ValueType*;
        using reference         = ValueType&;

        VectorIterator(ValueType *ptr, size_t idx);
        
        VectorIterator(const VectorIterator& copy);
        VectorIterator& operator=(const VectorIterator& copy);

        ValueType& operator*();
        ValueType* operator->();
        VectorIterator& operator++();
        VectorIterator operator++(int _);
        bool operator==(const VectorIterator& other);
        bool operator!=(const VectorIterator& other);
        std::ptrdiff_t operator-(const VectorIterator& other);

        size_t getIndex() const;
    private:
        ValueType* _ptr;
        size_t _index;
    };

    class ConstVectorIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = ValueType;
        using pointer           = ValueType*;
        using reference         = ValueType&;

        ConstVectorIterator(ValueType *ptr);
        
        ConstVectorIterator(const ConstVectorIterator& copy);
        ConstVectorIterator& operator=(const ConstVectorIterator& copy);

        ValueType& operator*();
        ValueType* operator->();
        ConstVectorIterator& operator++();
        ConstVectorIterator operator++(int _);
        bool operator==(const ConstVectorIterator& other);
        bool operator!=(const ConstVectorIterator& other);
        std::ptrdiff_t operator-(const ConstVectorIterator& other);
    private:
        ValueType* _ptr;
    };

    // заполнить вектор значениями ValueType()
    MyVector(size_t size = 0, 
             ResizeStrategy = ResizeStrategy::Multiplicative, 
             size_t coef = 2); // почему тут было float coef = 1.5f ?
    // заполнить вектор значениями value
    MyVector(size_t size, 
             ValueType value, 
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
    
    VectorIterator begin();
    ConstVectorIterator begin() const;
    VectorIterator end();
    ConstVectorIterator end() const;

    // доступ к элементу, 
    // должен работать за O(1)
    ValueType& at(const size_t idx);
	const ValueType& at(const size_t idx) const;
    ValueType& operator[](const size_t i);
    const ValueType& operator[](const size_t i) const;
    
    // добавить в конец,
    // должен работать за amort(O(1))
    void pushBack(const ValueType& value);
    // вставить,
    // должен работать за O(n)
    void insert(const size_t i, const ValueType& value);     // версия для одного значения
    void insert(const size_t i, const MyVector& value);      // версия для вектора
    void insert(ConstVectorIterator it, const ValueType& value);  // версия для одного значения
    void insert(ConstVectorIterator it, const MyVector& value);   // версия для вектора
    
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
    VectorIterator find(const ValueType& value, bool isBegin = true) const;
    
    // зарезервировать память (принудительно задать capacity)
    void reserve(const size_t capacity);
    
    // изменить размер
    // если новый размер больше текущего, то новые элементы забиваются value
    // если меньше - обрезаем вектор
    void resize(const size_t size, const ValueType& value = ValueType());

    // реаллокация вектора в случае, если loadFactor превысит максимальное значение
    void reallocVector();
    
    // очистка вектора, без изменения capacity
    void clear();
private:
    ValueType* _data;
    size_t _size;
    size_t _capacity;
    ResizeStrategy _strategy;
    float _resizeCoef;

    static const float MAX_LOAD;
    static const float MIN_LOAD; 
};