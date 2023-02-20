
	SET(
		plugin_SRCS 
		plugin.cpp
		plugin.h
		be_config_libraries.h
		be_config_libraries.cpp
		admin_lookup_buffer.h
		admin_lookup_buffer.cpp
	)

	ADD_LIBRARY( be_plugin_app_admin_window SHARED ${plugin_SRCS} )
	TARGET_LINK_LIBRARIES( be_plugin_app_admin_window be_base_entity_types )


