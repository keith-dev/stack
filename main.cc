#include "stack.hpp"
#include <thread>
#include <vector>
#include <iostream>

typedef sstack<int> sstack_t;

void worker(sstack_t& s, size_t nitems)
{
	for (size_t i = 0; i != nitems; ++i)
		s.push(i);
}

void work(sstack_t& s, size_t nitems, size_t nthreads)
{
#ifdef SEQUENTIAL
	for (size_t i = 0; i != nthreads; ++i)
		worker(s, nitems);
#else
	std::vector<std::thread> w;
	w.reserve(nthreads);
	for (size_t i = 0; i != nthreads; ++i)
		w.emplace_back(worker, std::ref(s), nitems);
	for (size_t i = 0; i != w.size(); ++i)
		w[i].join();
#endif
}

int main(int argc, char* argv[])
{
	size_t nitems   = argc > 1 ? atoi(argv[1]) : 500*1000;
	size_t nthreads = argc > 2 ? atoi(argv[2]) : 5*100;
	sstack_t s;
	work(s, nitems, nthreads);
	std::cout << s.size() << std::endl;
}
