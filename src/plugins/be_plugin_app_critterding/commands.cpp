#include "commands.h"
#include "plugins/be_plugin_bullet/bullet3/src/LinearMath/btVector3.h"
// #include <iostream>
 
	bool cmd_launchAdminWindow::set()
	{
		if ( !getAdminWindow() )
		{
			auto bin = topParent()->getChild( "bin", 1 );
			auto qt_app = bin->getChild( "QT Application", 2 );
			
			// if ( !qt_app )
			// {
			// 	// LOAD QT APP FIXME THIS DOESN'T NEED TO GET ONTO THE TREE
			// 		auto spawner = bin->addChild( "spawner", "QApplicationSpawner" );
			// 		auto t_parent_to_add_to = spawner->getChildCustom( bin );
			// 		bin->removeChild( spawner );
			// }
			
			if ( qt_app )
			{
				qt_app->addChild( "Admin App", "AdminWindow" );
				return true;
			}
		}
		return false;
	}

	bool cmd_launchControlPanel::set()
	{
		auto qt_app = topParent()->getChild( "bin", 1 )->getChild( "QT Application", 2 );
		if ( qt_app )
		{
			if ( !qt_app->getChild( "CdControlPanel", 1 ) )
			{
				qt_app->addChild( "CdControlPanel", "CdControlPanel" );
			}
			return true;
		}
		return false;
	}

	bool cmd_launchSystemMonitor::set()
	{
		auto qt_app = topParent()->getChild( "bin", 1 )->getChild( "QT Application", 2 );
		if ( qt_app )
		{
			if ( !qt_app->getChild( "SystemMonitor", 1 ) )
			{
				qt_app->addChild( "SystemMonitor", "SystemMonitor" );
			}
			return true;
		}
		return false;
	}

	bool cmd_launchSelectionWindow::set()
	{
		if ( getAdminWindow() )
		{
			auto scene = topParent()->getChild( "bin", 1 );
			if ( scene )
			{
				auto cd_app = scene->getChild( "Critterding", 1 );
				if ( cd_app )
				{
					// FIND HIT ENTITY
						BEntity* hit_entity(0);

						// single thread
							auto external_raycaster = cd_app->getChild( "external_raycaster", 1 );
							if ( external_raycaster )
							{
								hit_entity = external_raycaster->get_reference()->getChild( "hit_entity", 1 );
							}

						// 4 thread
							auto raycasters = cd_app->getChild( "raycasters", 1 );
							if ( raycasters )
							{
								float shortest( 0.0f );
								for_all_children_of( raycasters )
								{
									auto source_entity = (*child)->get_reference()->getChild( "source", 1 );
									btVector3 hit_source_vector( source_entity->getChild( "x", 1 )->get_float(), source_entity->getChild( "y", 1 )->get_float(), source_entity->getChild( "z", 1 )->get_float() );
									auto hit_position_entity = (*child)->get_reference()->getChild( "hit_position", 1 );
									btVector3 hit_position_vector( hit_position_entity->getChild( "x", 1 )->get_float(), hit_position_entity->getChild( "y", 1 )->get_float(), hit_position_entity->getChild( "z", 1 )->get_float() );
									auto distance = hit_source_vector.distance( hit_position_vector );

									if ( distance < shortest || shortest == 0.0f )
									{
										hit_entity = (*child)->get_reference()->getChild( "hit_entity", 1 );
										shortest = distance;
									}
								}
							}

					if ( hit_entity != 0 )
					{
						if ( hit_entity->get_reference() != 0 )
						{
							// CRITTER
								BEntity* selectedEntity(0);
								if ( hit_entity->get_reference()->name() == "bodypart_central" || hit_entity->get_reference()->name() == "bodypart_left" || hit_entity->get_reference()->name() == "bodypart_right" )
								{
									auto critter_system = hit_entity->parent()->parent()->parent()->getChild( "critter_system", 1 );
									auto unit_container = critter_system->getChild( "unit_container", 1 );
									if ( unit_container )
									{
										for_all_children_of2( unit_container )
										{
											if ( selectedEntity != 0 )
												break;

											for_all_children_of3( (*child2)->getChild( "external_body", 1 )->get_reference()->getChild( "body_fixed1", 1 )->getChild( "bodyparts", 1 ) )
											{
												if ( (*child3)->get_reference() == hit_entity->get_reference() )
												{
													selectedEntity = *child2;
												}
											}
										}
									}
								}

							// FOOD
								else if ( hit_entity->get_reference()->name() == "physics_entity_food" )
								{
									auto food_system = hit_entity->parent()->parent()->parent()->getChild( "food_system", 1 );

									auto unit_container = food_system->getChild( "unit_container", 1 );
									if ( unit_container )
									{
										for_all_children_of2( unit_container )
										{
											if ( selectedEntity != 0 )
												break;

											if ( (*child2)->getChild( "external_physics", 1 )->get_reference() == hit_entity->get_reference() )
											{
												selectedEntity = *child2;
											}
										}
									}
								}

							// // MAP
							// 	else if ( hit_entity->get_reference()->name() == "physics_entity_map" )
							// 	{
							// 		auto map = cd_app->getChild( "map", 1 );
							// 		if ( map )
							// 		{
							// 			if ( map->getChild( "external_physics", 1 )->get_reference() == hit_entity->get_reference() )
							// 			{
							// 				selectedEntity = map;
							// 			}
							// 		}
							// 	}
	// 
							// // REST
							// 	else
							// 	{
							// 		selectedEntity = hit_entity->get_reference();
							// 	}

							if ( selectedEntity )
							{
								// LAUNCH ADMIN WINDOW
									// if ( !getAdminWindow() )
									// {
									// 	auto qt_app = scene->getChild( "QT Application", 2 );
									// 	if ( qt_app )
									// 	{
									// 		qt_app->addChild( "Admin App", "AdminWindow" );
									// 	}
									// }

								// ADD COMMMAND TO BUFFER
									auto cmdbuffer = topParent()->getChild("_command_buffer", 1);
									if ( cmdbuffer )
									{
										auto cmdref = cmdbuffer->addChild("admin_entity_open_window", new BEntity_reference() ); // FIXME make this a reference when adding to the actions too
										// cmdref->set( hit_entity->get_reference() );
										cmdref->set( selectedEntity );
									}
							}
						}
					}
				}
			}
		}
		return false;
	}

	bool cmd_mousePickBody::set()
	{
		auto scene = topParent()->getChild( "bin", 1 );
		if ( scene )
		{
			auto cd_app = scene->getChild( "Critterding", 1 );
			if ( cd_app )
			{
				
				// single thread
					auto mousepicker = cd_app->getChild( "external_mousepicker", 1 );
					if ( mousepicker )
					{
						mousepicker->get_reference()->set( true );
						return true;
					}

				// 4 thread
					auto mousepickers = cd_app->getChild( "mousepickers", 1 );
					BEntity* shortest_raycaster( 0 );
					if ( mousepickers )
					{
						auto raycasters = cd_app->getChild( "raycasters", 1 );
						if ( raycasters )
						{
							float shortest( 0.0f );
							for_all_children_of( raycasters )
							{
								auto source_entity = (*child)->get_reference()->getChild( "source", 1 );
								btVector3 hit_source_vector( source_entity->getChild( "x", 1 )->get_float(), source_entity->getChild( "y", 1 )->get_float(), source_entity->getChild( "z", 1 )->get_float() );
								auto hit_position_entity = (*child)->get_reference()->getChild( "hit_position", 1 );
								btVector3 hit_position_vector( hit_position_entity->getChild( "x", 1 )->get_float(), hit_position_entity->getChild( "y", 1 )->get_float(), hit_position_entity->getChild( "z", 1 )->get_float() );
								auto distance = hit_source_vector.distance( hit_position_vector );
		
								if ( distance < shortest || shortest == 0.0f )
								{
									shortest_raycaster = (*child)->get_reference();
									shortest = distance;
								}
							}
						}
					}
				
					if ( shortest_raycaster != 0 )
					{
						// std::cout << "shortest raycaster: " << shortest_raycaster->id() << " " << shortest_raycaster->name()  << std::endl;
						
						auto mousepicker = shortest_raycaster->parent()->getChild( "mousepicker", 1 );
						if ( mousepicker )
						{
							mousepicker->set( true );
							return true;
						}
					}
				
				
				// auto mousepicker = cd_app->getChild( "physicsworld", 1 )->getChild( "mousepicker", 1 );
				// if ( mousepicker )
				// {
				// 	mousepicker->set( true );
				// 	return true;
				// }
				return true;
			}
		}
		return false;
	}

	bool cmd_mouseUnpickBody::set()
	{
		auto scene = topParent()->getChild( "bin", 1 );
		if ( scene )
		{
			auto cd_app = scene->getChild( "Critterding", 1 );
			if ( cd_app )
			{
				// single thread
					auto mousepicker = cd_app->getChild( "external_mousepicker", 1 );
					if ( mousepicker )
					{
						mousepicker->get_reference()->set( false );
						return true;
					}

					// auto mousepicker = cd_app->getChild( "physicsworld", 1 )->getChild( "mousepicker", 1 );
					// if ( mousepicker )
					// {
					// 	mousepicker->set( false );
					// 	return true;
					// }
			}
		}
		return false;
	}
	
