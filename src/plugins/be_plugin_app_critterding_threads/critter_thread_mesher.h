#ifndef CRITTER_THREAD_MESHER_H_INCLUDED
#define CRITTER_THREAD_MESHER_H_INCLUDED

#include "kernel/be_entity_interface.h"
#include "kernel/be_entity_ops_copy.h"
#include <thread>
#include <mutex>

	class CdCritterSystem;
	class CdFoodSystem;

	class CdCritterThreadMesher: public BEntity
	{
		public:
			CdCritterThreadMesher() : BEntity()
			{
				// SET PROCESSING BIT
					setProcessing();
			};
			virtual ~CdCritterThreadMesher() {};
			const char* class_id() const { return "CdCritterThreadMesher"; }

			virtual void construct();
			virtual void process();
			virtual bool set( const Bstring& id, BEntity* value );
		private:
			void migrate( BEntity* entity, BEntity* target );

			BEntityCopy m_entityCopy;

			// SHORTCUTS
			BEntity* m_x_active;
			BEntity* m_x_border;
			BEntity* m_x_direction_is_right;
			BEntity* m_x_target;
			BEntity* m_z_active;
			BEntity* m_z_border;
			BEntity* m_z_direction_is_down;
			BEntity* m_z_target;

			CdCritterSystem* m_critter_system;
			BEntity* m_critter_unit_container;
			// MUTEX
				std::mutex m_mutex;
	};

#endif
