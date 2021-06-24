#pragma once

#include <iostream>
#include <algorithm>
#include <exception>

template<typename T>
class BST
{
	struct Node {
		Node(const T& value, Node* left = nullptr, Node* right = nullptr);
		~Node() = default;

		bool isLeafNode() const;

		T _value;
		Node* _left;
		Node* _right;
	};

public:
	////
	BST();
	/*
	BST(const BST& copyTree);
	BST& operator=(const BST& copyTree);
	*/
	BST(BST&& moveTree) noexcept;
	BST& operator=(BST&& moveTree) noexcept;
	
	~BST();
	////

	// добавление узла
	void insert(const T& value);
	void insert(Node* node, const T& value);

	// удаление узла
	void remove(const T& value);
	void remove(Node* node, const T& value);

	// очистка дерева
	void clear();
	void clear(Node* node);

	// поиск в дереве
	const T& find(const T& value) const;
	const T& find(Node* node, const T& value) const;
	
	// обход дерева
	void traverse();
	void traverse(Node* node);

	bool isEmpty() const;

private:
    Node* _root;
	void _deleteNode(Node* node, Node* parent);
};



template<typename T>
BST<T>::Node::Node(const T& value, Node* left, Node* right) : 
	_value(value),
	_left(left),
	_right(right)
{

}

template<typename T>
bool BST<T>::Node::isLeafNode() const {
	return (this && !this->_left && !this->_right);
}

////

template<typename T>
BST<T>::BST() : _root(nullptr) 
{

}

template<typename T>
BST<T>::BST(BST<T>&& moveTree) noexcept : _root(nullptr)
{
	std::swap(_root, moveTree._root);
}

template<typename T>
BST<T>& BST<T>::operator=(BST<T>&& moveTree) noexcept {
	if (this != &moveTree) {
		if (!isEmpty()) {
			clear();
		}
	}
	std::swap(_root, moveTree._root);
	return *this;
}


template<typename T>
BST<T>::~BST()
{
	clear();
}

////

template<typename T>
void BST<T>::insert(const T& value) {
	if (!_root) {
		_root = new Node(value);
	}
	else {
		insert(_root, value);
	}
}

template<typename T>
void BST<T>::insert(Node* node, const T& value) {
	if (value <= node->_value) {
		if (!node->_left) {
			node->_left = new Node(value);
		}
		else {
			insert(node->_left, value);
		}
	}
	else {
		if (!node->_right) {
			node->_right = new Node(value);
		}
		else {
			insert(node->_right, value);
		}
	}
}

template<typename T>
const T& BST<T>::find(const T& value) const {
	return find(_root, value);
}

template<typename T>
const T& BST<T>::find(Node* node, const T& value) const {
	while (node) {
		if (node->_value == value) {
			return node->_value;
		}
		else if (value < node->_value) {
			node = node->_left;
		}
		else {
			node = node->_right;
		}
	}
	throw std::invalid_argument("Incorrect value");
}

template<typename T>
void BST<T>::remove(const T& value) {
	remove(_root, value);
}

template<typename T>
void BST<T>::remove(Node* node, const T& value) {
	if (!node) {
		return;
	}
	Node* parent = nullptr;
	while (node) {
		if (value < node->_value) {
			parent = node;
			node = node->_left;
		}
		else if (value > node->_value) {
			parent = node;
			node = node->_right;
		}
		else {
			_deleteNode(node, parent);
		}
	}
}

template<typename T>
void BST<T>::_deleteNode(Node* node, Node* parent) {
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
			node->_value = NRight->_value;
			node->_left = NRight->_left;
			node->_right = NRight->_right;
			delete NRight;
		}
		else {
			Node* NLeft = node->_left;
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
		node->_value = leftMost->_value;
		return _deleteNode(leftMost, leftMostParent);
	}
}

template<typename T>
void BST<T>::clear() {
	clear(_root);
	_root = nullptr;
}

template<typename T>
void BST<T>::clear(Node* node) {
	if (!node) {
		return;
	}
	clear(node->_left);
	clear(node->_right);
	delete node;
}

template<typename T>
void BST<T>::traverse() {
	traverse(_root);
}

template<typename T>
void BST<T>::traverse(Node* node) {
	if (!node) {
		return;
	}
	traverse(node->_left);
	std::cout << node->_value << " ";
	traverse(node->_right);
}

template<typename T>
bool BST<T>::isEmpty() const {
	return (!_root);
}