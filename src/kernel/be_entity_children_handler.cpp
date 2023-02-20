#include "be_entity_children_handler.h"
#include "be_entity_core_types.h"
#include "be_entity_id_handler.h"
#include "be_entity_io_handler.h"
// #include "be_lib_handler.h"
// #include <iostream>
// #include <sstream>


	// CONSTRUCTORS / DESTRUCTOR

		B_Children_Handler::B_Children_Handler() 
		: m_admin_app_search_entity(0)
		, m_cmdbuffer(0)
		{
			// CHILD ID HANDLING
				m_id_handler = new B_ID_Handler();
		}

		B_Children_Handler::~B_Children_Handler() 
		{
			// CHILD ID HANDLING
				delete m_id_handler;
		}

	// PROCESS POST (THREADS)
		void B_Children_Handler::process_post() const
		{
// // 			// PROCESS ID'S
// // 			if ( m_has_id_handler )
// // 			{
// // 				m_id_handler->processRecycle( m_timer->getTotalSeconds() );
// // 			}
// 
// 			// PROCESS CHILDREN
// 			for_all_children
// 			{
// 				(*child)->process_post();
// 			}
		}
		
	// CHILDREN
// 		bool B_Children_Handler::hasChildren(BEntity* const entity)
// 		{
// 			return hasChildren( entity->id() );
// 		}
	
