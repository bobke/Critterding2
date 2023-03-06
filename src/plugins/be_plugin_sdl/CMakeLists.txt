
	SET(
		plugin_SRCS 
		plugin.cpp
		plugin.h
	)

	FIND_PACKAGE ( SDL REQUIRED )
	IF (SDL_FOUND)
		MESSAGE("SDL FOUND")
		SET(bengine_LIBS ${bengine_LIBS} ${SDL_LIBRARY}) 
		Include_Directories (${SDL_INCLUDE_DIR})
	ELSE (SDL_FOUND)
		MESSAGE("SDL NOT FOUND")
	ENDIF (SDL_FOUND)
	
	FIND_PACKAGE( GLEW REQUIRED)
	if (GLEW_FOUND)
		include_directories(${GLEW_INCLUDE_DIRS})
		include_directories( /usr/X11R6/include )			# BSD HACK
		# include_directories( /usr/X11R6/include/libdrm )	# BSD HACK
		include_directories( $(shell pkg-config --cflags glew) ) # BSD HACK
	endif()	
	
	
	ADD_LIBRARY( be_plugin_sdl SHARED ${plugin_SRCS} )
	TARGET_LINK_LIBRARIES( be_plugin_sdl be_base_entity_types ${SDL_LIBRARY} ${GLEW_LIBRARIES} )


