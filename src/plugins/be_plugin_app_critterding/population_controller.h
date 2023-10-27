#ifndef POPULATION_CONTROLLER_H_INCLUDED
#define POPULATION_CONTROLLER_H_INCLUDED

#include "kernel/be_entity_interface.h"

	class CdCritterSystem;
	class CdFoodSystem;

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
			BEntity* m_below_y_trigger;
			CdCritterSystem* m_critter_system;
			CdFoodSystem* m_food_system;
			BEntity* m_critter_unit_container;
			BEntity* m_food_unit_container;
			
			BEntity* m_energy_reduce_by;
			BEntity* m_food_number_of_units;
	};

#endif
