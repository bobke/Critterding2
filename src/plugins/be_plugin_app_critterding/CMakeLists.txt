
	SET(
		plugin_SRCS 
		plugin.cpp
		plugin.h
		commands.cpp
		commands.h
		food_system.cpp
		food_system.h
		body_system.cpp
		body_system.h
		species_system.cpp
		species_system.h
		critter_system.cpp
		critter_system.h
		control_panel.cpp
		control_panel.h
	)

	ADD_LIBRARY( be_plugin_app_critterding SHARED ${plugin_SRCS} )
	TARGET_LINK_LIBRARIES( be_plugin_app_critterding be_base_entity_types )


