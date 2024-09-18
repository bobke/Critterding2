
	SET (
		bengine_SRCS 
		bengine.cpp 
		bengine.h
	)

	unset(missingDependencies)

	# PTHREAD
		MESSAGE(CHECK_START "pthread")
		FIND_LIBRARY(PTHREAD_LIBRARY NAMES pthread libpthread REQUIRED )
		IF (PTHREAD_LIBRARY)
			MESSAGE(CHECK_PASS "found " ${PTHREAD_LIBRARY})
			SET(bengine_LIBS ${bengine_LIBS} ${PTHREAD_LIBRARY}) 
		ELSE (PTHREAD_LIBRARY)
			MESSAGE(CHECK_FAIL "not found ")
			list(APPEND missingDependencies "pthread")
		ENDIF (PTHREAD_LIBRARY)
		
	# DL
	 # no "REQUIRED". On FreeBSD, NetBSD and OpenBSD there is no libdl, as the required functionality is already built into libc.
		MESSAGE(CHECK_START "dl")
		FIND_LIBRARY(DL_LIBRARY NAMES dl libdl )
		IF (DL_LIBRARY)
			MESSAGE(CHECK_PASS "found " ${DL_LIBRARY})
			SET(bengine_LIBS ${bengine_LIBS} ${DL_LIBRARY}) 
		ELSE (DL_LIBRARY)
			MESSAGE(CHECK_FAIL "not found ")
			# list(APPEND missingDependencies "dl")
		ENDIF (DL_LIBRARY)

	# LIST MISSING DEPENDENCIES
		list(POP_BACK CMAKE_MESSAGE_INDENT)
		if(missingDependencies)
			message(FATAL_ERROR " MISSING DEPENDENCIES: ${missingDependencies}")
		endif()		

	# LINK
		LINK_LIBRARIES ( ${bengine_LIBS} )
		
	# EXECUTABLE
		ADD_EXECUTABLE(bengine ${bengine_SRCS})

	# LINK SUBDIRECTORIES
	 	TARGET_LINK_LIBRARIES ( bengine kernel )
	 	# FIXME OR DISABLE LINK_LIBRARIES AND DO
	 	# TARGET_LINK_LIBRARIES ( bengine kernel ${bengine_LIBS} )

	# SUBDIRECTORIES
		ADD_SUBDIRECTORY(kernel)
		ADD_SUBDIRECTORY(plugins)
		ADD_SUBDIRECTORY(ai_plugins)
	 	
# 	# INCLUDE_DIRECTORIES
# 		INCLUDE_DIRECTORIES( ${bengine_INCLUDES} )
