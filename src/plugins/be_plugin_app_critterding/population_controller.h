#ifndef POPULATION_CONTROLLER_H_INCLUDED
#define POPULATION_CONTROLLER_H_INCLUDED

#include "critter_system.h"

	class CdPopulationController: public BEntity
	{
		public:
			CdPopulationController() : BEntity()
			{
				// SET PROCESSING BIT
					setProcessing();
			};
			virtual ~CdPopulationController() {};
			const char* class_id() const { return "CdPopulationController"; }

			virtual void construct();
			virtual void process();
		private:

			// SHORTCUTS
			BEntity* m_active;
			BEntity* m_population_trigger;
			BEntity* m_population_reduce_to;
			BEntity* m_critter_unit_container;
			CdCritterSystem* m_critter_system;
			
			BEntity* m_energy_reduce_by;
			BEntity* m_food_number_of_units;
			
	};

#endif
