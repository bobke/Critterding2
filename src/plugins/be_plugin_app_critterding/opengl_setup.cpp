#include "opengl_setup.h"
#include <GL/glew.h>
#include <iostream>

	OpenGL_Setup::OpenGL_Setup()
	{
		setProcessing();
		glewInit();
	}
	
	void OpenGL_Setup::construct()
	{
		m_glShadeModel_GL_SMOOTH = addChild( "glShadeModel_GL_SMOOTH", "bool" );
		m_glEnable_GL_MULTISAMPLE = addChild( "GL_MULTISAMPLE", "bool" );
		m_glEnable_GL_LINE_SMOOTH = addChild( "GL_LINE_SMOOTH", "bool" );
		m_glEnable_GL_POLYGON_SMOOTH = addChild( "GL_POLYGON_SMOOTH", "bool" );
		m_glEnable_GL_CULL_FACE_BACK = addChild( "GL_CULL_FACE_BACK", "bool" );
		m_glEnable_GL_CULL_FACE_BACK->set( true );
		m_glEnable_GL_CULL_FACE_FRONT = addChild( "GL_CULL_FACE_FRONT", "bool" );
		m_glEnable_GL_DEPTH_TEST = addChild( "GL_DEPTH_TEST", "bool" );
		m_glEnable_GL_DEPTH_TEST->set( true );
		m_glEnable_GL_BLEND = addChild( "GL_BLEND", "bool" );
		m_glEnable_GL_ALPHA_TEST = addChild( "GL_ALPHA_TEST", "bool" );
		m_glEnable_GL_NORMALIZE = addChild( "GL_NORMALIZE", "bool" );
		m_glEnable_GL_NORMALIZE->set( true );
	}
	

	void OpenGL_Setup::process()
	{
		//Hint for everything to be nicest
		glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
		glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);
		glHint(GL_FOG_HINT, GL_FASTEST);
		glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT, GL_FASTEST);
		glHint(GL_GENERATE_MIPMAP_HINT, GL_FASTEST);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
		glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
		glHint(GL_TEXTURE_COMPRESSION_HINT, GL_FASTEST);

		// GL_SMOOTH
			if ( m_glShadeModel_GL_SMOOTH->get_bool() )
			{
				glShadeModel(GL_SMOOTH);
			}
			else
			{
				glShadeModel(GL_FLAT);
			}
		
		// GL_MULTISAMPLE
			if ( m_glEnable_GL_MULTISAMPLE->get_bool() )
			{
				glEnable(GL_MULTISAMPLE);
			}
			else
			{
				glDisable(GL_MULTISAMPLE);
			}

		// GL_LINE_SMOOTH
			if ( m_glEnable_GL_LINE_SMOOTH->get_bool() )
			{
				glEnable(GL_LINE_SMOOTH);
				glHint(GL_LINE_SMOOTH_HINT, GL_NICEST );
			}
			else
			{
				glDisable(GL_LINE_SMOOTH);
				
			}

		// GL_POLYGON_SMOOTH
			if ( m_glEnable_GL_POLYGON_SMOOTH->get_bool() )
			{
				glEnable(GL_POLYGON_SMOOTH);
				glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST );
			}
			else
			{
				glDisable(GL_POLYGON_SMOOTH);
			}

		// GL_CULL_FACE 
			if ( m_glEnable_GL_CULL_FACE_BACK->get_bool() )
			{
				glEnable(GL_CULL_FACE);
				glCullFace(GL_BACK);
			}
			else if ( m_glEnable_GL_CULL_FACE_FRONT->get_bool() )
			{
				glEnable(GL_CULL_FACE);
				glCullFace(GL_FRONT);
			}
			else
			{
				glDisable(GL_CULL_FACE);
			}

		// GL_DEPTH_TEST
			if ( m_glEnable_GL_DEPTH_TEST->get_bool() )
			{
				glEnable(GL_DEPTH_TEST);
			}
			else
			{
				glDisable(GL_DEPTH_TEST);
			}

		// GL_BLEND
			if ( m_glEnable_GL_BLEND->get_bool() )
			{
				glEnable (GL_BLEND); 
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}
			else
			{
				glDisable(GL_BLEND); 
			}

		// GL_ALPHA_TEST
			if ( m_glEnable_GL_ALPHA_TEST->get_bool() )
			{
				glEnable ( GL_ALPHA_TEST );
				glAlphaFunc ( GL_GREATER, 0.5f ) ;
			}
			else
			{
				glDisable( GL_ALPHA_TEST );
			}

		// GL_NORMALIZE
			if ( m_glEnable_GL_NORMALIZE->get_bool() )
			{
				glEnable(GL_NORMALIZE);
			}
			else
			{
				glDisable(GL_NORMALIZE);
			}
		
		// // FIXME MOVE TO CAMERA
		// 	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  // 
		// 	// glViewport( 0, 0, m_width->get_int(), m_height->get_int() );
		// 	glViewport( 0, 0, 1224, 768 );
				
			// glUseProgram(0);
	}
