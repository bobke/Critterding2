#include "plugin.h"
#include "kernel/be_lib_handler.h"
#include "food_system.h"
#include "body_system.h"
#include "species_system.h"
#include "critter_system.h"
#include "control_panel.h"
#include "population_controller.h"
#include "critter_exchanger.h"
#include "commands.h"
#include "plugins/be_plugin_opengl/be_entity_camera.h"
#include <iostream>

	void Scene::construct()
	{
		// LOAD QT APP FIXME THIS DOESN'T NEED TO GET ONTO THE TREE
			pluginManager()->load( "qt6", "src/plugins/be_plugin_qt6", "be_plugin_qt6" );
			auto spawner = addChild( "spawner", "QApplicationSpawner" );
			auto t_parent_to_add_to = spawner->getChildCustom( this );
			removeChild( spawner );
		
		pluginManager()->load( "app_admin_window", "src/plugins/be_plugin_app_admin_window", "be_plugin_app_admin_window" );
		pluginManager()->load( "app_sysmon", "src/plugins/be_plugin_app_sysmon", "be_plugin_app_sysmon" );

		// t_parent_to_add_to->addChild( "Admin App", "AdminWindow" );
		// t_parent_to_add_to->addChild( "sysmon", "SystemMonitor" );

		auto sdl_window = addChild("Critterding", new Critterding())->getChild("SDL GLWindow");
		sdl_window->set("on_close_destroy_entity", this);
	}
	
	void Critterding::construct()
	{
		std::cout << "Scene::construct()" << std::endl;

		// settings
			auto settings = addChild( "settings", new BEntity() );
			m_eat_transfer_energy = settings->addChild( "eat_energy_transfer", new BEntity_float() );
			m_eat_transfer_energy->set( 100.0f );

		
		pluginManager()->load( "system", "src/plugins/be_plugin_system", "be_plugin_system" );
		pluginManager()->load( "sdl", "src/plugins/be_plugin_sdl", "be_plugin_sdl" );
		pluginManager()->load( "opengl", "src/plugins/be_plugin_opengl", "be_plugin_opengl" );
		pluginManager()->load( "bullet", "src/plugins/be_plugin_bullet", "be_plugin_bullet" );
		pluginManager()->load( "brainz", "src/plugins/be_plugin_brainz", "be_plugin_brainz" );
		pluginManager()->load( "qwt", "src/plugins/be_plugin_qwt", "be_plugin_qwt" ); // FIXME

		// // TIMER
		// 	addChild( "timer", "BTimer" );

		// RANDOM NUMBER GENERATOR
			auto rng = addChild( "random_number_generator", "Brng" );

		// SEED
			// FIXME FIX TIMER
			// auto startTimeMs = topParent()->getChild("sys", 1)->getChild( "timer",1 )->?? ;
			rng->set( "seed", Bint( 111 ) );
		
		// BULLET PHYSICS
			m_physics_world = addChild( "physicsworld", "PhysicsWorld" );
			m_physics_world_collisions = m_physics_world->getChild( "collisions", 1 );
			// m_physics_world->setFps(60);

		// SDL & OPENGL
			auto glscene = addChild( "SDL GLWindow", "SDLWindow" );
			// glscene->setFps(60);
			
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
			transform->getChild( "position_y" )->set( -15.0f );
			transform->getChild( "position_z" )->set( -88.0f );
			transform->getChild( "rotation_euler_x" )->set( 0.0f );
			transform->getChild( "rotation_euler_y" )->set( 0.0f );
			transform->getChild( "rotation_euler_z" )->set( 0.0f );
			
		// COMMANDS
			auto commands = glscene->addChild( "commands", new BEntity() );
			auto launchAdminWindow = commands->addChild( "launchAdminWindow", new cmd_launchAdminWindow() );
			auto launchControlPanel = commands->addChild( "launchControlPanel", new cmd_launchControlPanel() );
			auto launchSystemMonitor = commands->addChild( "launchSystemMonitor", new cmd_launchSystemMonitor() );
			auto launchSelectionWindow = commands->addChild( "launchSelectionWindow", new cmd_launchSelectionWindow() );

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
			
			light->getChild( "model_ambient_r", 1 )->set( 0.2f );
			light->getChild( "model_ambient_g", 1 )->set( 0.2f );
			light->getChild( "model_ambient_b", 1 )->set( 0.2f );
			light->getChild( "model_ambient_a", 1 )->set( 0.0f );
			
			light->getChild( "color_ambient_r", 1 )->set( 0.2f );
			light->getChild( "color_ambient_g", 1 )->set( 0.2f );
			light->getChild( "color_ambient_b", 1 )->set( 0.2f );
			light->getChild( "color_ambient_a", 1 )->set( 0.0f );
			
			light->getChild( "color_diffuse_r", 1 )->set( 0.2f );
			light->getChild( "color_diffuse_g", 1 )->set( 0.2f );
			light->getChild( "color_diffuse_b", 1 )->set( 0.2f );
			light->getChild( "color_diffuse_a", 1 )->set( 0.0f );

			light->getChild( "color_specular_r", 1 )->set( 0.2f );
			light->getChild( "color_specular_g", 1 )->set( 0.2f );
			light->getChild( "color_specular_b", 1 )->set( 0.2f );
			light->getChild( "color_specular_a", 1 )->set( 0.0f );
		}

		// MAP
		{
			auto map = addChild( "map", new BEntity() );
			// const char* map_location = "../share/modules/cube-floor-100-1.obj";
			const char* map_location = "../share/modules/easy.obj";
			// const char* map_location = "../share/modules/medium.obj";
			// const char* map_location = "../share/modules/hard.obj";

			// PHYSICS map
			auto physics_entity = m_physics_world->addChild( "physics_entity_map", "PhysicsEntity" );
				// physics_entity->set("filename", map_location);
				physics_entity->getChild( "filename", 1 )->set( map_location );
				map->addChild( "external_physics", new BEntity_external() )->set(physics_entity);

				auto physics_scale_x = physics_entity->addChild("scale_x", new BEntity_float_property());
				auto physics_scale_y = physics_entity->addChild("scale_y", new BEntity_float_property());
				auto physics_scale_z = physics_entity->addChild("scale_z", new BEntity_float_property());
					// physics_scale_x->set( 1.25f );
					// physics_scale_y->set( 1.0f );
					// physics_scale_z->set( 1.25f );
					physics_scale_x->set( 6.0f );
					physics_scale_y->set( 10.0f );
					physics_scale_z->set( 10.0f );

			// GRAPHICS
				// map
				auto t_graphicsModel = t_graphicsModelSystem->addChild("graphics_entity_map", "GraphicsModel");
				t_graphicsModel->addChild( "filename", new BEntity_string_property() )->set( map_location );
				auto graphics_transform = t_graphicsModel->addChild("transform", "Transform");
				// t_graphicsModel->set("filename", map_location);
				map->addChild( "external_graphics", new BEntity_external() )->set(t_graphicsModel);

			// CONNECT AND POSITION
				auto physics_entity_transform = physics_entity->getChild("transform", 1);
				if ( physics_entity_transform )
				{
					physics_entity_transform->getChild("position_x", 1)->set( 0.0f );
					physics_entity_transform->getChild("position_y", 1)->set( -20.0f );
					physics_entity_transform->getChild("position_z", 1)->set( -100.0f );
					// physics_entity_transform->getChild("rotation_euler_x", 1)->set( 0.0f );
					// physics_entity_transform->getChild("rotation_euler_y", 1)->set( 0.0f ); // FIXME IF 0 TRANSFORM NOT SET
					// physics_entity_transform->getChild("rotation_euler_z", 1)->set( 0.0f );

					physics_scale_x->connectServerServer( graphics_transform->getChild("scale_x", 1) );
					physics_scale_y->connectServerServer( graphics_transform->getChild("scale_y", 1) );
					physics_scale_z->connectServerServer( graphics_transform->getChild("scale_z", 1) );
					
					// graphics_transform->getChild("scale_x", 1)->set( 1.25f );
					// graphics_transform->getChild("scale_y", 1)->set( 1.0f );
					// graphics_transform->getChild("scale_z", 1)->set( 1.25f );
					graphics_transform->getChild("scale_x", 1)->set( 6.0f );
					graphics_transform->getChild("scale_y", 1)->set( 10.0f );
					graphics_transform->getChild("scale_z", 1)->set( 10.0f );

					// CONNECT
					physics_entity_transform->connectServerServer( graphics_transform );
					physics_entity_transform->onUpdate();
				}
		}

