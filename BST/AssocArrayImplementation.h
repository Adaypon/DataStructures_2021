#pragma once

template<typename Key, typename Value>
class AssocArrImplementation {
public:
	// добавление значения value с ключом key
	virtual void add(const Key& key, const Value& value) = 0;
	// найти значение, ассоциированные с ключом key
	virtual const Value& find(const Key& key) const = 0;
	// удалить пару ключ-значение
	virtual void remove(const Key& key) = 0;
	// виртуальный деструктор
	virtual ~AssocArrImplementation() {};
};