#include "critter_exchanger.h"
#include "kernel/be_entity_core_types.h"
#include <iostream>

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
			m_interval_seconds->set( 3.0f );
			m_last_updated = 0.0f;
			m_frame_counter_last = 0;
			auto timer = topParent()->getChild("sys", 1)->getChild("timer", 1);
			m_timer_s_total = timer->getChild("s_total", 1);
			m_timer_frame = timer->getChild("frame", 1);
	} 

	void CdCritterExchanger::process()
	{
		if ( m_active->get_bool() )
		{
			if ( m_critter_unit_container->hasChildren() )
			{
				// CHECK TIME
				const float elapsed_seconds = m_timer_s_total->get_float() - m_last_updated;
				const Buint elapsed_frames = m_timer_frame->get_uint() - m_frame_counter_last;
				if ( elapsed_seconds >= m_interval_seconds->get_float() ) //FIXME an line edit input for this
				{
					// SAVE CRITTER
						std::cout << "elapsed_seconds: " << elapsed_seconds << std::endl;

						// PICK RANDOM CRITTER
							m_rng->set( "min", Bint(0) );
							m_rng->set( "max", Bint( m_critter_unit_container->numChildren())-1 );
							auto randomChild = m_critter_unit_container->children()[m_rng->get_int()];

						// SAVE CRITTER
							std::cout << "to save " << randomChild->id() << " " << randomChild->name() << std::endl;

					// SET VALUES NEEDED FOR NEXT UPDATE
						m_last_updated = m_timer_s_total->get_float();
						m_frame_counter_last = m_timer_frame->get_uint();
				}
			}
		}
	}
