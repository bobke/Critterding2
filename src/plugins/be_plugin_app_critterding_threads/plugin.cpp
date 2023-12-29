#include "plugin.h"
#include "kernel/be_lib_handler.h"
#include "plugins/be_plugin_opengl/be_entity_camera.h"
// #include "plugins/be_plugin_app_critterding/critter_system.h"
#include "plugins/be_plugin_app_critterding/food_system.h"
#include "plugins/be_plugin_app_critterding/commands.h"
#include "plugins/be_plugin_bullet/be_entity_physics_entity.h"
#include "plugins/be_plugin_bullet/be_entity_transform.h" // FIXME work this away
// #include <iostream>

// 	void Scene::construct()
// 	{
// 		// LOAD QT APP FIXME THIS DOESN'T NEED TO GET ONTO THE TREE
// 			pluginManager()->load( "qt6", "src/plugins/be_plugin_qt6", "be_plugin_qt6" );
// 			auto spawner = addChild( "spawner", "QApplicationSpawner" );
// 			auto t_parent_to_add_to = spawner->getChildCustom( this );
// 			removeChild( spawner );
// 		
// 		pluginManager()->load( "app_admin_window", "src/plugins/be_plugin_app_admin_window", "be_plugin_app_admin_window" );
// 		pluginManager()->load( "app_sysmon", "src/plugins/be_plugin_app_sysmon", "be_plugin_app_sysmon" );
// 
// 		// t_parent_to_add_to->addChild( "Admin App", "AdminWindow" );
// 		// t_parent_to_add_to->addChild( "sysmon", "SystemMonitor" );
// 
// 		auto sdl_window = addChild("Critterding", new Critterding_threads())->getChild("SDL GLWindow");
// 		sdl_window->set("on_close_destroy_entity", this);
// 	}
	
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
		pluginManager()->load( "sdl", "src/plugins/be_plugin_sdl", "be_plugin_sdl" );
		pluginManager()->load( "opengl", "src/plugins/be_plugin_opengl", "be_plugin_opengl" );
		pluginManager()->load( "bullet", "src/plugins/be_plugin_bullet", "be_plugin_bullet" );
		pluginManager()->load( "brainz", "src/plugins/be_plugin_brainz", "be_plugin_brainz" );
		pluginManager()->load( "qwt", "src/plugins/be_plugin_qwt", "be_plugin_qwt" );
		pluginManager()->load( "thread", "src/plugins/be_plugin_thread", "be_plugin_thread" );

		// SDL & OPENGL
			auto glscene = addChild( "SDL GLWindow", "SDLWindow" );
			// glscene->setFps(60);
			glscene->addChild("OpenGL_Setup", "OpenGL_Setup");

			m_win_width = glscene->getChild( "width", 1 );
			m_win_height = glscene->getChild( "height", 1 );
			m_mouse_x = glscene->getChild( "mouse_x", 1 );
			m_mouse_y = glscene->getChild( "mouse_y", 1 );

			// SDL SWAPBUFFER, making sure this runs right after sdl_window and it's children are done processing
				addChild("SDLSwapBuffers", "SDLSwapBuffers");
			
			auto t_graphicsModelSystem = glscene->addChild("GraphicsModelSystem", "GraphicsModelSystem");
			glscene->set("on_close_destroy_entity", this);

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
			auto commands = glscene->addChild( "commands", new BEntity() );
			auto launchAdminWindow = commands->addChild( "launchAdminWindow", new cmd_launchAdminWindow() );
			auto launchControlPanel = commands->addChild( "launchControlPanel", new cmd_launchControlPanel() );
			auto launchSystemMonitor = commands->addChild( "launchSystemMonitor", new cmd_launchSystemMonitor() );
			auto launchSelectionWindow = commands->addChild( "launchSelectionWindow", new cmd_launchSelectionWindow() );
			auto mousePickBody = commands->addChild( "mousePickBody", new cmd_mousePickBody() );
			auto mouseUnpickBody = commands->addChild( "mouseUnpickBody", new cmd_mouseUnpickBody() );

		// BINDINGS
			auto bindings = glscene->getChild( "bindings", 1 );

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

		// LIGHT
		{
			auto light = t_graphicsModelSystem->addChild( "light", "GLLight" );
			
			light->getChild( "model_ambient_r", 1 )->set( 0.5f );
			light->getChild( "model_ambient_g", 1 )->set( 0.5f );
			light->getChild( "model_ambient_b", 1 )->set( 0.5f );
			light->getChild( "model_ambient_a", 1 )->set( 0.0f );
			
			light->getChild( "color_ambient_r", 1 )->set( 0.5f );
			light->getChild( "color_ambient_g", 1 )->set( 0.5f );
			light->getChild( "color_ambient_b", 1 )->set( 0.5f );
			light->getChild( "color_ambient_a", 1 )->set( 0.0f );
			
			light->getChild( "color_diffuse_r", 1 )->set( 0.4f );
			light->getChild( "color_diffuse_g", 1 )->set( 0.4f );
			light->getChild( "color_diffuse_b", 1 )->set( 0.4f );
			light->getChild( "color_diffuse_a", 1 )->set( 0.0f );

			light->getChild( "color_specular_r", 1 )->set( 0.2f );
			light->getChild( "color_specular_g", 1 )->set( 0.2f );
			light->getChild( "color_specular_b", 1 )->set( 0.2f );
			light->getChild( "color_specular_a", 1 )->set( 0.0f );
		}

		// GRAPHICS MAP
		{
			auto map = addChild( "graphics_map", new BEntity() );
			const char* map_location = "../share/modules/easy.obj";
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
			addChild("SDLSwapBuffers", "SDLSwapBuffers");

		// SERVERS
			auto thread1 = addChild("thread1", "thread");
			// auto thread1 = addChild("thread1", new BEntity());
			auto thread2 = addChild("thread2", "thread");
			auto server1 = thread1->addChild( "Critterding", new Server() );
			auto server2 = thread2->addChild( "Critterding", new Server() );
			
			const float spacing( 2.0f );
			server1->getChild("food_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("size_x", 1)->set( 100.0f );
			server2->getChild("food_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("size_x", 1)->set( 100.0f );
			server2->getChild("food_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("position_x", 1)->set( 0.0f );

			server1->getChild("food_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("size_x", 1)->set( 100.0f - 0.5f*spacing );
			server2->getChild("food_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("size_x", 1)->set( 100.0f - 0.5f*spacing );
			server2->getChild("food_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("position_x", 1)->set( 0.0f + 0.5f*spacing );

			const float critter_spacing( 1.0f );
			server1->getChild("critter_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("size_x", 1)->set( 100.0f );
			server2->getChild("critter_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("size_x", 1)->set( 100.0f );
			server2->getChild("critter_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("position_x", 1)->set( 0.0f );

			server1->getChild("critter_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("size_x", 1)->set( 100.0f - 0.5f*critter_spacing );
			server2->getChild("critter_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("size_x", 1)->set( 100.0f - 0.5f*critter_spacing );
			server2->getChild("critter_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("position_x", 1)->set( 0.0f + 0.5f*critter_spacing );
			
			// CRITTER AND FOOD SETTINGS
			server1->getChild("critter_system", 1)->getChild("settings", 1)->getChild( "minimum_number_of_units", 1)->set( uint( 20/2 ) );
			server2->getChild("critter_system", 1)->getChild("settings", 1)->getChild( "minimum_number_of_units", 1)->set( uint( 20/2 ) );
			server1->getChild("food_system", 1)->getChild("settings", 1)->getChild( "number_of_units", 1)->set( uint( 1500/2 ) );
			server2->getChild("food_system", 1)->getChild("settings", 1)->getChild( "number_of_units", 1)->set( uint( 1500/2 ) );
			
			// CRITTER THREAD MESHERS
				// 1 : X moves RIGHT to 2
				auto mesher1 = server1->addChild( "thread_mesher", "CdCritterThreadMesher" );
				mesher1->getChild( "x_active", 1 )->set( true );
				mesher1->getChild( "x_border", 1 )->set( 0.1f );
				mesher1->getChild( "x_direction_is_right", 1 )->set( true );
				mesher1->getChild( "x_target", 1 )->set( server2->getChild("critter_system", 1)->getChild("unit_container", 1) );

				// 2 : X moves LEFT  to 1
				auto mesher2 = server2->addChild( "thread_mesher", "CdCritterThreadMesher" );
				mesher2->getChild( "x_active", 1 )->set( true );
				mesher2->getChild( "x_border", 1 )->set( -0.1f );
				mesher2->getChild( "x_direction_is_right", 1 )->set( false );
				mesher2->getChild( "x_target", 1 )->set( server1->getChild("critter_system", 1)->getChild("unit_container", 1) );
			
			// SERVERS 3 AND 4 
			if ( true )
			{
				auto thread3 = addChild("thread3", "thread");
				auto thread4 = addChild("thread4", "thread");
				auto server3 = thread3->addChild( "Critterding", new Server() );
				auto server4 = thread4->addChild( "Critterding", new Server() );
				
				server1->getChild("food_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("size_x", 1)->set( 100.0f - 0.5f*spacing );
				server1->getChild("food_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("size_z", 1)->set( 70.0f - 0.5f*spacing );
				server2->getChild("food_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("size_x", 1)->set( 100.0f - 0.5f*spacing );
				server2->getChild("food_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("size_z", 1)->set( 70.0f - 0.5f*spacing );
				server3->getChild("food_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("size_x", 1)->set( 100.0f - 0.5f*spacing );
				server3->getChild("food_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("size_z", 1)->set( 70.0f - 0.5f*spacing );
				server4->getChild("food_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("size_x", 1)->set( 100.0f - 0.5f*spacing );
				server4->getChild("food_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("size_z", 1)->set( 70.0f - 0.5f*spacing );
	
				server2->getChild("food_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("position_x", 1)->set( 0.0f + 0.5f*spacing );
				server3->getChild("food_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("position_z", 1)->set( -100.0f + 0.5f*spacing );
				server4->getChild("food_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("position_x", 1)->set( 0.0f + 0.5f*spacing );
				server4->getChild("food_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("position_z", 1)->set( -100.0f + 0.5f*spacing );		
				
				server1->getChild("critter_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("size_x", 1)->set( 100.0f - 0.5f*critter_spacing );
				server1->getChild("critter_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("size_z", 1)->set( 70.0f - 0.5f*critter_spacing );
				server2->getChild("critter_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("size_x", 1)->set( 100.0f - 0.5f*critter_spacing );
				server2->getChild("critter_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("size_z", 1)->set( 70.0f - 0.5f*critter_spacing );
				server3->getChild("critter_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("size_x", 1)->set( 100.0f - 0.5f*critter_spacing );
				server3->getChild("critter_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("size_z", 1)->set( 70.0f - 0.5f*critter_spacing );
				server4->getChild("critter_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("size_x", 1)->set( 100.0f - 0.5f*critter_spacing );
				server4->getChild("critter_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("size_z", 1)->set( 70.0f - 0.5f*critter_spacing );
	
				server2->getChild("critter_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("position_x", 1)->set( 0.0f + 0.5f*critter_spacing );
				server3->getChild("critter_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("position_z", 1)->set( -100.0f + 0.5f*critter_spacing );
				server4->getChild("critter_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("position_x", 1)->set( 0.0f + 0.5f*critter_spacing );
				server4->getChild("critter_system", 1)->getChild("settings", 1)->getChild("dropzone", 1)->getChild("position_z", 1)->set( -100.0f + 0.5f*critter_spacing );
				
				// CRITTER AND FOOD SETTINGS
				// server1->getChild("critter_system", 1)->getChild("settings", 1)->getChild( "minimum_number_of_units", 1)->set( uint( 1 ) );
				// server2->getChild("critter_system", 1)->getChild("settings", 1)->getChild( "minimum_number_of_units", 1)->set( uint( 1 ) );
				// server3->getChild("critter_system", 1)->getChild("settings", 1)->getChild( "minimum_number_of_units", 1)->set( uint( 1 ) );
				// server4->getChild("critter_system", 1)->getChild("settings", 1)->getChild( "minimum_number_of_units", 1)->set( uint( 1 ) );
				server1->getChild("critter_system", 1)->getChild("settings", 1)->getChild( "minimum_number_of_units", 1)->set( uint( 20/4 ) );
				server2->getChild("critter_system", 1)->getChild("settings", 1)->getChild( "minimum_number_of_units", 1)->set( uint( 20/4 ) );
				server3->getChild("critter_system", 1)->getChild("settings", 1)->getChild( "minimum_number_of_units", 1)->set( uint( 20/4 ) );
				server4->getChild("critter_system", 1)->getChild("settings", 1)->getChild( "minimum_number_of_units", 1)->set( uint( 20/4 ) );

				// server1->getChild("food_system", 1)->getChild("settings", 1)->getChild( "number_of_units", 1)->set( uint( 130 ) );
				// server2->getChild("food_system", 1)->getChild("settings", 1)->getChild( "number_of_units", 1)->set( uint( 130 ) );
				// server3->getChild("food_system", 1)->getChild("settings", 1)->getChild( "number_of_units", 1)->set( uint( 130 ) );
				// server4->getChild("food_system", 1)->getChild("settings", 1)->getChild( "number_of_units", 1)->set( uint( 130 ) );
				server1->getChild("food_system", 1)->getChild("settings", 1)->getChild( "number_of_units", 1)->set( uint( 1500/4 ) );
				server2->getChild("food_system", 1)->getChild("settings", 1)->getChild( "number_of_units", 1)->set( uint( 1500/4 ) );
				server3->getChild("food_system", 1)->getChild("settings", 1)->getChild( "number_of_units", 1)->set( uint( 1500/4 ) );
				server4->getChild("food_system", 1)->getChild("settings", 1)->getChild( "number_of_units", 1)->set( uint( 1500/4 ) );
				
				
				// CRITTER THREAD MESHERS
				{
					// 1 : Y moves DOWN to 3
					mesher1->getChild( "z_active", 1 )->set( true );
					mesher1->getChild( "z_border", 1 )->set( -99.9f );
					mesher1->getChild( "z_direction_is_down", 1 )->set( true );
					mesher1->getChild( "z_target", 1 )->set( server3->getChild("critter_system", 1)->getChild("unit_container", 1) );

					// 2 : Y moves DOWN to 4
					mesher2->getChild( "z_active", 1 )->set( true );
					mesher2->getChild( "z_border", 1 )->set( -99.9f );
					mesher2->getChild( "z_direction_is_down", 1 )->set( true );
					mesher2->getChild( "z_target", 1 )->set( server4->getChild("critter_system", 1)->getChild("unit_container", 1) );

					// 3 : X moves RIGHT to 4 Y moves UP to 1
					auto mesher3 = server3->addChild( "thread_mesher", "CdCritterThreadMesher" );
					mesher3->getChild( "x_active", 1 )->set( true );
					mesher3->getChild( "x_border", 1 )->set( 0.1f );
					mesher3->getChild( "x_direction_is_right", 1 )->set( true );
					mesher3->getChild( "x_target", 1 )->set( server4->getChild("critter_system", 1)->getChild("unit_container", 1) );

					mesher3->getChild( "z_active", 1 )->set( true );
					mesher3->getChild( "z_border", 1 )->set( -100.1f );
					mesher3->getChild( "z_direction_is_down", 1 )->set( false );
					mesher3->getChild( "z_target", 1 )->set( server1->getChild("critter_system", 1)->getChild("unit_container", 1) );

					// 4 : X moves LEFT to 3 Y moves up to 2
					auto mesher4 = server4->addChild( "thread_mesher", "CdCritterThreadMesher" );
					mesher4->getChild( "x_active", 1 )->set( true );
					mesher4->getChild( "x_border", 1 )->set( -0.1f );
					mesher4->getChild( "x_direction_is_right", 1 )->set( false );
					mesher4->getChild( "x_target", 1 )->set( server3->getChild("critter_system", 1)->getChild("unit_container", 1) );

					mesher4->getChild( "z_active", 1 )->set( true );
					mesher4->getChild( "z_border", 1 )->set( -100.1f );
					mesher4->getChild( "z_direction_is_down", 1 )->set( false );
					mesher4->getChild( "z_target", 1 )->set( server2->getChild("critter_system", 1)->getChild("unit_container", 1) );
				}			
				
			}
			
			// THREADS FINISH
				addChild("threads_finish", "threads_finish");
			
		// RAYCAST
		{
			m_bullet_raycast1 = getChild("thread1", 1)->getChild("Critterding", 1)->getChild("physicsworld", 1)->addChild( "raycaster", "Bullet_Raycast" );
			m_bullet_raycast2 = getChild("thread2", 1)->getChild("Critterding", 1)->getChild("physicsworld", 1)->addChild( "raycaster", "Bullet_Raycast" );
			m_bullet_raycast3 = getChild("thread3", 1)->getChild("Critterding", 1)->getChild("physicsworld", 1)->addChild( "raycaster", "Bullet_Raycast" );
			m_bullet_raycast4 = getChild("thread4", 1)->getChild("Critterding", 1)->getChild("physicsworld", 1)->addChild( "raycaster", "Bullet_Raycast" );

			{
				auto source = m_bullet_raycast1->getChild( "source", 1 );
				m_raycast_source_x1 = source->getChild( "x", 1 );
				m_raycast_source_y1 = source->getChild( "y", 1 );
				m_raycast_source_z1 = source->getChild( "z", 1 );
				auto target = m_bullet_raycast1->getChild( "target", 1 );
				m_raycast_target_x1 = target->getChild( "x", 1 );
				m_raycast_target_y1 = target->getChild( "y", 1 );
				m_raycast_target_z1 = target->getChild( "z", 1 );
			}
			{
				auto source = m_bullet_raycast2->getChild( "source", 1 );
				m_raycast_source_x2 = source->getChild( "x", 1 );
				m_raycast_source_y2 = source->getChild( "y", 1 );
				m_raycast_source_z2 = source->getChild( "z", 1 );
				auto target = m_bullet_raycast2->getChild( "target", 1 );
				m_raycast_target_x2 = target->getChild( "x", 1 );
				m_raycast_target_y2 = target->getChild( "y", 1 );
				m_raycast_target_z2 = target->getChild( "z", 1 );
			}
			{
				auto source = m_bullet_raycast3->getChild( "source", 1 );
				m_raycast_source_x3 = source->getChild( "x", 1 );
				m_raycast_source_y3 = source->getChild( "y", 1 );
				m_raycast_source_z3 = source->getChild( "z", 1 );
				auto target = m_bullet_raycast3->getChild( "target", 1 );
				m_raycast_target_x3 = target->getChild( "x", 1 );
				m_raycast_target_y3 = target->getChild( "y", 1 );
				m_raycast_target_z3 = target->getChild( "z", 1 );
			}
			{
				auto source = m_bullet_raycast4->getChild( "source", 1 );
				m_raycast_source_x4 = source->getChild( "x", 1 );
				m_raycast_source_y4 = source->getChild( "y", 1 );
				m_raycast_source_z4 = source->getChild( "z", 1 );
				auto target = m_bullet_raycast4->getChild( "target", 1 );
				m_raycast_target_x4 = target->getChild( "x", 1 );
				m_raycast_target_y4 = target->getChild( "y", 1 );
				m_raycast_target_z4 = target->getChild( "z", 1 );
			}

			m_raycasters = addChild( "raycasters", new BEntity() );
			m_raycasters->addChild( "external_raycaster", new BEntity_external() )->set( m_bullet_raycast1 );
			m_raycasters->addChild( "external_raycaster", new BEntity_external() )->set( m_bullet_raycast2 );
			m_raycasters->addChild( "external_raycaster", new BEntity_external() )->set( m_bullet_raycast3 );
			m_raycasters->addChild( "external_raycaster", new BEntity_external() )->set( m_bullet_raycast4 );
		}

		// MOUSE PICKERS
			auto mousepicker1 = getChild("thread1", 1)->getChild("Critterding", 1)->getChild("physicsworld", 1)->addChild( "mousepicker", "Bullet_MousePicker" );
			auto mousepicker2 = getChild("thread2", 1)->getChild("Critterding", 1)->getChild("physicsworld", 1)->addChild( "mousepicker", "Bullet_MousePicker" );
			auto mousepicker3 = getChild("thread3", 1)->getChild("Critterding", 1)->getChild("physicsworld", 1)->addChild( "mousepicker", "Bullet_MousePicker" );
			auto mousepicker4 = getChild("thread4", 1)->getChild("Critterding", 1)->getChild("physicsworld", 1)->addChild( "mousepicker", "Bullet_MousePicker" );
		
			auto mousepickers = addChild( "mousepickers", new BEntity() );
			mousepickers->addChild( "external_mousepicker", new BEntity_external() )->set( mousepicker1 );
			mousepickers->addChild( "external_mousepicker", new BEntity_external() )->set( mousepicker2 );
			mousepickers->addChild( "external_mousepicker", new BEntity_external() )->set( mousepicker3 );
			mousepickers->addChild( "external_mousepicker", new BEntity_external() )->set( mousepicker4 );
		
		// POPULATION CONTROLLER
			auto population_controller = addChild( "CdPopulationController", "CdPopulationController" );
			population_controller->set( "register_critter_container", getChild("thread1", 1)->getChild("Critterding", 1)->getChild("critter_system", 1)->getChild("unit_container", 1) );
			population_controller->set( "register_critter_container", getChild("thread2", 1)->getChild("Critterding", 1)->getChild("critter_system", 1)->getChild("unit_container", 1) );
			population_controller->set( "register_critter_container", getChild("thread3", 1)->getChild("Critterding", 1)->getChild("critter_system", 1)->getChild("unit_container", 1) );
			population_controller->set( "register_critter_container", getChild("thread4", 1)->getChild("Critterding", 1)->getChild("critter_system", 1)->getChild("unit_container", 1) );
			population_controller->set( "register_food_container", getChild("thread1", 1)->getChild("Critterding", 1)->getChild("food_system", 1)->getChild("unit_container", 1) );
			population_controller->set( "register_food_container", getChild("thread2", 1)->getChild("Critterding", 1)->getChild("food_system", 1)->getChild("unit_container", 1) );
			population_controller->set( "register_food_container", getChild("thread3", 1)->getChild("Critterding", 1)->getChild("food_system", 1)->getChild("unit_container", 1) );
			population_controller->set( "register_food_container", getChild("thread4", 1)->getChild("Critterding", 1)->getChild("food_system", 1)->getChild("unit_container", 1) );
			
		// CRITTER EXCHANGER
			addChild( "CdCritterExchanger", "CdCritterExchanger" );
	}

	void Scene::process()
	{
		// std::cout << "a" << std::endl;
		// CAST RAY FROM MOUSE
			auto camera_position = m_camera->m_transform->m_transform.getOrigin();

			m_raycast_source_x1->set( camera_position.x() );
			m_raycast_source_y1->set( camera_position.y() );
			m_raycast_source_z1->set( camera_position.z() );
			m_raycast_source_x2->set( camera_position.x() );
			m_raycast_source_y2->set( camera_position.y() );
			m_raycast_source_z2->set( camera_position.z() );
			m_raycast_source_x3->set( camera_position.x() );
			m_raycast_source_y3->set( camera_position.y() );
			m_raycast_source_z3->set( camera_position.z() );
			m_raycast_source_x4->set( camera_position.x() );
			m_raycast_source_y4->set( camera_position.y() );
			m_raycast_source_z4->set( camera_position.z() );

			btVector3 rayDirection = m_camera->getScreenDirection( m_win_width->get_int(), m_win_height->get_int(), m_mouse_x->get_int(), m_mouse_y->get_int() );
			m_raycast_target_x1->set( rayDirection.x() );
			m_raycast_target_y1->set( rayDirection.y() );
			m_raycast_target_z1->set( rayDirection.z() );
			m_raycast_target_x2->set( rayDirection.x() );
			m_raycast_target_y2->set( rayDirection.y() );
			m_raycast_target_z2->set( rayDirection.z() );
			m_raycast_target_x3->set( rayDirection.x() );
			m_raycast_target_y3->set( rayDirection.y() );
			m_raycast_target_z3->set( rayDirection.z() );
			m_raycast_target_x4->set( rayDirection.x() );
			m_raycast_target_y4->set( rayDirection.y() );
			m_raycast_target_z4->set( rayDirection.z() );
			
			m_bullet_raycast1->process();
			m_bullet_raycast2->process();
			m_bullet_raycast3->process();
			m_bullet_raycast4->process();
		
	}

	BEntity* Server::findCritter( BEntity* e1, BEntity* e2 )
	{
		for_all_children_of2( m_critter_unit_container )
		{
			for_all_children_of3( (*child2)->getChild( "external_body", 1 )->get_reference()->getChild( "body_fixed1", 1 )->getChild( "bodyparts", 1 ) )
			{
				if ( (*child3)->get_reference() == e1 || (*child3)->get_reference() == e2 )
				{
					return (*child2);
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

		// auto c_e1 = dynamic_cast<BPhysicsEntityCube*>( e1 );
		// auto c_e2 = dynamic_cast<BPhysicsEntityCube*>( e2 );
		// if ( c_e1 && c_e2 )
		// {
		// 	BEntity* food_bp( e1 );
		// 	if ( e2->name() == "physics_entity_food" )
		// 	{
		// 		food_bp = e2;
		// 	}
		// 	for_all_children_of2( m_food_unit_container )
		// 	{
		// 		if ( (*child2)->getChild( "external_physics", 1 )->get_reference() == food_bp )
		// 		{
		// 			return (*child2);
		// 		}
		// 	}
		// }

		return 0;
	}	
	
	
// ---- FACTORIES
	enum CLASS
	{
		  PLUGIN_INFO
		, SCENE
		// , CRITTERDING_THREADS
	};

	extern "C" BEntity* create( BEntity* parent, const Buint type )
	{
		// PLUGIN DESCRIPTION ENTITY
			if ( type == PLUGIN_INFO )
			{
				BClassesHelper i;
					i.addClass( parent, CLASS::SCENE, "Scene" );
					// i.addClass( parent, CLASS::CRITTERDING_THREADS, "Critterding_threads" );
				return 0;
			}

		// ENTITIES
			else
			{
				BEntity* i(0);

				if ( type == CLASS::SCENE )
					i = new Scene();
				// else if ( type == CLASS::CRITTERDING_THREADS )
					// i = new Critterding_threads();

				return i;
			}
	}

	extern "C" void destroy( BEntity* p )
	{
		delete p;
	}
	
