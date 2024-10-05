#include "plugin.h"
#include "llama_gui.h"
#include "kernel/be_lib_handler.h"
#include "kernel/be_entity_io_handler.h"
// #include "kernel/be_plugin_base_entity_types.h"
#include <iostream>
// #include <iomanip>
// #include <array>
// #include <algorithm>
#include <memory>
// #include <sys/stat.h>
// #include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <fstream>
// #include <stdlib.h>

	void Scene::construct()
	{
		setName( "Entity Browser" );

		// SLEEPER
			topParent()->getChild( "sys", 1 )->getChild( "sleeper", 1 )->getChild( "target_fps", 1 )->set( (Buint)100 );
		
		// LOAD QT APP FIXME THIS DOESN'T NEED TO GET ONTO THE TREE
		pluginManager()->load( "qt6", "src/plugins/be_plugin_qt6", "be_plugin_qt6" );

			auto spawner = addChild( "spawner", "QApplicationSpawner" );
			// auto t_parent_to_add_to = spawner->getChildCustom( parent() );
			auto t_parent_to_add_to = spawner->getChildCustom( this );
			removeChild( spawner );

		auto bin = topParent()->getChild( "bin", 1 );
		auto qt_app = bin->getChild( "QT Application", 2 );

		// 	COMMANDS
			// auto commands = addChild( "commands", "entity" );
			// auto cmd_calcEntity = commands->addChild( "calc", new cmd_calc() );

		// ADMIN WINDOW
			pluginManager()->load( "app_admin_window", "src/plugins/be_plugin_app_admin_window", "be_plugin_app_admin_window" );
			qt_app->addChild( "Admin App", "AdminWindow" );
		
		
		// QWINDOW
			auto qwindow = qt_app->addChild( "cmdline_window", "QMainWindow" );
			qwindow->addChild( "title", "string_property" )->set("Entity Browser");
			qwindow->addChild( "x", "uint_property" )->set(Buint(750));
			qwindow->addChild( "y", "uint_property" )->set(Buint(300));
			qwindow->addChild( "width", "uint_property" )->set(Buint(900));
			qwindow->addChild( "height", "uint_property" )->set(Buint(930));
			qwindow->set("on_close_destroy_entity", this);

			// VERT LAYOUT
				auto general_layout_V = qwindow->addChild( "QT VBoxlayout", "QVBoxLayout" );

			// HORI LAYOUT
				auto general_layout_V2 = general_layout_V->addChild( "QT HBoxlayout", "QVBoxLayout" );

			// PARAMETERS
				// LAYOUTS PARAMETERS
					auto param_layout_H_a = general_layout_V2->addChild( "HBoxlayout_s", "QHBoxLayout" );
					auto param_layout_H_b = general_layout_V2->addChild( "HBoxlayout_a", "QHBoxLayout" );

				// OUTPUT TEXTBOX
					auto textbox = param_layout_H_a->addChild( "textbox_lineedit_OUTPUT", "QPlainTextEdit" );
					textbox->set( "width", Buint(900) );
					textbox->set( "height", Buint(900) );

				// QUERY INPUT
					auto query = param_layout_H_b->addChild( "query_lineedit_INPUT", "QLineEdit" );
					query->set( "width", Buint(890) );
					query->set( "height", Buint(28) );
					
		// ENTITY BROWSER
			auto browser = addChild("entity_browser", "BEntityBrowser");
			
		// CONNECT QUERY AND BROWSER
			query->connectServerServer( browser );
			
// 		// TEST ENTITIES
// 			auto trigger = addChild("trigger", "trigger");
// 			auto reference = addChild("reference", "reference");
// 			reference->set( trigger );
// 			
// 			addChild("bool", "bool");
// 			addChild("uint", "uint");
// 			addChild("int", "int");
// 			addChild("float", "float");
// 			addChild("double", "double");
// 			addChild("string", "string");
	}

	void BEntityBrowser::construct()
	{
		current_position = topParent();

		// execl("/bin/bash","/bin/bash", "-c", "/vol/space/llama.cpp/llama-cli -mg 0 -m /vol/space/oobabooga/models/qwen2.5-72b-instruct-q3_k_m-00001-of-00009.gguf --repeat_penalty 1.0 -i -r 'User:' -ngl 51 --ctx-size 2048 --file bengine-ai-assistant.txt --grammar-file ../share/ai-json.gbnf", (char *)NULL);
		// execl("/bin/bash","/bin/bash", "-c", "/vol/space/llama.cpp/llama-cli -mg 0 -m /vol/space/oobabooga/models/Arcee-Nova-Alpha-GGUF.Q6_K-00001-of-00008.gguf --repeat_penalty 1.0 -i -r 'User:' -ngl 27 --ctx-size 2048 --file bengine-ai-assistant.txt --grammar-file ../share/ai-json.gbnf", (char *)NULL);

		auto bin = topParent()->getChild( "bin", 1 );
		auto qt_app = bin->getChild( "QT Application", 2 );
		auto llama_gui = addChild( "llama_gui", "LLama_gui" );
		
		// LLAMA LOCATION
		llama_location = addChild( "llama_location", "string" );
		auto gui_llama_location = qt_app->getChild( "llama_location", 4);
		gui_llama_location->connectServerServer( llama_location );
		llama_location->connectServerServer( gui_llama_location );
		llama_location->set( "/vol/space/llama.cpp/llama-cli" );
		
		// MODEL LOCATION
		model_location = addChild( "model_location", "string" );
		auto gui_model_location = qt_app->getChild( "model_location", 4);
		gui_model_location->connectServerServer( model_location );
		model_location->connectServerServer( gui_model_location );
  
		// LAYERS ON GPU
		layers_on_gpu = addChild( "layers_on_gpu", "uint" );
		auto gui_layers_on_gpu = qt_app->getChild( "layers_on_gpu", 4);
		gui_layers_on_gpu->connectServerServer( layers_on_gpu );
		layers_on_gpu->connectServerServer( gui_layers_on_gpu );

		// MODELS

			// LIQUID CODING AGENT (8B)
				// model_location->set( "/vol/space/oobabooga/models/llama-3-8b-liquid-coding-agent.F16.gguf" );
				// layers_on_gpu->set( (Buint)33 );

			// LAMA 3
				// model_location->set( "/vol/space/oobabooga/models/Meta-Llama-3.1-70B-Instruct-Q6_K-00001-of-00002.gguf" );
				// layers_on_gpu->set( (Buint)30 );
		
				// model_location->set( "/vol/space/oobabooga/models/Meta-Llama-3.1-70B-Instruct-Q8_0-00001-of-00002.gguf" );
				// layers_on_gpu->set( (Buint)22 );

			// REFLECTION
				// model_location->set( "/vol/space/oobabooga/models/Reflection-Llama-3.1-70B-Q4_K_M.gguf" );
				// layers_on_gpu->set( (Buint)31 );

			// QWEN2
				// model_location->set( "/vol/space/oobabooga/models/qwen2.5-72b-instruct-q3_k_m-00001-of-00009.gguf" );
				// layers_on_gpu->set( (Buint)48 );
				model_location->set( "/vol/space/oobabooga/models/qwen2.5-72b-instruct-q6_k-00001-of-00016.gguf" );
				layers_on_gpu->set( (Buint)29 );
				// model_location->set( "/vol/space/oobabooga/models/qwen2.5-72b-instruct-q8_0-00001-of-00021.gguf" );
				// layers_on_gpu->set( (Buint)22 );

			// ACREE-NOVA
				// model_location->set( "/vol/space/oobabooga/models/Arcee-Nova-Alpha-GGUF.Q6_K-00001-of-00008.gguf" );
				// layers_on_gpu->set( (Buint)27 );

		// CTXSIZE
		ctx_size = addChild( "ctx_size", "uint" );
		auto gui_ctx_size = qt_app->getChild( "ctx_size", 4);
		gui_ctx_size->connectServerServer( ctx_size );
		ctx_size->connectServerServer( gui_ctx_size );
		ctx_size->set( (Buint)8192 );

		// REPEAT PENALTY
		repeat_penalty = addChild( "repeat_penalty", "float" );
		auto gui_repeat_penalty = qt_app->getChild( "repeat_penalty", 4);
		gui_repeat_penalty->connectServerServer( repeat_penalty );
		repeat_penalty->connectServerServer( gui_repeat_penalty );
		repeat_penalty->set( 1.0f );

		// PROMPT ASSISTANT
		prompt_assistant = addChild( "prompt_assistant", "string" );
		auto gui_prompt_assistant = qt_app->getChild( "prompt_assistant", 4);
		gui_prompt_assistant->connectServerServer( prompt_assistant );
		prompt_assistant->connectServerServer( gui_prompt_assistant );
		prompt_assistant->set( "../share/bengine-prompt-assistant.txt" );

		// // SESSION NAME
		// session_name = addChild( "session_name", "string" );
		// auto gui_session_name = qt_app->getChild( "session_name", 4);
		// gui_session_name->connectServerServer( session_name );
		// session_name->connectServerServer( gui_session_name );
		// session_name->set( "" );

	}

	std::string BEntityBrowser::print_entityLine( BEntity* e, bool main )
	{
		std::stringstream txt;
		
		// BASIC INFORMATION

			// ID 
				txt << e->id();
				txt << " : ";

			// NAME
				if ( main )
					txt << e->nameFullPath();
				else
					txt << e->name();
		
			// NUM CHILDREN
				if ( e->numChildren() > 0 )
				{
					txt << " (" << e->numChildren() << ")";
				}
			// CLASS
				txt << std::setw(35);
				txt << " : ";
				txt << e->class_id();

		// VALUES
			// txt << std::setw(50);
			txt << ": " << print_value(e);
		
		// CONNECTIONS
			if ( e->hasInput() )
			{
				auto input = e->getInput();
				for ( auto it(input->m_connected_outputs.begin()); it != input->m_connected_outputs.end(); it++ )
				{
					// BASIC INFORMATION
						// ID 
							txt << (*it)->id();
							txt << " : ";
						// NAME
							txt << (*it)->name();
				}
				
			}

			if ( e->hasOutput() )
			{
				auto output = e->getOutput();
				for ( auto it(output->m_connections.begin()); it != output->m_connections.end(); it++ )
				{
					// BASIC INFORMATION
						// ID 
							txt << (*it)->m_output_entity->id();
							txt << " : ";
						// NAME
							txt << (*it)->m_output_entity->name();
				}
			}
		
		return txt.str();
	}
	
	std::string BEntityBrowser::print_entity( BEntity* e )
	{
		std::stringstream output;
		// PRINT CURRENT POSITION
			output << print_entityLine( e, true );
		
		// PRINT ALL CHILDREN
			for_all_children_of( e )
			{
				output << std::endl << "     " << print_entityLine( (*child) );
			}
		return output.str();
	}
	
	BEntity* BEntityBrowser::getFinalChild( const std::string& arg )
	{
		parseH.reset();
		
		// SETUP LASTENTITY
		BEntity* last_entity(0);
		
		// START FROM TOP IF STARTS WITH /
		if ( parseH.beginMatchesStrip("/", arg) )
			last_entity = topParent();
		else
			last_entity = current_position;

		// go through each entity seperated by "/" and return final one
		std::string entity_string = parseH.returnUntillStrip( '/', arg );
		while ( last_entity && !entity_string.empty() )
		{
			
			// TODO {"command":"cd /bin/Critterding/164/GLWindow"} check in case of that id
			
			last_entity = last_entity->getChild( entity_string.c_str(), 1);
			entity_string = parseH.returnUntillStrip( '/', arg );
		}
		return last_entity;
	}

	bool BEntityBrowser::set( const char* value )
	{
		std::string command(value); 
		if ( std::string(command).empty()  )
			return false;

		auto vbox = parent()->parent()->getChild( "cmdline_window", 3 )->getChild( "QT VBoxlayout", 1 );
		
		textbox = vbox->getChild( "textbox_lineedit_OUTPUT", 3 );
		auto query = vbox->getChild( "query_lineedit_INPUT", 3 );

		m_search_from_root = false;

		parseH.reset();
		parseH.trimWhitespaces( command );
		command = parseH.returnRemainder( command );
		parseH.reset();

		// PRINT COMMAND
			std::string ct(">>");
			ct.append(command);

			if ( !m_ai_runs )
				textbox->set( ct.c_str() );

			std::stringstream output;
			// output <<  ">>" << command;

			const std::string& program = parseH.returnUntillStrip( ' ', command );
			if ( !program.empty() )
			{
				// LS
					if ( program == "ls" )
					{
						// ENTITY TO ENTER
							auto candidate_entity = parseH.returnRemainder( command );

						// HAS ARGUMENT
							if ( !candidate_entity.empty() )
							{
								// FIND ENTITY ON ID
								BEntity* found_entity(0);
								char* p;
								unsigned int id = strtol(candidate_entity.c_str(), &p, 10);
								if (!*p)
								{
									found_entity = getChildWithID( id, topParent() );
								}

								// FIND ENTITY ON NAME
								else
								{
									found_entity = getFinalChild( candidate_entity );
								}

								if ( found_entity )
								{
									output << std::endl << "" << print_entity( found_entity );
								}
								else
								{
									output << std::endl << "entity does not exist: " << candidate_entity;
									output << std::endl << "try \"ls\"";
								}
							}
						// NO ARGUMENTs
							else
							{
								output << std::endl << "" << print_entity( current_position );
							}
						
						// APPEND TO TEXTBOX
							textbox_last = output.str();
							if ( !m_ai_runs )
								textbox->set( output.str().c_str() );

						// RESET QUERY LINEEDIT
							query->set( "" );
						
						// // ENDLINE TO TEXTBOX
						// 	if ( !m_ai_runs )
						// 		textbox->set( "" );

						return true;
					}
	
				// CD
					else if ( program == "cd" )
					{
							// GO TO ROOT
								auto candidate_entity = parseH.returnRemainder( command );

								if ( candidate_entity == "/" )
								{
									current_position = topParent();

									output << std::endl << "entering " << current_position->name();
									textbox_last = output.str();
									if ( !m_ai_runs )
										textbox->set( output.str().c_str() );
								}

							// GO UP ONE ENTITY
								else
								{
									if ( candidate_entity == ".." )
									{
										if ( current_position != topParent() )
										{
											current_position = current_position->parent();
										}
										std::cout << "FULL NAME PATH: " << current_position->nameFullPath() << std::endl;
										output << std::endl << "entering " << current_position->nameFullPath() << std::endl;
										// current_position = current_position->parent();
										textbox_last = output.str();
										if ( !m_ai_runs )
											textbox->set( output.str().c_str() );
									}
									else
									{
										// FIND ENTITY ON ID
										BEntity* found_entity(0);
										char* p;
										unsigned int id = strtol(candidate_entity.c_str(), &p, 10);
										if (!*p)
										{
											found_entity = getChildWithID( id, topParent() );
										}

										// FIND ENTITY ON NAME
										else
										{
											found_entity = getFinalChild( candidate_entity );
										}

										if ( found_entity )
										{
											current_position = found_entity;

											if ( current_position == topParent() )
											{
												output << std::endl << "entering " << current_position->name();
											}
											else
											{
												output << std::endl << "entering " << current_position->nameFullPath();
											}
											textbox_last = output.str();
											if ( !m_ai_runs )
												textbox->set( output.str().c_str() );
										}
										else
										{
											// APPEND TO TEXTBOX
												output << std::endl << "entity does not exist: " << candidate_entity;
												output << std::endl << "try \"ls\"";
												textbox_last = output.str();
												if ( !m_ai_runs )
													textbox->set( output.str().c_str() );
										}
										
									}
								}

							// RESET QUERY LINEEDIT
								query->set( "" );
							
							// // ENDLINE TO TEXTBOX
							// 	if ( !m_ai_runs )
							// 		textbox->set( "" );

							return true;
					}
					
				// CAT, ECHO, GET
					else if ( program == "cat" || program == "echo" || program == "get" || program == "print" )
					{
						auto candidate_entity = parseH.returnRemainder( command );
						
						// FIND ENTITY ON ID
						// unsigned int id = strtol( candidate_entity.c_str() );
						
						BEntity* found_entity(0);
						char* p;
						unsigned int id = strtol(candidate_entity.c_str(), &p, 10);
						if (!*p)
						{
							found_entity = getChildWithID( id, topParent() );
						}

						// FIND ENTITY ON NAME
						else
						{
							found_entity = getFinalChild( candidate_entity );
						}

						if ( found_entity )
						{
							output << std::endl << print_value(found_entity) << "\n";
							textbox_last = output.str();
							if ( !m_ai_runs )
								textbox->set( output.str().c_str() );
						}
						else
						{
							// APPEND TO TEXTBOX
								output << std::endl << "entity does not exist: " << candidate_entity;
								output << std::endl << "try \"ls\"";
								textbox_last = output.str();
								if ( !m_ai_runs )
									textbox->set( output.str().c_str() );
						}
						

						// RESET QUERY LINEEDIT
							query->set( "" );

						// // ENDLINE TO TEXTBOX
						// 	if ( !m_ai_runs )
						// 		textbox->set( "" );

						return true;
					}

				// SET
					else if ( program == "set" )
					{
						auto candidate_entity = parseH.returnUntillStrip( " ", command );
						auto candidate_value = parseH.returnRemainder( command );

						// FIND ENTITY ON ID
						BEntity* found_entity(0);
						char* p;
						unsigned int id = strtol(candidate_entity.c_str(), &p, 10);
						if (!*p)
						{
							found_entity = getChildWithID( id, topParent() );
						}

						// FIND ENTITY ON NAME
						else
						{
							found_entity = getFinalChild( candidate_entity );
						}

						if ( found_entity )
						{
							// set it's value
							if ( !candidate_value.empty() && set_value( found_entity, candidate_value ) )
							{
								output << std::endl << "changed value of " << found_entity->name();
								output << " to: " << candidate_value;
							}
							else
							{
								output << std::endl << "failed to set value of " << found_entity->name() << " to: " << candidate_value;
							}

							textbox_last = output.str();
							if ( !m_ai_runs )
								textbox->set( output.str().c_str() );
						}
						else
						{
							// APPEND TO TEXTBOX
								output << std::endl << "entity does not exist: " << candidate_entity;
								output << std::endl << "try \"ls\"";
								textbox_last = output.str();
								if ( !m_ai_runs )
									textbox->set( output.str().c_str() );
						}


						// RESET QUERY LINEEDIT
							query->set( "" );

						// // ENDLINE TO TEXTBOX
						// 	if ( !m_ai_runs )
						// 		textbox->set( "" );

						return true;
					}

				// LOADLIB
					else if ( program == "load_plugin" )
					{
						// auto  = parseH.returnUntillStrip( " ", command );
						auto candidate_entity = parseH.returnRemainder( command );

						if ( !candidate_entity.empty() )
						{
							if ( pluginManager()->load( candidate_entity, "src/plugins/be_plugin_" + candidate_entity, "be_plugin_" + candidate_entity ) )
							{
								output << std::endl << "loaded " << candidate_entity;
							}
							else
							{
								output << std::endl << "failed loading " << candidate_entity << ": lib not found";
							}
						}
						
						// APPEND TO TEXTBOX
							textbox_last = output.str();
							if ( !m_ai_runs )
								textbox->set( output.str().c_str() );

						// RESET QUERY LINEEDIT
							query->set( "" );

						return true;
					}

				// LOAD ENTITY CLASS
					else if ( program == "load" )
					{
						// auto  = parseH.returnUntillStrip( " ", command );
						auto candidate_entity = parseH.returnUntillStrip( " ", command );
						// auto candidate_entity = parseH.returnRemainder( command );
						auto candidate_name = parseH.returnRemainder( command );

						if ( !candidate_name.empty() )
						{
							if ( !candidate_entity.empty() )
							{
								auto new_entity = current_position->addChild("", candidate_entity);
								if ( new_entity )
								{
									// if ( !m_ai_runs )
									output << std::endl <<  "loaded " << candidate_entity << " named '" << candidate_name << "' as child of " << current_position->nameFullPath() << std::endl;;
									new_entity->setName( candidate_name );
								}
								else
								{
									output << std::endl << "failed loading " << candidate_entity << ": entity class does not exist. use the name of a class in /lib";
								}
							}
						}
						else
						{
							output << std::endl << "failed loading " << candidate_entity << ": you must supply a name. use the name of a class in /lib";
						}
						
						// APPEND TO TEXTBOX
							textbox_last = output.str();
							if ( !m_ai_runs )
								textbox->set( output.str().c_str() );

						// RESET QUERY LINEEDIT
							query->set( "" );

						return true;
					}

				// HELP
					else if ( program == "help" )
					{
						// SET OUTPUT
							output << std::endl << "ls [ENTITY] " << "                           " << "List information about the ENTITY (the current " << current_position->name() << " by default)";
							output << std::endl << "cd [ENTITY] " << "                          " << "Change the current directory to the ENTITY";
							output << std::endl << "get [ENTITY] " << "                        " << "Get value of the ENTITY";
							output << std::endl << "set [ENTITY] [VALUE] " << "         " << "Set value of the ENTITY to VALUE";
							output << std::endl << "ai question/command" << "         " << "Demand from llama.cpp to do what is required";

						// APPEND TO TEXTBOX
							textbox_last = output.str();
							if ( !m_ai_runs )
								textbox->set( output.str().c_str() );

						// RESET QUERY LINEEDIT
							query->set( "" );
						
						// // ENDLINE TO TEXTBOX
						// 	if ( !m_ai_runs )
						// 		textbox->set( "" );

						return true;
					}
					
				// AI
					else if ( program == "ai" )
					{
						if ( !m_ai_runs )
						{
							auto candidate_value = parseH.returnRemainder( command );

							// RESET QUERY LINEEDIT
								query->set( "" );
							// // ENDLINE TO TEXTBOX
							// 	textbox->set( "" );
							
							// save position and set it to top
								auto save_position = current_position;
								current_position = topParent();
							
							output << launchAI( candidate_value.c_str() );
							output << execAI();

							// restore position
								current_position = save_position;

							// while (m_pid == 0)
							{
								// std::cout << "killing from set" << std::endl;
								kill( m_pid, SIGINT);
							}

							// APPEND TO TEXTBOX
								if ( !m_ai_runs )
									textbox->set( output.str().c_str() );

							return true;
						}
						else
						{
							output << "you are the ai, don't call yourself";
							// APPEND TO TEXTBOX
							textbox_last = output.str();
							return false;
						}
					}
			}

		// APPEND TO TEXTBOX
			output << std::endl << "unknown command: " << program;
			output << std::endl << "possible commands: help, ls, cd, get, set, load_plugin, load, ai";
  
		// APPEND TO TEXTBOX
			textbox_last = output.str();
			if ( !m_ai_runs )
				textbox->set( output.str().c_str() );
  
		// RESET QUERY LINEEDUT
			query->set("");
  
		// // ENDLINE TO TEXTBOX
		// 	if ( !m_ai_runs )
		// 		textbox->set( "" );
  
		// FIXME TURN AROUND SO THIS RETURNS TRUE
		return false;
	}

