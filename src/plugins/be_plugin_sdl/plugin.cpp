#include "plugin.h"
#include "kernel/be_entity_core_types.h"
#include <iostream>
#include <sstream>

	void Scene::construct()
	{
		std::cout << "Scene::construct()" << std::endl;


		addChild( "bindings", new BEntity() );
	}


	
	BGLWindow::BGLWindow() :
// 	m_eventsystem(eventsystem),
	w_bpp(0),
	// w_width(0),
	// w_height(0),
	n_width(0),
	n_height(0),
	fs(0),
	vidInfo(0),
	m_surface(0),
	vidFlags(0),
	hwaccel(0),
	settingsfs(0),
	m_resized(false),
	m_resizable(false)
	, m_destroy_entity_on_close(this)
	
// 	m_logDebug("WINDOW")
	{
		// register an exit event from glwindow
// 		m_eventsystem->registerEvent( DOWN, "glwindow-quit", boost::shared_ptr<Event>(new Event(BeCommand("quit"), EVENT_NOREPEAT, 0)) );	
		setProcessing();
		
	} 

	void BGLWindow::construct()
	{
		addChild( "bindings", new BEntity() );
		m_width = addChild("width", new BEntity_int());
		m_height = addChild("height", new BEntity_int());
		m_mouse_x = addChild("mouse_x", new BEntity_int());
		m_mouse_y = addChild("mouse_y", new BEntity_int());

		create("SDL WINDOW", 1224, 768);
	}
	
	void BGLWindow::create(const std::string& title, const unsigned int t_width, const unsigned int t_height)
	{
		if( SDL_Init(SDL_INIT_VIDEO) < 0 )
		{
			std::cout << "WINDOW error: SDL Video initialization failed with error '" << SDL_GetError() << std::endl;
// 			m_logDebug << "::WINDOW error: SDL Video initialization failed with error '" << SDL_GetError() << "'\n";
			exit(1);
		}

// 		Settings * const settingsPointer=Settings::Instance();
// 		if(settingsPointer)
		{
// 			Settings& settings=*settingsPointer;
// 			if( settings.getCVar("window_safemode") == 0 )
			{
// 				const int width=settings.getCVar("window_width");
// 				const int height=settings.getCVar("window_height");
// 				const int colorBits=settings.getCVar("window_color_bits");
// 				const int depthBits=settings.getCVar("window_depth_bits");
// 				const int stencilBits=settings.getCVar("window_stencil_bits");
// 				const int multisamples=settings.getCVar("window_multisamples");
// 				const int doublebuffer=settings.getCVar("window_doublebuffer");
// 				const int vsync=settings.getCVar("window_vsync");
// 				const int resizable=settings.getCVar("window_resizable");
// 				const int fullscreen=settings.getCVar("window_fullscreen");
// 				const int hardwareGl=settings.getCVar("window_hardware_gl");

				const int width=t_width;
				const int height=t_height;
				const int colorBits=24;
				const int depthBits=24;
				const int stencilBits=8;
				const int multisamples=1;
				const int doublebuffer=1;
				const int vsync=0;
				const int fullscreen=0;
				const int hardwareGl=1;
				m_resizable = 1;
				
				if(colorBits==32||colorBits==24)
				{
					SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
					SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
					SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
					SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 0);
				}
				else
				{
					SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 4);
					SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 4);
					SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 4);
					SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 4);
				}

				SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, depthBits);
				SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, stencilBits);

				if(multisamples>1)
				{
					SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
					SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, multisamples);
				}
				else
				{
					SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);
					SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0);
				}

				SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, doublebuffer);
				SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, vsync);

				Uint32 videoFlags = SDL_OPENGL;

				if(m_resizable)
				{
					videoFlags |= SDL_RESIZABLE;
				}

				if(fullscreen)
				{
					videoFlags |= SDL_FULLSCREEN;
				}

				SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, hardwareGl);


				vidInfo = SDL_GetVideoInfo();

				if ( !vidInfo )
				{
// 					m_logDebug << "::WINDOW error: Cannot get SDL video information '" <<  SDL_GetError() << "'\n";
					std::cout << "WINDOW error: Cannot get SDL video information '" <<  SDL_GetError() << std::endl;
					exit(1);
				}

				w_bpp = vidInfo->vfmt->BitsPerPixel;

				vidFlags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE;

				hwaccel = false;
				if( vidInfo->hw_available )
				{
					hwaccel = true;
					vidFlags |= SDL_HWSURFACE;
				}
				else
					vidFlags |= SDL_SWSURFACE;

				if( vidInfo->blit_hw != 0 )
					vidFlags |= SDL_HWACCEL;


				//Hacky
				w_bpp = colorBits;
				
				m_width->set( (int)width );
				m_height->set( (int)height );
				// w_width = width;
				// w_height = height;
				n_width = width;
				n_height = height;

