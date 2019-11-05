#!/bin/sh -ve
rm -rfv *.o *.dSYM txneko
for fn in cat txneko
do
	c++ -c -Wall -std=c++0x -g -O3 -o $fn.o $fn.cpp `txlin-macflags --cflags`
done
c++ -std=c++0x -g -O3 -o txneko -I. txneko.o cat.o `txlin-macflags --cflags` `txlin-macflags --libs`
exit $?
