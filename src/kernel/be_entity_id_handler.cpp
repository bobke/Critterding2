#include "be_entity_id_handler.h"
#include "be_entity_interface.h"

	B_ID_Handler::B_ID_Handler()
	: m_id_counter(0)
	, m_id_counter_offset(0)
	, m_grandTotalEntities(0)
	// , m_totalTime_lastRecycleCheck(0.0f)
	// , m_totalTime_last(0.0f)
	{};

	Buint64 B_ID_Handler::pop_front()
	// Buint64 B_ID_Handler::pop_front( const Bfloat totalTime )
	{
		m_mutex.lock();
		++m_grandTotalEntities;

		// m_totalTime_last = totalTime;

		if ( !m_map.empty() )
		{
			const auto& begin(m_map.begin());
			const Buint64 to_return = begin->first;
			m_map.erase ( begin );
// 			std::cout << "pop_front  " << this << " " << 1+to_return << std::endl;
			m_mutex.unlock();
			return to_return;
		}
		m_mutex.unlock();

// 		std::cout << "pop_front  " << this << " " << 1+m_id_counter << std::endl;
		return ++m_id_counter;
	}

// 	void B_ID_Handler::recycleID( const Buint64 t_id )
// 	{
// 		if ( entity->isIDRecyclable() )
// 		{
// 			spawn_IDRecycler();
// 
// 			if ( entity->hasDelayReuseID() )
// 				m_id_recycler->push(entity->id(), m_totalTime);
// 			else
// 				push(t_id);
// 		}
// 	}

	void B_ID_Handler::recycleID( const BEntity* entity )
	{
// 		std::cout << "recycleid " << entity->id() << std::endl;
		if ( entity->isIDRecyclable() )
		{
			m_mutex.lock();
			if ( entity->hasDelayReuseID() )
			{
				m_delayed_map.insert( { entity->id(), 0 } );
				// m_delayed_map.insert( { entity->id(), entity->topParent()->totalTime() } );
// 				m_delayed_map[entity->id()] = entity->topParent()->totalTime();
			}
			else
			{
				m_map.insert( { entity->id(), true } );
// 				m_map[entity->id()] = true;
			}
			m_mutex.unlock();

			processRecycle();
		}
	}

	void B_ID_Handler::setEntityIDCounterOffset( const Buint64& offset )
	{
		m_id_counter_offset = offset;
		m_id_counter += m_id_counter_offset;
	}

	void B_ID_Handler::processRecycle()
	{
		m_mutex.lock();
		// FIXME WHY ISN'T THIS TIME STUFF IN FRAMES, IF NEEDED AT ALL
// 		std::cout << "recycledebug test" << std::endl;
// 		std::cout << " total time " << totalTime << std::endl;
// 		std::cout << " m_totalTime_lastRecycleCheck " << m_totalTime_lastRecycleCheck << std::endl;
		
		// if it's at least x time ago that pop_front was last used
// 		if ( totalTime - m_totalTime_last > 0.0001f )
		{
			// if it's at least x time ago that we cleared id's from delayed_map
// 			if ( totalTime - m_totalTime_lastRecycleCheck > 0.1f )
			{
				// ERASE FROM DELAYED MAP AND PUSH THEM TO MAP
					Buint remove_delay_count(0);
					if ( !m_delayed_map.empty() )
					{
						// CHECKS CALC
							Buint64 max_checks( 1 + m_delayed_map.size() / 2 );

						// FROM THE FRONT
							auto front_it(m_delayed_map.begin());
							while ( max_checks-- > 0 && front_it != m_delayed_map.end() )
							{
// 								if ( totalTime - front_it->second > 60.0f )
								{
									m_map[front_it->first] = true;
									front_it = m_delayed_map.erase(front_it);
									
									++remove_delay_count;
								}
// 								else
// 									++front_it;
							}

						// FROM THE REAR, if front seek didn't reach end
						// FIXME NOT 100% SURE THIS IS STABLE, it might be because logically we should never reach the absolute first one.
							if ( max_checks > 0 )
							{
								auto back_it(m_delayed_map.rbegin());
								while ( max_checks-- > 0 && back_it != m_delayed_map.rend() )
								{
// 									if ( totalTime - back_it->second > 1.0f )
// 									{
										m_map[back_it->first] = true;
										m_delayed_map.erase(back_it->first);
										++remove_delay_count;
// 									}
// 									else
// 										++back_it;
								}
							}
					}

// 				// DECREASE m_id_counter AND REMOVE FROM MAP
// 					Buint64 remove_count(0);
// 					if ( !m_map.empty() )
// 					{
// 						// MAX_REMOVES CALC
// 							Buint64 max_checks( 1 + m_map.size() / 3 );
// 
// 						while ( !m_map.empty() && max_checks-- > 0 )
// 						{
// 							m_map.erase(m_map.rbegin()->first);
// 							--m_id_counter;
// 							remove_count++;
// 						}
// 					}

				// DECREASE m_id_counter AND REMOVE FROM MAP					if ( !m_map.empty() )
					Buint64 remove_count(0);
					{
						// MAX_REMOVES CALC
// 							Buint64 max_checks( 1 + m_map.size() / 3 );

// 						std::cout << this << " " << m_map.rbegin()->first  << " vs " << m_id_counter << std::endl;
						
						while ( !m_map.empty() && m_map.rbegin()->first == m_id_counter )
						{
							m_map.erase(m_map.rbegin()->first);
							--m_id_counter;
							remove_count++;
						}
					}

				// // DEBUG
				// 	if ( 0 == 1 && remove_count>0 )
				// 	{
				// 		std::cout << std::endl;
				// 		std::cout << std::endl;
				// 		std::cout << "recycledebug" << std::endl;
				// 		{
				// 			std::cout << "recycledebug> MAP : " << m_map.size();
				// 			if ( remove_count > 0 )
				// 				std::cout << " !!! REMOVED = " << remove_count;
				// 			std::cout << std::endl;
				// 		}
    // 
				// 		{
				// 			std::cout << "recycledebug> DELAYED : " << m_delayed_map.size();
				// 			if ( remove_delay_count > 0 )
				// 				std::cout << " !!! REMOVED = " << remove_delay_count;
				// 			std::cout << std::endl;
				// 		}
    // 
				// 		std::cout << "recycledebug> id counter: " << m_id_counter << std::endl;
				// 		std::cout << "recycledebug> grand total: " << m_grandTotalEntities << std::endl;
    // 
				// 		std::cout << std::endl;
				// 		std::cout << std::endl;
				// 	}

				// TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO 
				// AVOID REID BY FIRST ADDING TOP PARENT
				// DO REGISTERTOPARENT WHEN POSTCOPY!!!!!

// 				m_totalTime_lastRecycleCheck = totalTime;
			}
// 			m_totalTime_last = totalTime;
		}
		m_mutex.unlock();
	}


