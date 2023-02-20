cmake_minimum_required(VERSION 3.19)
PROJECT ( bengine3 )

# 	set (CMAKE_CXX_STANDARD 11)
	set (CMAKE_CXX_STANDARD 20)

	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s")

	IF (WIN32)
		SET (BUILD_SHARED_LIBS OFF)
		SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
		SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /arch:SSE2 /Oi") # Also consider /GL /fp:fast ?
	ENDIF (WIN32)

	IF (UNIX)
		SET (BUILD_SHARED_LIBS OFF)
		#add_definitions(-DUNIX -fPIC)
	ENDIF (UNIX)

	include_directories( deps src )

	LINK_LIBRARIES ( ${bengine3_LIBS} )
	LINK_DIRECTORIES ( ${bengine3_LIBS_DIRS} )
	#TARGET_LINK_LIBRARIES ( src )

	add_subdirectory(src)

