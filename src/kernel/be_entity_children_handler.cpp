#include "be_entity_children_handler.h"
#include "be_entity_core_types.h"
#include "be_entity_id_handler.h"
#include "be_entity_io_handler.h"
// #include "be_lib_handler.h"
#include <iostream>
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

		BEntityVector& B_Children_Handler::children(const BEntity* entity)
		{
			m_mutex_children.lock();
			BEntityVector& r = m_children_map[entity->id()];
			m_mutex_children.unlock();
			
			return r;
		}

		bool B_Children_Handler::addChild( BEntity* parent, BEntity* child )
		{
			if ( child != 0 )
			{
				m_mutex_children.lock();
				
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
				// std::cout << "setting parent of " << child->id() << " to " << parent->id() << std::endl;
				child->setParent( parent );
				// std::cout << "ok" << std::endl;
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

				m_mutex_children.unlock();
				return true;
			}
			return false;
		}

		void B_Children_Handler::clearChildren( BEntity* parent )
		{
			// if ( parent->hasChildren() )
			// 	std::cout << "clearChildren:: " << parent->id() << " name: " << parent->name() << std::endl;

			while ( parent->hasChildren() )
			{
				auto& children_vector = children( parent );
				
				const auto it = children_vector.end()-1;
				// std::cout << "  clearChildren:: " << (*it)->id() << " name: " << (*it)->name() << std::endl;

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

			// m_mutex.unlock();
			return false;
		}

		bool B_Children_Handler::removeChild( BEntity* parent, const BEntityVector::iterator& entity_iterator )
		{
			// m_mutex.lock();
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

			// PARENT IS DEPLOYED EXTERNAL CHILD, experimental
				if ( dynamic_cast<BEntity_reference*>( entity ) )
				{
					if ( entity->name() == "_external_child_backward_ref" )
					{
						// set external_child's reference here to 0
						auto external_entity = entity->get_reference();
						if ( external_entity != 0 )
						{
							if ( external_entity->get_reference() != 0 )
							{
								external_entity->set( (BEntity*)0 );
							}
						}
					}
				}

			// EXTERNAL CHILD
				if ( dynamic_cast<BEntity_external*>( entity ) )
				{
					if ( entity->get_reference() != 0 )
					{
						auto deployed_entity = entity->get_reference();

						// FIRST it's reference back here to 0
						auto backward_ref = deployed_entity->getChild("_external_child_backward_ref", 1);
						if ( backward_ref )
						{
							backward_ref->set( (BEntity*)0 );
						}

						// remove deployed entity
						deployed_entity->parent()->removeChild( deployed_entity );
					}
				}

			// REMOVE CHILDREN
				clearChildren( entity );

				m_mutex.lock();
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
				// m_mutex_children.lock();
				BEntityVector& children_vector = children( parent );
				children_vector.erase(entity_iterator);

			// IF NO CHILDREN LEFT, REMOVE PARENT VECTOR ENTIRELY
				m_mutex_children.lock();
				if ( children_vector.empty() )
				{
					m_children_map.erase( parent->id() );
					parent->setHasChildren(false);
				}
				m_mutex_children.unlock();

			// IF ADMIT SEARCH SHORTCUT IS REMOVED RESET IT
				if ( m_admin_app_search_entity == entity )
				{
					m_admin_app_search_entity = 0;
				}
				
			// REMOVE NAME
				entity->removeName();
				m_mutex.unlock();

			// DEBUG OUTPUT
				// std::cout << "B_Children_Handler::delete: " << entity->id() << " : " << entity->name() << std::endl;
				
			// m_mutex.unlock();

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

 
