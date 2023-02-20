#include "be_config_libraries.h"
#include "kernel/be_lib_handler.h"
// #include "kernel/be_entity_core_types.h"
#include "kernel/be_plugin_base_entity_types.h"
// #include "kernel/be_profiler.h"
#include <iostream>
#include <sstream>

	void BConfigLibraries::construct()
	{
		// LOAD REQUIRED LIBS
		pluginManager()->load( "basetypes", "src/kernel", "be_base_entity_types" );
		// pluginManager()->load( "vulkan", "src/plugins/be_plugin_vulkan", "be_plugin_vulkan" );
// 		pluginManager()->load( "thread", "src/plugins/be_plugin_thread", "be_plugin_thread" );

		// RANDOM TESTING LIBS
		// pluginManager()->load( "test", "src/plugins/be_plugin_test", "be_plugin_test" );
		pluginManager()->load( "sdl", "src/plugins/be_plugin_sdl", "be_plugin_sdl" );
		pluginManager()->load( "bullet", "src/plugins/be_plugin_bullet", "be_plugin_bullet" );
		
		pluginManager()->load( "system_monitor", "src/plugins/be_plugin_app_sysmon", "be_plugin_app_sysmon" );
		// pluginManager()->load( "attractors", "src/plugins/be_plugin_app_attractors", "be_plugin_app_attractors" );
		// pluginManager()->load( "critterding", "src/plugins/be_plugin_app_critterding", "be_plugin_app_critterding" );
		
		// SYSTEM MONITOR
		// FIXME seems it hangs, multiple qt inits?
// 		pluginManager()->load( "sysmon", "src/plugins/be_plugin_app_sysmon", "be_plugin_app_sysmon" );
// 		addChild( "System Monitor", "sysmon", "Scene" );
// 		auto t_qtapp = getChild( "QT Application" );

		// CREATE A WINDOW
// 		auto t_qtapp = parent()->getChild("BConfigLibraries QT Application", 1); // FIXME THIS HAS TO WORK

		// if we couldn't find a our qt application then assume one already exists
		// FIXME we'll need a system for this
		BEntity* qwindow;
		qwindow = addChild( "ConfigLibraries", "QMainWindow" );
		qwindow->addChild( "title", "string_property" )->set("ConfigLibraries");
		qwindow->addChild( "x", "uint_property" )->set(Buint(1100));
		qwindow->addChild( "y", "uint_property" )->set(Buint(30));
		qwindow->addChild( "width", "uint_property" )->set(Buint(500));
		qwindow->addChild( "height", "uint_property" )->set(Buint(400));
		qwindow->set("on_close_destroy_entity", this);

		// CREATE MENUS
		auto menu_file = qwindow->addChild( "menu_file", "QMenu" );
		menu_file->addChild( "title", "string_property" )->set("&File");

			// ACTION
			auto action_open = menu_file->addChild( "action_open", "QAction" );
			action_open->addChild( "title", "string_property" )->set("&Open");

			// COMMAND
			auto command_open = action_open->addChild("command_load_entity", new BEntity_trigger());
			auto target_parent = command_open->addChild("parent", new BEntity_reference());
			target_parent->set( qwindow );
			auto class_id = command_open->addChild("class_id", new BEntity_string());
			class_id->set( "ConfigLibraries" );

			// CONNECT COMMANDS
			action_open->connectServerServer(command_open);
			// // COMMAND
			// auto command = actions->addChild("load_entity", new BEntity_reference() ); // FIXME INTO A REFERENCE TO THE CONCERNING OBJECT
			// command->set(entity);
			// auto layout_target = command->addChild("layout_target", new BEntity_reference() ); // FIXME INTO A REFERENCE TO THE CONCERNING OBJECT
			// layout_target->set(vboxlayout_entity);

			auto general_layout_H = qwindow->addChild( "QT HBoxlayout", "QVBoxLayout" );
		
		// CREATE LEFT ENTITIES
			auto entity_groupbox = general_layout_H->addChild( "Entity Groupbox", "QGroupBox" );
			entity_groupbox->addChild( "title", "string_property" )->set("Libraries");
			auto groupVbox = entity_groupbox->addChild( "QT VBoxlayout", "QVBoxLayout" );
// 			auto edit = groupVbox->addChild( "edit test", "QLineEdit" );
			// ENTITIES
			{
				add_config_libraries_groupbox( groupVbox, topParent()->getChild("Libraries", 1) );
			}


// 				// RIGHT BOX (MDI)
// 				{
// 					// MDI AREA
// 					{
// 						auto mdi_area = general_layout_H->addChild("mdi area", "QMdiArea");
// 						auto subwindow = mdi_area->addChild("admin subwindow", "QMdiWindow" );
// 						auto subwindowlayout = subwindow->addChild( "QT HBoxlayout", "QHBoxLayout" );
// 
// 						add_admin_entity_groupbox(subwindowlayout, topParent());
// 
// 						// ADD VIEWPORT TO MDIAREA
// 							auto viewport = subwindowlayout->addChild("viewport", "QGraphicsView");
// 							auto viewscene = viewport->addChild("viewscene", "QGraphicsScene");
// 					}
// 				}
			

// 		auto general_layout_V = general_layout_H->addChild( "QT VBoxlayout", "QVBoxLayout" );
// 		general_layout_V->addChild("droppable label", "QLabelDroppable")->set("text", "drop here");
		
// 		auto general_layout_V = general_layout_H->addChild( "QT VBoxlayout", "QVBoxLayout" );
// 		auto topfiller = general_layout_V->addChild( "topfiller", "QWidget" );
// 		auto infolabel = general_layout_V->addChild( "infolabel", "QLabel" );
// 		auto bottomfiller = general_layout_V->addChild( "bottomfiller", "QWidget" );
// 		auto general_layout_H = general_layout_V->addChild( "QT HBoxlayout", "QHBoxLayout" );

	}

	// GROUPBOX OF ENTITIES
	void BConfigLibraries::add_config_libraries_groupbox( BEntity* parent, BEntity* entity )
	{
		// GROUPBOX
			auto groupbox_entities = parent->addChild("qt groupbox entities", "QGroupBox" );
				// groupbox_entities->set("title", entity->name().c_str());
			// VBOX
				auto vboxlayout_entities = groupbox_entities->addChild("qt vboxlayout", "QVBoxLayout" );

		// ENTITY LIST
			add_config_libraries_list( vboxlayout_entities, entity );
	
	}
	// GROUPBOX OF ENTITIES
	void BConfigLibraries::add_config_libraries_list( BEntity* parent, BEntity* entity )
	{
// 		// GROUPBOX
// 			auto groupbox_entities = parent->addChild("qt groupbox entities", "qt5_groupbox" );
// 				groupbox_entities->set(entity->name());
// 
// 			// VBOX
// 				auto vboxlayout_entities = groupbox_entities->addChild("qt vboxlayout", "qt5_vboxlayout" );
	
				// ADD EACH CHILD TO VBOX
					for_all_children_of( entity )
					{
						add_config_libraries_item( parent, *child );
					}
					
	}
	
	void BConfigLibraries::add_config_libraries_item( BEntity* parent, BEntity* entity )
	{
		if ( entity->name() != "_command_buffer" /*&& entity->name() != "Libraries"*/ )
		{
			// VBOX (for expanding into)
			// CONSTRUCT UNIQUE NAME for removal purpuses
			// FORMAT : "admin_section_(id)_(name)"
				std::stringstream stream;
				stream << "admin_section_" << entity->id() << "_" << entity->name();
	// 								std::cout << "opening " << stream.str() << std::endl;
			
			// SPAWN VBOX TO EXPAND INTO with unique name
				auto vboxlayout_entity = parent->addChild(stream.str(), "QVBoxLayout" );

			// HBOX
			{
				auto hboxlayout_entity = vboxlayout_entity->addChild("qt hboxlayout", "QHBoxLayout" );

	// 								// OPEN WINDOW
	// 								{
	// 									auto button_add = hboxlayout_entity->addChild("qt button", "QPushButton" );
	// 									button_add->set( "text", "W" );
	// 
	// 									// COMMAND
	// 										auto actions = button_add->addChild("_commands", new BEntity() );
	// 										auto command = actions->addChild("admin_entity_window_open", new BEntity_reference() ); // FIXME INTO A REFERENCE TO THE CONCERNING OBJECT
	// 										command->set(entity);
	// 								}

				// EXPAND & COLLAPSE (command will change to collapse when command is ran)
				{
					auto button_add = hboxlayout_entity->addChild("admin_button_expand", "QPushButton" );
					auto checkbox_loaded = hboxlayout_entity->addChild("admin_button_expand", "QCheckBox" );
					
					// CHECKBOX TOGGLE
					// if ( entity->hasChildren() )
					{
						// checkbox_loaded->set( "text", "+" );

						// COMMAND
							// auto actions = checkbox_loaded->addChild("_commands", new BEntity() );
							// auto command = actions->addChild("admin_entity_group_expand", new BEntity_reference() ); // FIXME INTO A REFERENCE TO THE CONCERNING OBJECT
							// command->set(entity);
							// auto layout_target = command->addChild("layout_target", new BEntity_reference() ); // FIXME INTO A REFERENCE TO THE CONCERNING OBJECT
							// layout_target->set(vboxlayout_entity);
					}
					
					
					// CHILDREN
					if ( entity->hasChildren() )
					{
						button_add->set( "text", "+" );

						// COMMAND
							auto actions = button_add->addChild("_commands", new BEntity() );
							auto command = actions->addChild("admin_entity_group_expand", new BEntity_reference() ); // FIXME INTO A REFERENCE TO THE CONCERNING OBJECT
							command->set(entity);
							auto layout_target = command->addChild("layout_target", new BEntity_reference() ); // FIXME INTO A REFERENCE TO THE CONCERNING OBJECT
							layout_target->set(vboxlayout_entity);
					}
					else
					{
						// REFERENCE & EXTERNAL
						if ( dynamic_cast<BEntity_reference*>( entity ) )
						{
								button_add->set( "text", "+" );

							// COMMAND
								auto actions = button_add->addChild("_commands", new BEntity() );
								auto command = actions->addChild("admin_entity_group_expand", new BEntity_reference() ); // FIXME INTO A REFERENCE TO THE CONCERNING OBJECT
								command->set( entity->get_reference() );
								auto layout_target = command->addChild("layout_target", new BEntity_reference() ); // FIXME INTO A REFERENCE TO THE CONCERNING OBJECT
								layout_target->set(vboxlayout_entity);
						}
						else
						{
							button_add->set( "text", " " );
						}
					}
				}

	// 								// DROPPABLE LABEL & SET ID
	// 								{
	// 									auto label = hboxlayout_entity->addChild("button_expand", "QPushButton" );
	// // 									auto label = hboxlayout_entity->addChild("qt label", "qt5_label_droppable" );
	// 									
	// 									std::stringstream childid;
	// 									childid << entity->id();
	// 									
	// 									label->set( "text", childid.str().c_str() );
	// 
	// 									// reference to adminned entity
	// 										label->addChild( "reference", new BEntity_reference() )->set( *child );
	// 								}

				// DROPPABLE LABEL & SET NAME
				{
	// 									auto label = hboxlayout_entity->addChild("qt label", "QPushButton" );
	// 									auto label = hboxlayout_entity->addChild("qt label", "QPushButtonDraggable" );
					auto label = hboxlayout_entity->addChild("qt label", "QPushButtonDragAndDroppable" );
					// std::cout << entity->name().c_str() << std::endl;
					label->set( "text", entity->name().c_str() );
					label->set( "width", Buint(350) );

					// drag and drop= reference to adminned entity
					label->addChild( "reference", new BEntity_reference() )->set( entity );

					// UINT // FIXME LINEEDIT
						auto t_uint = dynamic_cast<BEntity_uint*>( entity );
						if ( t_uint )
						{
							auto edit = hboxlayout_entity->addChild( "value_lineedit", "QLineEdit" );
							edit->set( "width", Buint(80) );
							edit->set( "height", Buint(14) );
							edit->set( t_uint->get_uint() );
							t_uint->connectServerServer( edit );
							edit->connectServerServer( t_uint );
						}

					// INT
						auto t_int = dynamic_cast<BEntity_int*>( entity );
						if ( t_int )
						{
							auto edit = hboxlayout_entity->addChild( "value_lineedit", "QLineEdit_int" );
							edit->set( "width", Buint(80) );
							edit->set( "height", Buint(14) );
							edit->set( t_int->get_int() );
							t_int->connectServerServer( edit );
							edit->connectServerServer( t_int );
						}

					// FLOAT
						auto t_float = dynamic_cast<BEntity_float*>( entity );
						if ( t_float )
						{
							auto edit = hboxlayout_entity->addChild( "value_lineedit", "QLineEdit_float" );
							edit->set( "width", Buint(80) );
							edit->set( "height", Buint(14) );
							edit->set( t_float->get_float() );
							t_float->connectServerServer( edit );
							edit->connectServerServer( t_float );
						}

					// FLOAT_PROPERTY
						auto t_floatp = dynamic_cast<BEntity_float_property*>( entity );
						if ( t_floatp )
						{
							auto edit = hboxlayout_entity->addChild( "value_lineedit", "QLineEdit_float" );
							edit->set( "width", Buint(80) );
							edit->set( "height", Buint(14) );
							edit->set( t_floatp->get_float() );
							t_floatp->connectServerServer( edit );
							edit->connectServerServer( t_floatp );
						}
						
					// STRING // FIXME???
						auto t_string = dynamic_cast<BEntity_string*>( entity );
						if ( t_string )
						{
							auto edit = hboxlayout_entity->addChild( "value_lineedit", "QLineEdit_string" );
							edit->set( "width", Buint(80) );
							edit->set( "height", Buint(14) );
							edit->set( t_string->get_float() );
							t_string->connectServerServer( edit );
							edit->connectServerServer( t_string );
						}

	// 									auto t_float = dynamic_cast<BEntity_float*>( *child );
	// 									if ( t_float )
	// 									{
	// 										auto edit = hboxlayout_entity->addChild( "value_lineedit", "QLineEdit" );
	// 										edit->set( "width", Buint(80) );
	// 										edit->set( "height", Buint(14) );
	// 										auto value_property = edit->addChild( "value", new BEntity_float_property() );
	// 										value_property->set( entity->get_float() );
	// // 										entity->connectServerServer( value_property );
	// 										value_property->connectServerServer( *child );
	// 									}
					
				}

				// RM
				{
					auto button = hboxlayout_entity->addChild("qt button", "QPushButton" );
					button->set("text", "R");

					// COMMAND
						auto actions = button->addChild("_commands", new BEntity() );
						auto command = actions->addChild("remove", new BEntity_reference() ); // FIXME INTO A REFERENCE TO THE CONCERNING OBJECT
						command->set(entity);

	// 										auto cmd_remove = button->addChild("remove", new BEntity_reference() );
	// 										cmd_remove->set(entity);
	// 										button->connectServerServer(cmd_remove);
				}

				// COPY
				{
					auto button = hboxlayout_entity->addChild("qt button", "QPushButton" );
					button->set("text", "C");

					// COMMAND
						auto actions = button->addChild("_commands", new BEntity() );
						auto command = actions->addChild("copy", new BEntity_reference() ); // FIXME INTO A REFERENCE TO THE CONCERNING OBJECT
						command->set(entity);
				}

				// SAVE
				{
					auto button = hboxlayout_entity->addChild("qt button", "QPushButton" );
					button->set("text", "S");

					// COMMAND
						auto actions = button->addChild("_commands", new BEntity() );
						auto command = actions->addChild("save", new BEntity_reference() ); // FIXME INTO A REFERENCE TO THE CONCERNING OBJECT
						command->set(entity);
				}

			}
		}
	}	
