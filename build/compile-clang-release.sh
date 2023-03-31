#!/bin/bash 
rm CMakeCache.txt -fr && rm CMakeFiles -fr
CC=/usr/bin/clang CXX=/usr/bin/clang++ CXXFLAGS="-march=native -Ofast -w -rdynamic -fPIC" cmake -DCMAKE_BUILD_TYPE=Release ../
# CXXFLAGS="-Ofast -Wall -Wextra" cmake -DCMAKE_BUILD_TYPE=Release ./
if [ -z "$1" ]
	then
		time make
	else
		time make -j${1}
fi
