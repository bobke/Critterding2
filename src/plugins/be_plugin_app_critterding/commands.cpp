#include "commands.h"
#include <iostream>
 
	bool cmd_launchAdminWindow::set()
	{
		if ( !getAdminWindow() )
		{
			auto qt_app = topParent()->getChild( "Scene", 1 )->getChild( "QT Application", 2 );
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
		auto qt_app = topParent()->getChild( "Scene", 1 )->getChild( "QT Application", 2 );
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
		auto qt_app = topParent()->getChild( "Scene", 1 )->getChild( "QT Application", 2 );
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
			auto scene = topParent()->getChild( "Scene", 1 );
			if ( scene )
			{
				auto cd_app = scene->getChild( "Critterding", 1 );
				if ( cd_app )
				{
					auto raycaster = cd_app->getChild( "physicsworld", 1 )->getChild( "raycaster", 1 );
					if ( raycaster )
					{
						auto hit_entity = raycaster->getChild( "hit_entity", 1 );
						if ( hit_entity )
						{
							if ( hit_entity->get_reference() != 0 )
							{
								// CRITTER
									BEntity* selectedEntity(0);
									if ( hit_entity->get_reference()->name() == "bodypart_central" || hit_entity->get_reference()->name() == "bodypart_left" |hit_entity->get_reference()->name() == "bodypart_right" )
									{
										auto unit_container = cd_app->getChild( "critter_system", 1 )->getChild( "unit_container", 1 );
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
										auto unit_container = cd_app->getChild( "food_system", 1 )->getChild( "unit_container", 1 );
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
									// LAUNCH ADMIN WINDO
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
		}
		return false;
	}
