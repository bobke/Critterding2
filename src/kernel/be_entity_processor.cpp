#include "be_entity_processor.h"
#include "be_timer.h"
#include "be_entity_top.h"
// #include <iostream>

	void BProcessor::reConstructList( BEntity* entity, Bbool skip_checks )
	{
		m_proc_entity_list.clear();
		// std::cout << " BProcessor::reConstructList " << entity->name() << std::endl;
		constructList( entity, skip_checks );
	}

	void BProcessor::constructList( BEntity* entity, Bbool skip_checks )
	{

		// if ( dynamic_cast<BEntityTop*>(entity) )  // ENTITY WILL NOT BE ADDED IF IT'S A TOP, JUST PASS CHILDREN.  THIS WILL BE ENTERED BY A THREAD TOP
		if ( skip_checks )
		{
			if ( entity->hasChildren() )
			{
				for_all_children_of(entity)
				{
					// SAME FOR IT'S CHILDREN
						constructList( (*child), false );
				}
			}
		}
		else // NORMAL CHECKING OF LIST
		{
			// CHECK ENTITY'S PROCESSING FLAG
				if ( entity->hasProcessing() )
				{
					// ADD ENTITY TO PROCESS LIST
						// std::cout << " BProcessor::constructList ADDING " << entity->name() << std::endl;
						addEntity( entity );
				}

			// RECURSIVELY CHECK THROUGH ALL CHILDREN FOR PROCESSING FLAG
				if ( entity->hasChildren() )
				{
					BEntityTop* entity_top = dynamic_cast<BEntityTop*>( entity );
					if ( entity_top )
					{
						// GO CREATE IT'S OWN PROCESSLIST
						entity_top->reConstructProcessList(entity_top);
					}
					else
					{
						for_all_children_of(entity)
						{
							constructList( (*child), false );
						}
					}
				}
		}

		// CHECK ENTITY'S PROCESSING FLAG
			if ( entity->hasDeferredProcessing() )
			{
				// ADD ENTITY TO PROCESS LIST
					addEntity( entity );
			}
	}

	// PROCESS
		void BProcessor::run()
		{
			// fixed end so when entities are added during a run they don't get to run
			// FIXME we actually want to be able to run it first frame though
			auto end = m_proc_entity_list.end();

			// PROCESS EACH ENTITY IN LIST
			for ( auto child=m_proc_entity_list.begin(); child != end; ++child )
			{
				// when 0 (always) or it's time
				if ( (*child).m_fps == 0 )
				{
					(*child).m_entity->process();
				}

				else
				{
					// update timer
					if ( m_timer_ms_total->get_uint() - (*child).m_time_last_processed >= (*child).m_ms_to_sleep )
					{
						(*child).m_time_last_processed = m_timer_ms_total->get_uint();
						(*child).m_entity->process();
					}
				}
			}
		}

	// ENTITY LIST CONTROL
		void BProcessor::addEntity( BEntity* entity )
		{
			// std::cout << " BProcessor::addEntity " << entity->id() << std::endl;
			// std::cout << "      fps: " << fpsBB( entity ) << std::endl;

			// create new ProcInfo and push_back on entity list
				ProcInfo t_proc_info;
				
				// pointer to entity itself
				t_proc_info.m_entity = entity;
				
				// grab fps back from fps backbuffer
				t_proc_info.m_fps = fpsBB( entity );

				// time last ran
				t_proc_info.m_time_last_processed = 0;

				// milliseconds to sleep
				t_proc_info.m_ms_to_sleep = 0;
				if ( t_proc_info.m_fps > 0 )
				{
					t_proc_info.m_ms_to_sleep = 1000 / t_proc_info.m_fps;
				}

				m_proc_entity_list.push_back( t_proc_info );

				// std::cout << " BProcessor::addEntity done " << entity->id() << std::endl;
		}

		void BProcessor::removeEntity( BEntity* entity )
		{
			// std::cout << " BProcessor::removeEntity " << entity->id() << std::endl;
			// FIXME this isn't thought out yet, at all
			
			// REMOVE FROM BACKBUFFER
			removeFpsBB( entity );

			// REMOVE DROM PROC LIST
				// PROCESS EACH ENTITY IN LIST
				for ( auto child=m_proc_entity_list.begin(); child != m_proc_entity_list.end(); ++child )
				{
					if ( (*child).m_entity == entity )
					{
						m_proc_entity_list.erase(child);
						return;
					}
				}
			
		}

		Buint BProcessor::listSize() const
		{
			return m_proc_entity_list.size();
		}
	
	// FPS
		void BProcessor::addFps( BEntity* entity, Buint fps )
		{
			// PROCESS EACH ENTITY IN LIST
			for ( auto child=m_proc_entity_list.begin(); child != m_proc_entity_list.end(); ++child )
			{
				// std::cout << "BProcessor::run() " << (*child).m_entity->name() << std::endl;
				if ( (*child).m_entity == entity )
				{
					(*child).m_fps = fps;
					return;
				}
			}
		}

		// // FIXME what is this doing?  we should be removing from backbuffer though
		// void BProcessor::removeFps( BEntity* entity )
		// {
		// 	// PROCESS EACH ENTITY IN LIST
		// 	for ( auto child=m_proc_entity_list.begin(); child != m_proc_entity_list.end(); ++child )
		// 	{
		// 		// std::cout << "BProcessor::run() " << (*child).m_entity->name() << std::endl;
		// 		if ( (*child).m_entity == entity )
		// 		{
		// 			m_proc_entity_list.erase(child);
		// 			return;
		// 		}
		// 	}
		// }
		
		Buint BProcessor::fps( BEntity* entity ) const
		{
			// FIND ENTITY
			for ( auto child=m_proc_entity_list.begin(); child != m_proc_entity_list.end(); ++child )
			{
				if ( (*child).m_entity == entity )
				{
					return (*child).m_fps;
				}
			}
			return 0;
		}

	// FPS BACKBUFFER, keeps record of the fps of an entity
		void BProcessor::addFpsBB( BEntity* entity, Buint fps )
		{
			// std::cout << "!!! settings FPS for entity " << entity->id() << " to " << fps << std::endl;
			m_be_fps_backbuffer[entity] = fps;

			// IF THIS ENTITY HAS FPS SPAWN TIMER IF NEEDED
				if ( m_timer_ms_total == 0 && fps > 0 )
				{
					auto found_sys = entity->topParent()->getChild("sys", 1);
					if ( !found_sys )
					{
						found_sys = entity->topParent()->addChild( "sys", new BEntity() );
					}
					auto timer = found_sys->getChild("timer", 1);
					if ( !timer )
					{
						timer = found_sys->addChild( "timer", new BTimer() );
					}
					m_timer_ms_total = timer->getChild("ms_total", 1);
				}
		}

		void BProcessor::removeFpsBB( BEntity* entity )
		{
			auto search = m_be_fps_backbuffer.find(entity);
			if (search != m_be_fps_backbuffer.end())
			{
				m_be_fps_backbuffer.erase(search);
			}
		}

		Buint BProcessor::fpsBB( BEntity* entity ) const
		{
			auto search = m_be_fps_backbuffer.find(entity);
			if (search != m_be_fps_backbuffer.end())
			{
				return search->second;
			}
			return 0;
		}