// 				Settings::Instance()->winWidth = &w_width;
// 				Settings::Instance()->winHeight = &w_height;

				//Set window title
				setTitle(title);

				//Create window
				m_surface = SDL_SetVideoMode(m_width->get_int(), m_height->get_int(), w_bpp, videoFlags);
				// glewInit();

// 				m_logDebug << "::WINDOW SDL subsystem initialized\n";

				//Enable GL multisampled rendering if required
				int value;
				SDL_GL_GetAttribute(SDL_GL_MULTISAMPLEBUFFERS, &value);
				// if(value)
				// {
				// 	glEnable(GL_MULTISAMPLE);
				// 	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST );
				// 	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST );
				// 	glEnable(GL_LINE_SMOOTH);
				// 	glEnable(GL_POLYGON_SMOOTH);
				// }

// 				//Hack
// 				settings.setCVar("fullscreen", fullscreen);
				settingsfs = 0;
				fs = 0;

				return;

			}
		}
		createSafe(title, t_width, t_height);
	}

	void BGLWindow::createSafe( const std::string& title, const unsigned int width, const unsigned int height )
	{
		vidInfo = SDL_GetVideoInfo();

		if ( !vidInfo )
		{
// 			m_logDebug << "::WINDOW error: Cannot get SDL video information '" <<  SDL_GetError() << "'\n";
			exit(1);
		}

		w_bpp = vidInfo->vfmt->BitsPerPixel;

		vidFlags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE;

		hwaccel = false;
		if( vidInfo->hw_available )
		{
			hwaccel = true;
			vidFlags |= SDL_HWSURFACE;
		}
		else
			vidFlags |= SDL_SWSURFACE;

		if( vidInfo->blit_hw != 0 )
			vidFlags |= SDL_HWACCEL;

		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 4);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 4);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 4);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 4);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		setTitle(title);
		// 	SDL_WM_SetIcon(SDL_LoadBMP("other files/critterding icon.png"), 0);
		// 	SDL_WM_SetIcon(SDL_LoadBMP("other files/cd.bmp"), 0);
		// 	string pixmappath = Settings::Instance()->binarypath;
		// 	pixmappath.append( "../share/critterding/pixmaps/cd.bmp" );
		// 	SDL_WM_SetIcon(SDL_LoadBMP(pixmappath.c_str()), 0);
		// 	SDL_WM_SetIcon(SDL_LoadBMP("/projects/lessons/lesson20/data/image2.bmp"), 0);

		m_width->set( (int)width );
		m_height->set( (int)height );
		// w_width = width;
		// w_height = height;
		n_width = width;
		n_height = height;

// 		Settings::Instance()->winWidth = &w_width;
// 		Settings::Instance()->winHeight = &w_height;
// 		settingsfs = Settings::Instance()->getCVarPtr("fullscreen");
// 		fs = *settingsfs;
		fs = 1;

		if ( fs == 1 )
			m_surface = SDL_SetVideoMode( m_width->get_int(), m_height->get_int(), w_bpp, vidFlags | SDL_FULLSCREEN );
		else
			m_surface = SDL_SetVideoMode( m_width->get_int(), m_height->get_int(), w_bpp, vidFlags | SDL_RESIZABLE );

		// glewInit();

