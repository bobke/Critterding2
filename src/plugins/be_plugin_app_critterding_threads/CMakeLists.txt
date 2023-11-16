
	include_directories( ../be_plugin_bullet/bullet3/src )

	SET(
		plugin_SRCS 
		plugin.cpp
		plugin.h
		control_panel.cpp
		control_panel.h
	)

	ADD_LIBRARY( be_plugin_app_critterding_threads SHARED ${plugin_SRCS} )
	TARGET_LINK_LIBRARIES( be_plugin_app_critterding_threads be_base_entity_types be_plugin_opengl be_plugin_bullet be_plugin_app_critterding )


