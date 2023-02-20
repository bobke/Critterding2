#ifndef SPECIES_SYSTEM_H_INCLUDED
#define SPECIES_SYSTEM_H_INCLUDED

#include "kernel/be_entity_interface.h"

	// class CdCritter;

	//  SYSTEM
		class CdSpeciesSystem : public BEntity
		{
			public:
				CdSpeciesSystem() : m_species_counter(0) {};
				const char* class_id() const { return "CdSpeciesSystem"; }
				virtual ~CdSpeciesSystem() {};

				void construct();

				void addNewSpecies( BEntity* entity );
				void copySpecies( BEntity* source, BEntity* target );
				void removeFromSpecies( BEntity* entity );

			private:
				// CONTAINER
				BEntity* m_unit_container;
				
				Buint m_species_counter;
		};

#endif
 