// 		m_logDebug << "::WINDOW SDL subsystem initialized\n";
		// 	std::cerr << "Video " << front.width() << "x" << front.height() << "x" << int(front.getSurface()->format->BitsPerPixel) << "\n";
		// 	std::cerr << "Render Mode: " <<  ((hwaccel) ? "Direct Rendering" : "Software Rendering")   << "\n";
		// 	std::cerr << "Hardware Blit Acceleration: " << ((vidInfo->blit_hw) ? "Yes": "No") << "\n";
	}

	void BGLWindow::setTitle(const std::string& title)
	{
		SDL_WM_SetCaption(title.c_str(),0);

		//On Windows also set the process console title
	#ifdef WIN32
		SetConsoleTitle(title.c_str());
	#endif
	}

	void BGLWindow::resize()
	{
		m_resized = true;

		if ( m_width->get_int() == 0 ) m_width->set( (int)1 );
		if ( m_height->get_int() == 0 ) m_height->set( (int)1 );
		// if ( w_height == 0 ) w_height = 1;
		// if ( w_width == 0 ) w_width = 1;
	// 	std::cout << "resize" << std::endl;
		
		SDL_FreeSurface(m_surface);
		m_surface = SDL_SetVideoMode( m_width->get_int(), m_height->get_int(), w_bpp, vidFlags | SDL_RESIZABLE );
		
	}

	void BGLWindow::toggleFs()
	{
		m_resized = true;

		Uint32 videoFlags=vidFlags;
		if ( fs )
		{
			if ( m_width->get_int() == 0 ) m_width->set( (int)1 );
			if ( m_height->get_int() == 0 ) m_height->set( (int)1 );
			// if ( w_height == 0 ) w_height = 1;
			// if ( w_width == 0 ) w_width = 1;
			n_width = m_width->get_int();
			n_height = m_height->get_int();
// 			w_width = Settings::Instance()->getCVar("fsX");
// 			w_height = Settings::Instance()->getCVar("fsY");
			videoFlags |= SDL_FULLSCREEN;
		}
		else
		{
			m_width->set( (int)n_width );
			m_height->set( (int)n_height );
			// w_width = n_width;
			// w_height = n_height;
			if ( m_resizable )
				videoFlags |= SDL_RESIZABLE;
		}
		SDL_FreeSurface(m_surface);
		m_surface = SDL_SetVideoMode( m_width->get_int(), m_height->get_int(), w_bpp, videoFlags );
		// glewInit();
// 		if ( m_canvas )
// 			m_canvas->resize(w_width, w_height);
	}

	void BGLWindow::process()
	{
		if ( fs != settingsfs )
		{
			fs = settingsfs;
			toggleFs();
		}

		while( SDL_PollEvent(&event) )
		{
			if(event.type == SDL_VIDEORESIZE)
			{
				// w_width = event.resize.w;
				// w_height = event.resize.h;
				m_width->set( (int)event.resize.w );
				m_height->set( (int)event.resize.h );
				resize();
				continue;
			}

			else if(event.type == SDL_QUIT)
			{
				// add remove command to the command buffer
				BEntity* cmdbuffer = topParent()->getChild("_command_buffer");
				if ( cmdbuffer )
				{
					cmdbuffer->addChild("remove", new BEntity_reference() )->set( m_destroy_entity_on_close );
				}
				continue;
			}

			if(event.type == SDL_KEYDOWN)
			{
				auto bindings = getChild( "bindings", 1 );
				if( bindings )
				{
					auto binding = bindings->getChild( SDL_GetKeyName( event.key.keysym.sym ), 1 );
					if ( binding )
					{
						if ( binding->class_id() == std::string("bool") )
						{
							if ( binding->get_bool() == false )
							{
								binding->set( true );
							}
						}
						else if ( binding->class_id() == std::string("trigger") )
						{
							binding->set();
						}
					}

					std::stringstream key_name;
					key_name << "key_down_" << SDL_GetKeyName( event.key.keysym.sym );
					auto binding2 = bindings->getChild( key_name.str().c_str(), 1 );
					if ( binding2 )
					{
						if ( binding2->class_id() == std::string("trigger") )
						{
							binding2->set();
						}
					}
				}

			}

			else if(event.type == SDL_KEYUP)
			{
				auto bindings = getChild( "bindings", 1 );
				if( bindings )
				{
					auto binding = bindings->getChild( SDL_GetKeyName( event.key.keysym.sym ), 1 );
					if ( binding )
					{
						if ( binding->class_id() == std::string("bool") )
						{
							if ( binding->get_bool() == true )
							{
								binding->set( false );
							}
						}
						else if ( binding->class_id() == std::string("trigger") )
						{
							binding->set();
						}
					}
					
					std::stringstream key_name;
					key_name << "key_up_" << SDL_GetKeyName( event.key.keysym.sym );
					auto binding2 = bindings->getChild( key_name.str().c_str(), 1 );
					if ( binding2 )
					{
						if ( binding2->class_id() == std::string("trigger") )
						{
							binding2->set();
						}
					}
					
				}
			}
			
			else if(event.type == SDL_MOUSEMOTION)
			{
				m_mouse_x->set( (int)event.motion.x );
				m_mouse_y->set( (int)event.motion.y );
			}
			
			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				std::stringstream mouseButton_name;
				mouseButton_name << "mousebutton_down_" << (int)event.button.button;
				
				auto bindings = getChild( "bindings", 1 );
				if( bindings )
				{
					auto binding = bindings->getChild( mouseButton_name.str().c_str(), 1 );
					if ( binding )
					{
						if ( binding->class_id() == std::string("bool") )
						{
							if ( binding->get_bool() == false )
							{
								binding->set( true );
							}
						}
						else if ( binding->class_id() == std::string("trigger") )
						{
							binding->set();
						}
					}
				}
			}

			else if (event.type == SDL_MOUSEBUTTONUP)
			{
				std::stringstream mouseButton_name;
				mouseButton_name << "mousebutton_up_" << (int)event.button.button;
				
				auto bindings = getChild( "bindings", 1 );
				if( bindings )
				{
					auto binding = bindings->getChild( mouseButton_name.str().c_str(), 1 );
					if ( binding )
					{
						if ( binding->class_id() == std::string("bool") )
						{
							if ( binding->get_bool() == true )
							{
								binding->set( false );
							}
						}
						else if ( binding->class_id() == std::string("trigger") )
						{
							binding->set();
						}
					}
				}
			}

			// else if (event.type == SDL_JOYBUTTONDOWN)
			// {
			// }
			// else if (event.type == SDL_JOYBUTTONUP)
			// {
			// }
			// else if(event.type == SDL_JOYAXISMOTION)
			// {
			// }
		}

	}

	// PROPERTIES
		bool BGLWindow::set( const Bstring& id, BEntity* value )
		{
// 			std::cout << "BQWindow::set " << id << " " << value->id() << std::endl;
			if ( id == "on_close_destroy_entity" )
			{
				if ( compareAndSetValue( m_destroy_entity_on_close, value ) )
				{
// 					std::cout << " is now " << m_destroy_entity_on_close->id() << std::endl;
					return true;
				}
			}

			return false;
		}

		BEntity* BGLWindow::get_reference( const Bstring& id )
		{
			if ( id == "on_close_destroy_entity" )
			{
				return m_destroy_entity_on_close;
			}

			return 0;
		}		
		
	
	
	BGLWindow::~BGLWindow()
	{
		SDL_FreeSurface( m_surface );
		SDL_Quit();
	}	


