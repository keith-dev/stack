#include "stack.hpp"
#include <thread>
#include <vector>
#include <iostream>

typedef stack<int> stack_t;

void worker(stack_t& s, size_t n)
{
	for (size_t i = 0; i != n; ++i)
		s.push(i);
}

void work(stack_t& s, size_t n)
{
	std::vector<std::thread> w;
#ifdef SEQUENTIAL
	for (size_t i = 0; i != 1000; ++i)
		worker(s, n);
#else
	for (size_t i = 0; i != 1000; ++i)
		w.emplace_back(worker, std::ref(s), n);
	for (size_t i = 0; i != w.size(); ++i)
		w[i].join();
#endif
}

int main(int argc, char* argv[])
{
	size_t n = argc > 1 ? atoi(argv[1]) : 100*1000;
	stack_t s;
	work(s, n);
	std::cout << s.size() << std::endl;
	return 0;
}
