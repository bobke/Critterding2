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
			
			bool set ( const Bstring& id, BEntity* value );
			
		private:
			BEntity* m_critter_containers;
			BEntity* m_food_containers;

			// SHORTCUTS
			BEntity* m_active;
			BEntity* m_population_trigger;
			BEntity* m_population_reduce_to;
			BEntity* m_below_y_trigger;
			BEntity* m_energy_reduce_by;
	};

#endif
