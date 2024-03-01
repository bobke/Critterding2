#include "plugin.h"
#include "key_names.h"
#include "callbacks.h"
#include "swapbuffers.h"

	BGLWindow::BGLWindow()
	: BEntity()
	, m_isFullscreen(false)
	, m_isVSync(false)
	, m_windowed_width(0)
	, m_windowed_height(0)
	, m_windowed_pos_x(0)
	, m_windowed_pos_y(0)
	{
		setProcessing();

		glfwSetErrorCallback( error_callback );

		if (!glfwInit())
		{
			std::cout << "WINDOW error: FLGW Video initialization failed" << std::endl;
			exit(1);
		}
	} 

	void BGLWindow::construct()
	{
		addChild( "bindings", new BEntity() );
		m_title = addChild("title", new BEntity_string_property());
		m_fullscreen = addChild("fullscreen", new BEntity_bool_property());
		m_vsync = addChild("vsync", new BEntity_bool_property());
		m_width = addChild("width", new BEntity_int_propertyNew());
		m_height = addChild("height", new BEntity_int_propertyNew());
		m_position_x = addChild("position_x", new BEntity_int_propertyNew());
		m_position_y = addChild("position_y", new BEntity_int_propertyNew());
		m_mouse_x = addChild("mouse_x", new BEntity_int());
		m_mouse_y = addChild("mouse_y", new BEntity_int());

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		
	
		m_window = glfwCreateWindow(1224, 768, "", NULL, NULL);
		m_title->set( "FGL Window" );

		if (!m_window)
		{
			std::cout << "WINDOW error: FLGW Create Window failed" << std::endl;
			glfwTerminate();
			exit(1);
		}

		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, this);

		m_primary_monitor = glfwGetPrimaryMonitor();
		
		glfwSwapInterval(0);
		// glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		
		// setup callbacks
			glfwSetWindowPosCallback( m_window, windowposition_callback );
			glfwSetWindowSizeCallback( m_window, window_size_callback );
			glfwSetWindowCloseCallback( m_window, window_close_callback );
			glfwSetKeyCallback( m_window, key_callback );
			glfwSetCursorPosCallback( m_window, mousepos_callback );
			glfwSetMouseButtonCallback( m_window, mouse_button_callback );


		// set window dimensions once
			int width, height;
			glfwGetFramebufferSize( m_window, &width, &height );
			m_width->set( width );
			m_height->set( height );
	}

	void BGLWindow::process()
	{
		// glfwMakeContextCurrent(m_window);
		// glfwSetWindowUserPointer(m_window, this);

		glfwPollEvents();
	}

	BGLWindow::~BGLWindow()
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	// PROPERTIES
		bool BGLWindow::set( const Bstring& id, BEntity* value )
		{
			// std::cout << "BQWindow::set " << id << " " << value->id() << std::endl;
			if ( id == "on_close_destroy_entity" )
			{
				compareAndSetValue( m_destroy_entity_on_close, value );
			}
			else
			{
				return false;
			}
			return true;
		}

		BEntity* BGLWindow::get_reference( const Bstring& id )
		{
			if ( id == "on_close_destroy_entity" )
			{
				return m_destroy_entity_on_close;
			}

			return 0;
		}

		bool BGLWindow::set( const Bstring& id, const Bbool& value )
		{
			if ( id == "fullscreen" )
			{
				if ( compareAndSetValue( m_isFullscreen, value ) )
				{
					if ( value )
					{
						m_windowed_width = m_width->get_int();
						m_windowed_height = m_height->get_int();
						m_windowed_pos_x = m_position_x->get_int();
						m_windowed_pos_y = m_position_y->get_int();

						const GLFWvidmode* mode = glfwGetVideoMode( m_primary_monitor );
						glfwSetWindowMonitor( m_window, m_primary_monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
					}
					else
					{
						const GLFWvidmode* mode = glfwGetVideoMode( m_primary_monitor );
						glfwSetWindowMonitor( m_window, NULL, m_windowed_pos_x, m_windowed_pos_y, m_windowed_width, m_windowed_height, GLFW_DONT_CARE);
					}

					m_fullscreen->onUpdate();
				}
			}
			else if ( id == "vsync" )
			{
				if ( compareAndSetValue( m_isVSync, value ) )
				{
					if ( value )
					{
						glfwSwapInterval(1);
					}
					else
					{
						glfwSwapInterval(0);
					}

					m_vsync->onUpdate();
				}
			}
			else
			{
				return false;
			}
			return true;
		}

		Bbool BGLWindow::get_bool( const Bstring& id )
		{
			if ( id == "fullscreen" )
			{
				return m_isFullscreen;
			}
			else if ( id == "vsync" )
			{
				return m_isVSync;
			}

			return false;
		}
		
		bool BGLWindow::set( const Bstring& id, const char* value )
		{
			if ( id == "title" )
			{
				// QString s(value);
				// if ( s != windowTitle() )
				if ( m_stored_title != value )
				{
					m_stored_title = value;
					glfwSetWindowTitle( m_window, value );
					m_title->onUpdate();
				}
			}
			else
			{
				return false;
			}
			return true;
		}
		
		const char* BGLWindow::get_string( const Bstring& id )
		{
			if ( id == "title" )
			{
				return m_stored_title.c_str();
			}

			return "";
		}

		bool BGLWindow::set( const Bstring& id, const Bint& value )
		{
			if ( id == "width" )
			{
				// fetch WIDTH through getWindowSize first because fullscreen toggle glitch
				int width, height;
				glfwGetWindowSize( m_window, &width, &height );
				glfwSetWindowSize( m_window, value, height );
			}
			else if ( id == "height" )
			{
				glfwSetWindowSize( m_window, m_width->get_int(), value );
			}
			else if ( id == "position_x" )
			{
				// fetch position X through getWindowPos first because fullscreen toggle glitch
				int pos_x, pos_y;
				glfwGetWindowPos( m_window, &pos_x, &pos_y );
				glfwSetWindowPos( m_window, value, pos_y );
			}
			else if ( id == "position_y" )
			{
				glfwSetWindowPos( m_window, m_position_x->get_int(), value );
			}
			else
			{
				return false;
			}
			return true;
		}


// ---- FACTORIES
	enum CLASS
	{
		  PLUGIN_INFO
		// , SCENE
		, GLWINDOW
		, GLSWAPBUFFERS
	};

	extern "C" BEntity* create( BEntity* parent, const Buint type )
	{
		// PLUGIN DESCRIPTION ENTITY
			if ( type == PLUGIN_INFO )
			{
				BClassesHelper i;
					// i.addClass( parent, CLASS::SCENE, "Scene" );
					i.addClass( parent, CLASS::GLWINDOW, "GLWindow" );
					i.addClass( parent, CLASS::GLSWAPBUFFERS, "GLSwapBuffers" );
				return 0;
			}

		// ENTITIES
			else
			{
				BEntity* i(0);
				
				/*if ( type == CLASS::SCENE )
					i = new Scene();
				else */if ( type == CLASS::GLWINDOW )
					i = new BGLWindow();
				else if ( type == CLASS::GLSWAPBUFFERS )
					i = new GLSwapBuffers();


				return i;
			}
	}

	extern "C" void destroy( BEntity* p )
	{
		delete p;
	}

