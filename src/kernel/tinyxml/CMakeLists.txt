set(tinyxml_STAT_SRCS
    tinystr.cpp
	tinyxml.cpp
	tinyxmlerror.cpp
	tinyxmlparser.cpp
    )

add_library(tinyxml STATIC ${tinyxml_STAT_SRCS})
