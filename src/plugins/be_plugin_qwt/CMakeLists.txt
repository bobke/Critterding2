	set(CMAKE_AUTOMOC ON)

	SET(
		plugin_SRCS 
		plugin.cpp
		plugin.h
	)

	find_package(Qt6 COMPONENTS Widgets REQUIRED)
	
	# QWT
		FIND_PATH(QWT_INCLUDE_DIR NAMES qwt.h PATHS
		/usr/qwt-6.2.0/include
		/usr/local/qwt-6.2.0/include
		/usr/include
		/usr/local/include
		"$ENV{LIB_DIR}/include" 
		"$ENV{INCLUDE}" 
		PATH_SUFFIXES qwt
		)
 
		FIND_LIBRARY(QWT_LIBRARY NAMES qwt PATHS 
		/usr/qwt-6.2.0/lib
		/usr/local/qwt-6.2.0/lib
		/usr/lib
		/usr/local/lib
		"$ENV{LIB_DIR}/lib" 
		"$ENV{LIB}/lib" 
		)
 
		IF (QWT_INCLUDE_DIR AND QWT_LIBRARY)
		SET(QWT_FOUND TRUE)
		ENDIF (QWT_INCLUDE_DIR AND QWT_LIBRARY)
 
		IF (QWT_FOUND)
			IF (NOT QWT_FIND_QUIETLY)
				MESSAGE("QWT FOUND")
				
				INCLUDE_DIRECTORIES( ${bengine3_INCLUDES} ${QWT_INCLUDE_DIR} )
				ADD_LIBRARY( be_plugin_qwt SHARED ${plugin_SRCS} )
				TARGET_LINK_LIBRARIES( be_plugin_qwt kernel ${QWT_LIBRARY} Qt6::Widgets )
				
				
			ENDIF (NOT QWT_FIND_QUIETLY)
		ELSE (QWT_FOUND)
			# IF (QWT_FIND_REQUIRED)
			# 	MESSAGE(FATAL_ERROR "Could not find QWT")
			# ENDIF (QWT_FIND_REQUIRED)
		ENDIF (QWT_FOUND)


	
	

	
	
	
	
	
	
	
	
	

# 	SET(CMAKE_AUTOMOC ON)
# 	
# 	SET(
# 		plugin_SRCS 
# 		plugin.cpp
# 		plugin.h
# 	)
# 
# 	FIND_PACKAGE(Qt5Widgets REQUIRED)
# 
# 	# QWT
# 		FIND_PATH(QWT_INCLUDE_DIR NAMES qwt.h PATHS
# 		/usr/include
# 		/usr/local/include
# 		"$ENV{LIB_DIR}/include" 
# 		"$ENV{INCLUDE}" 
# 		PATH_SUFFIXES qwt-qt4 qwt
# 		)
# 
# 		FIND_LIBRARY(QWT_LIBRARY NAMES qwt qwt5 qwt-qt4 qwt5-qt4 PATHS 
# 		/usr/lib
# 		/usr/local/lib
# 		"$ENV{LIB_DIR}/lib" 
# 		"$ENV{LIB}/lib" 
# 		)
# 
# 		IF (QWT_INCLUDE_DIR AND QWT_LIBRARY)
# 		SET(QWT_FOUND TRUE)
# 		ENDIF (QWT_INCLUDE_DIR AND QWT_LIBRARY)
# 
# 		IF (QWT_FOUND)
# 		IF (NOT QWT_FIND_QUIETLY)
# 			MESSAGE("QWT FOUND \n ${QWT_LIBRARY}")
# 		ENDIF (NOT QWT_FIND_QUIETLY)
# 		ELSE (QWT_FOUND)
# 		IF (QWT_FIND_REQUIRED)
# 			MESSAGE(FATAL_ERROR "Could not find QWT")
# 		ENDIF (QWT_FIND_REQUIRED)
# 		ENDIF (QWT_FOUND)
# 
# 
# # 	FIND_PACKAGE(Qt5OpenGL REQUIRED)
# 	LINK_LIBRARIES ( ${Qt5Widgets_LIBRARIES} ${QWT_LIBRARY} )
# 
# 	ADD_LIBRARY( be_plugin_qwt SHARED ${plugin_SRCS} )
# 	TARGET_LINK_LIBRARIES( be_plugin_qwt kernel )
# 
# 	
# 	
	
