#pragma once

#include "IVector.h"
#include <iostream>
#include <exception>

class Vector : public IVector
{
public:
	///
	Vector(const size_t size = 0);

    explicit Vector(const Vector& other);
    Vector(Vector&& other) noexcept;

    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;

	~Vector();
	///

	ValueType& at(const size_t idx) override;
	const ValueType& at(const size_t idx) const override;
	ValueType& operator[](const size_t i) override;
    const ValueType& operator[](const size_t i) const override;
	
	void pushBack(const ValueType& value) override;
	void pushFront(const ValueType& value) override;
	void insert(const ValueType& value, size_t idx) override;

	void clear() override;
	void erase(size_t pos) override;
    void erase(size_t pos, size_t len) override;
    void popBack() override;
	
	size_t size() const override;

	size_t find(const ValueType& value) const override;

	
private:
	ValueType* _data;
	unsigned int _size;
	unsigned int _capacity;
};