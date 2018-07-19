#include "stack.hpp"
#include <thread>
#include <vector>
#include <iostream>

typedef stack<int> stack_t;

void worker(stack_t& s)
{
	for (size_t i = 0; i != 10*1000; ++i)
		s.push(i);
}

void work(stack_t& s)
{
	std::vector<std::thread> w;
	for (size_t i = 0; i != 1000; ++i)
		w.emplace_back(worker, std::ref(s));
	for (size_t i = 0; i != w.size(); ++i)
		w[i].join();
}

int main()
{
	stack_t s;
	work(s);
	std::cout << s.size() << std::endl;
	return 0;
}
