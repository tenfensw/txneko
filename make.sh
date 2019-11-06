#!/bin/sh -ve
rm -rfv *.o *.dSYM txneko
for fn in main
do
	c++ -c -Wall -std=c++0x -Itxcairo -g -O3 -o $fn.o $fn.cxx `txlin-macflags --cflags` `pkg-config --cflags cairo`
done
c++ -std=c++0x -g -O3 -o txneko main.o `txlin-macflags --libs` `pkg-config --libs cairo`
exit $?
