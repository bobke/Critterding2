#!/bin/bash 
rm CMakeCache.txt -fr && rm CMakeFiles -fr
CXXFLAGS="-O0 -g2 -Wall -Wextra -rdynamic -fPIC" cmake -DCMAKE_BUILD_TYPE=Debug ../                                                                                                                                                           
if [ -z "$1" ]
	then
		time make
	else
		time make -j${1}
fi

