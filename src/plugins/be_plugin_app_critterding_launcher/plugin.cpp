#include "plugin.h"
#include "kernel/be_lib_handler.h"
#include "commands.h"
#include <iostream>


	void Scene::construct()
	{
		setName( "Critterding Launcher" );
		std::cout << "Scene::construct()" << std::endl;

		// SHORTCUTS
			auto bin = topParent()->getChild( "bin", 1 );
			auto sys = topParent()->getChild( "sys", 1 );

		// QT APP
			pluginManager()->load( "qt6", "src/plugins/be_plugin_qt6", "be_plugin_qt6" );
			auto spawner = addChild( "spawner", "QApplicationSpawner" );
			auto t_parent_to_add_to = spawner->getChildCustom( bin );
			removeChild( spawner );

		// ADMIN WINDOW
			pluginManager()->load( "app_admin_window", "src/plugins/be_plugin_app_admin_window", "be_plugin_app_admin_window" );
				auto qt_app = bin->getChild( "QT Application", 2 );
				auto admin_app = qt_app->addChild( "Admin App", "AdminWindow" );
				// admin_app->set("on_close_destroy_entity", qt_app);

		// SLEEPER
			sys->getChild( "sleeper", 1 )->getChild( "target_fps", 1 )->set( (Buint)60 );

		// QT WINDOW
			auto qwindow = addChild( "QT MainWindow", "QMainWindow" );
			qwindow->addChild( "title", "string_property" )->set("Critterding2 Launcher");
			qwindow->addChild( "x", "uint_property" )->set(Buint(1060));
			qwindow->addChild( "y", "uint_property" )->set(Buint(580));
			qwindow->addChild( "width", "uint_property" )->set(Buint(350));
			qwindow->addChild( "height", "uint_property" )->set(Buint(226));
			qwindow->set("on_close_destroy_entity", this);

		// 	COMMANDS
			auto commands = addChild( "commands", "entity" );
			auto cmd_launchEntity = commands->addChild( "launch", new cmd_launch() );
			
		// SETTINGS
			auto settings = addChild( "settings", "entity" );

		// MAIN VERTICAL LAYOUT BOX
			auto layout_V = qwindow->addChild( "hlayout", "QVBoxLayout" );

			// THREADS
			{
				auto entity_groupbox = layout_V->addChild( "Threads", "QGroupBox" );
				entity_groupbox->set("title", "Threads");
				BEntity* group_layout_V = entity_groupbox->addChild( "vlayout", "QVBoxLayout" );

				// ROWS
				{
					BEntity* layout_H = group_layout_V->addChild( "hlayout", "QHBoxLayout" );
						auto text_label = layout_H->addChild( "text_label", "QLabel" );
						text_label->set("text", "rows");
						text_label->set("width", Buint(121));
						auto lineedit = layout_H->addChild( "lineedit", "QLineEdit_uint" );
						lineedit->set( (Buint)1 );
						lineedit->set("width", Buint(40));
						lineedit->set("height", Buint(28));

						auto setting_threadsRows = settings->addChild( "threadsRows", "uint" );
						lineedit->connectServerServer( setting_threadsRows );
						lineedit->set();
						setting_threadsRows->connectServerServer( lineedit );
				}

				// COLUMNS
				{
					BEntity* layout_H = group_layout_V->addChild( "hlayout", "QHBoxLayout" );
						auto text_label = layout_H->addChild( "text_label", "QLabel" );
						text_label->set("text", "columns");
						text_label->set("width", Buint(121));
						auto lineedit = layout_H->addChild( "lineedit", "QLineEdit_uint" );
						lineedit->set( (Buint)4 );
						lineedit->set("width", Buint(40));
						lineedit->set("height", Buint(28));

						auto setting_threadsColumns = settings->addChild( "threadsColumns", "uint" );
						lineedit->connectServerServer( setting_threadsColumns );
						lineedit->set();
						setting_threadsColumns->connectServerServer( lineedit );
				}

				// GRAPHICS ON BACKGROUND THREAD
				{
					BEntity* layout_H = group_layout_V->addChild( "hlayout", "QHBoxLayout" );
						auto checkbox = layout_H->addChild( "lineedit", "QCheckBox" );
						checkbox->set( true );
						auto text_label = layout_H->addChild( "text_label", "QLabel" );
						text_label->set("text", "servers on background (experimental)");
						text_label->set("width", Buint(300));

						auto setting_servers_backtround_thread = settings->addChild( "threadsServersBackground", "bool" );
						checkbox->connectServerServer( setting_servers_backtround_thread );
						checkbox->set();
						setting_servers_backtround_thread->connectServerServer( checkbox );
				}
			}

			// ENERGY
			{
				auto entity_groupbox = layout_V->addChild( "Energy", "QGroupBox" );
				entity_groupbox->set("title", "Energy");
				BEntity* group_layout_V = entity_groupbox->addChild( "vlayout", "QVBoxLayout" );

				// CRITTERS
				{
					BEntity* layout_H = group_layout_V->addChild( "hlayout", "QHBoxLayout" );
						auto text_label = layout_H->addChild( "text_label", "QLabel" );
						text_label->set("text", "minimum critters");
						text_label->set("width", Buint(121));
						auto lineedit = layout_H->addChild( "lineedit", "QLineEdit_uint" );
						lineedit->set( (Buint)20 );
						lineedit->set("width", Buint(40));
						lineedit->set("height", Buint(28));

						auto setting_numCritters = settings->addChild( "numCritters", "uint" );
						lineedit->connectServerServer( setting_numCritters );
						lineedit->set();
						setting_numCritters->connectServerServer( lineedit );
				}

				// FOOD
				{
					BEntity* layout_H = group_layout_V->addChild( "hlayout", "QHBoxLayout" );
						auto text_label = layout_H->addChild( "text_label", "QLabel" );
						text_label->set("text", "minimum food");
						text_label->set("width", Buint(121));
						auto lineedit = layout_H->addChild( "lineedit", "QLineEdit_uint" );
						lineedit->set( (Buint)2100 );
						lineedit->set("width", Buint(40));
						lineedit->set("height", Buint(28));

						auto setting_numFood = settings->addChild( "numFood", "uint" );
						lineedit->connectServerServer( setting_numFood );
						lineedit->set();
						setting_numFood->connectServerServer( lineedit );
				}
			}
			

			// EXIT & LAUNCH BUTTONS
			{
				auto entity_groupbox = layout_V->addChild( "Threads", "QGroupBox" );
				BEntity* group_layout_V = entity_groupbox->addChild( "vlayout", "QVBoxLayout" );
				
				BEntity* layout_H = group_layout_V->addChild( "hlayout", "QHBoxLayout" );
					auto button_exit = layout_H->addChild("admin_button_expand", "QPushButton" );
					button_exit->set( "text", "Exit" );
					button_exit->set( "width", Buint(100) );
					button_exit->set( "height", Buint(28) );
					
					auto button_launch = layout_H->addChild("admin_button_expand", "QPushButton" );
					button_launch->set( "text", "Launch" );
					button_launch->set( "width", Buint(100) );
					button_launch->set( "height", Buint(28) );
					
					button_launch->connectServerServer( cmd_launchEntity );
			}

			
	}

	void Scene::process()
	{
	}

// ---- FACTORIES
	enum CLASS
	{
		  PLUGIN_INFO
		, SCENE
		, CRITTERDING_LAUNCHER
	};

	extern "C" BEntity* create( BEntity* parent, const Buint type )
	{
		// PLUGIN DESCRIPTION ENTITY
			if ( type == PLUGIN_INFO )
			{
				BClassesHelper i;
					i.addClass( parent, CLASS::SCENE, "Scene" );
					i.addClass( parent, CLASS::CRITTERDING_LAUNCHER, "CritterdingLauncher" );
				return 0;
			}

		// ENTITIES
			else
			{
				BEntity* i(0);

				if ( type == CLASS::SCENE )
					i = new Scene();
				else if ( type == CLASS::CRITTERDING_LAUNCHER )
					i = new Scene();

				return i;
			}
	}

	extern "C" void destroy( BEntity* p )
	{
		delete p;
	}
	
