
	SET(
		plugin_SRCS 
		plugin.cpp
		plugin.h
	)

	ADD_LIBRARY( be_plugin_sdl SHARED ${plugin_SRCS} )
	TARGET_LINK_LIBRARIES( be_plugin_sdl be_base_entity_types -lSDL -lGLEW )


