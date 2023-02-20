
	ADD_SUBDIRECTORY(tinyxml)

	SET(kernel_STAT_SRCS
		be_lib_handler.h
		be_lib_handler.cpp
		be_timer.h
		be_timer.cpp
		be_entity_id_handler.h
		be_entity_id_handler.cpp
		be_entity_io_handler.h
		be_entity_io_handler.cpp
		be_entity_interface.h
		be_entity_interface.cpp
		be_entity_core_types.h
		be_entity_core_types.cpp
		be_entity_children_handler.h
		be_entity_children_handler.cpp
		be_entity_processor.h
		be_entity_processor.cpp
		be_entity_ops_copy.h
		be_entity_ops_copy.cpp
		be_entity_top.h
		be_entity_top.cpp
		be_plugin_interface.h
		be_plugin_interface.cpp
		be_types.h
		be_types.cpp
		# be_worker_pool.h
		# be_worker_pool.cpp
		#be_log.h
		#be_log.cpp
	)

	ADD_LIBRARY(kernel STATIC ${kernel_STAT_SRCS} )
	TARGET_LINK_LIBRARIES( kernel tinyxml )

	SET(base_entity_types_SRCS 
		be_plugin_base_entity_types.h
		be_plugin_base_entity_types.cpp
	)

	ADD_LIBRARY( be_base_entity_types SHARED ${base_entity_types_SRCS} )
	TARGET_LINK_LIBRARIES( be_base_entity_types kernel )