// 		bool B_Children_Handler::hasChildren(const BEntity* entity)
// 		{
// // 			std::cout << " -- " << entity->id() << std::endl;
// 			if ( m_children_map.contains( entity->id() ) )
// 			{
// // 				std::cout << " -- > " << entity->id() << " has children" << std::endl;
// 				return true;
// 			}
// 			return false;
// 		}

		BEntityVector& B_Children_Handler::children(const BEntity* entity)
		{
			return m_children_map[entity->id()];
		}

		bool B_Children_Handler::addChild( BEntity* parent, BEntity* child )
		{
			if ( child != 0 )
			{
				// if parent doesn't have a children vector, create one
					if ( !parent->hasChildren() )
					{
		// 				std::cout << "B_Children_Handler::addChild creating vector for: " << parent->id() << std::endl;
						m_children_map[parent->id()] = BEntityVector();
						parent->setHasChildren( true );
					}

				// push it on
					m_children_map[parent->id()].push_back(child);

				child->setIDRecyclable();
				child->setID( spawnId() );
				child->setParent(parent);
				// child->setStartTime(parent->getTimer()->getTotalMilliSeconds());
				
	// 			std::cout << "B_Children_Handler::addChild: " << child->id() << " : " << parent->id() << std::endl;
				
				// RE-ID CHILDREN
					// this is giving builtin children new id's
					// remove and re add all the children if it's a container
					if ( child && child->hasChildren() )
					{
						BEntityVector& children_vector( children( child ) );

						for ( auto child=children_vector.begin(); child != children_vector.end(); ++child )
						{
							(*child)->setBuiltin();		// MARK child as a builtin, so it doesn't copy when entity_copy_callback
							(*child)->setID( spawnId() );
						}
					}

					
				parent->onAddChild( child );
// 				child->spawnCommandBuffer(); // FIXME SEEMS NOT NEEDED ??? and suddenly it doesn't work with threads anymore when uncommented...

// 				child->construct();

				// ADD PROCESSING
					if ( child->hasProcessing() )
					{
						// std::cout << "adding " << child->id() << " tot the processor" << std::endl;
						parent->addProcessing(child);
// 						child->addProcessing(child);
						// std::cout << "done adding" << child->id() << " tot the processor" << std::endl;
					}
				
				// ADD TO ADMIN WINDOW, IF EXISTS, add the command to the command buffer
				
					// // if ( m_admin_app_search_entity == 0 )
					// {
					// 	auto scene = child->topParent()->getChild("Scene", 1);
					// 	if ( scene )
					// 	{
					// 		auto admin_app = scene->getChild("Admin App", 2);
					// 		if ( admin_app )
					// 		{
					// 			// std::cout << "to add" << std::endl;
					// 			admin_app->set( "add", child );
					// 		}
					// 	}
					// }
				
				// FIXME SLOW AF
// 					if ( m_admin_app_search_entity == 0 )
// 					{
// 						auto scene = child->topParent()->getChild("Scene", 1);
// 						if ( scene )
// 						{
// 							auto admin_app = scene->getChild("Admin App", 2);
// 							if ( admin_app )
// 							{
// 								m_admin_app_search_entity = admin_app->getChild("qt vboxlayout", 6);
// 							}
// 						}
// 					}
// 
// 					if ( m_cmdbuffer == 0 )
// 					{
// 						m_cmdbuffer = child->topParent()->getChild("_command_buffer", 1);
// 					}
// 					
// 					// FAILS BECAUSE NAME NOT IN ORDER YET
// 					// if ( m_admin_app_search_entity )
// 					// {
// 					// 	std::stringstream stream;
// 					// 	stream << "admin_section_" << parent->id() << "_" << parent->name();
// 					// 	auto admin_section = m_admin_app_search_entity->getChild( stream.str().c_str() );
// 					// 	if ( admin_section )
// 					// 	{
// 					// 		auto r = new BEntity_reference();
// 					// 		r->set( child );
// 					// 		m_admin_app_search_entity->set("command_execute", r);
// 					// 	}
// 					// }
// 					
// 					if ( m_admin_app_search_entity && m_cmdbuffer )
// 					{
// 						// FIXME SLOW AF
// 						std::stringstream stream;
// 						stream << "admin_section_" << parent->id() << "_" << parent->name();
// 						auto admin_section = m_admin_app_search_entity->getChild( stream.str().c_str() );
// 						if ( admin_section )
// 						{
// 							auto groupbox = admin_section->getChild("qt groupbox entities", 1);
// 							if ( groupbox )
// 							{
// 								auto vlayout = groupbox->getChild("qt vboxlayout", 1);
// 								if ( vlayout )
// 								{
// 									auto cmdref = m_cmdbuffer->addChild("admin_entity_add", new BEntity_reference() );
// 									cmdref->set( child );
// 									cmdref->addChild("vlayout", new BEntity_reference() )->set( vlayout );
// 								}
// 							}
// 						}
// 					}
					

				
				
				
				return true;
			}
			return false;
		}

		void B_Children_Handler::clearChildren( BEntity* parent )
		{
			// FIXME DISABLED THIS FOR NOW BUT NEEDS TO WORK
			while ( parent->hasChildren() )
			{
				auto& children_vector = children( parent );
				
				const auto it = children_vector.end()-1;

				removeChild( parent, it );
			}

		}
		
		// WRAPPER FUNCTION, LOOKS UP THE MAP ITERATOR TO PASS ON TO REAL REMOVE
		bool B_Children_Handler::removeChild( BEntity* parent, BEntity* entity )
		{
				BEntityVector& children_vector = children( parent );

				// reverse lookup and remove child from children map
				auto it = children_vector.end();
				while ( it > children_vector.begin() )
				{
					it--;
					if( (*it)->id() == entity->id() )
					{
						return removeChild( parent, it );
					}
				}
			return false;
		}

		bool B_Children_Handler::removeChild( BEntity* parent, const BEntityVector::iterator& entity_iterator )
		{
// 			std::cout << "B_Children_Handler::removeChild: " << (*entity_iterator)->id() << std::endl;
			BEntity* entity = (*entity_iterator);

			// // REMOVE ADMIN ITEMS
			// // FIXME SLOW AF
			// 	if ( entity->parent()->name() != "_command_buffer")
			// 	{
			// 		if ( m_admin_app_search_entity )
			// 		{
			// 			std::stringstream stream;
			// 			stream << "admin_section_" << entity->id() << "_" << entity->name();
			// 			auto admin_section = m_admin_app_search_entity->getChild( stream.str().c_str() );
			// 			if ( admin_section )
			// 			{
			// 				// std::cout << "SHOULD REMOVE " << stream.str() << std::endl;
			// 				admin_section->parent()->removeChild( admin_section );
			// 			}
			// 		}
			// 	}
			
			// REMOVE ADMIN ITEMS
				// == 1 because it gets removed later, becoming 0 (no children)
				if ( entity->hasAdmin() || entity->isAdmin() || ( entity->parent()->hasAdmin() && entity->parent()->numChildren() == 1 ) )
				{
					if ( entity->topParent() )
					{
						auto admin_app = entity->getAdminWindow();

						// auto admin_app = getAdminWindow();
						if ( admin_app )
						{
							admin_app->set( "rm", entity );
						}
						
						// auto scene = entity->topParent()->getChild("Scene", 1); // FIXME DOING IT TWICE? (getadminwindow)
						// if ( scene )
						// {
						// 	auto admin_app = scene->getChild("Admin App", 2);
      // 
						// 	// auto admin_app = getAdminWindow();
						// 	if ( admin_app )
						// 	{
						// 		admin_app->set( "rm", entity );
						// 	}
						// }
					}
				}

			// EXTERNAL CHILD
				if ( dynamic_cast<BEntity_external*>(entity) )
				{
					entity->get_reference()->parent()->removeChild( entity->get_reference() );
				}

			// REMOVE CHILDREN
				clearChildren( entity );

			// DESTRUCT
				entity->destruct();

			// ONREMOVE
				parent->onRemoveChild( (*entity_iterator) );

			// REMOVE PROCESSING
				if ( entity->hasProcessing() )
					entity->removeProcessing();

			// REMOVE CONNECTIONS
				if ( entity->hasIOHandler() )
				{
					if ( entity->hasOutput() )
					{
						// GET LOCAL INPUT FOR EACH EACH CONNECTIONS
						const auto& t_output = entity->getOutput()->m_connections;
						for ( auto it1(t_output.begin()); it1 != t_output.end(); ++it1 )
						{
							(*it1)->getInputEntity()->getInput()->removeConnection(entity);
						}
					}

					if ( entity->hasInput() )
					{
						const auto& e_input = entity->getInput()->m_connected_outputs;
						for ( auto it1(e_input.begin()); it1 != e_input.end(); ++it1 )
						{
							(*it1)->getOutput()->removeConnection( entity );
						}
					}

				// FIXME 
					entity->deleteIOHandler();
				}

			// RECYCLE ID
				recycleID(entity);

			// REALLY REMOVE CHILD FROM PARENT VECTOR
				BEntityVector& children_vector = children( parent );
				children_vector.erase(entity_iterator);

			// IF NO CHILDREN LEFT, REMOVE PARENT VECTOR ENTIRELY
				if ( children_vector.empty() )
				{
					m_children_map.erase( parent->id() );
					parent->setHasChildren(false);
				}

			// IF ADMIT SEARCH SHORTCUT IS REMOVED RESET IT
				if ( m_admin_app_search_entity == entity )
				{
					m_admin_app_search_entity = 0;
				}
				
			// REMOVE NAME
				entity->removeName();

			// DEBUG OUTPUT
				// std::cout << "B_Children_Handler::delete: " << entity->id() << " : " << entity->name() << std::endl;
				
			// FINALLY DELETE ENTITY
				delete entity;

			return true;
		}

		Buint B_Children_Handler::numChildren( const BEntity* entity )
		{
			if ( entity->hasChildren() )
			{
				return m_children_map[entity->id()].size();
			}
			return 0;
		}

		Buint B_Children_Handler::numTotalChildren( const BEntity* entity )
		{
			if ( entity->hasChildren() )
			{
				Buint childrens_totalchildren( m_children_map[entity->id()].size() );
				for_all_children_of(entity)
				{
					childrens_totalchildren += numTotalChildren( (*child) );
				}
				return childrens_totalchildren;
			}
			return 0;
		}

	// CHILD ID HANDLING
		Buint B_Children_Handler::spawnId()
		{
			const auto id_to_return(m_id_handler->pop_front());
// 			entity->setIDRecyclable();
			return id_to_return;
		}

		void B_Children_Handler::recycleID( BEntity* e )
		{
			m_id_handler->recycleID(e);
		}


		void B_Children_Handler::setEntityIDCounterOffset( const Buint offset )
		{
			m_id_handler->setEntityIDCounterOffset(offset);
		}

