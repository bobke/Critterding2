#include "plugin.h"
#include "be_config_libraries.h"
#include "kernel/be_lib_handler.h"
// #include "kernel/be_entity_core_types.h"
#include "kernel/be_plugin_base_entity_types.h"
// #include "kernel/be_profiler.h"
#include <iostream>
#include <sstream>

	void Scene::construct()
	{
		std::cout << "Scene::construct()" << std::endl;

		// // LOAD QT APP
		// 	pluginManager()->load( "qt6", "src/plugins/be_plugin_qt6", "be_plugin_qt6" );
		// 	auto spawner = addChild( "spawner", "QApplicationSpawner" );
		// 	auto t_parent_to_add_to = spawner->getChildCustom( this );
		// 	removeChild( spawner );
  // 
		// // load admin window
		// auto admin_window = t_parent_to_add_to->addChild("Admin App", new BAdminWindow());
  // 
		// // kill the scene when the main window is closed
		// 	auto qmainwindow = admin_window->getChild("QT MainWindow");
		// 	qmainwindow->set("on_close_destroy_entity", this);
	}

	BAdminWindow::~BAdminWindow()
	{
		setAdminWindow( 0 );
	}
	
	void BAdminWindow::construct()
	{
		setAdminWindow( this );
		
		setName( "Admin Window" );
		std::cout << "Scene::construct()" << std::endl;

		// LOAD QT APP FIXME THIS DOESN'T NEED TO GET ONTO THE TREE
		pluginManager()->load( "qt6", "src/plugins/be_plugin_qt6", "be_plugin_qt6" );

			auto spawner = addChild( "spawner", "QApplicationSpawner" );
			// auto t_parent_to_add_to = spawner->getChildCustom( parent() );
			auto t_parent_to_add_to = spawner->getChildCustom( this );
			removeChild( spawner );
		
		
		// LOAD REQUIRED LIBS
		pluginManager()->load( "basetypes", "src/kernel", "be_base_entity_types" );
		// pluginManager()->load( "vulkan", "src/plugins/be_plugin_vulkan", "be_plugin_vulkan" );
// 		pluginManager()->load( "thread", "src/plugins/be_plugin_thread", "be_plugin_thread" );

		// RANDOM TESTING LIBS
		// pluginManager()->load( "test", "src/plugins/be_plugin_test", "be_plugin_test" );
		// pluginManager()->load( "sdl", "src/plugins/be_plugin_sdl", "be_plugin_sdl" );
		// pluginManager()->load( "bullet", "src/plugins/be_plugin_bullet", "be_plugin_bullet" );

		// pluginManager()->load( "test_editing", "src/plugins/be_plugin_test_editing", "be_plugin_test_editing" );
		
		// pluginManager()->load( "system_monitor", "src/plugins/be_plugin_app_sysmon", "be_plugin_app_sysmon" );
		// pluginManager()->load( "attractors", "src/plugins/be_plugin_app_attractors", "be_plugin_app_attractors" );
		// pluginManager()->load( "critterding", "src/plugins/be_plugin_app_critterding", "be_plugin_app_critterding" );
		// pluginManager()->load( "stunt coureur", "src/plugins/be_plugin_app_stunt_coureur", "be_plugin_app_stunt_coureur" );
		
		// SYSTEM MONITOR
		// FIXME seems it hangs, multiple qt inits?
// 		pluginManager()->load( "sysmon", "src/plugins/be_plugin_app_sysmon", "be_plugin_app_sysmon" );
// 		addChild( "System Monitor", "sysmon", "Scene" );
// 		auto t_qtapp = getChild( "QT Application" );

		// CREATE A WINDOW
// 		auto t_qtapp = parent()->getChild("BAdminWindow QT Application", 1); // FIXME THIS HAS TO WORK

		// if we couldn't find a our qt application then assume one already exists
		// FIXME we'll need a system for this
		auto qwindow = addChild( "QT MainWindow", "QMainWindow" );
		qwindow->addChild( "title", "string_property" )->set("Admin Window");
		qwindow->addChild( "x", "uint_property" )->set(Buint(100));
		qwindow->addChild( "y", "uint_property" )->set(Buint(30));
		qwindow->addChild( "width", "uint_property" )->set(Buint(500));
		qwindow->addChild( "height", "uint_property" )->set(Buint(500));
		qwindow->set("on_close_destroy_entity", this);

// 		// CREATE MENUS
// 		auto menu_file = qwindow->addChild( "menu_file", "QMenu" );
// 		menu_file->addChild( "title", "string_property" )->set("&File");
// 
// 			// ACTION
// 			auto action_open = menu_file->addChild( "action_open", "QAction" );
// 			action_open->addChild( "title", "string_property" )->set("&Open");
// 
// 			// COMMAND
// 			auto command_open_config_libraries = action_open->addChild("command_load_entity", new BEntity_trigger());
// 			command_open_config_libraries->addChild("parent", new BEntity_reference())->set( qwindow );
// 			command_open_config_libraries->addChild("class_id", new BEntity_string())->set( "ConfigLibraries" );
// 			
// 			auto command_open_admin_window = addChild("command_load_entity", new BEntity_trigger());
// 			command_open_admin_window->addChild("parent", new BEntity_reference())->set( parent() );
// 			command_open_admin_window->addChild("class_id", new BEntity_string())->set( "AdminWindow" );
// 
// 			// CONNECT COMMANDS
// 			action_open->connectServerServer(command_open_config_libraries);
// 
// 			// // COMMAND
// 			// auto command = actions->addChild("load_entity", new BEntity_reference() );
// 			// command->set(entity);
// 			// auto layout_target = command->addChild("layout_target", new BEntity_reference() );
// 			// layout_target->set(vboxlayout_entity);

			auto general_layout_H = qwindow->addChild( "QT HBoxlayout", "QHBoxLayout" );
		
		// CREATE LEFT ENTITIES
			auto entity_groupbox = general_layout_H->addChild( "Entity Groupbox", "QGroupBox" );
			entity_groupbox->addChild( "title", "string_property" )->set("Entities");
			auto groupVbox = entity_groupbox->addChild( "QT VBoxlayout", "QVBoxLayout" );
// 			auto edit = groupVbox->addChild( "edit test", "QLineEdit" );
			// ENTITIES
			{
				add_admin_entity_groupbox(groupVbox, topParent());
			}
			
			// // RIGHT BOX (MDI)
			// {
			// 	// MDI AREA
			// 	{
			// 		auto mdi_area = general_layout_H->addChild("mdi area", "QMdiArea");
			// 		auto subwindow = mdi_area->addChild("admin subwindow", "QMdiWindow" );
			// 		auto subwindowlayout = subwindow->addChild( "QT HBoxlayout", "QHBoxLayout" );
   // 
			// 		add_admin_entity_groupbox(subwindowlayout, topParent());
   // 
			// 		// ADD VIEWPORT TO MDIAREA
			// 			auto viewport = subwindowlayout->addChild("viewport", "QGraphicsView");
			// 			auto viewscene = viewport->addChild("viewscene", "QGraphicsScene");
			// 	}
			// }


// 		auto general_layout_V = general_layout_H->addChild( "QT VBoxlayout", "QVBoxLayout" );
// 		general_layout_V->addChild("droppable label", "QLabelDroppable")->set("text", "drop here");
		
// 		auto general_layout_V = general_layout_H->addChild( "QT VBoxlayout", "QVBoxLayout" );
// 		auto topfiller = general_layout_V->addChild( "topfiller", "QWidget" );
// 		auto infolabel = general_layout_V->addChild( "infolabel", "QLabel" );
// 		auto bottomfiller = general_layout_V->addChild( "bottomfiller", "QWidget" );
// 		auto general_layout_H = general_layout_V->addChild( "QT HBoxlayout", "QHBoxLayout" );

	}

	bool BAdminWindow::set( const Bstring& id, BEntity* value )
	{
		// std::cout << "BAdminWindow::set " << id << std::endl;

		if ( id == "rm" )
		{
			// update admin items "+" and "-"
			if ( value->parent() && value->parent()->hasAdmin() )
			{
				// if parents numChldren == 1 because this one will be removed from it later, making it 0
				if ( value->parent()->numChildren() == 1 )
				{
					auto search = m_lookup_buffer.m_admin_map.find( value->parent() );
					if ( search != m_lookup_buffer.m_admin_map.end() )
					{
						for( auto i : search->second )
						{
							// it is not expanded
							auto groupbox = i->getChild("qt groupbox entities", 1);
							if ( !groupbox )
							{
								// search for button
								auto hbox = i->getChild("qt hboxlayout", 1);
								if ( hbox )
								{
									auto button_expand = hbox->getChild("admin_button_expand", 1);
									if ( button_expand )
									{
										button_expand->set( "text", " " );

										// find commands
										auto commands = button_expand->getChild("_commands" );
										if ( commands )
										{
											commands->parent()->removeChild(commands);
										}

										// COMMAND
										{
											auto actions = button_expand->addChild("_commands", new BEntity() );
											auto command = actions->addChild("admin_entity_group_expand", new BEntity_reference() );
											command->set( value->parent() );
											auto layout_target = command->addChild("layout_target", new BEntity_reference() );
											layout_target->set( i );
										}
									}
								}
							}
						}
					}
				}
			}

			m_lookup_buffer.removeAdminEntities( value );

			// std::cout << "sizebuffer is now = " << m_lookup_buffer.m_admin_map.size() << std::endl;
		}

		else if ( id == "add" )
		{
			// find parent
			if ( value->parent() )
			{
				auto search = m_lookup_buffer.m_admin_map.find( value->parent() );
				if ( search != m_lookup_buffer.m_admin_map.end() )
				{
					for( auto i : search->second )
					{
						auto groupbox = i->getChild("qt groupbox entities", 1);
						if ( groupbox )
						{
							// std::cout << "g" << std::endl;
							auto vlayout = groupbox->getChild("qt vboxlayout", 1);
							if ( vlayout )
							{
								// std::cout << "add " << value->name() << std::endl;
								add_admin_item( vlayout, value );
								// std::cout << "add done" << std::endl;
								// auto cmdref = m_cmdbuffer->addChild("admin_entity_add", new BEntity_reference() );
								// cmdref->set( child );
								// cmdref->addChild("vlayout", new BEntity_reference() )->set( vlayout );
							}
						}
						else // FIXME
						{
							if ( value->parent()->numChildren() == 1 )
							{
								// entity is not collapsed
								// search for button
								auto qt_hboxlayout = i->getChild("qt hboxlayout", 1);
								if ( qt_hboxlayout )
								{
									auto button_expand = qt_hboxlayout->getChild("admin_button_expand", 1);
									if ( button_expand )
									{
										button_expand->set( "text", "+" );

										// find commands
										auto commands = button_expand->getChild("_commands" );
										if ( !commands )
										{
											commands = button_expand->addChild("_commands", new BEntity() );
											auto command = commands->addChild("admin_entity_group_expand", new BEntity_reference() );
											command->set( value->parent() );
											auto layout_target = command->addChild("layout_target", new BEntity_reference() );
											layout_target->set( i );
										}
				// 
										// // change it's command
										// auto command = commands->getChild("admin_entity_group_contract"); // FIXME INTO A REFERENCE TO THE CONCERNING
										// command->setName("admin_entity_group_expand");
									}
								}
							}
						}
						
					}
				}
			}
			else
			{
				std::cout << "NO PARENT" << std::endl;
			}
		}

		else if ( id == "command_execute" )
		{
			if ( value->name() == "admin_entity_group_expand" || value->name() == "admin_entity_group_contract" )
			{
				// get entity
				auto entity_to_expand = value->get_reference();
				
				// first find given layout
				auto l = value->getChild("layout_target");

				// get layout
				auto layout_to_work_on = l->get_reference();
				// std::cout << "should expand into " << layout_to_work_on->id() << std::endl;

				// get pushbutton
				auto expand_pushbutton_to_change = layout_to_work_on->getChild("admin_button_expand", 100);

				if ( expand_pushbutton_to_change )
				{
					// find commands
					auto commands = expand_pushbutton_to_change->getChild("_commands" );
					
					if ( value->name() == "admin_entity_group_expand" )
					{
						expand_pushbutton_to_change->set("text", "-");

						// change it's command
						auto command = commands->getChild("admin_entity_group_expand"); // FIXME INTO A REFERENCE TO THE CONCERNING
						command->setName("admin_entity_group_contract");
						
						// add groupbox
						add_admin_entity_groupbox(layout_to_work_on, entity_to_expand);
					}
					else // contract is implied
					{
						// - or space, depending on children
						if ( entity_to_expand->numChildren() > 0 )
							expand_pushbutton_to_change->set("text", "+");
						else
							expand_pushbutton_to_change->set("text", " ");

						// change it's command
						auto command = commands->getChild("admin_entity_group_contract"); // FIXME INTO A REFERENCE TO THE CONCERNING
						command->setName("admin_entity_group_expand");

						// remove groupbox
						auto groupbox = layout_to_work_on->getChild("qt groupbox entities", 100);
						layout_to_work_on->removeChild(groupbox);
					}
				}
				
				return true;
			}
			
			else if ( value->name() == "admin_entity_open_window" )
			{
				// get entity
				auto entity = value->get_reference();

				auto qwindow = addChild( "QT MainWindow", "QMainWindow" );
				qwindow->addChild( "title", "string_property" )->set( entity->name().c_str() );
				qwindow->addChild( "x", "uint_property" )->set(Buint(1000));
				qwindow->addChild( "y", "uint_property" )->set(Buint(300));
				qwindow->addChild( "width", "uint_property" )->set(Buint(460));
				qwindow->addChild( "height", "uint_property" )->set(Buint(350));

				auto general_layout_V = qwindow->addChild( "QT VBoxlayout", "QVBoxLayout" );

				{
					auto general_layout_H = general_layout_V->addChild( "QT HBoxlayout", "QHBoxLayout" );

					// ID
						// auto id_label = general_layout_H->addChild( "id_label", "QLabel" );
						// id_label->set( (Buint)entity->id() );

					// CLASS ID
						auto class_id_label = general_layout_H->addChild( "class_id_label", "QLabel" );
						class_id_label->set( entity->class_id() );

					// VALUE FIELDS
						add_admin_genValueFields( general_layout_H, entity );

					// GENERIC BUTTONS
						if ( entity->id() != 0 )
						{
							add_admin_genButtonsWindow( general_layout_H, entity );
						}
				}
				{
					auto general_layout_H = general_layout_V->addChild( "QT HBoxlayout", "QHBoxLayout" );
					
					// CREATE LEFT ENTITIES
						auto entity_groupbox = general_layout_H->addChild( "Entity Groupbox", "QGroupBox" );
						entity_groupbox->addChild( "title", "string_property" )->set("Entities");
						auto groupVbox = entity_groupbox->addChild( "QT VBoxlayout", "QVBoxLayout" );

						add_admin_entity_groupbox(groupVbox, entity);

						m_lookup_buffer.registerAdminEntity( entity, groupVbox );
						m_lookup_buffer.registerAdminEntity( entity, qwindow );
				}

				return true;
			}
			
			else if ( value->name() == "admin_entity_graph" )
			{
				// get entity
				auto entity = value->get_reference();
				
				auto qwindow = addChild( "QT MainWindow", "QMainWindow" );
				qwindow->addChild( "title", "string_property" )->set( "Graph" );
				qwindow->addChild( "x", "uint_property" )->set(Buint(1000));
				qwindow->addChild( "y", "uint_property" )->set(Buint(300));
				qwindow->addChild( "width", "uint_property" )->set(Buint(460));
				qwindow->addChild( "height", "uint_property" )->set(Buint(350));

				auto general_layout_H = qwindow->addChild( "QT HBoxlayout", "QHBoxLayout" );

				auto qwt_plot = general_layout_H->addChild( "plot", "QwtPlot" );

				auto curve = qwt_plot->addChild( "curve", "QwtCurve_Poll" );
				curve->set( "poll_entity", entity );
				// auto curve = qwt_plot->addChild( "curve", "QwtCurve" );
				// entity->connectServerServer( curve );
				
				auto threshold = entity->getChild("firingThreshold", 1);
				if ( threshold )
				{
					auto curve2 = qwt_plot->addChild( "curve", "QwtCurve_Poll" );
					curve2->set( "poll_entity", threshold );
					auto qpen = curve2->addChild( "pen", "QPen" );

					if ( threshold->get_float() > 0.0f )
					{
						qpen->set( "color_r", Buint(0) );
						qpen->set( "color_g", Buint(200) );
						qpen->set( "color_b", Buint(0) );
					}
					else
					{
						qpen->set( "color_r", Buint(200) );
						qpen->set( "color_g", Buint(0) );
						qpen->set( "color_b", Buint(0) );
					}
				}

				m_lookup_buffer.registerAdminEntity( entity, qwindow );

				return true;
			}
			
			else if ( value->name() == "admin_entity_add" )
			{
				// get entity
				auto entity = value->get_reference();
				auto vlayout = value->getChild("vlayout", 1)->get_reference();
				if ( vlayout )
				{
					add_admin_item( vlayout, entity );
				}
			}
			
			else if ( value->name() == "admin_load_entity" )
			{
				auto to_parent = value->get_reference();
				
				// FIX QFILEDIALOG FOR .SO's
				auto libmanager = dynamic_cast<BEntity_Plugin_Manager*>( to_parent );
				if ( libmanager )
				{
					auto file_dialog = addChild("file_dialog", "QFileDialog");
					file_dialog->getChild("title", 1)->set( "Open Library" );
					file_dialog->getChild("filetype", 1)->set( "*.so" );
					file_dialog->set();

					std::string selected_string = file_dialog->getChild("selected_file")->get_string();
					auto const slashpos = selected_string.find_last_of("/");
					
					auto path = selected_string.substr( 0, slashpos );
					auto filename = selected_string.substr( slashpos + 1 );

					// remove .so from end
					filename = filename.substr( 0, filename.size()-3 );

					// remove lib from start
					filename = filename.substr( 3, filename.size()-3 );
					
					pluginManager()->load( filename, path, filename );

					// load( const std::string& name, const std::string& dir, const std::string& lib )

					removeChild( file_dialog );
				}
				else
				{
					auto file_dialog = addChild("file_dialog", "QFileDialog");
					file_dialog->getChild("title", 1)->set( "Open Entity" );
					file_dialog->getChild("filetype", 1)->set( "*.ent" );
					file_dialog->set();

					m_entityLoad.loadEntity( to_parent, file_dialog->getChild("selected_file")->get_string() );
					removeChild( file_dialog );
				}

				

				// FIXME SPECIES
				// // pick the last entity from m_unit_container
				// auto it = to_parent->children().rbegin();
				// if ( it != to_parent->children().rend() )
				// {
				// 	// if it doesn't have a species_reference, create a new species
				// 	auto species_reference = (*it)->getChild("species_reference", 1);
				// 	if ( !species_reference )
				// 	{
				// 		// species
				// 		m_species_system->addNewSpecies( (*it) );
				// 	}
				// }
			}
		}

		
		return false;
	}

	// GROUPBOX OF ENTITIES
	void BAdminWindow::add_admin_entity_groupbox( BEntity* parent, BEntity* entity )
	{
		// GROUPBOX
			auto groupbox_entities = parent->addChild("qt groupbox entities", "QGroupBox" );
				// groupbox_entities->set("title", entity->name().c_str());
			// VBOX
				auto vboxlayout_entities = groupbox_entities->addChild("qt vboxlayout", "QVBoxLayout" );

		// ENTITY LIST
			add_admin_entity_list( vboxlayout_entities, entity );
	
	}
	// GROUPBOX OF ENTITIES
	void BAdminWindow::add_admin_entity_list( BEntity* parent, BEntity* entity )
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
				add_admin_item( parent, *child );
			}
	}
	
	void BAdminWindow::add_admin_item( BEntity* parent, BEntity* entity )
	{
		if ( entity->name() != "_command_buffer" /*&& entity->name() != "lib"*/ )
		{
			// VBOX (for expanding into)
			// CONSTRUCT UNIQUE NAME for removal purpuses
			// FORMAT : "admin_section_(id)_(name)"
				std::stringstream stream;
				stream << "admin_section_" << entity->id() << "_" << entity->name();
	// 								std::cout << "opening " << stream.str() << std::endl;
			
			// SPAWN VBOX TO EXPAND INTO with unique name
				auto vboxlayout_entity = parent->addChild(stream.str(), "QVBoxLayout" );
				
			// REGISTER IN LOOKUP BUFFER
				m_lookup_buffer.registerAdminEntity( entity, vboxlayout_entity );
				// entity->setHasAdmin();
				// vboxlayout_entity->setIsAdmin();

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
	// 										auto command = actions->addChild("admin_entity_window_open", new BEntity_reference() );
	// 										command->set(entity);
	// 								}

				// EXPAND & COLLAPSE (command will change to collapse when command is ran)
				{
					auto button_add = hboxlayout_entity->addChild("admin_button_expand", "QPushButton" );
					
					// CHILDREN
					if ( entity->hasChildren() )
					{
						button_add->set( "text", "+" );

						// COMMAND
							auto actions = button_add->addChild("_commands", new BEntity() );
							auto command = actions->addChild("admin_entity_group_expand", new BEntity_reference() );
							command->set(entity);
							auto layout_target = command->addChild("layout_target", new BEntity_reference() );
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
								auto command = actions->addChild("admin_entity_group_expand", new BEntity_reference() );
								command->set( entity->get_reference() );
								auto layout_target = command->addChild("layout_target", new BEntity_reference() );
								layout_target->set(vboxlayout_entity);
						}
						else
						{
							button_add->set( "text", " " );

							// COMMAND
								auto actions = button_add->addChild("_commands", new BEntity() );
								auto command = actions->addChild("admin_entity_group_expand", new BEntity_reference() );
								command->set( entity );
								auto layout_target = command->addChild("layout_target", new BEntity_reference() );
								layout_target->set(vboxlayout_entity);
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
					label->set( "width", Buint(220) );

					// drag and drop= reference to adminned entity
					label->addChild( "reference", new BEntity_reference() )->set( entity );
				}

				// VALUE FIELDS
					add_admin_genValueFields( hboxlayout_entity, entity );

				// GENERIC BUTTONS
					add_admin_genButtons( hboxlayout_entity, entity );
			}
		}
	}	

	void BAdminWindow::add_admin_genValueFields( BEntity* to_layout, BEntity* entity )
	{
		// BOOL
			auto t_bool = dynamic_cast<BEntity_bool*>( entity );
			if ( t_bool )
			{
				auto edit = to_layout->addChild( "value_lineedit", "QCheckBox" );
				// edit->set( "width", Buint(80) );
				// edit->set( "height", Buint(14) );
				edit->set( t_bool->get_bool() );
				t_bool->connectServerServer( edit );
				edit->connectServerServer( t_bool );
			}

		// BOOL_PROPERTY
			auto t_boolp = dynamic_cast<BEntity_bool_property*>( entity );
			if ( t_boolp )
			{
				auto edit = to_layout->addChild( "value_lineedit", "QCheckBox" );
				// edit->set( "width", Buint(80) );
				// edit->set( "height", Buint(14) );
				edit->set( t_boolp->get_bool() );
				t_boolp->connectServerServer( edit );
				edit->connectServerServer( t_boolp );
			}

		// UINT // FIXME LINEEDIT
			auto t_uint = dynamic_cast<BEntity_uint*>( entity );
			if ( t_uint )
			{
				auto edit = to_layout->addChild( "value_lineedit", "QLineEdit" );
				edit->set( "width", Buint(80) );
				edit->set( "height", Buint(14) );
				edit->set( t_uint->get_uint() );
				t_uint->connectServerServer( edit );
				edit->connectServerServer( t_uint );
			}

		// UINT_PROPERTY // FIXME LINEEDIT
			auto t_uintp = dynamic_cast<BEntity_uint_property*>( entity );
			if ( t_uintp )
			{
				auto edit = to_layout->addChild( "value_lineedit", "QLineEdit" );
				edit->set( "width", Buint(80) );
				edit->set( "height", Buint(14) );
				edit->set( t_uintp->get_uint() );
				t_uintp->connectServerServer( edit );
				edit->connectServerServer( t_uintp );
			}

		// INT
			auto t_int = dynamic_cast<BEntity_int*>( entity );
			if ( t_int && entity->name() != "random_number_generator" )  // HACK "random_number_generator", this ensures the clockwork universe when scrolling admin window
			{
				auto edit = to_layout->addChild( "value_lineedit", "QLineEdit_int" );
				edit->set( "width", Buint(80) );
				edit->set( "height", Buint(14) );
				edit->set( t_int->get_int() );
				t_int->connectServerServer( edit );
				edit->connectServerServer( t_int );
			}

		// INT_PROPERTY
			auto t_intp = dynamic_cast<BEntity_int_property*>( entity );
			if ( t_intp )
			{
				auto edit = to_layout->addChild( "value_lineedit", "QLineEdit_int" );
				edit->set( "width", Buint(80) );
				edit->set( "height", Buint(14) );
				edit->set( t_intp->get_int() );
				t_intp->connectServerServer( edit );
				edit->connectServerServer( t_intp );
			}

		// FLOAT
			auto t_float = dynamic_cast<BEntity_float*>( entity );
			if ( t_float )
			{
				auto edit = to_layout->addChild( "value_lineedit", "QLineEdit_float" );
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
				auto edit = to_layout->addChild( "value_lineedit", "QLineEdit_float" );
				edit->set( "width", Buint(80) );
				edit->set( "height", Buint(14) );
				edit->set( t_floatp->get_float() );
				// std::cout << "FLOATP " << t_floatp->get_float() << std::endl;
				t_floatp->connectServerServer( edit );
				edit->connectServerServer( t_floatp );
			}
			
		// STRING // FIXME???
			auto t_string = dynamic_cast<BEntity_string*>( entity );
			if ( t_string )
			{
				auto edit = to_layout->addChild( "value_lineedit", "QLineEdit_string" );
				edit->set( "width", Buint(80) );
				edit->set( "height", Buint(14) );
				edit->set( t_string->get_string() );
				t_string->connectServerServer( edit );
				edit->connectServerServer( t_string );
			}

		// STRING_PROPERTY
			auto t_stringp = dynamic_cast<BEntity_string_property*>( entity );
			if ( t_stringp )
			{
				auto edit = to_layout->addChild( "value_lineedit", "QLineEdit_string" );
				edit->set( "width", Buint(80) );
				edit->set( "height", Buint(14) );
				edit->set( t_stringp->get_string() );
				t_stringp->connectServerServer( edit );
				edit->connectServerServer( t_stringp );
			}

			// auto t_float = dynamic_cast<BEntity_float*>( *child );
			// if ( t_float )
			// {
			// 	auto edit = to_layout->addChild( "value_lineedit", "QLineEdit" );
			// 	edit->set( "width", Buint(80) );
			// 	edit->set( "height", Buint(14) );
			// 	auto value_property = edit->addChild( "value", new BEntity_float_property() );
			// 	value_property->set( entity->get_float() );
			// 	// entity->connectServerServer( value_property );
			// 	value_property->connectServerServer( *child );
			// }
		
	}
	
	void BAdminWindow::add_admin_genButtons( BEntity* to_layout, BEntity* entity )
	{
// 			// RM
// 			{
// 				auto button = to_layout->addChild("qt button", "QPushButton" );
// 				button->set("text", "rm");
//    
// 				// COMMAND
// 					auto actions = button->addChild("_commands", new BEntity() );
// 					auto command = actions->addChild("remove", new BEntity_reference() );
// 					command->set(entity);
//    
// 					// auto cmd_remove = button->addChild("remove", new BEntity_reference() );
// 					// cmd_remove->set(entity);
// 					// button->connectServerServer(cmd_remove);
// 			}
//    
// 			// COPY
// 			{
// 				auto button = to_layout->addChild("qt button", "QPushButton" );
// 				button->set("text", "cp");
//    
// 				// COMMAND
// 					auto actions = button->addChild("_commands", new BEntity() );
// 					auto command = actions->addChild("copy", new BEntity_reference() );
// 					command->set(entity);
// 			}

			// LOAD
			{
				auto button = to_layout->addChild("qt button", "QPushButton" );
				button->set("text", "ld");

				// COMMAND
					auto actions = button->addChild("_commands", new BEntity() );
					auto command = actions->addChild("admin_load_entity", new BEntity_reference() );
					command->set(entity);
			}

			// SAVE
			{
				auto button = to_layout->addChild("qt button", "QPushButton" );
				button->set("text", "sv");

				// COMMAND
					auto actions = button->addChild("_commands", new BEntity() );
					auto command = actions->addChild("save", new BEntity_reference() );
					command->set(entity);
			}

			// OPEN ADMIN WINDOW
			{
				auto button = to_layout->addChild("qt button", "QPushButton" );
				button->set("text", "wi");

				// COMMAND
					auto actions = button->addChild("_commands", new BEntity() );
					auto command = actions->addChild("admin_entity_open_window", new BEntity_reference() );
					command->set(entity);
			}
			
			// EXTERNAL || REFERENCE
			{
				if ( dynamic_cast<BEntity_external*>( entity ) || dynamic_cast<BEntity_reference*>( entity ) )
				{
					auto button = to_layout->addChild("qt button", "QPushButton" );
					button->set("text", "rf");

					// COMMAND
						auto actions = button->addChild("_commands", new BEntity() );
						auto command = actions->addChild("admin_entity_open_window", new BEntity_reference() );
						command->set(entity->get_reference());
				}
			}

			// GRAPH FOR FLOAT
			auto t_float = dynamic_cast<BEntity_float*>( entity );
			if ( t_float )
			{
				auto button = to_layout->addChild("qt button", "QPushButton" );
				button->set("text", "gr");

				// COMMAND
					auto actions = button->addChild("_commands", new BEntity() );
					auto command = actions->addChild("admin_entity_graph", new BEntity_reference() );
					command->set(entity);
			}

			// RECOMPILE LIBRARY
			{
				auto t_plugin = dynamic_cast<BEntity_Plugin*>( entity );
				if ( t_plugin )
				{
					auto button = to_layout->addChild("qt button", "QPushButton" );
					button->set("text", "update");

					// COMMAND
						auto actions = button->addChild("_commands", new BEntity() );
						auto command = actions->addChild("update_plugin", new BEntity_reference() );
						command->set(entity);
				}
			}
		
	}

	void BAdminWindow::add_admin_genButtonsWindow( BEntity* to_layout, BEntity* entity )
	{
			// OPEN PARENT
			{
				auto button = to_layout->addChild("qt button", "QPushButton" );
				button->set("text", "parent");

				// COMMAND
					auto actions = button->addChild("_commands", new BEntity() );
					auto command = actions->addChild("admin_entity_open_window", new BEntity_reference() );
					command->set( entity->parent() );
			}

			// COPY
			{
				auto button = to_layout->addChild("qt button", "QPushButton" );
				button->set("text", "copy");

				// COMMAND
					auto actions = button->addChild("_commands", new BEntity() );
					auto command = actions->addChild("copy", new BEntity_reference() );
					command->set(entity);
			}

			// SAVE
			{
				auto button = to_layout->addChild("qt button", "QPushButton" );
				button->set("text", "save");

				// COMMAND
					auto actions = button->addChild("_commands", new BEntity() );
					auto command = actions->addChild("save", new BEntity_reference() );
					command->set(entity);
			}

			// LOAD
			{
				auto button = to_layout->addChild("qt button", "QPushButton" );
				button->set("text", "load");

				// COMMAND
					auto actions = button->addChild("_commands", new BEntity() );
					auto command = actions->addChild("admin_load_entity", new BEntity_reference() );
					command->set(entity);
			}

			// RM
			{
				auto button = to_layout->addChild("qt button", "QPushButton" );
				button->set("text", "remove");

				// COMMAND
					auto actions = button->addChild("_commands", new BEntity() );
					auto command = actions->addChild("remove", new BEntity_reference() );
					command->set(entity);

					// auto cmd_remove = button->addChild("remove", new BEntity_reference() );
					// cmd_remove->set(entity);
					// button->connectServerServer(cmd_remove);
			}

			
			// EXTERNAL || REFERENCE
			{
				if ( dynamic_cast<BEntity_external*>( entity ) || dynamic_cast<BEntity_reference*>( entity ) )
				{
					auto button = to_layout->addChild("qt button", "QPushButton" );
					button->set("text", "referenced");

					// COMMAND
						auto actions = button->addChild("_commands", new BEntity() );
						auto command = actions->addChild("admin_entity_open_window", new BEntity_reference() );
						command->set(entity->get_reference());
				}
			}
			
			// GRAPH FOR FLOAT
			auto t_float = dynamic_cast<BEntity_float*>( entity );
			if ( t_float )
			{
				auto button = to_layout->addChild("qt button", "QPushButton" );
				button->set("text", "graph");

				// COMMAND
					auto actions = button->addChild("_commands", new BEntity() );
					auto command = actions->addChild("admin_entity_graph", new BEntity_reference() );
					command->set(entity);
			}
		
	}
	