// 		// MAP 2
// 		{
// 			auto map = addChild( "map", new BEntity() );
// 			const char* map_location = "../share/modules/easy.obj";
// 			// const char* map_location = "/projects/critterding-beta14/share/critterding/maps/planet-sphere/planet2.obj";
// 			// const char* map_location = "/projects/critterding-beta14/share/critterding/maps/planet/terraria_altrock3.obj";
// 			// const char* map_location = "/projects/bengine-new/share/sandbox/models/Medieval/Medieval_City.obj";
// 			// PHYSICS map
// 			auto physics_entity = m_physics_world->addChild( "physics_entity_map", "PhysicsEntity" );
// 				physics_entity->set("filename", map_location);
// 				map->addChild( "external_physics", new BEntity_external() )->set(physics_entity);
// 
// 				auto physics_scale_x = physics_entity->addChild("scale_x", new BEntity_float_property());
// 				auto physics_scale_y = physics_entity->addChild("scale_y", new BEntity_float_property());
// 				auto physics_scale_z = physics_entity->addChild("scale_z", new BEntity_float_property());
// 				physics_scale_x->set( 8.0f );
// 				physics_scale_y->set( 8.0f );
// 				physics_scale_z->set( 15.0f );
// 			// GRAPHICS
// 				// map
// 				auto t_graphicsModel = t_graphicsModelSystem->addChild("graphics_entity_map", "GraphicsModel");
// 				auto graphics_transform = t_graphicsModel->addChild("transform", "Transform");
// 				t_graphicsModel->set("filename", map_location);
// 				map->addChild( "external_graphics", new BEntity_external() )->set(t_graphicsModel);
// 
// 				graphics_transform->getChild("scale_x", 1)->set( 8.0f );
// 				graphics_transform->getChild("scale_y", 1)->set( 8.0f );
// 				graphics_transform->getChild("scale_z", 1)->set( 15.0f );
// 			
// 			// CONNECT AND POSITION
// 				auto physics_entity_transform = physics_entity->getChild("transform", 1);
// 				if ( physics_entity_transform )
// 				{
// 					physics_entity_transform->getChild("position_x", 1)->set( 0.0f );
// 					physics_entity_transform->getChild("position_y", 1)->set( -19.0f );
// 					physics_entity_transform->getChild("position_z", 1)->set( -100.0f );
// 					// CONNECT
// 					physics_entity_transform->connectServerServer( graphics_transform );
// 					physics_entity_transform->onUpdate();
// 				}
// 				
// 		}

		// skydome
			auto t_graphicsModelSkyDome = t_graphicsModelSystem->addChild("GraphicsModel_SkyDome", "GraphicsModel");
			// t_graphicsModelSkyDome->getChild("active", 1)->set( false );

			
			t_graphicsModelSkyDome->set("filename", "../share/modules/skydome3.obj");
			// t_graphicsModelSkyDome->set("filename", "/projects/critterding-beta14/share/critterding/skies/round/skydome3.obj");


		// BRAINZ SYSTEM
			auto brain_system = addChild( "brain_system", "BrainSystem" );

		// BODY SYSTEM
			auto body_system = addChild( "body_system", new BodySystem() );
			// auto body_system = addChild( "body_system", "CdBodySystem" );

		// CRITTER SYSTEM
			// auto critter_system = addChild( "critter_system", "CdCritterSystem" );
			auto critter_system = addChild( "critter_system", new CdCritterSystem() );
			m_critter_unit_container = critter_system->getChild( "unit_container", 1 );

		// FOOD SYSTEM
			// auto food_system = addChild( "food_system", "CdFoodSystem" );
			auto food_system = addChild( "food_system", new CdFoodSystem() );
			
			m_food_unit_container = food_system->getChild( "unit_container", 1 );

		// RAYCAST
			m_bullet_raycast = m_physics_world->addChild( "raycaster", "Bullet_Raycast" );
			auto source = m_bullet_raycast->getChild( "source", 1 );
			m_raycast_source_x = source->getChild( "x", 1 );
			m_raycast_source_y = source->getChild( "y", 1 );
			m_raycast_source_z = source->getChild( "z", 1 );
			auto target = m_bullet_raycast->getChild( "target", 1 );
			m_raycast_target_x = target->getChild( "x", 1 );
			m_raycast_target_y = target->getChild( "y", 1 );
			m_raycast_target_z = target->getChild( "z", 1 );

			
		// // CONTROL PANEL
			// auto control_panel = addChild( "control_panel", new CdControlPanel() );
			
		// POPULATION CONTROLLER
			addChild( "CdPopulationController", new CdPopulationController() );

		// CRITTER EXCHANGER
			addChild( "CdCritterExchanger", new CdCritterExchanger() );
			
