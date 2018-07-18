#include <utility>
#include <stdexcept>
#include <memory>
#include <iostream>

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
		while (head) {
			node* p = head;
			head = head->next;
			delete p;
		}
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
		node* p = new node(val, head);
		std::swap(p, head);
	}
	T pop() {
		if (empty()) throw std::runtime_error("pop empty stack");
		node* p = head->next;
		std::swap(p, head);

		std::unique_ptr<node> u(p);
		return p->data;
	}
private:
	node* head;
};

void worker(stack<int>& s)
{
	s.push(0);
}

int main()
{
	stack<int> s;
	worker(s);
	std::cout << s.size() << std::endl;
	return 0;
}
