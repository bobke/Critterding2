#ifndef PLUGIN_H_INCLUDED
#define PLUGIN_H_INCLUDED

#include "kernel/be_plugin_interface.h"
#include "kernel/be_entity_core_types.h"

	// SCENE
		class Scene: public BEntity
		{
			public:
				Scene() : BEntity() {};
				virtual ~Scene() {};
				
				virtual void construct();
		};
		

	// CRITTERDING
		class Critterding: public BEntity
		{
			public:
				Critterding() : BEntity() { setProcessing(); };
				const char* class_id() const { return "Critterding"; }
				virtual ~Critterding() {};
				
				virtual void construct();
				virtual void process();
				
			private:
				BEntity* findCritter( BEntity* e1, BEntity* e2 );
				BEntity* findFood( BEntity* e1, BEntity* e2 );
				BEntity* m_physics_world;
				BEntity* m_physics_world_collisions;
				BEntity* m_critter_unit_container;
				BEntity* m_food_unit_container;

				BEntity* m_eat_transfer_energy;
				
		};

#endif
