#include "kernel/be_entity_core_types.h"
#include "plugin.h"
#include <iostream>
#include <GL/glew.h>

	void Scene::construct()
	{
		std::cout << "Scene::construct()" << std::endl;


		addChild( "bindings", new BEntity() );
	}


	
	BGLWindow::BGLWindow() :
// 	m_eventsystem(eventsystem),
	w_bpp(0),
	w_width(0),
	w_height(0),
	n_width(0),
	n_height(0),
	fs(0),
	vidInfo(0),
	m_surface(0),
	vidFlags(0),
	hwaccel(0),
	settingsfs(0),
	mousex(0),
	mousey(0),
	m_resized(false),
	m_resizable(false)
	, m_destroy_entity_on_close(this)
	
// 	m_logDebug("WINDOW")
	{
		// register an exit event from glwindow
// 		m_eventsystem->registerEvent( DOWN, "glwindow-quit", boost::shared_ptr<Event>(new Event(BeCommand("quit"), EVENT_NOREPEAT, 0)) );	
		setProcessing();
		
		create("SDL WINDOW", 1224, 768);
		
	} 

	void BGLWindow::construct()
	{
		addChild( "bindings", new BEntity() );
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
				w_width = width;
				w_height = height;
				n_width = width;
				n_height = height;

// 				Settings::Instance()->winWidth = &w_width;
// 				Settings::Instance()->winHeight = &w_height;

				//Set window title
				setTitle(title);

				//Create window
				m_surface = SDL_SetVideoMode(w_width, w_height, w_bpp, videoFlags);
				glewInit();

// 				m_logDebug << "::WINDOW SDL subsystem initialized\n";

				//Enable GL multisampled rendering if required
				int value;
				SDL_GL_GetAttribute(SDL_GL_MULTISAMPLEBUFFERS, &value);
				if(value)
				{
					glEnable(GL_MULTISAMPLE);
					glHint(GL_LINE_SMOOTH_HINT, GL_NICEST );
					glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST );
					glEnable(GL_LINE_SMOOTH);
					glEnable(GL_POLYGON_SMOOTH);
				}

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

		w_width = width;
		w_height = height;
		n_width = width;
		n_height = height;

// 		Settings::Instance()->winWidth = &w_width;
// 		Settings::Instance()->winHeight = &w_height;
// 		settingsfs = Settings::Instance()->getCVarPtr("fullscreen");
// 		fs = *settingsfs;
		fs = 1;

		if ( fs == 1 )
			m_surface = SDL_SetVideoMode( w_width, w_height, w_bpp, vidFlags | SDL_FULLSCREEN );
		else
			m_surface = SDL_SetVideoMode( w_width, w_height, w_bpp, vidFlags | SDL_RESIZABLE );
		glewInit();
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

		if ( w_height == 0 ) w_height = 1;
		if ( w_width == 0 ) w_width = 1;
	// 	std::cout << "resize" << std::endl;
		
		SDL_FreeSurface(m_surface);
		m_surface = SDL_SetVideoMode( w_width, w_height, w_bpp, vidFlags | SDL_RESIZABLE );
		
	}

	void BGLWindow::toggleFs()
	{
		m_resized = true;

		Uint32 videoFlags=vidFlags;
		if ( fs )
		{
			if ( w_height == 0 ) w_height = 1;
			if ( w_width == 0 ) w_width = 1;
			n_width = w_width;
			n_height = w_height;
// 			w_width = Settings::Instance()->getCVar("fsX");
// 			w_height = Settings::Instance()->getCVar("fsY");
			videoFlags |= SDL_FULLSCREEN;
		}
		else
		{
			w_width = n_width;
			w_height = n_height;
			if ( m_resizable )
				videoFlags |= SDL_RESIZABLE;
		}
		SDL_FreeSurface(m_surface);
		m_surface = SDL_SetVideoMode( w_width, w_height, w_bpp, videoFlags );
		glewInit();
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
				w_width = event.resize.w;
				w_height = event.resize.h;
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

			// if we have bindings, check keypresses
			{
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
						
						// auto binding = bindings->getChild( SDL_GetKeyName( event.key.keysym.sym ), 1 );
						// if ( binding && binding->get_bool() == false )
						// {
						// 	binding->set( true );
						// }
						
						
						// // HACK DEBUG STUFF to show buttons pressed
						// if ( (binding && binding->get_bool() == false) || !binding ) 
							// std::cout << "pressed '" << SDL_GetKeyName( event.key.keysym.sym ) << "'" << std::endl;
					}

						
					
	// 				const std::string& key = SDL_GetKeyName( event.key.keysym.sym );
	// 				if ( !m_canvas || !m_canvas->keyPress( key ) )
	// 					m_eventsystem->activateKeystate( key );
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
						}
		// 				const std::string& key = SDL_GetKeyName( event.key.keysym.sym );
		// 				if ( !m_canvas || !m_canvas->keyRelease( key ) )
		// 					m_eventsystem->deactivateKeystate( key );
		// 	// 			m_eventsystem->deactivateKeystate( SDL_GetKeyName( event.key.keysym.sym ) );
					}
				}
				
			}
			

