#pragma once

#include "kernel/be_entity_core_types.h"
#include <GLFW/glfw3.h>
#include "kernel/be_entity_macros.h"
#include <iostream>
#include <sstream>


	// ERROR CALLBACK
		void error_callback(int error, const char* description)
		{
			fprintf(stderr, "Error: %s\n", description);
		}

	// WINDOW CLOSE
		auto window_close_callback = [](GLFWwindow *w)
		{
			auto window = static_cast<BGLWindow*>(glfwGetWindowUserPointer( w ));
			BEntity* cmdbuffer = window->topParent()->getChild("_command_buffer");
			if ( cmdbuffer )
			{
				cmdbuffer->addChild("remove", new BEntity_reference() )->set( window->m_destroy_entity_on_close );
			}
		};

	// WINDOW SIZE
		auto window_size_callback = [](GLFWwindow *w, int width, int height)
		{
			auto window = static_cast<BGLWindow*>(glfwGetWindowUserPointer( w ));
			window->m_width->set( width );
			window->m_height->set( height );
			window->getChild("GraphicsModelSystem", 1)->getChild("Camera", 1)->getChild("aspect_ratio", 1)->set( (float)width/height );

		};


	// WINDOW POSITION
		auto windowposition_callback = [](GLFWwindow *w, int x, int y)
		{
			auto window = static_cast<BGLWindow*>(glfwGetWindowUserPointer( w ));
			window->m_position_x->set( x );
			window->m_position_y->set( y );
		};

	// MOUSE POSITION
		auto mousepos_callback = [](GLFWwindow *w, double x, double y)
		{
			auto window = static_cast<BGLWindow*>(glfwGetWindowUserPointer( w ));
			
			// if (x < 0 ) x = 0;
			// if (x > window->m_width->get_int() ) x = window->m_width->get_int();
			// if (y < 0 ) y = 0;
			// if (y > window->m_height->get_int() ) y = window->m_height->get_int();

			window->m_mouse_x->set( (int)x );
			window->m_mouse_y->set( (int)y );
		};

	// MOUSE CLICKS
		auto mouse_button_callback = [](GLFWwindow *w, int button, int action, int mods)
		{
			auto window = static_cast<BGLWindow*>(glfwGetWindowUserPointer( w ));
			if ( action == GLFW_PRESS )
			{
				auto bindings = window->getChild( "bindings", 1 );
				if( bindings )
				{
					std::stringstream mouseButton_name;
					mouseButton_name << "mousebutton_down_" << button;

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
			
			if ( action == GLFW_RELEASE )
			{
				auto bindings = window->getChild( "bindings", 1 );
				if( bindings )
				{
					std::stringstream mouseButton_name;
					mouseButton_name << "mousebutton_up_" << button;

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
			
		};

	// KEY PRESSES
		auto key_callback = [](GLFWwindow *w, int key, int scancode, int action, int mods)
		{
			if ( action != GLFW_REPEAT )
			{
				// std::cout << " key: " << key << " action " <<  action;
				// std::cout << " key_name2: " << get_key_name( key ) << std::endl;

				auto window = static_cast<BGLWindow*>(glfwGetWindowUserPointer( w ));
				if ( action == GLFW_PRESS )
				{
					// std::cout << " press ";
					
					auto bindings = window->getChild( "bindings", 1 );
					if( bindings )
					{
						// const char* keyname = glfwGetKeyName( key, scancode );
						const char* keyname = get_key_name( key );
						
						if ( keyname )
						{
							auto binding = bindings->getChild( keyname, 1 );
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
							key_name << "key_down_" << keyname;
							auto binding2 = bindings->getChild( key_name.str().c_str(), 1 );
							if ( binding2 )
							{
								if ( binding2->class_id() == std::string("bool") )
								{
									binding2->set( !binding2->get_bool() );
								}
								if ( binding2->class_id() == std::string("trigger") )
								{
									binding2->set();
								}
							}
						}
					}

				}
				if ( action == GLFW_RELEASE )
				{
					// std::cout << " release";
					
					auto bindings = window->getChild( "bindings", 1 );
					if( bindings )
					{
						// const char* keyname = glfwGetKeyName( key, scancode );
						const char* keyname = get_key_name( key );
						if ( keyname )
						{
							auto binding = bindings->getChild( keyname, 1 );
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
							key_name << "key_up_" << keyname;
							auto binding2 = bindings->getChild( key_name.str().c_str(), 1 );
							if ( binding2 )
							{
								if ( binding2->class_id() == std::string("bool") )
								{
									binding2->set( !binding2->get_bool() );
								}
								if ( binding2->class_id() == std::string("trigger") )
								{
									binding2->set();
								}
							}
						}
					}
				}
			}
		};

