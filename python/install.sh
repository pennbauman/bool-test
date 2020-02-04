#!/bin/sh
# Boolean Tester Installer

# Create script directory
if [ ! -d /usr/share/bool-test/ ]; then
    sudo mkdir /usr/share/bool-test/
fi 
# Create or replace python scripts
if [ -f /usr/share/bool-test/boolean-tester.py ]; then
    sudo rm /usr/share/bool-test/boolean-tester.py 
fi
sudo cp boolean-tester.py /usr/share/bool-test/
# Create or replace help text
if [ -f /usr/share/bool-test/help.txt ]; then
    sudo rm /usr/share/bool-test/help.txt
fi
sudo cp help.txt /usr/share/bool-test/
# Create or replace runner bash scripts
if [ -f /bin/bool-test ]; then
    sudo rm /bin/bool-test
fi 
sudo cp bool-test /bin/
