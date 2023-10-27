#ifndef FOOD_SYSTEM_H_INCLUDED
#define FOOD_SYSTEM_H_INCLUDED

#include "kernel/be_entity_interface.h"

// 	// RANDOMIZER
// 		class BeRand
// 		{
// 			public:
// 				BeRand();
// 				virtual ~BeRand() {};
// 				const int get(const int minimum, const int maximum) const;
// 		};

		class BMousePicker;

	//  SYSTEM
		class CdFoodSystem : public BEntity
		{
			public:
				CdFoodSystem() : m_rng(0), m_critter_unit_container(0), m_framecount(0) { setProcessing(); };
				const char* class_id() const { return "CdFoodSystem"; }
				virtual ~CdFoodSystem() {};
				
				void construct();
				void process();
				
				void removeFood( BEntity* entity );

			private:
				// FOOD CONTAINER
				BEntity* m_unit_container;
				BMousePicker* m_mouse_picker;
				bool removeFromCollisions( BEntity* to_remove );
				BEntity* m_collisions;
				BEntity* m_insert_frame_interval;
				unsigned int m_framecount;
				
				// SETTINGS
				BEntity* m_number_of_units;
				BEntity* m_intitial_energy;
				BEntity* m_maximum_age;
				BEntity* m_dropzone_position_x;
				BEntity* m_dropzone_position_y;
				BEntity* m_dropzone_position_z;
				BEntity* m_dropzone_size_x;
				BEntity* m_dropzone_size_y;
				BEntity* m_dropzone_size_z;
				
				BEntity* m_rng;
// 				BeRand m_randomizer;
				BEntity* m_critter_unit_container;
		};

	//  UNIT
		class CdFood : public BEntity
		{
			public:
				CdFood() {};
				const char* class_id() const { return "CdFood"; }
				virtual ~CdFood() {};
				void construct();
				
				Buint age() { return m_age->get_uint(); }
				Bfloat energy() { return m_energy->get_float(); }
				void setAge( Buint age ) { m_age->set( age ); }
				void setEnergy( Bfloat energy ) { m_energy->set( energy ); }
			private:
				// PROPERTIES
				BEntity* m_age;
				BEntity* m_energy;
		};

#endif
 
