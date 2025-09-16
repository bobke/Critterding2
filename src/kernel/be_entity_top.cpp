#include "be_entity_top.h"
#include "be_lib_handler.h"
#include "be_entity_children_handler.h"
#include "be_entity_core_types.h"
#include <iostream>
#include <algorithm>
#include <array>
#include <sstream>

// #include <sys/types.h>
#include <sys/stat.h>
// #include <unistd.h>


		BEntityTop::BEntityTop(bool connection_type)
		: m_processor(new BProcessor())
		, m_reconstruct_list(false)
		, m_connection_type(connection_type)
		, m_child_handler(0)
		, m_numLoops(1)
		, m_isLoopManager(false)
		, m_command_buffer(0)
		, m_plugin_manager(0)
		, m_admin_window(0)
		{
			// SET PROCESSING BIT
				setProcessing();
		};

		void BEntityTop::construct() 
		{
		}

		BEntityTop::~BEntityTop()
		{
			if ( m_child_handler != 0 )
			{
				m_child_handler->clearChildren( this );
				delete m_child_handler;
			}
			delete m_processor;
		}

		// MOVE RECONSTRUCT FLAG TO PROCESSOR
		void BEntityTop::reConstructProcessList( BEntity* entity )
		{
// 			m_processor->constructList( entity, false );
			if ( m_reconstruct_list )
			{
				// std::cout << " BEntityTop::constructProcessList " << entity->name() << std::endl;
				m_processor->reConstructList( entity, true );
				m_reconstruct_list = false;
			}
		}
		
		Buint BEntityTop::processorListSize() const
		{
			return m_processor->listSize();
		}

	// PROCESSING
		void BEntityTop::process_general()
		{
			// when no loopmanager exists we run the scene only once
			if ( !isLoopManager() )
			{
				// RECONSTRUCT PROCESS LIST IF NEEDED
					reConstructProcessList( this );  // HACK

				// PROCESS
					m_processor->run();

				// PROCESS COMMAND BUFFER 
					process_and_clear_command_buffer();
			}

			// when loopmanager exists we expect the scene to remove itself
			else 
			{
				BEntity* scene = getChild("bin", 1);
				unsigned int numChildren  = scene->numChildren();

				// WHILE SCENE HAS NOT BEEN DELETED
					// while ( scene )
					while ( numChildren != 0 )
					{
						// PROCESS COMMAND BUFFER
							process_and_clear_command_buffer();

						// HACK if number of children changed, reConstructList, because segfault, where there shouldn't be (one in processor an entry remains referring to a non existant entitiy)
							unsigned int new_numChildren = scene->numChildren();
							if ( new_numChildren != numChildren )
							{
								m_reconstruct_list = true;
							}
							numChildren = new_numChildren;

							// RECONSTRUCT PROCESS LIST IF NEEDED
							reConstructProcessList( this );

						// PROCESS
							m_processor->run();

						// // PROCESS COMMAND BUFFER // WHY DID WE HAVE THIS REALLY WHEN THEN NEXT LOOP STARTS WITH THIS EXACTLY... NONE
						// 	process_and_clear_command_buffer();
      
						// // TRY TO REFIND SCENE TO CHECK IF STILL EXISTS
						// 	scene = getChild("bin", 1);
							
						// NUM LOOPS
							++m_numLoops;

				}
			}
		}

		void BEntityTop::addProcessing( BEntity* entity ) // FIXME
		{
			// FIXME ignore entity warning for now
			(void)entity;
			m_reconstruct_list = true;
		}

		void BEntityTop::removeProcessing( BEntity* entity )
		{
			m_processor->removeEntity( entity );
		}

