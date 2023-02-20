
	SET(
		plugin_SRCS 
		plugin.cpp
		plugin.h
		brain_system.cpp
		brain_system.h
	)

	ADD_LIBRARY( be_plugin_brainz SHARED ${plugin_SRCS} )
	TARGET_LINK_LIBRARIES( be_plugin_brainz be_base_entity_types )


