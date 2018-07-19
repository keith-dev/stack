#pragma once

#if LOCK
	#include <mutex>
#endif

#ifdef LOCK_FREE
	#include <atomic>
#else
	#include <utility>
#endif

#include <memory>
#include <stdexcept>

template <class T>
class stack
{
	struct node {
		node(T val, node* ptr = nullptr) : data(val), next(ptr) {}
		T data;
		node* next;
	};
public:
	stack() : head(nullptr) {}
	~stack() {
//		while (head) {
//			node* p = head;
//			head = p->next;
//			delete p;
//		}
	}
	bool empty() const {
		return head != nullptr;
	}
	size_t size() const {
		size_t n = 0;
		for (node* p = head; p; p = p->next) ++n;
		return n;
	}
	void push(T val) {
#if LOCK
		std::lock_guard<std::mutex> lock(mtx);
#endif
		node* p = new node(val, head);
#ifdef LOCK_FREE
		while ( !head.compare_exchange_weak(p->next, p) );
#else
		std::swap(p, head);
#endif
	}
	T pop() {
#if LOCK
		std::lock_guard<std::mutex> lock(mtx);
#endif
		if (empty()) throw std::runtime_error("pop empty stack");
		node* p = head;
#ifdef LOCK_FREE
		while ( !head.compare_exhange_weak(p, p->next) )
			if (empty()) throw std::runtime_error("pop empty stack");
#else
		std::swap(head, p->next);
#endif
		std::unique_ptr<node> u(p);
		return p->data;
	}
private:
#if LOCK
	std::mutex mtx;
#endif
#ifdef LOCK_FREE
	std::atomic<node*> head;
#else
	node* head;
#endif
};
