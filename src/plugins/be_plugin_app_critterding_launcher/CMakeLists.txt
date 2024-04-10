
	SET(
		plugin_SRCS 
		plugin.cpp
		plugin.h
		commands.cpp
		commands.h
	)

	ADD_LIBRARY( be_plugin_app_critterding_launcher SHARED ${plugin_SRCS} )
	TARGET_LINK_LIBRARIES( be_plugin_app_critterding_launcher kernel )


