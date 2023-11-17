
	SET(
		plugin_SRCS 
		plugin.cpp
		plugin.h
	)

	#LINK_LIBRARIES ( ${Qt5Widgets_LIBRARIES} ${Qt5OpenGL_LIBRARIES} )

	ADD_LIBRARY( be_plugin_thread SHARED ${plugin_SRCS} )
	TARGET_LINK_LIBRARIES( be_plugin_thread be_base_entity_types )

