#include "bengine.h"
#include "kernel/be_entity_core_types.h"
#include "kernel/be_entity_top.h"
#include "kernel/be_lib_handler.h"
#include "kernel/be_timer.h"
#include <iostream>
#include <unistd.h>

int main(int argc, char* argv[])
{
	std::cout << "bengine3 starting..." << std::endl;

		if ( argc > 1  )
		{
		// TOP PARENT ENTITY
			BEntityTop* toptop = new BEntityTop(); // in this entity we do slower mem saving stuff
			toptop->setName("root");
			toptop->construct();
			toptop->enableLoopManager();
			toptop->spawnChildrenManager();
			toptop->spawnCommandBuffer();
			toptop->spawnPluginManager();


		// PLUGIN MANAGER 
			BEntity_Plugin_Manager* plugin_manager = toptop->pluginManager();
			// plugin_manager->load( "basetypes", "src/kernel", "be_base_entity_types" );

		// CONSTRUCT LIB TO LOAD FROM PARAMS

			std::cout << "param: " << argv[1] << std::endl;
			std::string t_plugin("be_plugin_");
			t_plugin.append( argv[1] );
			std::cout << "t_plugin: " << t_plugin << std::endl;

		// HACK DO TIMER HERE SO WE SEE IT IN ADMINWINDOW
			auto sys = toptop->addChild("sys", new BEntity());
			// sys->addChild("dummy", new BEntity());
			sys->addChild( "timer", new BTimer() );
			sys->addChild( "sleeper", new BSleeper() );

			// binary path
			char buf3[1024];
			readlink("/proc/self/exe", buf3, 1024);
			std::string path1(buf3);
			size_t pos = path1.find_last_of("/", path1.size());
			if ( pos != std::string::npos )
			{
				std::string buff2 = path1.substr( 0, pos+1 );
				sys->addChild( "binary_path", new BEntity_string() )->set( buff2.c_str() );
			}

			// // binary path
			std::string binary( argv[0] );
			sys->addChild( "binary", new BEntity_string() )->set( binary.c_str() );

			std::cout << binary.c_str() << std::endl;

		// LOAD SCENE
			plugin_manager->load( argv[1], "src/plugins/"+t_plugin, t_plugin );

		// LOADING OBJECT FROM CLASS NAMED SCENE FROM LIBRARY
			BEntity* scene = toptop->addChild("bin", "Scene");

			if ( scene != 0 )
			{
				std::cout << "Scene Loaded" << std::endl;

			// ENTITY PRINTOUT
				// toptop->print(toptop, 100);

			// CONSTRUCT PROCESS LIST
				// toptop->reConstructProcessList( scene );

			// MEMORY PRINTOUT
				{
					std::cout << "Memory: " << std::endl;

					std::cout << "  sizeof entity: " << sizeof(BEntity) << " bytes" << std::endl;
					// toptop->printMemProfile();

					const Buint num_totalChildren(1 + toptop->numTotalChildren());
					std::cout << "  total children: " << num_totalChildren;
					if ( num_totalChildren > 1000000 )
					{
						std::cout << " (" << num_totalChildren / 1000000 << "m)";
					}
					else if ( num_totalChildren > 1000 )
					{
						std::cout << " (" << num_totalChildren / 1000 << "k)";
					}
					std::cout << std::endl;
		// 			std::cout << "  children with processing: " << toptop->processorListSize() << std::endl;
					std::cout << "  entity memory overhead: " << sizeof(BEntity) * num_totalChildren << " bytes" << std::endl;
				}

			// RUN
				std::cout << "running..." << std::endl;
				toptop->process_general();
			}
			
			delete toptop;
		}
		else
		{
			std::cout << "parameter expected: specify a library, for example 'app_critterding'" << std::endl;
		}

	// FINISH
		(void)argc;

	std::cout << "bengine3 exiting..." << std::endl;
	return 0;
}
