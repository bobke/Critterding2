	SET(
		plugin_SRCS 
		plugin.cpp
		plugin.h
		be_parser.cpp
		be_parser.h
	)

	ADD_LIBRARY( be_plugin_app_cmdline SHARED ${plugin_SRCS} )
	TARGET_LINK_LIBRARIES( be_plugin_app_cmdline be_base_entity_types )
