#include "plugin.h"
#include "kernel/be_lib_handler.h"
#include "plugins/be_plugin_opengl_modern/be_entity_camera.h"
#include "plugins/be_plugin_app_critterding/food_system.h"
#include "plugins/be_plugin_app_critterding/critter_system.h"
#include "plugins/be_plugin_app_critterding/commands.h"
#include "critter_thread_mesher.h"
// #include "plugins/be_plugin_bullet/be_entity_physics_entity.h"
// #include "plugins/be_plugin_bullet/be_entity_transform.h" // FIXME work this away
// #include <iostream>
#include <sstream>

	void Server::construct()
	{
		// settings
			auto settings = addChild( "settings", new BEntity() );
			m_eat_transfer_energy = settings->addChild( "eat_energy_transfer", new BEntity_float() );
			m_eat_transfer_energy->set( 100.0f );
		
		// RANDOM NUMBER GENERATOR
			auto rng = addChild( "random_number_generator", "Brng" );
		
		// SEED
			// FIXME FIX TIMER
			// auto startTimeMs = topParent()->getChild("sys", 1)->getChild( "timer",1 )->?? ;
			rng->set( "seed", Bint( 111 ) );
		
		// FOOD SYSTEM
		{
			auto food_system = addChild( "food_system", new CdFoodSystem() );
			m_food_unit_container = food_system->getChild( "unit_container", 1 );
		}

		// CRITTER SYSTEM
		{
			auto critter_system = addChild( "critter_system", "CdCritterSystem" );
			m_critter_unit_container = critter_system->getChild( "unit_container", 1 );

			// REGISTER UNIT CONTAINER IN VISION SYSTEM
			auto vision_system = parent()->parent()->getChild( "vision_system", 1 );
				vision_system->set( "register_container", m_critter_unit_container );
		}

		// BULLET PHYSICS
			m_physics_world = addChild( "physicsworld", "PhysicsWorld" );
			m_physics_world_collisions = m_physics_world->getChild( "collisions", 1 );

		// PHYSICS map
			auto map = addChild( "map", new BEntity() );
			const char* map_location = "../share/modules/easy.obj";
			// const char* map_location = "../share/modules/hard.obj";
			auto physics_entity = m_physics_world->addChild( "physics_entity_map", "PhysicsEntity" );
			// physics_entity->set("filename", map_location);
			physics_entity->getChild( "filename", 1 )->set( map_location );
			map->addChild( "external_physics", new BEntity_external() )->set(physics_entity);

			auto physics_weight = physics_entity->addChild("weight", new BEntity_float_property());
				physics_weight->set( 0.0f );

			auto physics_scale_x = physics_entity->addChild("scale_x", new BEntity_float_property());
			auto physics_scale_y = physics_entity->addChild("scale_y", new BEntity_float_property());
			auto physics_scale_z = physics_entity->addChild("scale_z", new BEntity_float_property());
			physics_scale_x->set( 8.0f );
			physics_scale_y->set( 1.0f );
			physics_scale_z->set( 10.0f );

			auto physics_entity_transform = physics_entity->getChild("transform", 1);
			if ( physics_entity_transform )
			{
				physics_entity_transform->getChild("position_x", 1)->set( 0.0f );
				physics_entity_transform->getChild("position_y", 1)->set( -20.0f );
				physics_entity_transform->getChild("position_z", 1)->set( -100.0f );
			}		
	}

	void Server::process()
	{
		// CHECK PHYSICS COLLISIONS
			for_all_children_of( m_physics_world_collisions )
			{
				auto e1 = (*child)->getChild( "entity1", 1 )->get_reference();
				auto e2 = (*child)->getChild( "entity2", 1 )->get_reference();
				// std::cout << "collision e1: " << e1->name() << "(" << e1->id() << ")" << std::endl;
				// std::cout << "collision e2: " << e2->name() << "(" << e2->id() << ")" << std::endl;

				// FIXME BUGGY WHEN DELETING CRITTERS
				// EAT: TRANSFER ENERGY FROM FOOD TO CRITTER 
					auto critter = findCritter( e1, e2 );
					if ( critter )
					{
						// CHECK MOTOR NEURON FIXME OPTIMIZE
						auto eat = critter->getChild("motor_neurons", 1)->getChild("eat", 1);
						if ( eat->get_float() != 0.0f ) // FIXME
						{
							eat->set( 0.0f );

							auto food = findFood( e1, e2 );
							if ( food )
							{
								// ENERGY TRANSFER
								auto critter_energy = critter->getChild("energy", 1);
								auto food_energy = food->getChild("energy", 1);

								if ( food_energy->get_float() < m_eat_transfer_energy->get_float() )
								{
									critter_energy->set( critter_energy->get_float() + food_energy->get_float() );
									food_energy->set( 0.0f );
								}
								else
								{
									critter_energy->set( critter_energy->get_float() + m_eat_transfer_energy->get_float() );
									food_energy->set( food_energy->get_float() - m_eat_transfer_energy->get_float() );
								}
							}
						}
					}
			}
	}
	
	
	void Scene::construct()
	{
		setName( "Critterding" );
		std::cout << "Scene::construct()" << std::endl;
		
		// LOAD QT APP FIXME THIS DOESN'T NEED TO GET ONTO THE TREE
		pluginManager()->load( "qt6", "src/plugins/be_plugin_qt6", "be_plugin_qt6" );

			auto spawner = addChild( "spawner", "QApplicationSpawner" );
			auto t_parent_to_add_to = spawner->getChildCustom( this );
			// auto t_parent_to_add_to = spawner->getChildCustom( parent() );
			removeChild( spawner );

		pluginManager()->load( "app_admin_window", "src/plugins/be_plugin_app_admin_window", "be_plugin_app_admin_window" );
		pluginManager()->load( "app_sysmon", "src/plugins/be_plugin_app_sysmon", "be_plugin_app_sysmon" );
		pluginManager()->load( "critterding", "src/plugins/be_plugin_app_critterding", "be_plugin_app_critterding" );

		pluginManager()->load( "system", "src/plugins/be_plugin_system", "be_plugin_system" );
		pluginManager()->load( "opengl", "src/plugins/be_plugin_opengl_modern", "be_plugin_opengl_modern" );
		pluginManager()->load( "bullet", "src/plugins/be_plugin_bullet", "be_plugin_bullet" );
		pluginManager()->load( "brainz", "src/plugins/be_plugin_brainz", "be_plugin_brainz" );
		pluginManager()->load( "qwt", "src/plugins/be_plugin_qwt", "be_plugin_qwt" );
		pluginManager()->load( "thread", "src/plugins/be_plugin_thread", "be_plugin_thread" );
		pluginManager()->load( "imgui", "src/plugins/be_plugin_imgui", "be_plugin_imgui" );

		if ( !pluginManager()->load( "glfw", "src/plugins/be_plugin_glfw", "be_plugin_glfw" ) )
		{
			// pluginManager()->load( "sdl", "src/plugins/be_plugin_sdl", "be_plugin_sdl" );
		}

		// LAUNCHER SETTINGS
			BEntity* launcher_settings(0);
			BEntity* launcher_setting_servers_on_background(0);
			auto launcher = topParent()->getChild( "bin", 1 )->getChild( "Critterding Launcher", 1 ); 
			if ( launcher )
			{
				launcher_settings = launcher->getChild( "settings", 1 ); 
				if ( launcher_settings )
				{
					launcher_setting_servers_on_background = launcher_settings->getChild( "threadsServersBackground", 1 ); 
				}
			}

		// SDL & OPENGL
			auto glwindow = addChild( "GLWindow", "GLWindow" );
			glwindow->set("title", "Critterding 2 (threads)");
			glwindow->set("on_close_destroy_entity", this);
			// glwindow->setFps(60);
			m_win_width = glwindow->getChild( "width", 1 );
			m_win_height = glwindow->getChild( "height", 1 );
			m_mouse_x = glwindow->getChild( "mouse_x", 1 );
			m_mouse_y = glwindow->getChild( "mouse_y", 1 );

		// DEAR IMGUI
			auto imgui = glwindow->addChild( "ImGuiContext", "ImGuiContext" );
			imgui->set( "init_glfw", glwindow );

			// auto imguiwindow = glwindow->addChild( "ImGuiWindow", "ImGuiWindow" );
			// 	auto hbox = imguiwindow->addChild( "hbox", "ImGuiHBoxLayout" );
			// 	{
			// 		{
			// 			auto groupbox = hbox->addChild( "groupbox", "ImGuiGroupBox" );
			// 			{
			// 				auto groupbox2 = groupbox->addChild( "groupbox", "ImGuiGroupBox" );
			// 				{
			// 					{
			// 						auto hbox2 = groupbox2->addChild( "hbox", "ImGuiHBoxLayout" );
			// 							auto lineedit = hbox2->addChild( "ImGuiLineEdit_uint", "ImGuiLineEdit_uint" );
			// 							auto pushbutton = hbox2->addChild( "ImGuiPushButton", "ImGuiPushButton" );
			// 							pushbutton->set("text", "+");
			// 					}
			// 					{
			// 						auto hbox2 = groupbox2->addChild( "hbox", "ImGuiHBoxLayout" );
			// 							auto lineedit = hbox2->addChild( "ImGuiLineEdit_uint", "ImGuiLineEdit_uint" );
			// 							auto pushbutton = hbox2->addChild( "ImGuiPushButton", "ImGuiPushButton" );
			// 							pushbutton->set("text", "+");
			// 					}
			// 					groupbox2->addChild( "end", "ImGuiGroupBox_end" );
			// 				}
			// 				groupbox->addChild( "end", "ImGuiGroupBox_end" );
			// 			}
			// 		}
			// 		{
			// 			auto groupbox = hbox->addChild( "groupbox", "ImGuiGroupBox" );
			// 			{
			// 				auto hbox2 = groupbox->addChild( "hbox", "ImGuiHBoxLayout" );
			// 					auto lineedit = hbox2->addChild( "ImGuiLineEdit_uint", "ImGuiLineEdit_uint" );
			// 					auto pushbutton = hbox2->addChild( "ImGuiPushButton", "ImGuiPushButton" );
			// 					pushbutton->set("text", "+");
			// 				groupbox->addChild( "end", "ImGuiGroupBox_end" );
			// 			}
			// 		}
			// 	}
			// imguiwindow->addChild( "ImGuiWindow_end", "ImGuiWindow_end" );


		// OPENGL SETUP
			glwindow->addChild("OpenGL_Setup", "OpenGL_Setup");

		// IMGUI RENDER
			addChild( "ImGuiRender", "ImGuiRender" );
			
		// SDL SWAPBUFFER, making sure this runs right after sdl_window and it's children are done processing
			addChild("GLSwapBuffers", "GLSwapBuffers")->set("set_glwindow", glwindow);

		// GRAPHICS MODELSYSTEM
			auto t_graphicsModelSystem = glwindow->addChild("GraphicsModelSystem", "GraphicsModelSystem");

		// CAMERA
			m_camera = new BCamera();
			t_graphicsModelSystem->addChild("Camera", m_camera);
			auto transform = m_camera->getChild( "transform", 1 );

			transform->getChild( "position_x" )->set( 0.0f );
			transform->getChild( "position_y" )->set( 156.0f );
			transform->getChild( "position_z" )->set( -100.0f );
			transform->getChild( "rotation_euler_x" )->set( -0.5f * 3.141592f );
			transform->getChild( "rotation_euler_y" )->set( 0.0f );
			transform->getChild( "rotation_euler_z" )->set( 0.0f );

		// COMMANDS
			auto commands = glwindow->addChild( "commands", new BEntity() );
			auto toggleFullscreen = commands->addChild( "toggleFullscreen", new cmd_toggleFullscreen() );
			auto launchAdminWindow = commands->addChild( "launchAdminWindow", new cmd_launchAdminWindow() );
			auto launchControlPanel = commands->addChild( "launchControlPanel", new cmd_launchControlPanel() );
			auto launchSystemMonitor = commands->addChild( "launchSystemMonitor", new cmd_launchSystemMonitor() );
			auto launchSelectionWindow = commands->addChild( "launchSelectionWindow", new cmd_launchSelectionWindow() );
			auto mousePickBody = commands->addChild( "mousePickBody", new cmd_mousePickBody() );
			auto mouseUnpickBody = commands->addChild( "mouseUnpickBody", new cmd_mouseUnpickBody() );

		// BINDINGS
			auto bindings = glwindow->getChild( "bindings", 1 );

			// render
				auto re = t_graphicsModelSystem->getChild("active", 1);
				if ( re )
				{
					auto re_bool = bindings->addChild( "key_down_f10", new BEntity_bool() );
					re_bool->set( true );
					re_bool->connectServerServer( re );
				}
			// fullscreen
				bindings->addChild( "key_down_f11", new BEntity_trigger() )->connectServerServer( toggleFullscreen );
				// auto fs = glwindow->getChild("fullscreen", 1);
				// if ( fs )
					// bindings->addChild( "key_down_f11", new BEntity_bool() )->connectServerServer( fs );
			// vsync
				auto vs = glwindow->getChild("vsync", 1);
				if ( vs )
					bindings->addChild( "key_down_f12", new BEntity_bool() )->connectServerServer( vs );
		
			auto binding_f1 = bindings->addChild( "f1", new BEntity_trigger() );
			binding_f1->connectServerServer( launchAdminWindow );

			auto binding_f2 = bindings->addChild( "f2", new BEntity_trigger() );
			binding_f2->connectServerServer( launchControlPanel );

			auto binding_f3 = bindings->addChild( "f3", new BEntity_trigger() );
			binding_f3->connectServerServer( launchSystemMonitor );

			// bindings to mouse
			auto binding_mouse_2 = bindings->addChild( "mousebutton_down_2", new BEntity_trigger() );  // FIXME CONNECT TO bool under std_window
			binding_mouse_2->connectServerServer( launchSelectionWindow );
   
			// auto binding_mouse_3_down = bindings->addChild( "mousebutton_down_3", new BEntity_trigger() );  // FIXME CONNECT TO bool under std_window
			// binding_mouse_3_down->connectServerServer( mousePickBody );
			// auto binding_mouse_3_up = bindings->addChild( "mousebutton_up_3", new BEntity_trigger() );  // FIXME CONNECT TO bool under std_window
			// binding_mouse_3_up->connectServerServer( mouseUnpickBody );
			
			// bindings to movements
			auto movement = m_camera->getChild("movement", 1);
			auto forward = movement->getChild( "forward", 1 );
			auto backward = movement->getChild( "backward", 1 );
			auto left = movement->getChild( "left", 1 );
			auto right = movement->getChild( "right", 1 );
			auto up = movement->getChild( "up", 1 );
			auto down = movement->getChild( "down", 1 );
			auto binding_up = bindings->addChild( "up", new BEntity_bool() );  // FIXME CONNECT TO bool under std_window
			auto binding_down = bindings->addChild( "down", new BEntity_bool() );  // FIXME CONNECT TO bool under std_window
			auto binding_left = bindings->addChild( "left", new BEntity_bool() );  // FIXME CONNECT TO bool under std_window
			auto binding_right = bindings->addChild( "right", new BEntity_bool() );  // FIXME CONNECT TO bool under std_window
			auto binding_home = bindings->addChild( "home", new BEntity_bool() );  // FIXME CONNECT TO bool under std_window
			auto binding_end = bindings->addChild( "end", new BEntity_bool() );  // FIXME CONNECT TO bool under std_window
			binding_up->connectServerServer( forward );
			binding_down->connectServerServer( backward );
			binding_left->connectServerServer( left );
			binding_right->connectServerServer( right );
			binding_home->connectServerServer( up );
			binding_end->connectServerServer( down );
			
			// bindings to looking
			auto looking = m_camera->getChild("looking", 1);
			auto look_left = looking->getChild( "left", 1 );
			auto look_right = looking->getChild( "right", 1 );
			auto look_up = looking->getChild( "up", 1 );
			auto look_down = looking->getChild( "down", 1 );
			auto look_roll_left = looking->getChild( "roll_left", 1 );
			auto look_roll_right = looking->getChild( "roll_right", 1 );
			auto binding_4 = bindings->addChild( "[4]", new BEntity_bool() );  // FIXME CONNECT TO bool under std_window
			auto binding_6 = bindings->addChild( "[6]", new BEntity_bool() );  // FIXME CONNECT TO bool under std_window
			auto binding_2 = bindings->addChild( "[2]", new BEntity_bool() );  // FIXME CONNECT TO bool under std_window
			auto binding_8 = bindings->addChild( "[8]", new BEntity_bool() );  // FIXME CONNECT TO bool under std_window
			auto binding_1 = bindings->addChild( "[1]", new BEntity_bool() );  // FIXME CONNECT TO bool under std_window
			auto binding_3 = bindings->addChild( "[3]", new BEntity_bool() );  // FIXME CONNECT TO bool under std_window
			binding_4->connectServerServer( look_left );
			binding_6->connectServerServer( look_right );
			binding_2->connectServerServer( look_up );
			binding_8->connectServerServer( look_down );
			binding_1->connectServerServer( look_roll_left );
			binding_3->connectServerServer( look_roll_right );

// 		// LIGHT
// 		{
// 			auto light = t_graphicsModelSystem->addChild( "light", "GLLight" );
// 			
// 			light->getChild( "model_ambient_r", 1 )->set( 0.5f );
// 			light->getChild( "model_ambient_g", 1 )->set( 0.5f );
// 			light->getChild( "model_ambient_b", 1 )->set( 0.5f );
// 			light->getChild( "model_ambient_a", 1 )->set( 0.0f );
// 			
// 			light->getChild( "color_ambient_r", 1 )->set( 0.5f );
// 			light->getChild( "color_ambient_g", 1 )->set( 0.5f );
// 			light->getChild( "color_ambient_b", 1 )->set( 0.5f );
// 			light->getChild( "color_ambient_a", 1 )->set( 0.0f );
// 			
// 			light->getChild( "color_diffuse_r", 1 )->set( 0.4f );
// 			light->getChild( "color_diffuse_g", 1 )->set( 0.4f );
// 			light->getChild( "color_diffuse_b", 1 )->set( 0.4f );
// 			light->getChild( "color_diffuse_a", 1 )->set( 0.0f );
// 
// 			light->getChild( "color_specular_r", 1 )->set( 0.2f );
// 			light->getChild( "color_specular_g", 1 )->set( 0.2f );
// 			light->getChild( "color_specular_b", 1 )->set( 0.2f );
// 			light->getChild( "color_specular_a", 1 )->set( 0.0f );
// 		}

		// "SHADERS" hack for now
			auto shaders = t_graphicsModelSystem->addChild( "shaders", "entity" );
			// auto u_instanceModelMatrixAttrib = shaders->addChild( "InstanceModelMatrix", "ShaderAttrib" );
			// auto u_instanceScale = shaders->addChild( "InstanceScale", "ShaderAttrib" );
			auto u_vec4_color = shaders->addChild( "u_Color", "ShaderUniformVec4" );
			auto u_i14_textureSample = shaders->addChild( "u_textureSample", "ShaderUniformI1" );
			shaders->addChild( "e_scale_x", "float" )->set(0.0f);
			shaders->addChild( "e_scale_y", "float" )->set(0.0f);
			shaders->addChild( "e_scale_z", "float" )->set(0.0f);
			
		// GRAPHICS MAP
		{
			auto map = addChild( "graphics_map", new BEntity() );
			const char* map_location = "../share/modules/easy.obj";
			// const char* map_location = "../share/modules/hard.obj";
			auto t_graphicsModel = t_graphicsModelSystem->addChild("graphics_entity_map", "GraphicsModel");
			t_graphicsModel->addChild( "filename", new BEntity_string_property() )->set( map_location );
			auto graphics_transform = t_graphicsModel->addChild("transform", "Transform");
			// t_graphicsModel->set("filename", map_location);
			map->addChild( "external_graphics", new BEntity_external() )->set(t_graphicsModel);

		// POSITION
			graphics_transform->getChild("position_x", 1)->set( 0.0f );
			graphics_transform->getChild("position_y", 1)->set( -20.0f );
			graphics_transform->getChild("position_z", 1)->set( -100.0f );
			graphics_transform->getChild("scale_x", 1)->set( 8.0f );
			graphics_transform->getChild("scale_y", 1)->set( 1.0f );
			graphics_transform->getChild("scale_z", 1)->set( 10.0f );
		}

		// SKY DOME
		{
			auto t_graphicsModelSkyDome = t_graphicsModelSystem->addChild("GraphicsModel_SkyDome", "GraphicsModel");
			t_graphicsModelSkyDome->set("filename", "../share/modules/skydome3.obj");
		}

		// VISION SYSTEM
			auto vision_system = addChild( "vision_system", "CdVisionSystem" );
			// addChild("GLSwapBuffers", "GLSwapBuffers")->set("set_glwindow", glwindow);

		// DEPTHMAP VIEWER
			t_graphicsModelSystem->addChild("DepthMapViewer", "DepthMapViewer");

		// MOUSEPICERS
			auto mousepickers = addChild( "mousepickers", new BEntity() );
			m_raycasters = addChild( "raycasters", new BEntity() );

		// THREADS FINISH
			BEntity* threads_finish(0);
			if ( (launcher_setting_servers_on_background && launcher_setting_servers_on_background->get_bool()) /*|| !launcher_setting_servers_on_background*/ )
			{
				threads_finish = addChild("threads_finish", "threads_finish");
			}

		// POPLUATION CONTROLLER
			auto population_controller = addChild( "CdPopulationController", "CdPopulationController" );

		// SERVERS
			const float spacing( 2.0f );
			unsigned int total_minimum_critters( 20 ); // FIXME TO GLOBAL ENTITY
			unsigned int total_minimum_food( 2000 ); // FIXME TO GLOBAL ENTITY
			const float critter_spacing( 1.0f );
			
			unsigned int rows( 1 );
			unsigned int columns( 4 );
			
			// IF LAUNCHER UPDATE VALUES FROM LAUNCHER
			if ( launcher_settings )
			{
				auto setting_rows = launcher_settings->getChild( "threadsRows", 1 ); 
				if ( setting_rows )
				{
					rows = setting_rows->get_uint();
				}
				auto setting_columns = launcher_settings->getChild( "threadsColumns", 1 ); 
				if ( setting_columns )
				{
					columns = setting_columns->get_uint();
				}
				auto setting_critters = launcher_settings->getChild( "numCritters", 1 ); 
				if ( setting_critters )
				{
					total_minimum_critters = setting_critters->get_uint();
				}
				auto setting_food = launcher_settings->getChild( "numFood", 1 ); 
				if ( setting_food )
				{
					total_minimum_food = setting_food->get_uint();
				}
			}

			const unsigned int total_threads( rows * columns );
			std::cout << "threads: " << total_threads << " (" << rows << " rows * " << columns << " columns)" << std::endl;

			const float dropzone_total_width( 190 );
			const float dropzone_total_height( 130 );
			const float dropzone_individual_width( dropzone_total_width / columns );
			const float dropzone_individual_height( dropzone_total_height / rows );

			const float startposition_x = -1.0f * (dropzone_total_width / 2);
			const float startposition_z = -100.0f - (dropzone_total_height / 2);

			// THREADS AND SERVERS
			{
				unsigned int thread_counter(1);
				for ( unsigned int current_row(0); current_row < rows; ++current_row )
				{
					
					for ( unsigned int current_column(0); current_column < columns; ++current_column )
					{
						// find current thread
							std::stringstream thread_name_ss;
							thread_name_ss << "thread" << thread_counter;

							auto thread = addChild(thread_name_ss.str().c_str(), "thread");
							auto server = thread->addChild( "Critterding", new Server() );

						// shortcuts
							auto food_system = server->getChild("food_system", 1);
							auto critter_system = server->getChild("critter_system", 1);
							auto dropzone_food = food_system->getChild("settings", 1)->getChild("dropzone", 1);
							auto dropzone_critter = critter_system->getChild("settings", 1)->getChild("dropzone", 1);

						// DROPZONE FOOD
							dropzone_food->getChild("position_x", 1)->set( startposition_x + ( dropzone_individual_width * current_column ) + 0.5f*spacing );
							dropzone_food->getChild("position_z", 1)->set( startposition_z + ( dropzone_individual_height * current_row ) + 0.5f*spacing );
							dropzone_food->getChild("size_x", 1)->set( dropzone_individual_width - 0.5f*spacing );
							dropzone_food->getChild("size_z", 1)->set( dropzone_individual_height - 0.5f*spacing );

						// DROPZONE CRITTER
							dropzone_critter->getChild("position_x", 1)->set( startposition_x + ( dropzone_individual_width * current_column ) + 0.5f*critter_spacing );
							dropzone_critter->getChild("position_z", 1)->set( startposition_z + ( dropzone_individual_height * current_row ) + 0.5f*critter_spacing );
							dropzone_critter->getChild("size_x", 1)->set( dropzone_individual_width - 0.5f*critter_spacing );
							dropzone_critter->getChild("size_z", 1)->set( dropzone_individual_height - 0.5f*critter_spacing );

						// MINIMUM FOOD AND CRITTERS
							food_system->getChild("settings", 1)->getChild( "number_of_units", 1)->set( uint( total_minimum_food / total_threads ) );
							critter_system->getChild("settings", 1)->getChild( "minimum_number_of_units", 1)->set( uint( total_minimum_critters / total_threads ) );
						
						// REGISTER TO POPULATION CONTROLLER
							population_controller->set( "register_critter_container", critter_system->getChild("unit_container", 1) );
							population_controller->set( "register_food_container", server->getChild("food_system", 1)->getChild("unit_container", 1) );

						// RAYCAST
						{
							m_bullet_raycast = server->getChild("physicsworld", 1)->addChild( "raycaster", "Bullet_Raycast" );
							{
								auto source = m_bullet_raycast->getChild( "source", 1 );
								m_raycast_source_x = source->getChild( "x", 1 );
								m_raycast_source_y = source->getChild( "y", 1 );
								m_raycast_source_z = source->getChild( "z", 1 );
								auto target = m_bullet_raycast->getChild( "target", 1 );
								m_raycast_target_x = target->getChild( "x", 1 );
								m_raycast_target_y = target->getChild( "y", 1 );
								m_raycast_target_z = target->getChild( "z", 1 );
							}
				
							m_raycasters->addChild( "external_raycaster", new BEntity_external() )->set( m_bullet_raycast );
						}

						// MOUSE PICKERS
							auto mousepicker = server->getChild("physicsworld", 1)->addChild( "mousepicker", "Bullet_MousePicker" );
							mousepickers->addChild( "external_mousepicker", new BEntity_external() )->set( mousepicker );
							
							
							
						++thread_counter;
					}
				}
			}

			// THREADMESHERS
			{
				unsigned int thread_counter(1);
				for ( int current_row(0); current_row < rows; ++current_row )
				{
					
					for ( int current_column(0); current_column < columns; ++current_column )
					{
						// find current thread
							std::stringstream thread_name_ss;
							thread_name_ss << "thread" << thread_counter;
				
							auto thread = getChild( thread_name_ss.str().c_str(), 1 );
							auto server = thread->getChild( "Critterding", 1 );
							
						// Migrate below
							if ( current_row < rows - 1 )
							{
								// std::cout << thread_name_ss.str() << " should migrate to below " << std::endl;

								// get the one below
								auto server_target = getServer( current_row+1, current_column, rows, columns );
								// std::cout << "Target Server : " << server_target->parent()->name() << std::endl;
								{
									auto mesher = server->addChild( "thread_mesher", "CdCritterThreadMesher" );

									mesher->getChild( "z_active", 1 )->set( true );
									auto v = startposition_z + ( dropzone_individual_height * (current_row+1) ) + 0.1f;
									// std::cout << "!!! down " << v << std::endl;
									mesher->getChild( "z_border", 1 )->set( v );
									// mesher->getChild( "z_border", 1 )->set( -99.9f );
									mesher->getChild( "z_direction_is_down", 1 )->set( true );
									mesher->getChild( "z_target", 1 )->set( server_target->getChild("critter_system", 1)->getChild("unit_container", 1) );
								}
								
							}

						// Migrate up
							if ( current_row > 0 )
							{
								// std::cout << thread_name_ss.str() << " should migrate to up " << std::endl;
								
								// get the one above
								auto server_target = getServer( current_row-1, current_column, rows, columns );
								// std::cout << "Target Server : " << server_target->parent()->name() << std::endl;
								{
									auto mesher = server->addChild( "thread_mesher", "CdCritterThreadMesher" );

									mesher->getChild( "z_active", 1 )->set( true );
									auto v = startposition_z + ( dropzone_individual_height * (current_row) ) - 0.1f;
									// std::cout << "!!! up " << v << std::endl;
									mesher->getChild( "z_border", 1 )->set( v );
									// mesher->getChild( "z_border", 1 )->set( -100.1f );
									mesher->getChild( "z_direction_is_down", 1 )->set( false );
									mesher->getChild( "z_target", 1 )->set( server_target->getChild("critter_system", 1)->getChild("unit_container", 1) );
								}
								
							}

						// Migrate left
							if ( current_column > 0 )
							{
								// std::cout << thread_name_ss.str() << " should migrate to left " << std::endl;

								// get the one on the left
								auto server_target = getServer( current_row, current_column-1, rows, columns );
								// std::cout << "Target Server : " << server_target->parent()->name() << std::endl;
								{
									auto mesher = server->addChild( "thread_mesher", "CdCritterThreadMesher" );

									mesher->getChild( "x_active", 1 )->set( true );
									auto v = startposition_x + ( dropzone_individual_width * (current_column) ) - 0.1f;
									// std::cout << "!!! left " << v << std::endl;
									mesher->getChild( "x_border", 1 )->set( v );
									// mesher->getChild( "x_border", 1 )->set( -0.1f );
									mesher->getChild( "x_direction_is_right", 1 )->set( false );
									mesher->getChild( "x_target", 1 )->set( server_target->getChild("critter_system", 1)->getChild("unit_container", 1) );
								}
								
							}

						// Migrate right
							if ( current_column < columns - 1 )
							{
								// std::cout << thread_name_ss.str() << " should migrate to right " << std::endl;

								// get the one on the right
								auto server_target = getServer( current_row, current_column+1, rows, columns );
								// std::cout << "Target Server : " << server_target->parent()->name() << std::endl;
								{
									auto mesher = server->addChild( "thread_mesher", "CdCritterThreadMesher" );

									mesher->getChild( "x_active", 1 )->set( true );
									auto v = startposition_x + ( dropzone_individual_width * (current_column+1) ) + 0.1f;
									// std::cout << "!!! right " << v << std::endl;
									mesher->getChild( "x_border", 1 )->set( v );
									// mesher->getChild( "x_border", 1 )->set( 0.1f );
									mesher->getChild( "x_direction_is_right", 1 )->set( true );
									mesher->getChild( "x_target", 1 )->set( server_target->getChild("critter_system", 1)->getChild("unit_container", 1) );
								}
							}

						++thread_counter;
					}
				}
			}

		// // THREADS FINISH
			if ( launcher_setting_servers_on_background && !launcher_setting_servers_on_background->get_bool() || !launcher_setting_servers_on_background )
			{
				addChild("threads_finish", "threads_finish");
			}

		// CRITTER EXCHANGER
			addChild( "CdCritterExchanger", "CdCritterExchanger" );
			
		// ASSURES NICE CLEANUP FOR THREADS
			if ( (launcher_setting_servers_on_background && launcher_setting_servers_on_background->get_bool()) /*|| !launcher_setting_servers_on_background*/ )
			{
				addChild( "thread_finish_external", new BEntity_external() )->set( threads_finish );
			}
		
		// DEAR IMGUI
			// auto imgui = glwindow->addChild( "ImGuiWindow", "ImGuiWindow" );
			// imgui->set( "init_glfw", glwindow );
			// glwindow->addChild( "ImGuiRender", "ImGuiRender" );
				
		// // RAYCAST
		// {
		// 	m_bullet_raycast1 = getChild("thread", 1)->getChild("Critterding", 1)->getChild("physicsworld", 1)->addChild( "raycaster", "Bullet_Raycast" );
		// 	m_bullet_raycast2 = getChild("thread", 1)->getChild("Critterding", 1)->getChild("physicsworld", 1)->addChild( "raycaster", "Bullet_Raycast" );
		// 	m_bullet_raycast3 = getChild("thread", 1)->getChild("Critterding", 1)->getChild("physicsworld", 1)->addChild( "raycaster", "Bullet_Raycast" );
		// 	m_bullet_raycast4 = getChild("thread", 1)->getChild("Critterding", 1)->getChild("physicsworld", 1)->addChild( "raycaster", "Bullet_Raycast" );
  // 
		// 	{
		// 		auto source = m_bullet_raycast1->getChild( "source", 1 );
		// 		m_raycast_source_x1 = source->getChild( "x", 1 );
		// 		m_raycast_source_y1 = source->getChild( "y", 1 );
		// 		m_raycast_source_z1 = source->getChild( "z", 1 );
		// 		auto target = m_bullet_raycast1->getChild( "target", 1 );
		// 		m_raycast_target_x1 = target->getChild( "x", 1 );
		// 		m_raycast_target_y1 = target->getChild( "y", 1 );
		// 		m_raycast_target_z1 = target->getChild( "z", 1 );
		// 	}
		// 	{
		// 		auto source = m_bullet_raycast2->getChild( "source", 1 );
		// 		m_raycast_source_x2 = source->getChild( "x", 1 );
		// 		m_raycast_source_y2 = source->getChild( "y", 1 );
		// 		m_raycast_source_z2 = source->getChild( "z", 1 );
		// 		auto target = m_bullet_raycast2->getChild( "target", 1 );
		// 		m_raycast_target_x2 = target->getChild( "x", 1 );
		// 		m_raycast_target_y2 = target->getChild( "y", 1 );
		// 		m_raycast_target_z2 = target->getChild( "z", 1 );
		// 	}
		// 	{
		// 		auto source = m_bullet_raycast3->getChild( "source", 1 );
		// 		m_raycast_source_x3 = source->getChild( "x", 1 );
		// 		m_raycast_source_y3 = source->getChild( "y", 1 );
		// 		m_raycast_source_z3 = source->getChild( "z", 1 );
		// 		auto target = m_bullet_raycast3->getChild( "target", 1 );
		// 		m_raycast_target_x3 = target->getChild( "x", 1 );
		// 		m_raycast_target_y3 = target->getChild( "y", 1 );
		// 		m_raycast_target_z3 = target->getChild( "z", 1 );
		// 	}
		// 	{
		// 		auto source = m_bullet_raycast4->getChild( "source", 1 );
		// 		m_raycast_source_x4 = source->getChild( "x", 1 );
		// 		m_raycast_source_y4 = source->getChild( "y", 1 );
		// 		m_raycast_source_z4 = source->getChild( "z", 1 );
		// 		auto target = m_bullet_raycast4->getChild( "target", 1 );
		// 		m_raycast_target_x4 = target->getChild( "x", 1 );
		// 		m_raycast_target_y4 = target->getChild( "y", 1 );
		// 		m_raycast_target_z4 = target->getChild( "z", 1 );
		// 	}
  // 
		// 	m_raycasters = addChild( "raycasters", new BEntity() );
		// 	m_raycasters->addChild( "external_raycaster", new BEntity_external() )->set( m_bullet_raycast1 );
		// 	m_raycasters->addChild( "external_raycaster", new BEntity_external() )->set( m_bullet_raycast2 );
		// 	m_raycasters->addChild( "external_raycaster", new BEntity_external() )->set( m_bullet_raycast3 );
		// 	m_raycasters->addChild( "external_raycaster", new BEntity_external() )->set( m_bullet_raycast4 );
		// }

// 		// MOUSE PICKERS
// 			auto mousepicker1 = getChild("thread1", 1)->getChild("Critterding", 1)->getChild("physicsworld", 1)->addChild( "mousepicker", "Bullet_MousePicker" );
// 			auto mousepicker2 = getChild("thread2", 1)->getChild("Critterding", 1)->getChild("physicsworld", 1)->addChild( "mousepicker", "Bullet_MousePicker" );
// 			auto mousepicker3 = getChild("thread3", 1)->getChild("Critterding", 1)->getChild("physicsworld", 1)->addChild( "mousepicker", "Bullet_MousePicker" );
// 			auto mousepicker4 = getChild("thread4", 1)->getChild("Critterding", 1)->getChild("physicsworld", 1)->addChild( "mousepicker", "Bullet_MousePicker" );
// 		
// 			auto mousepickers = addChild( "mousepickers", new BEntity() );
// 			mousepickers->addChild( "external_mousepicker", new BEntity_external() )->set( mousepicker1 );
// 			mousepickers->addChild( "external_mousepicker", new BEntity_external() )->set( mousepicker2 );
// 			mousepickers->addChild( "external_mousepicker", new BEntity_external() )->set( mousepicker3 );
// 			mousepickers->addChild( "external_mousepicker", new BEntity_external() )->set( mousepicker4 );

		// FORCE IMGUI
			// topParent()->getChild( "lib", 1 )->addChild("Translate_QT_IMGUI", "Translate_QT_IMGUI");
	}

	BEntity* Scene::getServer( const unsigned int row, const unsigned int column, const unsigned int rows, const unsigned int columns )
	{
		unsigned int thread_counter(1);
		for ( unsigned int current_row(0); current_row < rows; ++current_row )
		{
			
			for ( unsigned int current_column(0); current_column < columns; ++current_column )
			{
				if ( current_row == row && current_column == column )
				{
					// find current thread
						std::stringstream thread_name_ss;
						thread_name_ss << "thread" << thread_counter;
						
					return getChild( thread_name_ss.str().c_str(), 1 )->getChild("Critterding", 1);
				}
				++thread_counter;
			}
		}
		
	}

	void Scene::process()
	{
// 		// std::cout << "a" << std::endl;
// 		// CAST RAY FROM MOUSE
// 			auto camera_position = m_camera->m_transform->m_transform.getOrigin();
// 
// 			m_raycast_source_x1->set( camera_position.x() );
// 			m_raycast_source_y1->set( camera_position.y() );
// 			m_raycast_source_z1->set( camera_position.z() );
// 			m_raycast_source_x2->set( camera_position.x() );
// 			m_raycast_source_y2->set( camera_position.y() );
// 			m_raycast_source_z2->set( camera_position.z() );
// 			m_raycast_source_x3->set( camera_position.x() );
// 			m_raycast_source_y3->set( camera_position.y() );
// 			m_raycast_source_z3->set( camera_position.z() );
// 			m_raycast_source_x4->set( camera_position.x() );
// 			m_raycast_source_y4->set( camera_position.y() );
// 			m_raycast_source_z4->set( camera_position.z() );
// 
// 			btVector3 rayDirection = m_camera->getScreenDirection( m_win_width->get_int(), m_win_height->get_int(), m_mouse_x->get_int(), m_mouse_y->get_int() );
// 			m_raycast_target_x1->set( rayDirection.x() );
// 			m_raycast_target_y1->set( rayDirection.y() );
// 			m_raycast_target_z1->set( rayDirection.z() );
// 			m_raycast_target_x2->set( rayDirection.x() );
// 			m_raycast_target_y2->set( rayDirection.y() );
// 			m_raycast_target_z2->set( rayDirection.z() );
// 			m_raycast_target_x3->set( rayDirection.x() );
// 			m_raycast_target_y3->set( rayDirection.y() );
// 			m_raycast_target_z3->set( rayDirection.z() );
// 			m_raycast_target_x4->set( rayDirection.x() );
// 			m_raycast_target_y4->set( rayDirection.y() );
// 			m_raycast_target_z4->set( rayDirection.z() );
// 			
// 			m_bullet_raycast1->process();
// 			m_bullet_raycast2->process();
// 			m_bullet_raycast3->process();
// 			m_bullet_raycast4->process();
	}

	BEntity* Server::findCritter( BEntity* e1, BEntity* e2 )
	{
		for_all_children_of2( m_critter_unit_container )
		{
			
			auto critter = dynamic_cast<CdCritter*>( *child2 );
			if ( critter )
			{
				if ( critter->m_bodyparts_shortcut == 0 )
				{
					critter->m_bodyparts_shortcut = critter->getChild( "external_body", 1 )->get_reference()->getChild( "body_fixed1", 1 )->getChild( "bodyparts", 1 );
				}

				for_all_children_of3( critter->m_bodyparts_shortcut )
				{
					if ( (*child3)->get_reference() == e1 || (*child3)->get_reference() == e2 )
					{
						return (*child2);
					}
				}
			}
		}

		return 0;
	}
	
	// FIXME like findCritter above
	BEntity* Server::findFood( BEntity* e1, BEntity* e2 )
	{
		for_all_children_of2( m_food_unit_container )
		{
			auto bp = (*child2)->getChild( "external_physics", 1 )->get_reference();
			if ( bp == e1 || bp == e2 )
			{
				return (*child2);
			}
		}

		return 0;
	}
	
	
// ---- FACTORIES
	enum CLASS
	{
		  PLUGIN_INFO
		, SCENE
		, CRITTERDING_THREADS
		, CD_CRITTER_THREAD_MESHER
	};

	extern "C" BEntity* create( BEntity* parent, const Buint type )
	{
		// PLUGIN DESCRIPTION ENTITY
			if ( type == PLUGIN_INFO )
			{
				BClassesHelper i;
					i.addClass( parent, CLASS::SCENE, "Scene" );
					i.addClass( parent, CLASS::CRITTERDING_THREADS, "Critterding" );
					i.addClass( parent, CLASS::CD_CRITTER_THREAD_MESHER, "CdCritterThreadMesher" );
				return 0;
			}

		// ENTITIES
			else
			{
				BEntity* i(0);

				if ( type == CLASS::SCENE )
					i = new Scene();
				else if ( type == CLASS::CRITTERDING_THREADS )
					i = new Scene();
				else if ( type == CLASS::CD_CRITTER_THREAD_MESHER )
					i = new CdCritterThreadMesher();

				return i;
			}
	}

	extern "C" void destroy( BEntity* p )
	{
		delete p;
	}
	
