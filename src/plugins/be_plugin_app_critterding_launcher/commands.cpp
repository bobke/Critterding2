#include "commands.h"
#include "kernel/be_lib_handler.h"
#include <iostream>

	bool cmd_launch::set()
	{
		std::cout << "launching Critterding" << std::endl;

		auto cmdbuffer = topParent()->getChild( "_command_buffer", 1 );
		auto bin = topParent()->getChild( "bin", 1 );
		auto sys = topParent()->getChild( "sys", 1 );

		// LAUNCH CRITTERDING
			pluginManager()->load( "critterding_threads", "src/plugins/be_plugin_app_critterding_threads", "be_plugin_app_critterding_threads" );
			bin->addChild( "Critterding", "Critterding" );
		
		// DISABLE SLEEPER
			sys->getChild( "sleeper", 1 )->getChild( "target_fps", 1 )->set( (Buint)0 );

		// REMOVE LAUNCHER
			auto command = cmdbuffer->addChild("remove", new BEntity_reference() );
			command->set(bin->getChild("Critterding Launcher", 1));

		return true;
	}

