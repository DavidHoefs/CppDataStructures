#pragma once
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Generic.h"

namespace algo {
	template <typename Object>
	class List {
	private:
		class ListNode {
		public:
			ListNode(const Object& obj = Object{}, ListNode* pNext = nullptr, ListNode* pPrev = nullptr) : element{ obj }, next{ pNext }, prev(pPrev){}

			ListNode(const Object&& obj, ListNode* pNext = nullptr, ListNode* pPrev = nullptr) : element(std::move(obj)), next(pNext), prev(pPrev) {}

		private:
			Object element;
			ListNode* next;
			ListNode* prev;

			friend class List<Object>;
		};

	public:
		class const_iterator {
		public:
			const_iterator() : current{ nullptr } {}

			const Object& operator*() const {
				return retrieve();
			}

			const_iterator& operator++() {
				current = current->next;
				return *this;
			}

			const_iterator operator++(int) {
				const_iterator old = *this;
				++(*this);
				return old;
			}

			const_iterator& operator-- ()
			{
				current = current->prev;
				return *this;
			}

			const_iterator operator-- (int)
			{
				const_iterator old = *this;
				--(*this);
				return old;
			}

			bool operator== (const const_iterator& rhs) const
			{
				return (current == rhs.current);
			}

			bool operator!= (const const_iterator& rhs) const
			{
				return (current != rhs.current);
			}

		protected:
			ListNode* current;
			Object& retrieve() const {
				return current->element;
			}

			const_iterator(ListNode* p) :current{ p } {}

			friend class List<Object>;
		};

		class iterator : public const_iterator {
		public:
			iterator() { }

			Object& operator*()
			{
				return const_iterator::retrieve();
			}

			const Object& operator*() const
			{
				return const_iterator::operator*();
			}

			iterator& operator++()
			{
				this->current = this->current->next;
				return *this;
			}

			iterator operator++ (int)
			{
				iterator old = *this;
				++(*this);
				return old;
			}

			iterator& operator--()
			{
				this->current = this->current->prev;
				return *this;
			}

			iterator operator-- (int)
			{
				iterator old = *this;
				--(*this);
				return old;
			}

		protected:
			iterator(ListNode* node) : const_iterator{ node }
			{ }

			friend class List<Object>;
		}; //end of class iterator

	public:
		List() {
			initialize();
		}
		~List() {
			clear();
			delete _head;
			delete _tail;
		}

		List(const List& rhs) {
			initialize();
			for (auto& elem : rhs)
				pushBack(elem);
		}

		List(List&& rhs) :_size(rhs._size), _head(rhs._head), _tail(rhs._tail) {
			rhs._size = 0;
			rhs._head = rhs._tail = nullptr;
		}

		List& operator= (const List& rhs) {
			List copy = rhs;
			algo::swap(copy, *this);
			return *this;
		}

		List& operator=(List&& rhs) {
			algo::swap(_size, rhs._size);
			algo::swap(_head, rhs._head);
			algo::swap(_tail, rhs._tail);
			return *this;
		}

		iterator begin() {
			return iterator(_head->next);
		}

		const_iterator begin() const {
			return const_iterator(_head->next);
		}

		iterator end() {
			return iterator(_tail);
		}

		const_iterator end() const {
			return const_iterator(_tail);
		}

		int size() const {
			return _size;
		}

		bool empty() const {
			return (_size == 0);
		}

		void clear() {
			while (!empty()) {
				popFront();
			}
		}

		Object& front() {
			return (*begin());
		}

		const Object& front() const {
			return (*begin());
		}

		Object& back() {
			return (*--end());
		}

		const Object& back() const {
			return (*--end());
		}

		void pushFront(const Object& obj) {
			insert(obj, begin());
		}

		void pushFront(Object&& obj)
		{
			insert(std::move(obj), begin());
		}

		void pushBack(const Object& obj) {
			insert(obj, end());
		}

		void pushBack(Object&& obj)
		{
			insert(std::move(obj), end());
		}

		void popFront() {
			erase(begin());
		}

		void popBack() {
			erase(--end());
		}

		iterator insert(const Object& obj, iterator it) {
			ListNode* currentNode = it.current;
			ListNode* newNode = new ListNode{ obj,currentNode,currentNode->prev };
			currentNode->prev->next = newNode;
			currentNode->prev = newNode;
			++_size;

			return iterator(newNode);
		}

		iterator erase(iterator it) {
			ListNode* currentNode = it.current;
			iterator returnIterator(currentNode->next);
			currentNode->prev->next = currentNode->next;
			currentNode->next->prev = currentNode->prev;

			delete currentNode;
			--_size;
			return returnIterator;
		}

		iterator erase(iterator from, iterator to) {
			for (iterator it = from; it != to;)
			{
				it = erase(it);
			}
			return to;
		}

		void print(const List<int>& lst) {
			for (List<int>::const_iterator it = lst.begin(); it != lst.end(); it++)
			{
				std::cout << *it << " ";
			}
			std::cout << std::endl;
		}

		void printList(List<Object>& lst)
		{
			for (List<Object>::const_iterator it = lst.begin(); it != lst.end(); it++)
			{
				std::cout << *it << " ";
			}
			std::cout << std::endl;
		}

		/// <summary>
		/// Checks if list of chars is a palindrome. Compares first and last, popping values after evaluating.
		/// </summary>
		/// <returns>TRUE/FALSE</returns>

		bool isPalindrome() {
			if (empty())
				return false;

			while (!empty()) {
				if (_head->next == nullptr || _size == 1) {
					break;
				}
				char first = this->front();
				char last = this->back();
				if (first != last) {
					return false;
				}
				this->popBack();
				this->popFront();
			}

			return true;
		}

	private:
		int _size;
		ListNode* _head;
		ListNode* _tail;

		void initialize() {
			_size = 0;
			_head = new ListNode;
			_tail = new ListNode;
			_head->next = _tail;
			_tail->prev = _head;
		}
	};
}

#endif
