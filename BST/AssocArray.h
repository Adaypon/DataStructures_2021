#pragma once
#include "bst_key_value.h"
#include "AssocArrayImplementation.h"

template<typename Key, typename Value>
class AssocArray : public AssocArrImplementation<Key, Value>, public BST<Key, Value>
{
public:
	///
	AssocArray();

    AssocArray(const AssocArray& other);
    AssocArray(AssocArray&& other) noexcept;

	AssocArray& operator=(const AssocArray& other);
    AssocArray& operator=(AssocArray&& other) noexcept;

	~AssocArray() = default;
	///

	// добавление значения value с ключом key
	void add(const Key& key, const Value& value) override;
	// найти значение, ассоциированные с ключом key
	const Value& find(const Key& key) const override;
	// удалить пару ключ-значение
	void remove(const Key& key) override;

private:
	BST<Key, Value> _assocArrBST;
};


template<typename Key, typename Value>
AssocArray<Key, Value>::AssocArray() : 
	_assocArrBST(BST<Key, Value>())
{

}

template<typename Key, typename Value>
AssocArray<Key, Value>::AssocArray(const AssocArray& other) :
	_assocArrBST(other._assocArrBST)
{

}

template<typename Key, typename Value>
AssocArray<Key, Value>& AssocArray<Key, Value>::operator=(const AssocArray& other) {
	_assocArrBST = other._assocArrBST;
	return *this;
}

template<typename Key, typename Value>
AssocArray<Key, Value>::AssocArray(AssocArray&& other) noexcept :
	_assocArrBST(std::move(other._assocArrBST))
{
	
}

template<typename Key, typename Value>
AssocArray<Key, Value>& AssocArray<Key, Value>::operator=(AssocArray&& other) noexcept {
	_assocArrBST = std::move(other._assocArrBST);
	return *this;
}


template<typename Key, typename Value>
void AssocArray<Key, Value>::add(const Key& key, const Value& value) {
	_assocArrBST.insert(key, value);
}

template<typename Key, typename Value>
const Value& AssocArray<Key, Value>::find(const Key& key) const {
	return _assocArrBST.find(key);
}

template<typename Key, typename Value>
void AssocArray<Key, Value>::remove(const Key& key) {
	_assocArrBST.remove(key);
}