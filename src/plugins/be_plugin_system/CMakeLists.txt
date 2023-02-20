
	SET(
		plugin_SRCS 
		plugin.cpp
		plugin.h
		be_entity_rng.cpp
		be_entity_rng.h
	)

	ADD_LIBRARY( be_plugin_system SHARED ${plugin_SRCS} )
	TARGET_LINK_LIBRARIES( be_plugin_system be_base_entity_types )