// 	TOP FUNCTIONS
		BEntity* BEntityTop::getNearestTop()
		{
			return this;
		}

		bool BEntityTop::getNearestTopConnectionType()
		{
			return m_connection_type;
		}
		
	// NAME
		void BEntityTop::addName(BEntity* entity, const std::string& entityName)
		{
			m_be_name_map[entity] = entityName;
		}

		void BEntityTop::removeName(BEntity* entity)
		{
			auto search = m_be_name_map.find(entity);
			if (search != m_be_name_map.end())
			{
				m_be_name_map.erase(search);
			}
		}
		
		std::string& BEntityTop::name(BEntity* entity )
		{
			return m_be_name_map[entity];
		}

	// FPS
		void BEntityTop::addFps(BEntity* entity, const Buint fps)
		{
			m_processor->addFpsBB( entity, fps );
		}

		void BEntityTop::removeFps(BEntity* entity)
		{
			m_processor->removeFpsBB( entity );
		}
		
		Buint BEntityTop::fps( BEntity* entity )
		{
			return m_processor->fpsBB( entity );
		}		
		
	// CHILDREN
		void BEntityTop::spawnChildrenManager()
		{
			m_child_handler = new B_Children_Handler();
		}	

	
		B_Children_Handler* BEntityTop::childHandler() const
		{
			if ( m_child_handler != 0 )
				return m_child_handler;

			if ( parent() != 0 )
				return parent()->childHandler();
			
			std::cout << "B_Children_Handler* BEntityTop::childHandler()::has no childhandler and no parent " << id() << std::endl;
			return 0;
		}

	// COMMAND BUFFER
		void BEntityTop::spawnCommandBuffer()
		{
			m_command_buffer = new BEntity();
			// m_command_buffer = new BECommandBuffer();
			addChild( "_command_buffer", m_command_buffer );
		}

		bool BEntityTop::is_not_in_removed_entities( BEntity* entity )
		{
			if ( std::find( m_removed_entities.begin(), m_removed_entities.end(), entity ) == m_removed_entities.end() )
			{
				return true;
			}
			return false;
		}
		
		void BEntityTop::process_and_clear_command_buffer()
		{
			// WHY DOES THIS NOT WORK IN ONE GO, THEN CLEAR AFTER?
			if ( m_command_buffer != 0 && m_command_buffer->hasChildren() )
			{
				while ( m_command_buffer->hasChildren() )
				{
					auto childrenvector = m_command_buffer->children();
					auto command_it(childrenvector.begin());
   
					auto c = (*command_it);

					// if our c is named reference then load the referenced command
					if ( c->name() == "reference" )
					{
						// if our c is a reference then load the referenced command
						auto ref_c = c->get_reference();
						if ( ref_c )
						{
							// std::cout << "  reference " << std::endl;
							c = ref_c;
						}
					}

					// check commands

					// FIXME WHEN HAMMERING "R" (REMOVE) IN ADMIN (IN VALGRIND) WE CAN MAKE IT CRASH HERE, SINCE c WAS REPLACED ABOVE WITH A REFERENCE THAT'S GONE?
					if ( c->name() == "commitValue" )
					{
						// std::cout << c->get_reference()->name() << std::endl;
						if ( c->getChild("entity_with_input") )
						{
							// std::cout << c->getChild("entity_with_input")->get_reference() << std::endl;
							auto entity_with_output = c->get_reference();
							auto entity_with_input = c->getChild("entity_with_input")->get_reference();
							
							// FORCE APPLY // HACK name() != "transform" portion
							if ( is_not_in_removed_entities( entity_with_output ) && is_not_in_removed_entities( entity_with_input ) )
							{
								// std::cout << "apply " << entity_with_output->name() << " to " << entity_with_input->name() << std::endl;
								entity_with_output->apply( entity_with_input );
							}
						}
					}

					else if ( c->name() == "pass_command" )
					{
						auto pass_entity = c->get_reference();
						auto command = c->getChild("command", 1);
						
						BEntity_string* cmd_string = dynamic_cast<BEntity_string*>( command );
						if ( cmd_string )
						{
							auto entity = command->getChild("entity", 1);
							if ( !entity || is_not_in_removed_entities( entity->get_reference() ) )
							{
								// std::cout << "  target: " << pass_entity->name() << " command: " << cmd_string->get_string() << std::endl;
								pass_entity->set( cmd_string->get_string(), command );
							}
						}
					}

					else if ( c->name() == "remove" )
					{
						// std::cout << "BEntityTop::process_and_clear_command_buffer::command remove " << std::endl;
						// get reference
						auto entity = c->get_reference();
						
						// FIXME DOES NOT CATCH MIGRATED CRITTERS: SO DO THE CHECKS AT INPUTTING TO THE COMMAND BUFFER
						// if it was already removed earlier, do nothing
						if ( is_not_in_removed_entities( entity ) )
						{
							m_removed_entities.push_back( entity );
							if ( entity )
							{
								if ( entity != m_command_buffer && entity->name() != "lib" )
								{
									// std::cout << "removing: " << entity->id() << std::endl;
									entity->parent()->removeChild(entity);
								}
								else 
								{
									// std::cout << "best not removed: " << entity->id() << std::endl;
								}
							}
						}
					}

					else if ( c->name() == "copy" )
					{
						// std::cout << "command: copy" << std::endl;
						auto entity = c->get_reference();
						if ( entity )
						{
							if ( is_not_in_removed_entities( entity ) )
							{
								// std::cout << "copying: " << entity->id() << std::endl;
								m_entityCopy.copyEntity( entity );
							}
						}
					}

					else if ( c->name() == "save" )
					{
						auto entity = c->get_reference();
						if ( entity )
						{
							if ( is_not_in_removed_entities( entity ) )
							{
								// std::cout << "saving: " << entity->id() << std::endl;
								std::string t_filename = "entity_";
								t_filename.append(std::to_string(entity->id()));
								t_filename.append(".ent");
								
								m_entitySave.saveEntity( entity, t_filename );
							}
						}
					}

					else if ( c->name() == "admin_load_entity" || c->name() == "admin_entity_group_expand" || c->name() == "admin_entity_group_contract" || c->name() == "admin_entity_add" || c->name() == "admin_entity_open_window" || c->name() == "admin_entity_graph" )
					{
						// if it has an admin window now, execute
						auto admin_window = getAdminWindow();
						if ( admin_window )
						{
							admin_window->set("command_execute", c);
						}
					}

					else if ( c->name() == "update_plugin" )
					{
						auto plugin = dynamic_cast<BEntity_Plugin*>(c->get_reference());
						if ( plugin )
						{
							if ( is_not_in_removed_entities( plugin ) )
							{
								auto location = plugin->m_location;
								auto filename = plugin->m_filename;
								auto name = plugin->name();
								
			
								struct stat result;
								std::string full_filename = location + "/lib" + filename + ".so";
								// std::cout << "!!!" << full_filename << std::endl;
								unsigned int orig_mod_time;
								if( stat(full_filename.c_str(), &result) == 0 )
								{
									orig_mod_time = result.st_mtime;
									// std::cout << "original timestamp" << orig_mod_time << std::endl;
								}

								
								// RECOMPILE LIBRARY
									std::cout << "recompiling: " << plugin->name() << std::endl;
									std::stringstream cmd;
									// cmd << "cd src && cd plugins && cd be_plugin_" << "test_editing" << " && time make" << std::endl;
									std::cout << "cd " << plugin->m_location << " && time make -j8" << std::endl;
									cmd << "cd " << plugin->m_location << " && time make -j8" << std::endl;
									
									std::cout << exec( cmd.str().c_str() );

								// // REMOVE LIB'S ENTITIES
								// 	auto ent = getChild("bin")->getChild("test_editing");
								// 	if ( ent )
								// 	{
								// 		std::cout << "removing entities" << std::endl;
								// 		ent->parent()->removeChild(ent);
								// 	}

								unsigned int new_mod_time;
								if( stat(full_filename.c_str(), &result) == 0 )
								{
									new_mod_time = result.st_mtime;
									// std::cout << "new timestamp" << new_mod_time << std::endl;
								}
									
								if ( orig_mod_time != orig_mod_time )
								{
								// REMOVE LIBRARY
									auto lib = getChild("lib", 1)->getChild(name.c_str(), 1);
									if ( lib )
									{
										std::cout << "unloading library" << std::endl;
										lib->parent()->removeChild(lib);
									}
								
								// RELOAD LIBRARY
									std::cout << "loading library" << std::endl;
									pluginManager()->load( name, location, filename );
								}
								else
								{
									std::cout << "warning: library is unchanged" << std::endl;
								}

								// m_entitySave.saveEntity( entity, t_filename );
							}
						}
					}
					
					else
					{
						// std::cout << "running command" << std::endl;
						(*command_it)->get_reference()->set();
					}
					
					// else
					// {
					// 	std::cout << "WARNING::unknown command: " << c->id() << " " << c->name() << std::endl;
					// }

					// // BASIC COMMANDS
					// 	BCommand* cmd = dynamic_cast<BCommand*>(*command_it);
					// 	if ( cmd )
					// 	{
					// 		cmd->set();
					// 	}

					// std::cout << BEntity::name().c_str() << " :: removing name " << (*command_it)->name() << std::endl;
					m_command_buffer->removeChild( *command_it );
				}
				// m_command_buffer->clearChildren();
				m_removed_entities.clear();
			}
		}

		std::string BEntityTop::exec(const char* cmd)
		{
			std::array<char, 128> buffer;
			std::string result;
			std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
			if (!pipe) {
				throw std::runtime_error("popen() failed!");
			}
			while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
				result += buffer.data();
			}
			return result;
		}

		
		void BEntityTop::print( BEntity* entity, const Buint max_levels )
		{
			m_child_handler->print( entity, max_levels );
		}
		
		BEntity* BEntityTop::getCommandBuffer()
		{
			return m_command_buffer;
		}

	// PLUGIN_MANAGER
		void BEntityTop::spawnPluginManager()
		{
			m_plugin_manager = new BEntity_Plugin_Manager();
			addChild("lib", m_plugin_manager);
		}

		BEntity_Plugin_Manager* BEntityTop::pluginManager() const
		{
			if ( m_plugin_manager != 0 )
				return m_plugin_manager;

			if ( parent() != 0 )
				return parent()->pluginManager();
			
			std::cout << "BEntity_Plugin_Manager* BEntityTop::pluginManager()::error none can be found" << std::endl;
			return 0;
		}

		BEntity* BEntityTop::getAdminWindow()
		{
			return m_admin_window;
		}

		void BEntityTop::setAdminWindow( BEntity* entity )
		{
			m_admin_window = entity;
		}

