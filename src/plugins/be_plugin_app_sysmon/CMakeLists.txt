
	SET(
		plugin_SRCS 
		plugin.cpp
		plugin.h
		rasterwindow.cpp
		rasterwindow.h
	)

	ADD_LIBRARY( be_plugin_app_sysmon SHARED ${plugin_SRCS} )
	#TARGET_LINK_LIBRARIES( be_plugin_app_sysmon kernel be_base_entity_types )
	TARGET_LINK_LIBRARIES( be_plugin_app_sysmon be_base_entity_types )


