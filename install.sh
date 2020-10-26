#!/bin/sh
# Penn Bauman
# pennbauman@protonmail.com

echo -n "Compiling..."
g++ -O2 bool-test.cpp -o bool-test
echo "Done"

sudo mv bool-test /bin/
echo "Installed"
