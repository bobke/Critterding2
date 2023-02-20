#include "species_system.h"
// #include "critter_system.h"
#include "kernel/be_entity_core_types.h"
#include <sstream>
 
	void CdSpeciesSystem::construct()
	{
		m_unit_container = addChild( "unit_container", new BEntity() );
	} 

	void CdSpeciesSystem::addNewSpecies( BEntity* entity )
	{
		std::stringstream name;
		name << "species " << ++m_species_counter;
		
		// add species to container
		auto new_species = m_unit_container->addChild( name.str(), new BEntity() );
		auto critter_reference = new_species->addChild( "critter_reference", new BEntity_reference() );
		critter_reference->set( entity );
		
		// set species to critter
		auto species_reference = entity->getChild( "species_reference", 1 );
		if ( !species_reference )
		{
			species_reference = entity->addChild("species_reference", new BEntity_reference());
		}
		species_reference->set( new_species );
	}

	void CdSpeciesSystem::copySpecies( BEntity* source, BEntity* target )
	{
		auto existing_species = source->getChild("species_reference", 1)->get_reference();
		auto critter_reference = existing_species->addChild( "critter_reference", new BEntity_reference() );
		critter_reference->set( target );

		// set species to critter
		auto species_reference = target->getChild( "species_reference", 1 );
		species_reference->set( existing_species );
	}
	
	void CdSpeciesSystem::removeFromSpecies( BEntity* entity )
	{
		auto species = entity->getChild("species_reference", 1)->get_reference();
		
		if ( species && species->hasChildren() )
		{
			for_all_children_of( species )
			{
				if ( (*child)->get_reference() == entity )
				{
					species->removeChild( (*child) );

					// remove entire species if empty
					if ( !species->hasChildren() )
					{
						m_unit_container->removeChild( species );
					}

					// stop loop
					return;
				}
			}
		}
	}
