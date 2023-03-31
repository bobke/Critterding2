#!/bin/bash 
rm CMakeCache.txt -fr && rm CMakeFiles -fr
CC=/usr/bin/clang CXX=/usr/bin/clang++ CXXFLAGS="-O0 -g3 -Wall -Wextra -rdynamic -fPIC -fsanitize=leak" cmake -DCMAKE_BUILD_TYPE=Debug ../                                                                                                                                                           
if [ -z "$1" ]
	then
		time make
	else
		time make -j${1}
fi

