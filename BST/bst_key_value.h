#pragma once

#include <iostream>
#include <algorithm>
#include <exception>

template<typename Key, typename Value>
class BST
{
	struct Node {
		Node(const Key& key, const Value& value, Node* left = nullptr, Node* right = nullptr);
		~Node() = default;

		bool isLeafNode() const;

		Key _key;
		Value _value;
		Node* _left;
		Node* _right;
	};

public:
	////
	BST();
	
	BST(const BST& copyTree);
	BST& operator=(const BST& copyTree);
	Node* BSTDeepCopy(const Node* node) const; // recursive function for copy semantics
	
	BST(BST&& moveTree) noexcept;
	BST& operator=(BST&& moveTree) noexcept;
	
	~BST();
	////

	// добавление узла
	void insert(const Key& key, const Value& value);
	void insert(Node* node, const Key& key, const Value& value);

	// удаление узла
	void remove(const Key& key);
	void remove(Node* node, const Key& key);

	// очистка дерева
	void clear();
	void clear(Node* node);

	// поиск в дереве
	const Value& find(const Key& key) const;
	const Value& find(Node* node, const Key& key) const;
	
	// обход дерева
	void traverse();
	void traverse(Node* node);

	bool isEmpty() const;

private:
    Node* _root;
	void _deleteNode(Node* node, Node* parent);
};



template<typename Key, typename Value>
BST<Key, Value>::Node::Node(const Key& key, const Value& value, Node* left, Node* right) : 
	_key(key),
	_value(value),
	_left(left),
	_right(right)
{

}

template<typename Key, typename Value>
bool BST<Key, Value>::Node::isLeafNode() const {
	return (this && !this->_left && !this->_right);
}

////

template<typename Key, typename Value>
BST<Key, Value>::BST() : _root(nullptr) 
{

}

template<typename Key, typename Value>
BST<Key, Value>::BST(const BST& copyTree) :
	_root(BSTDeepCopy(copyTree._root))
{

}

template<typename Key, typename Value>
BST<Key, Value>& BST<Key, Value>::operator=(const BST& copyTree) {
	if (this != &copyTree) {
		if (!isEmpty()) {
			clear();
		}
		_root = BSTDeepCopy(copyTree._root);
	}
	return *this;
}

template<typename Key, typename Value>
typename BST<Key, Value>::Node* BST<Key, Value>::BSTDeepCopy(const Node* node) const {
	if (!node) {
		return nullptr;
	}
	Node* copyNode = new Node(node->_key, node->_value);
	copyNode->_left = BSTDeepCopy(node->_left);
	copyNode->_right = BSTDeepCopy(node->_right);
	return copyNode;
}

template<typename Key, typename Value>
BST<Key, Value>::BST(BST&& moveTree) noexcept : _root(nullptr)
{
	std::swap(_root, moveTree._root);
}

template<typename Key, typename Value>
BST<Key, Value>& BST<Key, Value>::operator=(BST&& moveTree) noexcept {
	if (this != &moveTree) {
		if (!isEmpty()) {
			clear();
		}
	}
	std::swap(_root, moveTree._root);
	return *this;
}

template<typename Key, typename Value>
BST<Key, Value>::~BST()
{
	clear();
}

////

template<typename Key, typename Value>
void BST<Key, Value>::insert(const Key& key, const Value& value) {
	if (!_root) {
		_root = new Node(key, value);
	}
	else {
		insert(_root, key, value);
	}
}

template<typename Key, typename Value>
void BST<Key, Value>::insert(Node* node, const Key& key, const Value& value) {
	if (key <= node->_key) {
		if (!node->_left) {
			node->_left = new Node(key, value);
		}
		else {
			insert(node->_left, key, value);
		}
	}
	else {
		if (!node->_right) {
			node->_right = new Node(key, value);
		}
		else {
			insert(node->_right, key, value);
		}
	}
}

template<typename Key, typename Value>
const Value& BST<Key, Value>::find(const Key& key) const {
	return find(_root, key);
}

template<typename Key, typename Value>
const Value& BST<Key, Value>::find(Node* node, const Key& key) const {
	while (node) {
		if (node->_key == key) {
			return node->_value;
		}
		else if (key < node->_key) {
			node = node->_left;
		}
		else {
			node = node->_right;
		}
	}
	throw std::invalid_argument("Incorrect key");
}

template<typename Key, typename Value>
void BST<Key, Value>::remove(const Key& key) {
	remove(_root, key);
}

template<typename Key, typename Value>
void BST<Key, Value>::remove(Node* node, const Key& key) {
	if (!node) {
		return;
	}
	Node* parent = nullptr;
	while (node) {
		if (key < node->_key) {
			parent = node;
			node = node->_left;
		}
		else if (key > node->_key) {
			parent = node;
			node = node->_right;
		}
		else {
			_deleteNode(node, parent);
		}
	}
}

template<typename Key, typename Value>
void BST<Key, Value>::_deleteNode(Node* node, Node* parent) {
	// case 1: нет потомков
	if (node->isLeafNode()) {
		if (parent->_left == node) {
			parent->_left = nullptr;
		}
		else {
			parent->_right = nullptr;
		}
		delete node;
		return;
	}

	// case 2: один потомок
	if (!node->_left || !node->_right) {
		if (!node->_left) {
			Node* NRight = node->_right;
			node->_key = NRight->_key;
			node->_value = NRight->_value;
			node->_left = NRight->_left;
			node->_right = NRight->_right;
			delete NRight;
		}
		else {
			Node* NLeft = node->_left;
			node->_key = NLeft->_key;
			node->_value = NLeft->_value;
			node->_left = NLeft->_left;
			node->_right = NLeft->_right;
			delete NLeft;
		}
		return;
	}

	// case 3: два потомка
	if (!node->_right->_left) {
		node->_value = node->_right->_value;
		Node* tmpNode = node->_right->_right;
		delete node->_right;
		node->_right = tmpNode;
	}
	else {
		Node* leftMost = node->_right;
		Node* leftMostParent = parent;
		// поиск минимального элемента в правом поддереве
		while (leftMost->_left) {
			leftMostParent = leftMost;
			leftMost = leftMost->_left;
		}
		node->_key = leftMost->_key;
		node->_value = leftMost->_value;
		return _deleteNode(leftMost, leftMostParent);
	}
}

template<typename Key, typename Value>
void BST<Key, Value>::clear() {
	clear(_root);
	_root = nullptr;
}

template<typename Key, typename Value>
void BST<Key, Value>::clear(Node* node) {
	if (!node) {
		return;
	}
	clear(node->_left);
	clear(node->_right);
	delete node;
}

template<typename Key, typename Value>
void BST<Key, Value>::traverse() {
	traverse(_root);
}

template<typename Key, typename Value>
void BST<Key, Value>::traverse(Node* node) {
	if (!node) {
		return;
	}
	traverse(node->_left);
	std::cout << node->_key << ": " << node->_value << std::endl;
	traverse(node->_right);
}

template<typename Key, typename Value>
bool BST<Key, Value>::isEmpty() const {
	return (!_root);
}