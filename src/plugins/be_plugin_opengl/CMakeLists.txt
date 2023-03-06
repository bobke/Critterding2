
	FIND_PACKAGE( OpenGL REQUIRED)
	FIND_PACKAGE( GLEW REQUIRED)
	if (GLEW_FOUND)
		include_directories(${GLEW_INCLUDE_DIRS})
		include_directories( $(shell pkg-config --cflags glew) ) # BSD HACK
	endif()	
	

	
	
	SET(Boost_USE_MULTITHREAD ON) #set a flag
# 	FIND_PACKAGE(Boost)
	FIND_PACKAGE ( Boost COMPONENTS filesystem system iostreams thread REQUIRED)
	if(Boost_FOUND)
		include_directories(${Boost_INCLUDE_DIRS}) 
		# MESSAGE(${Boost_LIBRARIES})
	endif()	
	
	#set(CMAKE_AUTOMOC ON)
	find_package(Qt6 COMPONENTS Widgets Gui OpenGLWidgets REQUIRED)

	INCLUDE_DIRECTORIES(".")
	ADD_SUBDIRECTORY(LinearMath)

	#INCLUDE_DIRECTORIES(LinearMath)
	
	SET(
		plugin_SRCS 
		plugin.cpp
		plugin.h
		be_model_system.cpp
		be_model_system.h
		be_texture_store.cpp
		be_texture_store.h
		#be_texture.cpp
		#be_texture.h
		be_geometry.cpp
		be_geometry.h
		be_texture_2d_resource.h
		be_graphics_model_resource.cpp
		be_graphics_model_resource.h
		be_obj_loader.cpp
		be_obj_loader.h
		be_parser.cpp
		be_parser.h
		be_types_extra.cpp
		be_types_extra.h
		
		#threadpool/future.hpp
		#threadpool/pool_adaptors.hpp
		#threadpool/pool.hpp
		
		tinyxml/tinyxml.cpp
		tinyxml/tinyxml.h
		tinyxml/tinystr.cpp
		tinyxml/tinystr.h
		tinyxml/tinyxmlparser.cpp
		tinyxml/tinyxmlerror.cpp
		
		graphics/be_buffer.cpp
		graphics/be_buffer.h
		#graphics/be_camera.cpp
		#graphics/be_camera.h
		#graphics/be_color.cpp
		#graphics/be_color.h
		#graphics/be_framebuffer.cpp
		#graphics/be_framebuffer.h
		graphics/be_graphics_kernel.cpp
		graphics/be_graphics_kernel.h
		graphics/be_graphics_system.cpp
		graphics/be_graphics_system.h
		#graphics/be_mesh.cpp
		#graphics/be_mesh.h
		graphics/be_shader.cpp
		graphics/be_shader.h
		graphics/be_texture.cpp
		graphics/be_texture.h
		graphics/be_vertex_array.cpp
		graphics/be_vertex_array.h
		#graphics/sc_graphics.cpp
		#graphics/sc_graphics.h
		
		filesystem/be_dir.cpp
		filesystem/be_dir.h
		filesystem/be_file.cpp
		filesystem/be_file.h
		filesystem/be_filesystem.cpp
		filesystem/be_filesystem.h
		filesystem/be_rootpaths.cpp
		filesystem/be_rootpaths.h

		be_entity_graphics_model_system.cpp
		be_entity_graphics_model_system.h
		be_entity_transform.cpp
		be_entity_transform.h
		be_entity_camera.cpp
		be_entity_camera.h
		be_entity_graphics_model.cpp
		be_entity_graphics_model.h
		be_entity_light.cpp
		be_entity_light.h
		
		be_worker_pool.h
		be_worker_pool.cpp
	)

	ADD_LIBRARY( be_plugin_opengl SHARED ${plugin_SRCS} )
	TARGET_LINK_LIBRARIES( be_plugin_opengl be_base_entity_types ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} LinearMath  ${Boost_LIBRARIES} Qt6::Widgets Qt6::Gui Qt6::OpenGLWidgets )
