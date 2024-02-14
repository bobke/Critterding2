
	SET(
		plugin_SRCS 
		plugin.cpp
		plugin.h
	)

	FIND_PACKAGE ( SDL )
	IF (SDL_FOUND)
		MESSAGE("SDL FOUND")
		SET(bengine_LIBS ${bengine_LIBS} ${SDL_LIBRARY}) 
		Include_Directories (${SDL_INCLUDE_DIR})
		ADD_LIBRARY( be_plugin_sdl SHARED ${plugin_SRCS} )
		TARGET_LINK_LIBRARIES( be_plugin_sdl be_base_entity_types ${SDL_LIBRARY} )
		
	ELSE (SDL_FOUND)
		MESSAGE("SDL NOT FOUND")
	ENDIF (SDL_FOUND)
	