// ---- FACTORIES
	enum CLASS
	{
		  PLUGIN_INFO
		, SCENE
		, SDLWINDOW
		, SDL_SWAPBUFFERS
	};

	extern "C" BEntity* create( BEntity* parent, const Buint type )
	{
// 		std::cout << "LIB CREATE:: type: " << type  << std::endl;
		// PLUGIN DESCRIPTION ENTITY
			if ( type == PLUGIN_INFO )
			{
				BClassesHelper i;
					i.addClass( parent, CLASS::SCENE, "Scene" );
					i.addClass( parent, CLASS::SDLWINDOW, "SDLWindow" );
					i.addClass( parent, CLASS::SDL_SWAPBUFFERS, "SDLSwapBuffers" );
				return 0;
			}

		// ENTITIES
			else
			{
				BEntity* i(0);
				
				if ( type == CLASS::SCENE )
					i = new Scene();
				else if ( type == CLASS::SDLWINDOW )
					i = new BGLWindow();
				else if ( type == CLASS::SDL_SWAPBUFFERS )
					i = new SDL_SwapBuffers();

				return i;
			}
	}

	extern "C" void destroy( BEntity* p )
	{
// 		std::cout << "LIB DESTROY:: " << p->id() << std::endl;
		delete p;
	}
	
