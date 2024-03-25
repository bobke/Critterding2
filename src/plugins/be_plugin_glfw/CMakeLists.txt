
	SET(
		plugin_SRCS 
		plugin.cpp
		plugin.h
		swapbuffers.cpp
		swapbuffers.h
	)

	# find_package(glfw3 3.3 REQUIRED)	
	
	FIND_PACKAGE ( glfw3 3.3 REQUIRED )
	# IF (EXISTS ${CONFIG_FILES})
		MESSAGE("GLFW FOUND")
		# SET(bengine_LIBS ${bengine_LIBS} ${GLFW_LIBRARY}) 
		Include_Directories (${GLFW_INCLUDE_DIR})
		
		ADD_LIBRARY( be_plugin_glfw SHARED ${plugin_SRCS} )
		# TARGET_LINK_LIBRARIES( be_plugin_glfw be_base_entity_types glfw )
		TARGET_LINK_LIBRARIES( be_plugin_glfw kernel glfw )

		# ELSE ()
		# MESSAGE("GLFW NOT FOUND")
	# ENDIF ()




