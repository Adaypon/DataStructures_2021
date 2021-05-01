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
    // реализовать итераторы
    class VectorIterator;
    class ConstVectorIterator;

    // заполнить вектор значениями ValueType()
    MyVector(size_t size = 0, 
             ResizeStrategy = ResizeStrategy::Multiplicative, 
             float coef = 1.5f);
    // заполнить вектор значениями value
    MyVector(size_t size, 
             ValueType value, 
             ResizeStrategy = ResizeStrategy::Multiplicative, 
             float coef = 1.5f);
    
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
    
    // очистка вектора, без изменения capacity
    void clear();
private:
    ValueType* _data;
    size_t _size;
    size_t _capacity;
    ResizeStrategy _strategy;
    float _resizeCoef;
};