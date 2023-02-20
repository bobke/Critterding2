# FIXME BREAKS AFTER CMAKE

	SET(BUILD_SHARED_LIBS OFF)
	SET(BUILD_CPU_DEMOS OFF)
	SET(BUILD_DEMOS OFF)
	SET(BUILD_EXTRAS OFF)
	SET(BUILD_MINICL_OPENCL_DEMOS OFF)
	SET(BUILD_MULTITHREADING OFF)
	SET(USE_GLUT OFF)
	SET(USE_DX11 OFF)
	SET(BUILD_BULLET2_DEMOS OFF)
	SET(BUILD_UNIT_TESTS OFF)
	SET(BUILD_BULLET3 OFF)
	SET(INSTALL_LIBS OFF)    # THIS DOESNT WORK THE FIRST TIME AFTER REMOVING CMAKECACHE, ALTERED BULLETS CMAKELISTS.TXT:783
# 	SET(INSTALL_EXTRA_LIBS OFF)

	include_directories( bullet3/src )
	
	
	
	ADD_SUBDIRECTORY(bullet3)

	
	INCLUDE_DIRECTORIES(".")
	
	# FIXME REMOVE
	set(CMAKE_AUTOMOC ON)
	find_package(Qt6 COMPONENTS Widgets Gui OpenGLWidgets REQUIRED)

	SET(Boost_USE_MULTITHREAD ON) #set a flag
# 	FIND_PACKAGE(Boost)
	FIND_PACKAGE ( Boost COMPONENTS filesystem system iostreams thread REQUIRED)

	
	FIND_PACKAGE( OpenGL REQUIRED)
	FIND_PACKAGE( GLEW REQUIRED)
	
	
	SET(
		plugin_SRCS 

		plugin.cpp
		plugin.h
		
		be_entity_physicsworld.cpp
		be_entity_physicsworld.h
		be_entity_physics_entity.cpp
		be_entity_physics_entity.h
		physicsmodel_rigid.cpp
		physicsmodel_rigid.h
		physicsmodel_rigid_box.cpp
		physicsmodel_rigid_box.h
		physicsmodel_rigid_trianglemesh.cpp
		physicsmodel_rigid_trianglemesh.h
		physicsmodel_rigid_convexmesh.cpp
		physicsmodel_rigid_convexmesh.h
		be_entity_constraint_hinge.cpp
		be_entity_constraint_hinge.h

		be_types_extra.cpp
		be_types_extra.h
		be_geometry.cpp
		be_geometry.h
		be_obj_loader.h
		be_obj_loader.cpp
		# be_model_system.h
		# be_model_system.cpp
		# be_texture_store.h
		# be_texture_store.cpp
		be_parser.h
		be_parser.cpp

		filesystem/be_filesystem.h
		filesystem/be_filesystem.cpp
		filesystem/be_rootpaths.h
		filesystem/be_rootpaths.cpp
		filesystem/be_file.h
		filesystem/be_file.cpp

		graphics/be_texture.h
		graphics/be_texture.cpp
		graphics/be_shader.h
		graphics/be_shader.cpp
		graphics/be_buffer.h
		graphics/be_buffer.cpp
		graphics/be_graphics_kernel.h
		graphics/be_graphics_kernel.cpp
		graphics/be_graphics_system.h
		graphics/be_graphics_system.cpp
		graphics/be_vertex_array.h
		graphics/be_vertex_array.cpp

		tinyxml/tinyxml.cpp
		tinyxml/tinyxml.h
		tinyxml/tinystr.cpp
		tinyxml/tinystr.h
		tinyxml/tinyxmlparser.cpp
		tinyxml/tinyxmlerror.cpp
	)

	ADD_LIBRARY( be_plugin_bullet SHARED ${plugin_SRCS} )
	TARGET_LINK_LIBRARIES( be_plugin_bullet be_base_entity_types Bullet3Common BulletSoftBody BulletDynamics BulletCollision LinearMath  ${GLEW_LIBRARIES} Qt6::Widgets Qt6::Gui Qt6::OpenGLWidgets  -lboost_system -lboost_thread -lboost_filesystem -lboost_iostreams)


