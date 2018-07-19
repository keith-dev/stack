PROG_CXX = prog
SRCS = main.cc
INCS = stack.hpp
MK_MAN = no

CXXFLAGS = -O2 -std=c++11 -Wall -Wextra -pthread -DLOCK_FREE=1

all: $(PROG_CXX)

clean:
		- rm $(PROG_CXX) $(SRCS:.cc=.o)

$(PROG_CXX): $(SRCS:.cc=.o)
		$(LINK.cc) -o $@ $^ $(LDADD)