// 		void B_Children_Handler::spawn_IDHandler()
// 		{
// 			if ( !m_has_id_handler )
// 			{
// 				m_id_handler = new B_ID_Handler();
// 				m_has_id_handler = true;
// 			}
// 		}
		
// 		void B_Children_Handler::clearIDHandler()
// 		{
// 			if ( m_has_id_handler )
// 			{
// 				delete m_id_handler;
// 				m_has_id_handler = false;
// 			}
// 			
// 		}










































		void B_Children_Handler::print(BEntity* entity, const Buint max_levels)
		{
			std::cout << std::endl;
			std::cout << "printing entity tree to " << max_levels << " levels" << std::endl;

			std::cout << entity->id() << ": " << entity->name() << std::endl;
			print_children( entity, 1, max_levels );
			
			std::cout << std::endl;
		}

		void B_Children_Handler::print_children( const BEntity* entity, const Buint level, const Buint max_levels )
		{
			if ( entity->hasChildren() && level <= max_levels )
			{
				const BEntityVector& children_vector( children( entity ) );

				for ( auto child=children_vector.begin(); child != children_vector.end(); ++child )
				{
					do_times(level)
					{
						std::cout << "    ";
					}
					std::cout << (*child)->id() << ": ";
					
					// * if processing
					if ( (*child)->hasProcessing() )
						std::cout << "*";
					// ** if deferred processing
					// if ( (*child)->hasDeferredProcessing() )
					// 	std::cout << "**";
					
					std::cout << (*child)->name() << std::endl;

					// if ( (*child)->name() == "_external_child" )
					// {
					auto external = dynamic_cast<BEntity_external*>( *child );
					if ( external )
					{
						auto external_child = external->get_reference();
						do_times(level+1)
						{
							std::cout << "    ";
						}
						std::cout << external_child->id() << ": ";
						
						// * if processing
						if ( external_child->hasProcessing() )
							std::cout << "*";
						// ** if deferred processing
						// if ( (*child)->hasDeferredProcessing() )
						// 	std::cout << "**";
						
						std::cout << external_child->name() << std::endl;
						print_children(external_child, level+2, max_levels); 
					}

					print_children((*child), level+1, max_levels); 
				}
			}

			
		}

 
