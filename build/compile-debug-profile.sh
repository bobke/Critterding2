#!/bin/bash 
rm CMakeCache.txt -fr && rm CMakeFiles -fr
CXXFLAGS="-Og -g2 -Wall -Wextra -fPIC -pg" cmake -DCMAKE_BUILD_TYPE=Debug ../                                                                                                                                                           
if [ -z "$1" ]
	then
		time make
	else
		time make -j${1}
fi

