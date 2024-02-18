#ifndef PLUGIN_H_INCLUDED
#define PLUGIN_H_INCLUDED

#include "kernel/be_plugin_interface.h"
#include "kernel/be_entity_core_types.h"

	class BCamera;

// 	// SCENE
// 		class Scene: public BEntity
// 		{
// 			public:
// 				Scene() : BEntity() {};
// 				virtual ~Scene() {};
// 				
// 				virtual void construct();
// 		};

	// CRITTERDING
		class Scene: public BEntity
		{
			public:
				Scene() : BEntity() { setProcessing(); };
				const char* class_id() const { return "Critterding"; }
				virtual ~Scene() {};
				
				virtual void construct();
				virtual void process();
				
			private:
				BEntity* findCritter( BEntity* e1, BEntity* e2 );
				BEntity* findFood( BEntity* e1, BEntity* e2 );
				BEntity* m_critter_unit_container;
				BEntity* m_food_unit_container;

				BEntity* getServer( const unsigned int row, const unsigned int column, const unsigned int rows, const unsigned int columns );
				
				BEntity* m_eat_transfer_energy;

				BCamera* m_camera;

				BEntity* m_raycasters;
				BEntity* m_bullet_raycast;
				BEntity* m_raycast_source_x;
				BEntity* m_raycast_source_y;
				BEntity* m_raycast_source_z;
				BEntity* m_raycast_target_x;
				BEntity* m_raycast_target_y;
				BEntity* m_raycast_target_z;

				
				BEntity* m_win_width;
				BEntity* m_win_height;
				BEntity* m_mouse_x;
				BEntity* m_mouse_y;
		};

		class Server: public BEntity
		{
			public:
				Server() : BEntity() { setProcessing(); }
				virtual ~Server() {};
				
				virtual void construct();
				virtual void process();

			private:
				
				BEntity* m_physics_world;
				BEntity* m_physics_world_collisions;
			
				BEntity* findCritter( BEntity* e1, BEntity* e2 );
				BEntity* findFood( BEntity* e1, BEntity* e2 );
				BEntity* m_critter_unit_container;
				BEntity* m_food_unit_container;

				BEntity* m_eat_transfer_energy;
		};
		
#endif
