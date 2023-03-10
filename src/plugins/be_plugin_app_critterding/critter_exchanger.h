#ifndef CRITTER_EXCHANGER_H_INCLUDED
#define CRITTER_EXCHANGER_H_INCLUDED

#include "critter_system.h"

	class CdCritterExchanger: public BEntity
	{
		public:
			CdCritterExchanger() : BEntity()
			{
				// SET PROCESSING BIT
					setProcessing();
			};
			virtual ~CdCritterExchanger() {};
			const char* class_id() const { return "CdCritterExchanger"; }

			virtual void construct();
			virtual void process();
		private:

			// SHORTCUTS
			BEntity* m_active;
			BEntity* m_critter_unit_container;
			CdCritterSystem* m_critter_system;
			BEntity* m_rng;
	
			// TIMER
			BEntity* m_interval_seconds;
			BEntity* m_timer_s_total;
			BEntity* m_timer_frame;
			Buint64 m_frame_counter_last;
			Bfloat m_last_updated;
		
	};

#endif
