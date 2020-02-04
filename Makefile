# Penn Bauman
# pennbauman@protonmail.com
#
CXX=clang++

bool-test: bool-test.cpp
	$(CXX) bool-test.cpp

test: bool-test
	./a.out

help: bool-test
	./a.out -h

clean:
	@rm -f *.o *.out bool-test