// 		// BODY SETTINGS
// 			auto body_settings = addChild( "body_settings", new BEntity() );
// 			body_settings->addChild( "mutation_chance", new BEntity_uint() )->set( Buint(20) );
// 			body_settings->addChild( "bodypart_min", new BEntity_uint() )->set( Buint(3) );
// 			body_settings->addChild( "bodypart_max", new BEntity_uint() )->set( Buint(7) );
// 			body_settings->addChild( "eye_min", new BEntity_uint() )->set( Buint(1) );
// 			body_settings->addChild( "eye_max", new BEntity_uint() )->set( Buint(1) );
// 			body_settings->addChild( "spike_min", new BEntity_uint() )->set( Buint(0) );
// 			body_settings->addChild( "spike_max", new BEntity_uint() )->set( Buint(1) );
	}

	void Critterding::process()
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

		// CAST RAY FROM MOUSE
			auto camera_position = m_camera->m_transform->m_transform.getOrigin();
			m_raycast_source_x->set( camera_position.x() );
			m_raycast_source_y->set( camera_position.y() );
			m_raycast_source_z->set( camera_position.z() );

			btVector3 rayDirection = m_camera->getScreenDirection( m_win_width->get_int(), m_win_height->get_int(), m_mouse_x->get_int(), m_mouse_y->get_int() );
			m_raycast_target_x->set( rayDirection.x() );
			m_raycast_target_y->set( rayDirection.y() );
			m_raycast_target_z->set( rayDirection.z() );
			
			m_bullet_raycast->process();

	}

	BEntity* Critterding::findCritter( BEntity* e1, BEntity* e2 )
	{
		BEntity* critter_bp( e1 );
		if ( e2->name() == "bodypart_central" )
		{
			critter_bp = e2;
		}
		for_all_children_of2( m_critter_unit_container )
		{
			for_all_children_of3( (*child2)->getChild( "external_body", 1 )->get_reference()->getChild( "body_fixed1", 1 )->getChild( "bodyparts", 1 ) )
			{
				if ( (*child3)->get_reference() == critter_bp )
				{
					return (*child2);
				}
			}
		}
		return 0;
	}
	
	BEntity* Critterding::findFood( BEntity* e1, BEntity* e2 )
	{
		BEntity* food_bp( e1 );
		if ( e2->name() == "physics_entity_food" )
		{
			food_bp = e2;
		}
		for_all_children_of2( m_food_unit_container )
		{
			if ( (*child2)->getChild( "external_physics", 1 )->get_reference() == food_bp )
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
		, CRITTERDING
		, CD_CONTROL_PANEL
		, CD_POPULATION_CONTROL
		, CD_CRITTER_EXCHANGER
		, CD_CRITTER_SYSTEM
		, CD_SPECIES_SYSTEM
		, CD_CRITTER
		, CD_FOOD_SYSTEM
		, CD_FOOD
		, CD_BODY_SYSTEM
		, CD_BODY // FIXME REMOVE LEGACY
		, CD_BODY_FIXED1
	};

	extern "C" BEntity* create( BEntity* parent, const Buint type )
	{
		// PLUGIN DESCRIPTION ENTITY
			if ( type == PLUGIN_INFO )
			{
				BClassesHelper i;
					i.addClass( parent, CLASS::SCENE, "Scene" );
					i.addClass( parent, CLASS::CRITTERDING, "Critterding" );
					i.addClass( parent, CLASS::CD_CONTROL_PANEL, "CdControlPanel" );
					i.addClass( parent, CLASS::CD_POPULATION_CONTROL, "CdPopulationController" );
					i.addClass( parent, CLASS::CD_CRITTER_EXCHANGER, "CdCritterExchanger" );
					i.addClass( parent, CLASS::CD_CRITTER_SYSTEM, "CdCritterSystem" );
					i.addClass( parent, CLASS::CD_SPECIES_SYSTEM, "CdSpeciesSystem" );
					i.addClass( parent, CLASS::CD_CRITTER, "CdCritter" );
					i.addClass( parent, CLASS::CD_FOOD_SYSTEM, "CdFoodSystem" );
					i.addClass( parent, CLASS::CD_FOOD, "CdFood" );
					i.addClass( parent, CLASS::CD_BODY_SYSTEM, "CdBodySystem" );
					i.addClass( parent, CLASS::CD_BODY, "CdBody" );
					i.addClass( parent, CLASS::CD_BODY_FIXED1, "BodyFixed1" );
				return 0;
			}

		// ENTITIES
			else
			{
				BEntity* i(0);

				if ( type == CLASS::SCENE )
					i = new Scene();
				else if ( type == CLASS::CRITTERDING )
					i = new Critterding();
				else if ( type == CLASS::CD_CONTROL_PANEL )
					i = new CdControlPanel();
				else if ( type == CLASS::CD_POPULATION_CONTROL )
					i = new CdPopulationController();
				else if ( type == CLASS::CD_CRITTER_EXCHANGER )
					i = new CdCritterExchanger();
				else if ( type == CLASS::CD_CRITTER_SYSTEM )
					i = new CdCritterSystem();
				else if ( type == CLASS::CD_SPECIES_SYSTEM )
					i = new CdSpeciesSystem();
				else if ( type == CLASS::CD_CRITTER )
					i = new CdCritter();
				else if ( type == CLASS::CD_FOOD_SYSTEM )
					i = new CdFoodSystem();
				else if ( type == CLASS::CD_FOOD )
					i = new CdFood();
				else if ( type == CLASS::CD_BODY_SYSTEM )
					i = new BodySystem();
				else if ( type == CLASS::CD_BODY )
					i = new BEntity();
				else if ( type == CLASS::CD_BODY_FIXED1 )
					i = new BodyFixed1();

				return i;
			}
	}

	extern "C" void destroy( BEntity* p )
	{
		delete p;
	}
	