// LAUNCH AI

	void BEntityBrowser::process()
	{
// 		if ( m_ai_runs )
// 		{
			// std::cout << "proc" << std::endl;
// 			// Set the output pipe to non-blocking mode (so we can read while the command runs)
// 			fcntl(out_pipe[0], F_SETFL, O_NONBLOCK);
// 			// fcntl(in_pipe[1], F_SETFL, O_NONBLOCK);
// 			
// 			std::string result = execAI();
// 			if ( !result.empty() )
// 			{
// 				// output << result;
// 				// textbox->set( output.str().c_str() );
// 				textbox->set( result.c_str() );
// 			}
// 
// 		}
	}

	std::string BEntityBrowser::launchAI(const char* cmd)
	{
		// 1. Create two pipes: one for input and one for output
		// `pipe()` returns two file descriptors: one for reading and one for writing
		if (pipe(in_pipe) == -1 || pipe(out_pipe) == -1) {
			perror("pipe");  // If pipe creation fails, show an error
			return "";        // Exit if pipe creation fails
		}

		// 2. Create a child process with fork()
		m_pid = fork();
		if (m_pid == -1)
		{
			perror("fork");  // If fork fails, show an error
			return "";        // Exit if fork fails
		}

		// CHILD PROCESS
		if (m_pid == 0)
		{
			setsid();
			
			// Redirect the standard input (stdin) to the reading end of in_pipe
			dup2(in_pipe[0], STDIN_FILENO);   // Now the command's stdin will come from in_pipe[0]
			// Redirect the standard output (stdout) to the writing end of out_pipe
			dup2(out_pipe[1], STDOUT_FILENO); // The command's stdout will go to out_pipe[1]
			// dup2(out_pipe[1], STDERR_FILENO); // Redirect stderr to capture errors too

			// Close the unused ends of the pipes (important!)
			close(in_pipe[0]);  // Close in_pipe[0] because we are done with it in the child
			close(in_pipe[1]);  // Close in_pipe[1] in the child (the parent will write to this)
			close(out_pipe[0]); // Close out_pipe[0] in the child (the parent will read from this)
			close(out_pipe[1]); // Close out_pipe[1] because the child has stdout redirected to it

			// LAUNCHING LLAMA.CPP
			// execl("/bin/bash","/bin/bash", "-c", "/vol/space/llama.cpp/llama-cli -mg 0 -m /vol/space/oobabooga/models/llama-3-8b-liquid-coding-agent.F16.gguf --repeat_penalty 1.0 -i -r 'User:' -ngl 33 --ctx-size 4096 --file ../share/bengine-prompt-assistant.txt --grammar-file ../share/ai-json.gbnf", (char *)NULL);
//ok			// execl("/bin/bash","/bin/bash", "-c", "/vol/space/llama.cpp/llama-cli -mg 0 -m /vol/space/oobabooga/models/Reflection-Llama-3.1-70B-Q4_K_M.gguf --repeat_penalty 1.0 -i -r 'User:' -ngl 26 --ctx-size 4096 --file ../share/bengine-prompt-assistant.txt --grammar-file ../share/ai-json.gbnf", (char *)NULL);
//ok			// execl("/bin/bash","/bin/bash", "-c", "/vol/space/llama.cpp/llama-cli -mg 0 -m /vol/space/oobabooga/models/Meta-Llama-3.1-70B-Instruct-Q4_K_L.gguf --repeat_penalty 1.0 -i -r 'User:' -ngl 42 --ctx-size 4096 --file ../share/bengine-prompt-assistant.txt --grammar-file ../share/ai-json.gbnf", (char *)NULL);
			// execl("/bin/bash","/bin/bash", "-c", "/vol/space/llama.cpp/llama-cli -mg 0 -m /vol/space/oobabooga/models/Meta-Llama-3.1-70B-Instruct-Q5_K_S.gguf --repeat_penalty 1.0 -i -r 'User:' -ngl 32 --ctx-size 4096 --file ../share/bengine-prompt-assistant.txt --grammar-file ../share/ai-json.gbnf", (char *)NULL);
// good		// execl("/bin/bash","/bin/bash", "-c", "/vol/space/llama.cpp/llama-cli -mg 0 -m /vol/space/oobabooga/models/Meta-Llama-3.1-70B-Instruct-Q6_K-00001-of-00002.gguf --repeat_penalty 1.0 -i -r 'User:' -ngl 31 --ctx-size 4096 --file ../share/bengine-prompt-assistant.txt --grammar-file ../share/ai-json.gbnf", (char *)NULL);
			
		// 	CREATE PROMPT

			std::stringstream construct_prompt;
			
			// // NEW OR CONTINUE SESSION
			// std::string sessname(session_name->get_string());
			// if ( !sessname.empty() )
			// {
			// 	construct_prompt << "PROMPT_CACHE_FILE=chat.prompt.bin CHAT_SAVE_DIR=./chat/" << sessname << " ";
			// }
			// else
			// {
			// 	session_output.clear();
			// }
			
			construct_prompt << llama_location->get_string() << " -m " << model_location->get_string() << " --repeat_penalty " << repeat_penalty->get_float() << " -i -r 'User:' -ngl " << layers_on_gpu->get_uint() << " --ctx-size " << ctx_size->get_uint() << " --file " << "bengine-ai-assistant.txt" << " --grammar-file  ../share/ai-json.gbnf";
			
			// if ( !sessname.empty() )
			// {
			// 	construct_prompt << " --prompt-cache cache.txt"; //  --prompt-cache-all
			// }



			// std::ifstream file1("../share/bengine-prompt-assistant.txt");
			std::ifstream file1( prompt_assistant->get_string() );
			std::ofstream file2("bengine-ai-assistant.txt");
			std::string line;
			if (file1.good() && file2.good())
			{
				while (getline(file1, line))
				{
					file2 << line;
					file2 << '\n';
				}
				file2 << cmd;
				file2 << '\n';
				file2 << '\n';
			}
			file1.close();
			file2.close();

			// EXECUTE LLAMA.CPP
				std::cout << construct_prompt.str() << std::endl;
				execl("/bin/bash","/bin/bash", "-c", construct_prompt.str().c_str(), (char *)NULL);
			
			// If `execl()` fails, print an error and exit
			perror("execl");

		}

		// PARENT PROCESS
		else
		{
			// enable ai runs
				m_ai_runs = true;

			// Set the output pipe to non-blocking mode (so we can read while the command runs)
			fcntl(out_pipe[0], F_SETFL, O_ASYNC);
			// fcntl(in_pipe[1], F_SETFL, O_NONBLOCK);
			
			// Close the ends of the pipes we won't use
			close(in_pipe[0]);  // Parent doesn't need to read from in_pipe
			close(out_pipe[1]); // Parent doesn't write to out_pipe

			// WE'RE STUCK IN THIS LOOP
			stop = false;
			started = false;
			// bool unqueried = true;
			after_first_command = false;

			//FIXME chrono reset every time to make timer work, shit.   

			begin = std::chrono::steady_clock::now();
			end = std::chrono::steady_clock::now();
		}

		return "";
	}
		
	std::string BEntityBrowser::execAI()
	{
		while ( true )
		{
			fcntl(out_pipe[0], F_SETFL, O_NONBLOCK);
			// std::cout << "read pipe" << std::endl;
			count = read(out_pipe[0], buffer, sizeof(buffer) - 1);

			// RECEIVED FROM PIPE
			if (count > 0)
			{
				begin = std::chrono::steady_clock::now();
				
				buffer[count] = '\0';  // Null-terminate the string
				output << buffer;
				std::cout << buffer << std::flush;
			}

			// NOT RECEIVED FROM PIPE
			else
			{
				end = std::chrono::steady_clock::now();
				if ( after_first_command && std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() > 5000000 )
				{
					std::cout << std::endl << "ai passed out after " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs], poking ai" << std::endl;

					// disable ai runs
						m_ai_runs = false;
					
					// KILL PROCESS AND EXIT
					kill( m_pid, SIGINT);
					// execl("/bin/bash","/bin/bash", "-c", "killall -9 llama-cli", (char *)NULL);
					return "I have failed you";
				}

				// end = std::chrono::steady_clock::now();
				if ( std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() > 100000 )
				{
					// std::cout << std::endl << "ai passed out after " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs], poking ai";
					
					begin = std::chrono::steady_clock::now();
					
					
					std::string result = output.str();
					if ( !started )
					{
						if ( result.find('{') != result.npos )
						{
							// std::cout << "started" << std::endl;
							started = true;
						}
					}
	
					if ( started && !stop )
					{
						
						if ( result.find('}') != result.npos )
						{
							// std::cout << std::endl << "STOP" << std::endl << std::endl;
							output.str("");
							output.clear();
							
							stop = true;
							
							after_first_command = true;
							
							parseH.reset();
							
							parseH.returnUntillStrip( "{", result );
							
							if ( result.find('\"') != result.npos )
							{
								parseH.returnUntillStrip( "\"", result );
								
								if ( parseH.beginMatchesStrip( "command\":", result ) )
								{
									// std::cout << std::endl << "COMMAND" << std::endl << std::endl;

									parseH.returnUntillStrip( "\"", result );
									
									std::string cmd_run = parseH.returnUntillStrip( "\"", result );
									// std::cout << std::endl << std::endl << std::endl << "command_run: " << cmd_run << std::endl << std::endl << std::endl;
									this->set( cmd_run.c_str() );
									
									// std::cout << std::endl << "textbox_last: " << textbox_last;

									std::string str = textbox_last;
									textbox_last = "";
									std::string::size_type pos = 0; // Must initialize
									while ( ( pos = str.find ("\n",pos) ) != std::string::npos )
									{
										str.replace(pos, 1, " \\ ");
									}

									str = str + "";

									// Write the str to the command
									const char *input = str.c_str();  // We send this to the child process
									write(in_pipe[1], input, strlen(input));
									const char *endchar = "\n";  // We send this to the child process
									write(in_pipe[1], endchar, strlen(endchar));

									// Close input pipe after sending input to indicate no more input
									// close(in_pipe[1]);
									
									// sleep (2);
									parseH.reset();
									started = false;
									stop = false;
									
									// return cmd_run;
								}
								else if ( parseH.beginMatchesStrip( "answer\":", result ) )
								{
									auto answer_full = parseH.returnRemainder( result );
									parseH.reset();
									answer_full = parseH.returnUntillStrip( "}", answer_full );
									parseH.reset();
									
									std::string answer_run;
									if ( answer_full.find('\"') != answer_full.npos )
									{
										parseH.returnUntillStrip( "\"", answer_full );
										answer_run = parseH.returnUntillStrip( "\"", answer_full );
									}
									
									else /*if ( answer_run.empty() )*/
									{
										answer_run = parseH.returnRemainder( answer_full );
									}
									std::cout << "\n";
								
									kill( m_pid, SIGINT );
									// wait(nullptr);

									std::string::size_type pos = 0; // Must initialize
									while ( ( pos = answer_run.find ("\\n",pos) ) != std::string::npos )
									{
										answer_run.replace(pos, 2, " \n");
									}

								// disable ai runs
									m_ai_runs = false;

									// std::cout << "answer: " << answer_run << std::endl;
									return answer_run;
								}
								else if ( parseH.beginMatchesStrip( "python\":", result ) )
								{
									auto answer_full = parseH.returnRemainder( result );
									parseH.reset();
									answer_full = parseH.returnUntillStrip( "}", answer_full );
									parseH.reset();
									
									std::string answer_run;
									if ( answer_full.find('\"') != answer_full.npos )
									{
										parseH.returnUntillStrip( "\"", answer_full );
										answer_run = parseH.returnUntillStrip( "\"", answer_full );
									}
									
									else /*if ( answer_run.empty() )*/
									{
										answer_run = parseH.returnRemainder( answer_full );
									}
									std::cout << "\n";

									kill( m_pid, SIGINT );
									// wait(nullptr);

									std::string::size_type pos = 0; // Must initialize
									while ( ( pos = answer_run.find ("\\n",pos) ) != std::string::npos )
									{
										answer_run.replace(pos, 2, " \n");
									}

									// disable ai runs
										m_ai_runs = false;

									// write pyscript
										std::ofstream file2("pyscript.py");
										file2 << answer_run;
										file2.close();

									execl("/bin/bash","/bin/bash", "-c", "python pyscript.py", (char *)NULL);

									// std::cout << "answer: " << answer_run << std::endl;
									return answer_run;
								}
								else if ( parseH.beginMatchesStrip( "pre_answer\":", result ) || parseH.beginMatchesStrip( "pre_python\":", result ) )
								{
									const char *endchar = "\n";  // We send this to the child process
									write(in_pipe[1], endchar, strlen(endchar));
									
									started = false;
									stop = false;
								}
							}
						}
					}
				}
				
			}

			usleep(10000);
		}
		// Wait for the child process to finish (important to avoid zombie processes)
		// wait(nullptr);
		return output.str();
	}

	
	bool BEntityBrowser::set_value( BEntity* e, const std::string& value )
	{
		{
			auto t_trigger = dynamic_cast<BEntity_bool*>( e );
			if ( t_trigger )
			{
				e->set();
				return true;
			}
		}
		{
			auto t_bool = dynamic_cast<BEntity_bool*>( e );
			if ( t_bool )
			{
				if ( value == "0" || value == "0.0" || value == "false" || value == "False" || value == "FALSE" )
				{
					e->set( false );
				}
				else // FIXME or be explicit?
				{
					e->set( true );
				}
				return true;
			}
		}
		{
			auto t_bool = dynamic_cast<BEntity_bool_property*>( e );
			if ( t_bool )
			{
				if ( value == "0" || value == "0.0" || value == "false" || value == "False" || value == "FALSE" )
				{
					e->set( false );
				}
				else // FIXME or be explicit?
				{
					e->set( true );
				}
				return true;
			}
		}
		{
			auto t_value = dynamic_cast<BEntity_uint*>( e );
			if ( t_value )
			{
				e->set( (uint)std::stoull( value ) );
				return true;
			}
		}
		{
			auto t_value = dynamic_cast<BEntity_uint_property*>( e );
			if ( t_value )
			{
				e->set( (uint)std::stoull( value ) );
				return true;
			}
		}
		{
			auto t_value = dynamic_cast<BEntity_int*>( e );
			if ( t_value )
			{
				e->set( (int)std::stoi( value ) );
				return true;
			}
		}
		{
			auto t_value = dynamic_cast<BEntity_int_property*>( e );
			if ( t_value )
			{
				e->set( (int)std::stoi( value ) );
				return true;
			}
		}
		{
			auto t_value = dynamic_cast<BEntity_float*>( e );
			if ( t_value )
			{
				e->set( (float)std::stof( value ) );
				return true;
			}
		}
		{
			auto t_value = dynamic_cast<BEntity_float_property*>( e );
			if ( t_value )
			{
				e->set( (float)std::stof( value ) );
				return true;
			}
		}
		{
			auto t_value = dynamic_cast<BEntity_double*>( e );
			if ( t_value )
			{
				e->set( (double)std::stod( value ) );
				return true;
			}
		}
		{
			auto t_value = dynamic_cast<BEntity_double_property*>( e );
			if ( t_value )
			{
				e->set( (double)std::stod( value ) );
				return true;
			}
		}
		{
			auto t_value = dynamic_cast<BEntity_string*>( e );
			if ( t_value )
			{
				e->set( value.c_str() );
				return true;
			}
		}
		{
			auto t_value = dynamic_cast<BEntity_string_property*>( e );
			if ( t_value )
			{
				e->set( value.c_str() );
				return true;
			}
		}

		return false;
	}
	
	std::string BEntityBrowser::print_value( BEntity* e )
	{
		std::stringstream txt;
		
		auto t_reference = dynamic_cast<BEntity_reference*>( e );
		if ( t_reference )
		{
			txt << e->get_reference()->id();
			return txt.str();
		}

		auto t_bool = dynamic_cast<BEntity_bool*>( e );
		if ( t_bool )
		{
			txt << e->get_bool();
			return txt.str();
		}

		auto t_bool_property = dynamic_cast<BEntity_bool_property*>( e );
		if ( t_bool_property )
		{
			txt << e->get_bool();
			return txt.str();
		}
		
		
		auto t_uint = dynamic_cast<BEntity_uint*>( e );
		if ( t_uint )
		{
			txt << e->get_uint();
			return txt.str();
		}

		auto t_uint_property = dynamic_cast<BEntity_uint_property*>( e );
		if ( t_uint_property )
		{
			txt << e->get_uint();
			return txt.str();
		}
		
		auto t_int = dynamic_cast<BEntity_int*>( e );
		if ( t_int )
		{
			txt << e->get_int();
			return txt.str();
		}

		auto t_int_property = dynamic_cast<BEntity_int_property*>( e );
		if ( t_int_property )
		{
			txt << e->get_int();
			return txt.str();
		}

		auto t_float = dynamic_cast<BEntity_float*>( e );
		if ( t_float )
		{
			txt << e->get_float();
			return txt.str();
		}

		auto t_float_property = dynamic_cast<BEntity_float_property*>( e );
		if ( t_float_property )
		{
			txt << e->get_float();
			return txt.str();
		}

		auto t_double = dynamic_cast<BEntity_double*>( e );
		if ( t_double )
		{
			txt << e->get_double();
			return txt.str();
		}

		auto t_double_property = dynamic_cast<BEntity_double_property*>( e );
		if ( t_double_property )
		{
			txt << e->get_double();
			return txt.str();
		}

		auto t_string = dynamic_cast<BEntity_string*>( e );
		if ( t_string )
		{
			txt << e->get_string();
			return txt.str();
		}

		auto t_string_property = dynamic_cast<BEntity_string_property*>( e );
		if ( t_string_property )
		{
			txt << e->get_string();
			return txt.str();
		}

		return txt.str();
	}
 
	// bool cmd_runquery::set()
	// {
	// 	// auto query = parent()->getChild( "query", 3 );
	// 	// auto num_a = logic->getChild( "number_a", 1 )->get_float();
	// 	// auto num_b = logic->getChild( "number_b", 1 )->get_float();
	// 	// logic->getChild( "result", 1 )->set( num_a + num_b );
	// 	// return true;
	// }

	
	
	
	
// ---- FACTORIES
	enum CLASS
	{
		  PLUGIN_INFO
		, SCENE
		, BENTITYBROWSER
		, LLAMA_GUI
	};

	extern "C" BEntity* create( BEntity* parent, const Buint type )
	{
		// PLUGIN DESCRIPTION ENTITY
			if ( type == PLUGIN_INFO )
			{
				BClassesHelper i;
					i.addClass( parent, CLASS::SCENE, "Scene" );
					i.addClass( parent, CLASS::BENTITYBROWSER, "BEntityBrowser" );
					i.addClass( parent, CLASS::LLAMA_GUI, "LLama_gui" );
				return 0;
			}
		// ENTITIES
			else
			{
				BEntity* i(0);
				
				if ( type == CLASS::SCENE )
					i = new Scene();
				else if ( type == CLASS::BENTITYBROWSER )
					i = new BEntityBrowser();
				else if ( type == CLASS::LLAMA_GUI )
					i = new LLama_GUI();
				return i;
			}
	}

	extern "C" void destroy( BEntity* p )
	{
		delete p;
	}

