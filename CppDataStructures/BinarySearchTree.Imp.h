
#ifndef BINARY_SEARCH_TREE_IMP_H
#define BINARY_SEARCH_TREE_IMP_H

//#include "Generic.h"
#include <stdexcept>
#include <iomanip>
#include <deque>
#include "BinarySearchTree.h"



namespace algo {



	/// <summary>
	/// Default Constructor
	/// </summary>
	/// <typeparam name="T"></typeparam>
	 // default constructor
	template <typename T>
	BinarySearchTree<T>::BinarySearchTree() : root{ nullptr }
	{ }

	
	/// <summary>
	/// Copy Constructor
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="rhs"></param>
	template <typename T>
	BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree& rhs) : root{ nullptr } {
		root = __copy(rhs.root);
	}

	/// <summary>
	/// Move Constructor
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="rhs"></param>
	template<typename T>
	BinarySearchTree<T>::BinarySearchTree(BinarySearchTree&& rhs)
		: root{ rhs.root }
	{
		rhs.root = nullptr;
	}

	/// <summary>
	/// Copy Assignment
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="rhs"></param>
	/// <returns></returns>
	template<typename T>
	BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree& rhs) {
		BinarySearchTree copy = rhs;
		swap(*this, copy);
		return *this;
	}

	/// <summary>
	/// Move assignment
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="rhs"></param>
	/// <returns></returns>
	template<typename T>
	BinarySearchTree<T>& BinarySearchTree<T>::operator=(BinarySearchTree&& rhs) {
		swap(root, rhs.root);
		return *this;
	}

	/// <summary>
	/// Deconstructor
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<typename T>
	BinarySearchTree<T>::~BinarySearchTree() {
		clear();
	}

	/// <summary>
	/// Find smallest element in tree
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <returns></returns>
	template<typename T>
	const T& BinarySearchTree<T>::findMin() const {
		if (empty())
			throw std::underflow_error("Empty Tree");
		return __findMin(root)->element;
	}

	/// <summary>
	/// Finds the largest element in the tree
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <returns></returns>
	template <typename T>
	const T& BinarySearchTree<T>::findMax() const {
		if (empty())
			return std::underflow_error("Empty Tree");
		return __findMax(root)->element;
	}

	/// <summary>
	/// Checks if tree contains element
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="obj"></param>
	/// <returns></returns>
	template<typename T>
	bool BinarySearchTree<T>::contains(const T& obj) const {
		return __contains(root, obj);
	}

	/// <summary>
	/// Checks if tree is empty
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <returns></returns>
	template<typename T>
	bool BinarySearchTree<T>::empty() const {
		return (root == nullptr);
	}

	/// <summary>
	/// Prints the tree in sorted order
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="out"></param>
	template <typename T>
	void BinarySearchTree<T>::printTree(std::ostream& out) const {
		if (empty())
			std::cout << "Tree is empty\n";
		__printTree(root, out);
	}

	/// <summary>
	/// Clears the BST
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<typename T>
	void BinarySearchTree<T>::clear() const {
		__clear(root);
	}

	/// <summary>
	/// Inserts element into the tree, ignores duplicates
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="obj"></param>
	template<typename T>
	void BinarySearchTree<T>::insert(const T& obj) {
		__insert(root, obj);
	}

	/// <summary>
	/// Move element into tree, duplicates ignored
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="obj"></param>
	template<typename T>
	void BinarySearchTree<T>::insert(T&& obj) {
		__insert(root, std::move(obj));
	}

	/// <summary>
	/// Removes an element from the tree
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="obj"></param>
	template<typename T>
	void BinarySearchTree<T>::remove(const T& obj) {
		__remove(root, obj);
	}

	/// <summary>
	/// Gets the height of the tree
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <returns></returns>
	template<typename T>
	const int BinarySearchTree<T>::height() const {
		return __height(root);
	}

	/// <summary>
	/// Pretty print the tree
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<typename T>
	void BinarySearchTree<T>::prettyPrint() const {
		__prettyPrint(root);
	}

	template<typename T>
	typename BinarySearchTree<T>::BinaryNode* BinarySearchTree<T>::getRoot() const {
		return root;
	}

	template<typename T>
	const T& BinarySearchTree<T>::__findMin(BinaryNode* node) const {
		if (node == nullptr)
			return nullptr;
		else if (node->left == nullptr)
			return node;
		else
			return __findMin(node->left);
	}

	template<typename T>
	const T& BinarySearchTree<T>::__findMax(BinaryNode* node) const {
		if (node == nullptr)
			return nullptr;
		else if (node->right == nullptr)
			return node;
		else
			return __findMax(node->right);
	}

	template <typename T>
	bool BinarySearchTree<T>::__contains(BinaryNode* node, const T& obj) const {
		if (node == nullptr)
			return false;
		else if (obj < node->element)
			return __contains(node->left, obj);
		else if (obj > node->element)
			return __contains(node->right, obj);
		else
			return true;
	}

	template <typename T>
	void BinarySearchTree<T>::__insert(BinaryNode*& node, const T& obj) {
		if (node == nullptr)
			node = new BinaryNode(obj, nullptr, nullptr);
		else if (obj < node->element)
			__insert(node->left, obj);
		else if (obj > node->element)
			__insert(node->right, obj);
		else {
			// ignore duplicates
		}
	}

	template<typename T>
	void BinarySearchTree<T>::__insert(BinaryNode*& node, T&& obj) {
		if (node == nullptr) {
			node = new BinaryNode(std::move(obj), nullptr, nullptr);
			return;
		}

		BinaryNode* currNode = node;
		bool flag = true;

		while (flag) {
			if (currNode->element > obj) {
				if (currNode->left == nullptr) {
					currNode->left = new BinaryNode(std::move(obj), nullptr, nullptr);
					flag = false;
				}
				else {
					currNode = currNode->left;
				}
			}
			else if (currNode->element < obj) {
				if (currNode->right == nullptr) {
					currNode->right = new BinaryNode(std::move(obj), nullptr, nullptr);
					flag = false;
				}
				else {
					currNode = currNode->right;
				}
			}
			else {
				// duplicate case
				flag = false;
			}
		}
	}

	template <typename T>
	void BinarySearchTree<T>::__remove(BinaryNode* node, const T& obj) {
		if (node == nullptr)
			return;

		if (obj < node->element)
			__remove(node->left, obj);
		else if (obj > node->element)
			__remove(node->right, obj);
		else {
			if (node->left != nullptr && node->right != nullptr) {
				node->element == __findMin(node->right)->element;
				__remove(node->right, node->element);
			}
			else {
				BinaryNode* oldNode = node;
				node = (node->left != nullptr) ? node->left : node->right;
				delete oldNode;
			}
		}
	}

	template<typename T>
	void BinarySearchTree<T>::__clear(BinaryNode* node) const {
		if (node != nullptr) {
			__clear(node->left);
			__clear(node->right);
			delete node;
		}
	}

	template <typename T>
	void BinarySearchTree<T>::__printTree(BinaryNode* node, std::ostream& out) const {
		if (node != nullptr) {
			__printTree(node->left, out);
			out << node->element << " ";
			__printTree(node->right, out);
		}
	}

	template <typename T>
	typename BinarySearchTree<T>::BinaryNode* BinarySearchTree<T>::__copy(BinaryNode* node) {
		if (node == nullptr)
			return nullptr;

		return new BinaryNode(node->element, __copy(node->left), __copy(node->right));
	}

	template <typename T>
	void BinarySearchTree<T>::__prettyPrint(BinaryNode* node, int indent, std::ostream& out) const
	{
		if (node != nullptr) {
			if (node->right != nullptr)
				__prettyPrint(node->right, indent + 4, out);

			if (indent)
				out << std::setw(indent) << ' ';

			if (node->right != nullptr)
				out << " /\n" << std::setw(indent) << ' ';

			out << node->element << std::endl;

			if (node->left != nullptr) {
				out << std::setw(indent) << ' ' << " \\\n";
				__prettyPrint(node->left, indent + 4, out);
			}
		}
	}

	//private function to get tree height
	template <typename T>
	const int BinarySearchTree<T>::__height(BinaryNode* node)
	{
		if (node == nullptr) {
			return 0;
		}
		int leftHeight = __height(node->left);
		int rightHeight = __height(node->right);
		return ((leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1);
	}

	template <typename T>
	void BinarySearchTree<T>::mirror()
	{
		__mirror(root);
	}

	template <typename T>
	void BinarySearchTree<T>::__mirror(BinaryNode*& node)
	{
		if (node != nullptr)
		{
			__mirror(node->left);
			__mirror(node->right);
			swap(node->left, node->right);
		}
	}

}

#endif