#ifndef CRITTER_SYSTEM_H_INCLUDED
#define CRITTER_SYSTEM_H_INCLUDED

#include "kernel/be_entity_interface.h"
#include "kernel/be_entity_ops_copy.h"

	class CdSpeciesSystem;
	class BeRigidBody;
	class BMousePicker;

	//  SYSTEM
		class CdCritterSystem : public BEntity
		{
			public:
				CdCritterSystem() : m_framecount(1) { setProcessing(); };
				const char* class_id() const { return "CdCritterSystem"; }
				virtual ~CdCritterSystem() {};

				void construct();
				void process();
				void removeCritter( BEntity* entity, bool force_direct_deletion=false );
				// bool set( const char* value );
				virtual bool set( const Bstring& id, BEntity* value );

			private:
				BMousePicker* m_mouse_picker;
				BEntity* m_unit_container;
				bool removeFromCollisions( BEntity* to_remove );
				BEntity* m_collisions;
				BEntityCopy m_entityCopy;
				// BEntityLoad m_entityLoad;
				BEntity* m_command_buffer;
				
				BEntity* m_insert_frame_interval;
				unsigned int m_framecount;
				
				// SETTINGS
				BEntity* m_minimum_number_of_units;
				BEntity* m_intitial_energy;
				BEntity* m_procreate_minimum_energy;
				BEntity* m_maximum_age;
				BEntity* m_dropzone_position_x;
				BEntity* m_dropzone_position_y;
				BEntity* m_dropzone_position_z;
				BEntity* m_dropzone_size_x;
				BEntity* m_dropzone_size_y;
				BEntity* m_dropzone_size_z;
				BEntity* m_copy_random_position;
				
				CdSpeciesSystem* m_species_system;
				BEntity* m_body_system_unit_container;
				BEntity* m_brain_system;
		};

	//  UNIT
		class CdCritter : public BEntity
		{
			public:
				CdCritter() {};
				const char* class_id() const { return "CdCritter"; }
				virtual ~CdCritter() {};
				void construct();

				Buint age() { return m_age->get_uint(); }
				Bfloat energy() { return m_energy->get_float(); }
				void setAge( Buint age ) { m_age->set( age ); }
				void setEnergy( Bfloat energy ) { m_energy->set( energy ); }
				void setSpecies( BEntity* species ) { m_species->set( species ); }
				BEntity* m_brain;
				BEntity* m_brain_inputs;

				// performance shortcuts
				BEntity* m_transform_shortcut;
				BEntity* m_physics_component_shortcut;
				BEntity* m_bodyparts_shortcut;
				// BEntity* m_always_firing_input;
		private:
				// PROPERTIES
				BEntity* m_age;
				BEntity* m_energy;
				BEntity* m_species;
		};

#endif
 
