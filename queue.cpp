#include <iostream>
#include <memory>
#include <algorithm>
#include <cstddef>
#include "allocator.cpp"

template<typename T>
class Queue {
private:
	class Node {
	public:
		Node(): next{nullptr}, prev{next} {};
		friend class Queue;

	private:
		std::shared_ptr<Node> next;
		std::weak_ptr<Node> prev;
		T value;
	};

public:
	class ForwardIterator {
	public:
		using value_type = T;
	    using reference = T&;
	    using pointer = T*;
	    using difference_type = ptrdiff_t;
	    using iterator_category = std::forward_iterator_tag;
		friend class Queue;

		ForwardIterator(std::shared_ptr<Node> it = nullptr): ptr{it} {};
		ForwardIterator(const ForwardIterator &other): ptr{other.ptr} {};

		ForwardIterator operator++() {
			if (this->ptr.lock() == nullptr) {
				return *this;
			}
			this->ptr = ptr.lock()->next;
			return *this;
		}

		ForwardIterator operator++(int s) {
			if (ptr.lock() == nullptr) {
				return *this;
			}
			ForwardIterator old{this->ptr.lock()};
			++(*this);
			return old;
		}

		T& operator*() {
			return this->ptr.lock()->value;
		}

		const T& operator*() const {
			return this->ptr.lock()->value;
		}

		std::shared_ptr<Node> operator->() {
			return this->ptr.lock();
		}

		std::shared_ptr<const Node> operator->() const {
			return this->ptr.lock();
		}

		bool operator==(const ForwardIterator &rhs) const {
			return this->ptr.lock() == rhs.ptr.lock();
		}

		bool operator!=(const ForwardIterator &rhs) const {
			return this->ptr.lock() != rhs.ptr.lock();
		}

		ForwardIterator Next() const {
			if (this->ptr.lock() == nullptr)
				return ForwardIterator{};
			return this->ptr.lock()->next;
		}

	private:
		std::weak_ptr<Node> ptr;
	};



	void Push(const T& val) {
		if (!head) {
			head = allocNode(val);
			tail = head;
		} else {
			std::shared_ptr<Node> newElem = allocNode(val);
			newElem->prev = tail;
			tail.lock()->next = newElem;
			tail = newElem;
		}
		size++;
	}

	void Pop() {
		if (this->head) {
			head = head->next;
			size--;
		}
	}

	ForwardIterator Insert(const ForwardIterator it, const T& val) {
		if (it == ForwardIterator{}) {
			if (tail.lock() == nullptr) {
				Push(val);
				return Begin();
			}
			std::shared_ptr<Node> newElem = allocNode(val);
			newElem->prev = tail;
			tail.lock()->next = newElem;
			tail = newElem;
			size++;
			return newElem;
		}
		if (it == Begin()) {
			std::shared_ptr<Node> newElem = allocNode(val);
			newElem->next = it.ptr.lock();
			it->prev.lock() = newElem;
			head = newElem;
			size++;
			return newElem;
		}
		std::shared_ptr<Node> newElem = allocNode(val);
		newElem->next = it.ptr.lock();
		it->prev.lock()->next = newElem;
		newElem->prev = it->prev;
		it->prev.lock() = newElem;
		size++;
		return newElem;
	}


	ForwardIterator Erase(const ForwardIterator it) {
		if (it == ForwardIterator{}) {
			return End();
		}
		if (it->prev.lock() == nullptr && head == tail.lock()) {
			head = nullptr;
			tail = head;
			size = 0;
			return End();
		}
		if (it->prev.lock() == nullptr) {
			it->next->prev.lock() = nullptr;
			head = it->next;
			size--;
			return head;
		}
		ForwardIterator res = it.Next();
		if (res == ForwardIterator{}) {
			it->prev.lock()->next = nullptr;
			size--;
			return End();
		}
		it->next->prev = it->prev;
		it->prev.lock()->next = it->next;
	    size--;
		return res;
	}


	ForwardIterator Begin() {
		return head;
	}

	ForwardIterator End() {
		return ForwardIterator{};
	}

	size_t Size() const {
		return size;
	}



private:

	std::shared_ptr<Node> head;
	std::weak_ptr<Node> tail;
	size_t size;

	static const size_t memSize = 10000;
	TAllocator<Node,memSize> alloc;

	void deallocNode( Node *ptr ) {
		alloc.deallocate( ptr );
	}

	std::shared_ptr<Node> allocNode(const T& val) {
		Node *res = alloc.allocate();
		res->value = val;
		return std::shared_ptr<Node>( res, std::bind( &Queue::deallocNode, this, std::placeholders::_1 ));
	}
};
