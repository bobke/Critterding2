#include "population_controller.h"
#include "kernel/be_entity_core_types.h"

	void CdPopulationController::construct()
	{
		setFps(2);

		m_active = addChild( "active", new BEntity_bool() );
		m_population_trigger = addChild( "population_trigger", new BEntity_uint() );
		m_population_reduce_to = addChild( "population_reduce_to", new BEntity_uint() );
		m_active->set( true );
		m_population_trigger->set( Buint(160) );
		m_population_reduce_to->set( Buint(140) );

		m_critter_system = dynamic_cast<CdCritterSystem*>( topParent()->getChild("critter_system") );
		m_critter_unit_container = m_critter_system->getChild("unit_container");
	} 

	void CdPopulationController::process()
	{
		if ( m_active->get_bool() )
		{
			if ( m_critter_unit_container->numChildren() >= m_population_trigger->get_uint() )
			{
				while ( m_critter_unit_container->numChildren() > m_population_reduce_to->get_uint() )
				{
					m_critter_system->removeCritter( *m_critter_unit_container->children().begin() );
				}
			}
		}
	}
