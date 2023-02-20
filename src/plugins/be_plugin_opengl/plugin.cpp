#include "plugin.h"
#include "be_entity_graphics_model_system.h"
#include "be_entity_graphics_model.h"
#include "be_entity_camera.h"
#include "be_entity_light.h"
// #include "graphics/be_graphics_system.h"
// #include "kernel/be_plugin_interface.h"

// ---- FACTORIES
	enum CLASS
	{
		  PLUGIN_INFO
		, SCENE
		, GLCLEARCOLOR
		, GLCLEARCOLORBUFFER
		, GLQUADS
		, GLEND
		, GLCOLOR3F
		, GLCOLOR4F
		, GLVERTEX2F
		, GRAPHICSMODELSYSTEM
		, GRAPHICSMODEL
		, CAMERA
		, TRANSFORM
		, GLLIGHT
		
	};

	extern "C" BEntity* create( BEntity* parent, const Buint type )
	{
		// PLUGIN DESCRIPTION ENTITY
			if ( type == PLUGIN_INFO )
			{
				BClassesHelper i;
					i.addClass( parent, CLASS::SCENE, "Scene" );
					i.addClass( parent, CLASS::GLCLEARCOLOR, "glClearColor" );
					i.addClass( parent, CLASS::GLCLEARCOLORBUFFER, "glClearColorBuffer" );
					i.addClass( parent, CLASS::GLQUADS, "glQuads" );
					i.addClass( parent, CLASS::GLEND, "glEnd" );
					i.addClass( parent, CLASS::GLCOLOR3F, "glColor3f" );
					i.addClass( parent, CLASS::GLCOLOR4F, "glColor4f" );
					i.addClass( parent, CLASS::GLVERTEX2F, "glVertex2f" );
					i.addClass( parent, CLASS::GRAPHICSMODELSYSTEM, "GraphicsModelSystem" );
					i.addClass( parent, CLASS::GRAPHICSMODEL, "GraphicsModel" );
					i.addClass( parent, CLASS::CAMERA, "Camera" );
					i.addClass( parent, CLASS::TRANSFORM, "Transform" );
					i.addClass( parent, CLASS::GLLIGHT, "GLLight" );
				return 0;
				
				
// 				BEntityClasses* i = new BEntityClasses();
// 					i->addClass( CLASS::CLEARCOLOR, "BglClearColor" );
// 					i->addClass( CLASS::CLEARCOLORBUFFER, "BglClearColorBuffer" );
// 				return i;
			}

		// ENTITIES
			else
			{
				BEntity* i(0);
				
				if ( type == CLASS::SCENE )
					i = new Scene();
				else if ( type == CLASS::GLCLEARCOLOR )
					i = new BglClearColor();
				else if ( type == CLASS::GLCLEARCOLORBUFFER )
					i = new BglClearColorBuffer();
				else if ( type == CLASS::GLQUADS )
					i = new BglQuads();
				else if ( type == CLASS::GLEND )
					i = new BglEnd();
				else if ( type == CLASS::GLCOLOR3F )
					i = new BglColor3f();
				else if ( type == CLASS::GLCOLOR4F )
					i = new BglColor4f();
				else if ( type == CLASS::GLVERTEX2F )
					i = new BglVertex2f();
				else if ( type == CLASS::GRAPHICSMODELSYSTEM )
					i = new BGraphicsModelSystem();
				else if ( type == CLASS::GRAPHICSMODEL )
					i = new BGraphicsModel();
				else if ( type == CLASS::CAMERA )
// 					i = new BEntityCamera();
					i = new BCamera();
				else if ( type == CLASS::TRANSFORM )
					i = new glTransform();
				else if ( type == CLASS::GLLIGHT )
					i = new BGLLight();
				
				


				return i;
			}
	}

	extern "C" void destroy(BEntity* p)
	{
		delete p;
	}
		
