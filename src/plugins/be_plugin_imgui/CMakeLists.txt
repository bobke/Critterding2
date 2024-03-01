
	SET(
		plugin_SRCS 
		plugin.cpp
		plugin.h
		lineedit.cpp
		lineedit.h
		pushbutton.cpp
		pushbutton.h
		groupbox.cpp
		groupbox.h
		checkbox.cpp
		checkbox.h
	)
	
	set(IMGUI_SOURCES
		imgui/imgui.cpp
		imgui/imgui_demo.cpp
		imgui/imgui_draw.cpp
		imgui/imgui_widgets.cpp
		imgui/imgui_tables.cpp
		imgui/backends/imgui_impl_opengl3.cpp
		imgui/backends/imgui_impl_glfw
	)	

	INCLUDE_DIRECTORIES( imgui PRIVATE "imgui" )
	ADD_LIBRARY( imgui STATIC ${IMGUI_SOURCES} )
	ADD_LIBRARY( be_plugin_imgui SHARED ${plugin_SRCS} )
	TARGET_LINK_LIBRARIES( be_plugin_imgui be_base_entity_types imgui be_plugin_glfw )
