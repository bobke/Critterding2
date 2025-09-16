#include "population_controller.h"
#include "kernel/be_entity_core_types.h"
#include "critter_system.h"
#include "food_system.h"
#include <iostream>

	void CdPopulationController::construct()
	{
		setFps(1);

		m_active = addChild( "active", new BEntity_bool() );
		m_active->set( true );

		m_population_trigger = addChild( "population_trigger", new BEntity_uint() );
		m_population_trigger->set( Buint(200) );

		m_population_reduce_to = addChild( "population_reduce_to", new BEntity_uint() );
		m_population_reduce_to->set( Buint(150) );

		m_energy_reduce_by = addChild( "energy_reduce_by", new BEntity_uint() );
		m_energy_reduce_by->set( Buint(1) );
		
		m_below_y_trigger = addChild( "below_y_trigger", new BEntity_float() );
		m_below_y_trigger->set( -200.0f );

		m_critter_containers = addChild("critter_containers", new BEntity());
		m_food_containers = addChild("food_containers", new BEntity());
	} 

	void CdPopulationController::process()
	{
		if ( m_active->get_bool() )
		{
			// CRITTER DEPTH CHECK AND CALCULATE SUM OF ALL CRITTERS
			int sumCritters( 0 );
			{
				for_all_children_of3( m_critter_containers )
				{
					auto critter_unit_container = (*child3)->get_reference();
					sumCritters += critter_unit_container->numChildren();

					// REMOVE CRITTERS FALLEN BELOW y
					for_all_children_of( critter_unit_container )
					{
						auto critter = dynamic_cast<CdCritter*>( *child );
						if ( critter )
						{
							if ( critter->m_transform_shortcut == 0 )
							{
								critter->m_transform_shortcut = critter->getChild("external_body", 1)->get_reference()->getChild("body_fixed1", 1)->getChild("bodyparts", 1)->getChild("external_bodypart_physics", 1)->get_reference()->getChild("transform", 1);
							}

							if ( critter->m_transform_shortcut->getChild("position_y", 1)->get_float() < m_below_y_trigger->get_float() )
							{
								auto critter_system = dynamic_cast<CdCritterSystem*>( critter_unit_container->parent() );
								critter_system->removeCritter( critter, true );
								return; // actually needed with how for loop is implemented
							}
						}
					}
				}
			}

			// IF SUM > POPULATION_TRIGGER START REMOVING CRITTERS, each time finding the unit_container with most children
			if ( sumCritters >= m_population_trigger->get_uint() )
			{
				// KEEP REMOVING FIRST UNTIL LIMIT REACHED
				while ( sumCritters > m_population_reduce_to->get_uint() )
				{
					// find container with highest number of critters
						BEntity* highestcontainer( 0 );
						for_all_children_of( m_critter_containers )
						{
							if ( highestcontainer == 0 || (*child)->get_reference()->numChildren() > highestcontainer->numChildren() )
							{
								highestcontainer = (*child)->get_reference();
							}
						}

					// remove critter
						auto critter_system = dynamic_cast<CdCritterSystem*>( highestcontainer->parent() );
						critter_system->removeCritter( *highestcontainer->children().begin(), true );
						sumCritters--;
				}

				// REDUCE ENERGY
				if ( m_energy_reduce_by->get_uint() > 0 )
				{
					for ( unsigned int i( 0 ); i < m_energy_reduce_by->get_uint(); ++i )
					{
						// find container with highest number of food
							BEntity* highestcontainer( 0 );
							BEntity* highest_number_of_units( 0 );
							for_all_children_of( m_food_containers )
							{
								auto this_number_of_units = (*child)->get_reference()->parent()->getChild("settings")->getChild("number_of_units");
								if ( highestcontainer == 0 || this_number_of_units->get_uint() > highest_number_of_units->get_uint() )
								{
									highestcontainer = (*child)->get_reference();
									highest_number_of_units = this_number_of_units;
								}
							}

						// alter energy
							highest_number_of_units->set( highest_number_of_units->get_uint() - 1 );
					}
				}
			}

			// FOOD DEPTH CHECK
			for_all_children_of( m_food_containers )
			{
				auto food_unit_container = (*child)->get_reference();

				// REMOVE FOOD FALLEN BELOW y
				for_all_children_of2( food_unit_container ) // FIXME
				{
					if ( (*child2)->getChild("external_physics", 1)->get_reference()->getChild("transform", 1)->getChild("position_y", 1)->get_float() < m_below_y_trigger->get_float() )
					{
						auto food_system = dynamic_cast<CdFoodSystem*>( food_unit_container->parent() );
						food_system->removeFood( *child2, true );
						return; // actually needed with how for loop is implemented
					}
				}
			}
		}
	}

	bool CdPopulationController::set( const Bstring& id, BEntity* value )
	{
		if ( id == "register_critter_container" )
		{
			// std::cout << "CdPopulationController::registered critter container " << value->name() << std::endl;
			m_critter_containers->addChild( "critter_container_ref", new BEntity_reference() )->set( value ) ;

			return true;
		}
		if ( id == "register_food_container" )
		{
			// std::cout << "CdPopulationController::registered food container " << value->name() << std::endl;
			m_food_containers->addChild( "food_container_ref", new BEntity_reference() )->set( value ) ;

			return true;
		}

		std::cout << "CdPopulationController::warning: unknown command '" << id << "'" << std::endl;
		return false;
	}
