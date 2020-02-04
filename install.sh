#!/bin/sh
# Penn Bauman
# pennbauman@protonmail.com

if clang++ --version &> /dev/null; then
	echo "Making (clang++)"
	clang++ -O2 bool-test.cpp -o bool-test
else
	echo "Making (g++)"
	g++ -O2 bool-test.cpp -o bool-test
fi

sudo mv bool-test /bin/
echo "Installed"
