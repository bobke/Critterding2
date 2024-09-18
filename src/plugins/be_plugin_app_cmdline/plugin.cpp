#include "plugin.h"
#include "kernel/be_lib_handler.h"
#include "kernel/be_entity_io_handler.h"
#include "kernel/be_plugin_base_entity_types.h"
#include <iostream>
#include <iomanip>
#include <array>
// #include <algorithm>
#include <memory>
// #include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <chrono>
#include <fstream>

#include <stdlib.h>

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
			qwindow->addChild( "x", "uint_property" )->set(Buint(1050));
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
					auto query = param_layout_H_b->addChild( "query_lineedit_INPUT", "QLineEdit_string" );
					query->set( "width", Buint(890) );
					query->set( "height", Buint(28) );
					
		// ENTITY BROWSER
			auto browser = addChild("entity_browser", "BEntityBrowser");
			
		// CONNECT QUERY AND BROWSER
			query->connectServerServer( browser );
			
		// TEST ENTITIES
			auto trigger = addChild("trigger", "trigger");
			auto reference = addChild("reference", "reference");
			reference->set( trigger );
			
			addChild("bool", "bool");
			addChild("uint", "uint");
			addChild("int", "int");
			addChild("float", "float");
			addChild("double", "double");
			addChild("string", "string");
	}

	void BEntityBrowser::construct()
	{
		current_position = topParent();
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
		
		auto textbox = vbox->getChild( "textbox_lineedit_OUTPUT", 3 );
		auto query = vbox->getChild( "query_lineedit_INPUT", 3 );

		m_search_from_root = false;

		parseH.reset();
		parseH.trimWhitespaces( command );
		command = parseH.returnRemainder( command );
		parseH.reset();

		// PRINT COMMAND
			std::string ct(">>");
			ct.append(command);
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
							textbox->set( output.str().c_str() );

						// RESET QUERY LINEEDIT
							query->set( "" );
						
						// ENDLINE TO TEXTBOX
							textbox->set( "" );

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
									textbox->set( output.str().c_str() );
								}

							// GO UP ONE ENTITY
								else
								{
									if ( candidate_entity == ".." )
									{
										if ( current_position->id() > 0 )
										{
											current_position = current_position->parent();

											output << std::endl << "entering " << current_position->nameFullPath();
											textbox_last = output.str();
											textbox->set( output.str().c_str() );
										}
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

											output << std::endl << "entering " << current_position->nameFullPath();
											textbox_last = output.str();
											textbox->set( output.str().c_str() );
										}
										else
										{
											// APPEND TO TEXTBOX
												output << std::endl << "entity does not exist: " << candidate_entity;
												output << std::endl << "try \"ls\"";
												textbox_last = output.str();
												textbox->set( output.str().c_str() );
										}
										
									}
								}

							// RESET QUERY LINEEDIT
								query->set( "" );
							
							// ENDLINE TO TEXTBOX
								textbox->set( "" );

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
							textbox->set( output.str().c_str() );
						}
						else
						{
							// APPEND TO TEXTBOX
								output << std::endl << "entity does not exist: " << candidate_entity;
								output << std::endl << "try \"ls\"";
								textbox_last = output.str();
								textbox->set( output.str().c_str() );
						}
						

						// RESET QUERY LINEEDIT
							query->set( "" );
						
						// ENDLINE TO TEXTBOX
							textbox->set( "" );

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
							if ( set_value( found_entity, candidate_value ) )
							{
								output << std::endl << "changed value of " << found_entity->name();
								if ( !candidate_value.empty() )
									output << " to: " << candidate_value;
							}
							else
							{
								output << std::endl << "failed to set value of " << found_entity->name() << " to: " << candidate_value;
							}

							textbox_last = output.str();
							textbox->set( output.str().c_str() );
						}
						else
						{
							// APPEND TO TEXTBOX
								output << std::endl << "entity does not exist: " << candidate_entity;
								output << std::endl << "try \"ls\"";
								textbox_last = output.str();
								textbox->set( output.str().c_str() );
						}


						// RESET QUERY LINEEDIT
							query->set( "" );
						
						// ENDLINE TO TEXTBOX
							textbox->set( "" );

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

						// APPEND TO TEXTBOX
							textbox_last = output.str();
							textbox->set( output.str().c_str() );

						// RESET QUERY LINEEDIT
							query->set( "" );
						
						// ENDLINE TO TEXTBOX
							textbox->set( "" );

						return true;
					}
					
				// AI
					else if ( program == "ai" )
					{
						auto candidate_value = parseH.returnRemainder( command );

						// RESET QUERY LINEEDIT
							query->set( "" );
						// ENDLINE TO TEXTBOX
							textbox->set( "" );
						
						output << execAI( candidate_value.c_str() );

						// APPEND TO TEXTBOX
							textbox->set( output.str().c_str() );

						return true;
					}

			}

		// APPEND TO TEXTBOX
			output << std::endl << "unknown command: " << program;
			output << std::endl << "possible commands: ls, cd, get, set, ai (asking the AI: dragons lay here)";
			// output << std::endl << "possible commands: ls, cd, get, set";

		// APPEND TO TEXTBOX
			textbox_last = output.str();
			textbox->set( output.str().c_str() );

		// RESET QUERY LINEEDUT
			query->set("");

		// ENDLINE TO TEXTBOX
			textbox->set( "" );

		// FIXME TURN AROUND SO THIS RETURNS TRUE
		return false;
	}

	std::string BEntityBrowser::execAI(const char* cmd)
	{
		// 	CREATE PROMPT
			std::ifstream file1("/vol/space/llama.cpp/prompts/bengine-assistant.txt");
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
		
		
		// 1. Create two pipes: one for input and one for output
		// `pipe()` returns two file descriptors: one for reading and one for writing
		if (pipe(in_pipe) == -1 || pipe(out_pipe) == -1) {
			perror("pipe");  // If pipe creation fails, show an error
			return "";        // Exit if pipe creation fails
		}

		// 2. Create a child process with fork()
		pid_t pid = fork();
		if (pid == -1) {
			perror("fork");  // If fork fails, show an error
			return "";        // Exit if fork fails
		}

		// CHILD PROCESS
		if (pid == 0)
		{
			// Redirect the standard input (stdin) to the reading end of in_pipe
			dup2(in_pipe[0], STDIN_FILENO);   // Now the command's stdin will come from in_pipe[0]
			// Redirect the standard output (stdout) to the writing end of out_pipe
			dup2(out_pipe[1], STDOUT_FILENO); // The command's stdout will go to out_pipe[1]

			// Close the unused ends of the pipes (important!)
			close(in_pipe[0]);  // Close in_pipe[0] because we are done with it in the child
			close(in_pipe[1]);  // Close in_pipe[1] in the child (the parent will write to this)
			close(out_pipe[0]); // Close out_pipe[0] in the child (the parent will read from this)
			close(out_pipe[1]); // Close out_pipe[1] because the child has stdout redirected to it

			
			// BE AWARE REMOVING -n 256 FIXED HANGING IN INTERACTIVE MODE
			
			// LAUNCHING LLAMA.CPP
			// execl("/bin/bash","/bin/bash", "-c", "/vol/space/llama.cpp/llama-cli -mg 0 -m /vol/space/oobabooga/models/llama-3-8b-liquid-coding-agent.F16.gguf --repeat_penalty 1.0 -i -r 'User:' -ngl 33 --ctx-size 4096 --file /vol/space/llama.cpp/prompts/bengine-assistant.txt --grammar-file /vol/space/llama.cpp/grammars/json.gbnf", (char *)NULL);
//ok			// execl("/bin/bash","/bin/bash", "-c", "/vol/space/llama.cpp/llama-cli -mg 0 -m /vol/space/oobabooga/models/Reflection-Llama-3.1-70B-Q4_K_M.gguf --repeat_penalty 1.0 -i -r 'User:' -ngl 26 --ctx-size 4096 --file /vol/space/llama.cpp/prompts/bengine-assistant.txt --grammar-file /vol/space/llama.cpp/grammars/json.gbnf", (char *)NULL);
//ok			// execl("/bin/bash","/bin/bash", "-c", "/vol/space/llama.cpp/llama-cli -mg 0 -m /vol/space/oobabooga/models/Meta-Llama-3.1-70B-Instruct-Q4_K_L.gguf --repeat_penalty 1.0 -i -r 'User:' -ngl 42 --ctx-size 4096 --file /vol/space/llama.cpp/prompts/bengine-assistant.txt --grammar-file /vol/space/llama.cpp/grammars/json.gbnf", (char *)NULL);
			// execl("/bin/bash","/bin/bash", "-c", "/vol/space/llama.cpp/llama-cli -mg 0 -m /vol/space/oobabooga/models/Meta-Llama-3.1-70B-Instruct-Q5_K_S.gguf --repeat_penalty 1.0 -i -r 'User:' -ngl 32 --ctx-size 4096 --file /vol/space/llama.cpp/prompts/bengine-assistant.txt --grammar-file /vol/space/llama.cpp/grammars/json.gbnf", (char *)NULL);
// good		// execl("/bin/bash","/bin/bash", "-c", "/vol/space/llama.cpp/llama-cli -mg 0 -m /vol/space/oobabooga/models/Meta-Llama-3.1-70B-Instruct-Q6_K-00001-of-00002.gguf --repeat_penalty 1.0 -i -r 'User:' -ngl 31 --ctx-size 4096 --file /vol/space/llama.cpp/prompts/bengine-assistant.txt --grammar-file /vol/space/llama.cpp/grammars/json.gbnf", (char *)NULL);

			// USE THESE
			// LAMA 3
			// execl("/bin/bash","/bin/bash", "-c", "/vol/space/llama.cpp/llama-cli -mg 0 -m /vol/space/oobabooga/models/Meta-Llama-3.1-70B-Instruct-Q6_K-00001-of-00002.gguf --repeat_penalty 1.0 -i -r 'User:' -ngl 31 --ctx-size 4096 --file bengine-ai-assistant.txt --grammar-file /vol/space/llama.cpp/grammars/json.gbnf", (char *)NULL);			
			// REFLECTION
			execl("/bin/bash","/bin/bash", "-c", "/vol/space/llama.cpp/llama-cli -mg 0 -m /vol/space/oobabooga/models/Reflection-Llama-3.1-70B-Q4_K_M.gguf --repeat_penalty 1.0 -i -r 'User:' -ngl 31 --ctx-size 1024 --file bengine-ai-assistant.txt --grammar-file /vol/space/llama.cpp/grammars/json.gbnf", (char *)NULL);			
			// LIQUID (8B)
			// execl("/bin/bash","/bin/bash", "-c", "/vol/space/llama.cpp/llama-cli -mg 0 -m /vol/space/oobabooga/models/llama-3-8b-liquid-coding-agent.F16.gguf --repeat_penalty 1.0 -i -r 'User:' -ngl 33 --ctx-size 4096 --file bengine-ai-assistant.txt --grammar-file /vol/space/llama.cpp/grammars/json.gbnf", (char *)NULL);			
			
			// If `execl()` fails, print an error and exit
			perror("execl");
			return "";
		}
		
		// PARENT PROCESS
		else
		{
			// Set the output pipe to non-blocking mode (so we can read while the command runs)
			fcntl(out_pipe[0], F_SETFL, O_NONBLOCK);
			fcntl(in_pipe[1], F_SETFL, O_NONBLOCK);
			
			// Close the ends of the pipes we won't use
			close(in_pipe[0]);  // Parent doesn't need to read from in_pipe
			close(out_pipe[1]); // Parent doesn't write to out_pipe

			// // // Write command to the command
			// write(in_pipe[1], cmd, strlen(cmd));
			// const char *endchar = "\n";  // We send this to the child process
			// write(in_pipe[1], endchar, strlen(endchar));

			// WE'RE STUCK IN THIS LOOP
			bool stop = false;
			bool started = false;
			// bool unqueried = true;
			bool after_first_command = false;
			// Read output from the command while it's running
			char buffer[128];
			ssize_t count;
			std::stringstream output;
			std::cout << "start loop" << std::endl;

			std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

			while ( true )
			{
				// std::cout << "read pipe" << std::endl;
				count = read(out_pipe[0], buffer, sizeof(buffer) - 1);

				if (count > 0)
				{
					begin = std::chrono::steady_clock::now();
					
					buffer[count] = '\0';  // Null-terminate the string
					output << buffer;
					std::cout << buffer;
				}
				else
				{
					end = std::chrono::steady_clock::now();
					if ( after_first_command && std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() > 6000000 )
					{
						std::cout << std::endl << "ai passed out after " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs], poking ai" << std::endl;

						write(in_pipe[1], cmd, strlen(cmd));
						
						const char *endchar = "\n";  // We send this to the child process
						write(in_pipe[1], endchar, strlen(endchar));
						begin = std::chrono::steady_clock::now();
						// continue;
					}

					// end = std::chrono::steady_clock::now();
					if ( std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() > 700000 )
					{
						// std::cout << std::endl << "ai passed out after " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs], poking ai";
						
						
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
								
								// std::cout << "|";
								// return result;
								stop = true;
								
								after_first_command = true;
								
								parseH.reset();
								
								parseH.returnUntillStrip( "{", result );
								
								if ( result.find('\"') != result.npos )
								{
									parseH.returnUntillStrip( "\"", result );
									
									// std::string cmd_found = parseH.returnUntillStrip( "command\":", result );
									// std::cout << std::endl << std::endl << "cmd_found : '" << cmd_found << "'" << std::endl << std::endl;
									// if ( !cmd_found.empty() )
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
										// std::cout << std::endl << "str: " << str;

	// 									// IGNORE FIRST
	// 									if ( unqueried )
	// 									{
	// 										// // Write command to the command
	// 										write(in_pipe[1], cmd, strlen(cmd));
	// 										const char *endchar = "\n";  // We send this to the child process
	// 										write(in_pipe[1], endchar, strlen(endchar));
	// 										unqueried = false;
	// 									}
	//          
	// 									else
										{
											// Write the str to the command
											const char *input = str.c_str();  // We send this to the child process
											write(in_pipe[1], input, strlen(input));
											const char *endchar = "\n";  // We send this to the child process
											write(in_pipe[1], endchar, strlen(endchar));
										}
										
										
										// Close input pipe after sending input to indicate no more input
										// close(in_pipe[1]);
										
										// sleep (2);
										parseH.reset();
										started = false;
										stop = false;
										
										// return cmd_run;
									}
									else
									{
										if ( parseH.beginMatchesStrip( "answer\":", result ) )
										{
											parseH.returnUntillStrip( "\"", result );
											std::string answer_run = parseH.returnUntillStrip( "\"", result );
											
												// const char *sigint = SIGINT;
												// write(in_pipe[1], sigint, strlen(sigint));
												kill( pid, SIGINT);

											return answer_run;
										}
									}
									
									// if ( unqueried )
									// {
									// 	// Write command to the command
									// 	write(in_pipe[1], cmd, strlen(cmd));
									// 	const char *endchar = "\n";  // We send this to the child process
									// 	write(in_pipe[1], endchar, strlen(endchar));
									// 	unqueried = false;
									// }
								}
							}
						}
						

					}
					
				}
					// end = std::chrono::steady_clock::now();
					// std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

				// if (count == 0)
				// {
				// 	// EAGAIN means no data available, continue looping
				// 	// continue;
				// 	break;
				// }
				// else if (count == 0)
				// {
				// 	// Command has finished and closed the pipe
				// 	break;
				// }
				
				
				// EXPERIMENT, CALL PROCESS LOOP
				// topParent()->process_general();
				
			}
			std::cout << "end loop" << std::endl;

			// std::cout << output.str();

			// Wait for the child process to finish (important to avoid zombie processes)
			wait(nullptr);
			return output.str();
		}

		return "";
	}

	
	bool BEntityBrowser::set_value( BEntity* e, const std::string& value )
	{
		if ( e->class_id() == std::string("trigger") )
		{
			e->set();
			return true;
		}
		else if ( e->class_id() == std::string("bool") || e->class_id() == std::string("bool_property") )
		{
			if ( value == "0" || value == "0.0" || value == "false" || value == "False" || value == "FALSE" )
			{
				e->set( false );
			}
			else
			{
				e->set( true );
			}
			return true;
		}
		else if ( e->class_id() == std::string("uint") || e->class_id() == std::string("uint_property") )
		{
			e->set( (uint)std::stoull( value ) );
			return true;
		}
		else if ( e->class_id() == std::string("int") || e->class_id() == std::string("int_property") )
		{
			e->set( (int)std::stoi( value ) );
			return true;
		}
		else if ( e->class_id() == std::string("float") || e->class_id() == std::string("float_property") )
		{
			e->set( (float)std::stof( value ) );
			return true;
		}
		else if ( e->class_id() == std::string("double") || e->class_id() == std::string("double_property") )
		{
			e->set( (double)std::stod( value ) );
			return true;
		}
		else if ( e->class_id() == std::string("string") || e->class_id() == std::string("string_property") )
		{
			e->set( value.c_str() );
			return true;
		}
		return false;
	}
	
	std::string BEntityBrowser::print_value( BEntity* e )
	{
		std::stringstream txt;
		if ( e->class_id() == std::string("reference") )
		{
			txt << e->get_reference()->id();
		}
		else if ( e->class_id() == std::string("bool") || e->class_id() == std::string("bool_property") )
		{
			txt << e->get_bool();
		}
		else if ( e->class_id() == std::string("uint") || e->class_id() == std::string("uint_property") )
		{
			txt << e->get_uint();
		}
		else if ( e->class_id() == std::string("int") || e->class_id() == std::string("int_property") )
		{
			txt << e->get_int();
		}
		else if ( e->class_id() == std::string("float") || e->class_id() == std::string("float_property") )
		{
			txt << e->get_float();
		}
		else if ( e->class_id() == std::string("double") || e->class_id() == std::string("double_property") )
		{
			txt << e->get_double();
		}
		else if ( e->class_id() == std::string("string") || e->class_id() == std::string("string_property") )
		{
			txt << e->get_string();
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
	};

	extern "C" BEntity* create( BEntity* parent, const Buint type )
	{
		// PLUGIN DESCRIPTION ENTITY
			if ( type == PLUGIN_INFO )
			{
				BClassesHelper i;
					i.addClass( parent, CLASS::SCENE, "Scene" );
					i.addClass( parent, CLASS::BENTITYBROWSER, "BEntityBrowser" );
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
				return i;
			}
	}

	extern "C" void destroy( BEntity* p )
	{
		delete p;
	}