// ---- FACTORIES
	enum CLASS
	{
		  PLUGIN_INFO
		, SCENE
		, ADMIN_WINDOW
		, CONFIG_LIBRARIES
	};

	extern "C" BEntity* create( BEntity* parent, const Buint type )
	{
// 		std::cout << "LIB CREATE:: type: " << type  << std::endl;
		// PLUGIN DESCRIPTION ENTITY
			if ( type == PLUGIN_INFO )
			{
				BClassesHelper i;
					i.addClass( parent, CLASS::SCENE, "Scene" );
					i.addClass( parent, CLASS::ADMIN_WINDOW, "AdminWindow" );
					i.addClass( parent, CLASS::CONFIG_LIBRARIES, "ConfigLibraries" );
				return 0;
			}

		// ENTITIES
			else
			{
				BEntity* i(0);
				
				if ( type == CLASS::SCENE )
					i = new BAdminWindow();
				else if ( type == CLASS::ADMIN_WINDOW )
					i = new BAdminWindow();
				else if ( type == CLASS::CONFIG_LIBRARIES )
					i = new BConfigLibraries();

				return i;
			}
	}

	extern "C" void destroy(BEntity* p)
	{
// 		std::cout << "LIB DESTROY:: " << p->id() << std::endl;
		delete p;
	}
	
