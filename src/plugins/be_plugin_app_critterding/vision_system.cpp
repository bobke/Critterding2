#include "vision_system.h"
#include "plugins/be_plugin_opengl/be_entity_graphics_model.h"
#include "plugins/be_plugin_bullet/be_entity_physics_entity.h"
#include "kernel/be_plugin_base_entity_types.h"
#include "critter_system.h"
#include <iostream>

	void CdVisionSystem::construct()
	{
		m_print = addChild("print", new BEntity_bool());
		// m_print->set( true );
		m_critter_sightrange = addChild("sight_range", new BEntity_float());
		m_critter_sightrange->set( 5.0f );
		
		m_drawEntities = topParent()->getChild("Scene", 1)->getChild("Critterding", 1)->getChild("SDL GLWindow", 1)->getChild("GraphicsModelSystem", 1);
		m_turn_180 = btTransform( btQuaternion( SIMD_PI, 0.0f, 0.0f ) );

		m_critter_retinasize = 6; // FIXME max 8?
		m_retinasperrow = 2048 / m_critter_retinasize;
		// m_critter_sightrange = 10.0f;

		// vision retina allocation
		unsigned int items = 4 * 2048 * 2048;
		retina = (unsigned char*)malloc( items );
		memset( retina, 0, items );

		// generate namespace for the frame buffer, colorbuffer and depthbuffer
		glGenFramebuffersEXT(1, &fb);
		glGenTextures(1, &color_tex); 
		glGenRenderbuffersEXT(1, &depth_rb);

		//switch to our fbo so we can bind stuff to it
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);

		//create the colorbuffer texture and attach it to the frame buffer
		glBindTexture(GL_TEXTURE_2D, color_tex);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 2048, 2048, 0, GL_RGBA, GL_INT, NULL);
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, color_tex, 0); 
		
		// create a render buffer as our depthbuffer and attach it
		glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depth_rb);
		glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, 2048, 2048);
		glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depth_rb);

		// Go back to regular frame buffer rendering
		// glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	} 

	void CdVisionSystem::process()
	{
		// std::cout << "------------- " << fb << std::endl;
		bool empty(true);

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb); 
		glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		unsigned int pos = 0;
		for_all_children_of( m_unit_container )
		{
			// std::cout << "head: " << pos+1 << std::endl;
			calcFramePos(pos);
			
			empty = false;
			// std::cout << (*child)->name() << " " << (*child)->id() << std::endl;
			// auto bodypart_to_attach_cam = (*child)->getChild("external_body", 1)->get_reference()->getChild("body_fixed1", 1)->getChild("bodyparts", 1)->getChild("external_bodypart_graphics", 1)->get_reference();
			
			CdCritter* critter = dynamic_cast<CdCritter*>( (*child) );
			if ( critter->m_physics_component == 0 )
			{
				 critter->m_physics_component = critter->getChild("external_body", 1)->get_reference()->getChild("body_fixed1", 1)->getChild("bodyparts", 1)->getChild("external_bodypart_physics", 1)->get_reference();
			}
			auto bodypart_to_attach_cam = dynamic_cast<BPhysicsEntity*>( critter->m_physics_component )->getPhysicsComponent();
			
			if ( bodypart_to_attach_cam != 0 )
			{
				glViewport(framePosX, framePosY, m_critter_retinasize, m_critter_retinasize);

				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				glFrustum( -0.05f, 0.05f, -0.05, 0.05, 0.1f, m_critter_sightrange->get_float());

				// GET MATRIX
				// bodypart_to_attach_cam->getTransform().getOpenGLMatrix( m_drawingMatrix );
 				m_pos_transform = bodypart_to_attach_cam->getTransform() * m_turn_180;
				m_pos_transform.inverse().getOpenGLMatrix( m_drawingMatrix );
				glMultMatrixf( m_drawingMatrix );

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				
				// DRAW WORLD
					if ( m_drawEntities )
					{
						for_all_children_of2( m_drawEntities )
						{
							auto model = dynamic_cast<BGraphicsModel*>( (*child2) );
							if ( model )
							{
								// std::cout << " drawentity: " << (*child2)->name() << std::endl;
								
								// (*child2)->process();
								model->processWhenInSight( &bodypart_to_attach_cam->getTransform(), m_critter_sightrange->get_float() );

								// auto t = (*child2)->getChild("transform", 1);
								// if ( t )
								// {
								// 	btVector3 v = btVector3( t->get_float("position_x"), t->get_float("position_y"), t->get_float("position_z") );
								// 	dynamic_cast<BGraphicsModel*>( (*child2) )->processWhenInSight( &v );
								// 	// (*child2)->process();
								// }
							}
						}
					}

				pos++;
			}
		}

		// Read pixels into retina
		if ( !empty )
		{
			// glReadBuffer(GL_BACK);
			// glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
   // 
			// // figure out how many rows, if rows is 1 then columns = 0 else it's retinasperrow
			// unsigned int t_rows = (pos / m_retinasperrow) + 1;
			// unsigned int t_columns = m_retinasperrow;
			// if ( t_rows == 1 )
			// {
			// 	t_columns = pos;
			// }
			// glReadPixels(0, 0, t_columns * m_critter_retinasize, t_rows * m_critter_retinasize, GL_RGBA, GL_UNSIGNED_BYTE, retina);

			
			unsigned int picwidth = m_retinasperrow * (m_critter_retinasize);
			unsigned int picheight = m_critter_retinasize;
			unsigned int rows = m_unit_container->numChildren();
			while ( rows > m_retinasperrow )
			{
				picheight += m_critter_retinasize;
				rows -= m_retinasperrow;
			}
			glReadBuffer(GL_BACK);
			glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
			glReadPixels(0, 0, picwidth, picheight, GL_RGBA, GL_UNSIGNED_BYTE, retina);
			
			
			// FEED TO BRAIN
			unsigned int critter_counter = 0;
			for_all_children_of( m_unit_container )
			{
				// while vision_value_R not found
				auto brain_inputs = (*child)->getChild("external_brain", 1)->get_reference()->getChild("inputs", 1);
				
				// setup inputs and cycle through to the correct input
				const auto& brain_inputs_children_vector = brain_inputs->children();
				const auto& brain_inputs_begin = brain_inputs_children_vector.begin();
				const auto& brain_inputs_end = brain_inputs_children_vector.end();
				auto brain_input = brain_inputs_begin;
				while ( brain_input != brain_inputs_end && (*brain_input)->name() != "vision_value_R" )
				{
					// std::cout << (*brain_input)->name() << std::endl;
					++brain_input;
				}
				
				// FEED
				calcFramePos(critter_counter);
				for ( unsigned int h=retinaRowStart; h < retinaRowStart+(m_critter_retinasize*retinaRowLength); h += retinaRowLength )
				{
					for ( unsigned int w=h+retinaColumnStart; w < h+retinaColumnStart+(m_critter_retinasize*4); ++w )
					{
						const int value = (int)retina[w];
						if ( value > 0 )
						{
							const float fvalue = (float)value / 255;
							// std::cout << "setting brain_input " << (*brain_input)->name() << " to " << ((float)(int)retina[w]) / 255 << std::endl;

							// if it's the same, force update to outputs
							if ( (*brain_input)->get_float() == fvalue )
							{
								(*brain_input)->onUpdate();
							}
							else
							{
								(*brain_input)->set( fvalue );
							}
							
						}
						++brain_input;
					}
				}

				critter_counter++;
			}
			
			
			// PRINT
			if ( m_print->get_bool() )
			{
				unsigned int critter_counter = 0;
				for_all_children_of( m_unit_container )
				{
					calcFramePos(critter_counter);
					std::cout << "critter " << critter_counter << ":" << " x:" << retinaColumnStart << " y:" << retinaRowStart << " retinaRowLength: " << retinaRowLength << std::endl;

					for ( unsigned int h=retinaRowStart; h < retinaRowStart+(m_critter_retinasize*retinaRowLength); h += retinaRowLength )
					{
						for ( unsigned int w=h+retinaColumnStart; w < h+retinaColumnStart+(m_critter_retinasize*4); w+=4 )
						{
							if ( (int)retina[w+0] > 80 ) std::cout << "\033[1;31mR\033[0m";
							else std::cout << ".";
							if ( (int)retina[w+1] > 80 ) std::cout << "\033[1;32mG\033[0m";
							else std::cout << ".";
							if ( (int)retina[w+2] > 80 ) std::cout << "\033[1;34mB\033[0m";
							else std::cout << ".";
							if ( (int)retina[w+3] > 80 ) std::cout << "\033[1;35mA\033[0m";
							else std::cout << ".";
						}
						std::cout << std::endl;
					}
					std::cout << std::endl;

					critter_counter++;
				}
			}
			

			// if ( (int)retina[0] != 0 )
			// {
			// 	std::cout << (int)retina[0] << " : " << (int)retina[1] << " : " << (int)retina[2] << " : " << (int)retina[3] << std::endl;
			// }
		}

		// glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0); 
	}

	void CdVisionSystem::calcFramePos(unsigned int pos)
	{
		// unsigned int m_retinasperrow = 50;
		visionPosition = pos;

		// Calc 2D cartesian vectors X & Y for frame positioning of retina
		framePosY = 0;
		while ( pos >= m_retinasperrow )
		{
			pos -= m_retinasperrow;
			framePosY += m_critter_retinasize;
		}
		framePosX = (pos * m_critter_retinasize);

		// Calculate where in the Great Retina this critter shold start (column & row)
		unsigned int target = visionPosition;
		retinaRowStart = 0;

		// determine on which row of the retina to start for this critter
		retinaRowLength = m_retinasperrow * m_critter_retinasize * 4;

		// determine on which column to start
		while ( target >= m_retinasperrow )
		{
			retinaRowStart += m_critter_retinasize * retinaRowLength;
			target -= m_retinasperrow;
		}
		retinaColumnStart = target * m_critter_retinasize * 4;

	// cerr << framePosX << " : " << framePosY << endl;
	// usleep (1000);

	}	

	CdVisionSystem::~CdVisionSystem()
	{
		free(retina);
	}
	