#include "critter_exchanger.h"
#include "kernel/be_entity_core_types.h"
#include "kernel/be_entity_ops_copy.h"
#include <iostream>
#include <unistd.h>


	void CdCritterExchanger::construct()
	{
		setFps(1);

		m_active = addChild( "active", new BEntity_bool() );
		m_active->set( true );

		auto critterding = topParent()->getChild("Scene", 1)->getChild("Critterding");

		m_critter_system = dynamic_cast<CdCritterSystem*>( critterding->getChild("critter_system") );
		m_critter_unit_container = m_critter_system->getChild("unit_container");

		m_rng = critterding->getChild("random_number_generator");

		// TIMER
			m_interval_seconds = addChild( "interval_seconds", new BEntity_float() );
			m_interval_seconds->set( 180.0f );
			m_last_updated = 0.0f;
			m_frame_counter_last = 0;
			auto timer = topParent()->getChild("sys", 1)->getChild("timer", 1);
			m_timer_s_total = timer->getChild("s_total", 1);
			m_timer_frame = timer->getChild("frame", 1);
			
		// WEIGHTS
			m_weight_save = addChild( "weight_save", new BEntity_uint() );
			m_weight_load = addChild( "weight_load", new BEntity_uint() );
			
			m_weight_save->set( Buint(40) );
			m_weight_load->set( Buint(60) );
	} 

	void CdCritterExchanger::process()
	{
		if ( m_active->get_bool() )
		{
			// CHECK TIME
			const float elapsed_seconds = m_timer_s_total->get_float() - m_last_updated;
			const Buint elapsed_frames = m_timer_frame->get_uint() - m_frame_counter_last;
			if ( elapsed_seconds >= m_interval_seconds->get_float() ) //FIXME an line edit input for this
			{

				int sum = m_weight_save->get_uint() + m_weight_load->get_uint();
				// PICK SAVE OR LOAD
				m_rng->set( "min", Bint(0) );
				m_rng->set( "max", sum );

				// SAVING
				if ( m_rng->get_int() < m_weight_save->get_uint() )
				{
					if ( m_critter_unit_container->hasChildren() )
					{
							std::cout << "elapsed_seconds: " << elapsed_seconds << std::endl;

						// PICK RANDOM CRITTER
							m_rng->set( "min", Bint(0) );
							m_rng->set( "max", Bint( m_critter_unit_container->numChildren())-1 );
							auto randomChild = m_critter_unit_container->children()[m_rng->get_int()];

						// CREATE FILENAME
							std::string filename_to_save;
							unsigned int count(0);
							filename_to_save = "critter_exchange_unit_";
							filename_to_save.append(std::to_string(count));
							filename_to_save.append(".ent");

							while (access(filename_to_save.c_str(), F_OK) == 0)
							{
								// file exists
								filename_to_save = "critter_exchange_unit_";
								filename_to_save.append(std::to_string(++count));
								filename_to_save.append(".ent");
							}

						// SAVE CRITTER
							std::cout << "to save " << randomChild->id() << " " << filename_to_save << std::endl;

							BEntitySave b;
							b.saveEntity( randomChild, filename_to_save );
					}
				}

				// LOADING
				else
				{
					// CREATE FILENAME
						std::string filename;
						unsigned int count(0);
						unsigned int countmax(100);

						filename = "critter_exchange_unit_";
						filename.append(std::to_string(count));
						filename.append(".ent");

						while ( access(filename.c_str(), F_OK) != 0 && count++ < countmax )
						{
							// file exists
							filename= "critter_exchange_unit_";
							filename.append(std::to_string(count));
							filename.append(".ent");
						}

						// found
						if ( count < countmax )
						{
							std::cout << "to load " << filename << std::endl;
							// lOAD CRITTER
							BEntityLoad b;
							b.loadEntity(m_critter_unit_container, filename);

							// REMOVE FILE
							if( remove( filename.c_str() ) != 0 )
								perror( "Error deleting file" );
							else
								puts( "File successfully deleted" );
						}
				}
			// SET VALUES NEEDED FOR NEXT UPDATE
				m_last_updated = m_timer_s_total->get_float();
				m_frame_counter_last = m_timer_frame->get_uint();
			}
		}
	}