// 			else if(event.type == SDL_KEYDOWN)
// 			{
// 				const std::string& key = SDL_GetKeyName( event.key.keysym.sym );
// 				if ( !m_canvas || !m_canvas->keyPress( key ) )
// 					m_eventsystem->activateKeystate( key );
// 			}
// 
// 			else if (event.type == SDL_MOUSEBUTTONDOWN)
// 			{
// 	// 			std::cout << (int)event.button.button << std::endl;
// 				if ( !m_canvas || !m_canvas->buttonPress(event.button.button) )
// 					m_eventsystem->activateKeystate( event.button.button+2048 );
// 			}
// 			else if (event.type == SDL_MOUSEBUTTONUP)
// 			{
// 				if ( m_canvas ) m_canvas->buttonRelease(event.button.button);
// 					m_eventsystem->deactivateKeystate( event.button.button+2048 );
// 			}
// 
// 			else if (event.type == SDL_JOYBUTTONDOWN)
// 			{
// 				m_eventsystem->activateKeystate( event.button.button+4096 );
// 			}
// 			else if (event.type == SDL_JOYBUTTONUP)
// 			{
// 				m_eventsystem->deactivateKeystate( event.button.button+4096 );
// 			}
// 
// 			else if(event.type == SDL_JOYAXISMOTION)
// 			{
// 				m_eventsystem->setAxisstate( event.jaxis.axis+6144, event.jaxis.value );
// 			}
// 
// 			else if(event.type == SDL_MOUSEMOTION)
// 			{
// 				if ( m_canvas )
// 					m_canvas->moveMouse( event.motion.x, event.motion.y );
// 
// 				m_eventsystem->setAxisstate( 0+7168, event.motion.x );
// 				m_eventsystem->setAxisstate( 1+7168, event.motion.y );
// 			}
// 
		}

		// SETUP OPENGL
		if ( 1 == 1 )
		{
			//Hint for everything to be nicest
			glHint(GL_FOG_HINT, GL_FASTEST);
			glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT, GL_FASTEST);
			glHint(GL_GENERATE_MIPMAP_HINT, GL_FASTEST);
			glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
			glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
			glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);
			glHint(GL_TEXTURE_COMPRESSION_HINT, GL_FASTEST);

			//Smooth shading
			glShadeModel(GL_SMOOTH);

			//Enable back face culling
// 			glDisable(GL_CULL_FACE);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);

			//Enable depth test
			glEnable(GL_DEPTH_TEST);

			//Alpha blending
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable (GL_BLEND); 
// 			glDisable(GL_BLEND); 

// 			glDisable( GL_ALPHA_TEST );
			glEnable ( GL_ALPHA_TEST );
			glAlphaFunc ( GL_GREATER, 0.5f ) ;

			// GLfloat v[4];
			// v[0] = 0.5f;
			// v[1] = 0.5f;
			// v[2] = 0.5f;
			// v[3] = 1.0f;

			// glEnable(GL_LIGHTING);
			glEnable(GL_NORMALIZE);

			// glLightModelfv(GL_LIGHT_MODEL_AMBIENT, v);
			// glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
			// glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
			// glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);


			// glColorMaterial(GL_FRONT_AND_BACK, 0);
			
			//Set default light model settings
// 			m_graphicsSystem->lightModel(GL_LIGHT_MODEL_AMBIENT, Vector4f(0.5f, 0.5f, 0.5f, 1.0f));
// 			m_graphicsSystem->lightModel(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
// 			m_graphicsSystem->lightModel(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
// 			m_graphicsSystem->lightModel(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
// 
// 			// Set one directional light by default
// 				// BeDirectionalLight light;
// 				// light.setDirection(Vector3f(1,1,0));
// 				// light.setSpecular(Vector4f(1,1,1,1));
// 				// m_graphicsSystem->applyLight(GL_LIGHT0, &light);
// 		
			//Set the default material
// 			m_graphicsSystem->applyMaterial(GL_FRONT_AND_BACK, 0);

// 			//Disable lighting
// 			m_graphicsSystem->disable(GL_LIGHTING);
// 
			//Set default matrices
// 				glMatrixLoadIdentityEXT(GL_PROJECTION);
// 				glMatrixLoadIdentityEXT(GL_MODELVIEW);
		}		
		
// 		std::cout << w_width << " " << w_height << std::endl;
		// glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0); 
		
				glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
				glViewport(0,0,w_width,w_height);

				// // 	glViewport(0,0,640,480);
					// glViewport(0,0,w_width,w_height);
				// 	glEnable(GL_DEPTH_TEST);
				// 	glEnable(GL_BLEND);
				// 	glEnable(GL_ALPHA_TEST);
				// 	glDepthMask(GL_FALSE);
				// 	glMatrixLoadIdentityEXT(GL_PROJECTION);
				// 	glMatrixOrthoEXT(GL_PROJECTION, 0, w_width, w_height, 0,  0, 1);
				// 	glMatrixLoadIdentityEXT(GL_MODELVIEW);
				
				// // 	glColor4f(1,1,1,1);
				
				glUseProgram(0);
// 				process_children();
				
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
	
