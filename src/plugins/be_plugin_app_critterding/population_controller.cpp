#include "population_controller.h"
#include "kernel/be_entity_core_types.h"

	void CdPopulationController::construct()
	{
		setFps(1);

		m_active = addChild( "active", new BEntity_bool() );
		m_active->set( true );

		m_population_trigger = addChild( "population_trigger", new BEntity_uint() );
		m_population_trigger->set( Buint(160) );

		m_population_reduce_to = addChild( "population_reduce_to", new BEntity_uint() );
		m_population_reduce_to->set( Buint(120) );

		m_y_trigger = addChild( "y_trigger", new BEntity_float() );
		m_y_trigger->set( -200.0f );

		m_critter_system = dynamic_cast<CdCritterSystem*>( topParent()->getChild("critter_system") );
		m_critter_unit_container = m_critter_system->getChild("unit_container");

		auto food_system = topParent()->getChild("food_system");
		m_food_unit_container = food_system->getChild("unit_container");
		
		m_energy_reduce_by = addChild( "energy_reduce_by", new BEntity_uint() );
		m_energy_reduce_by->set( Buint(1) );
		
		m_food_number_of_units = food_system->getChild("settings")->getChild("number_of_units");
	} 

	void CdPopulationController::process()
	{
		if ( m_active->get_bool() )
		{
			if ( m_critter_unit_container->numChildren() >= m_population_trigger->get_uint() )
			{
				// KEEP REMOVING FIRST UNTIL LIMIT REACHED
				while ( m_critter_unit_container->numChildren() > m_population_reduce_to->get_uint() )
				{
					m_critter_system->removeCritter( *m_critter_unit_container->children().begin() );
				}

				// REDUCE ENERGY
				if ( m_energy_reduce_by->get_uint() > 0 )
				{
					m_food_number_of_units->set( m_food_number_of_units->get_uint() - m_energy_reduce_by->get_uint() );
				}
			}

			// REMOVE CRITTERS FALLEN BELOW y
			for_all_children_of( m_critter_unit_container )
			{
				const float posY =  (*child)->getChild("external_body", 1)->get_reference()->getChild("body_fixed1", 1)->getChild("bodyparts", 1)->getChild("external_bodypart_physics", 1)->get_reference()->getChild("transform", 1)->getChild("position_y", 1)->get_float();
				if ( posY < m_y_trigger->get_float() )
				{
					// std::cout << "THE CRITTER FALLENING" << std::endl;
					m_critter_system->removeCritter( *child );
					return;
				}
			}

			// REMOVE FOOD FALLEN BELOW y
			for_all_children_of2( m_food_unit_container )
			{
				const float posY =  (*child2)->getChild("external_physics", 1)->get_reference()->getChild("transform", 1)->getChild("position_y", 1)->get_float();
				if ( posY < m_y_trigger->get_float() )
				{
					// std::cout << "THE FOOD FALLENING" << std::endl;
					m_food_unit_container->removeChild( *child2 );
					return;
				}
			}
		}
	}
