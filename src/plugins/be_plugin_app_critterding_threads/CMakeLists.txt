
	include_directories( ../be_plugin_bullet/bullet3/src )

	SET(
		plugin_SRCS 
		plugin.cpp
		plugin.h
		control_panel.cpp
		control_panel.h
		critter_thread_mesher.cpp
		critter_thread_mesher.h
	)

	ADD_LIBRARY( be_plugin_app_critterding_threads SHARED ${plugin_SRCS} )
	TARGET_LINK_LIBRARIES( be_plugin_app_critterding_threads be_plugin_app_critterding )


