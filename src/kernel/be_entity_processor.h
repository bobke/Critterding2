#ifndef BE_PROCESSOR_H_INCLUDED
#define BE_PROCESSOR_H_INCLUDED

// #include <vector>
#include <unordered_map>
#include "be_entity_interface.h"

class BProcessor
{
		public:
			BProcessor() : m_timer_ms_total(0) {};
			virtual ~BProcessor() {};

			void run();

			void reConstructList( BEntity* entity, Bbool skip_checks=false ); 
			void constructList( BEntity* entity, Bbool skip_checks=false );

			void addEntity( BEntity* entity );
			void removeEntity( BEntity* entity );

			// FPS
				void addFps( BEntity* entity, Buint fps );
				void removeFps(BEntity* entity);
				Buint fps( BEntity* entity ) const;
				// BeTimer m_timer;
				BEntity* m_timer_ms_total;

			// FPS BACKBUFFER, keeps record of the fps of an entity
				void addFpsBB( BEntity* entity, Buint fps );
				void removeFpsBB(BEntity* entity);
				Buint fpsBB( BEntity* entity ) const;
				std::unordered_map<BEntity*, Buint> m_be_fps_backbuffer;

			Buint listSize() const;
		private:
			
			struct ProcInfo
			{
				BEntity* m_entity;

				Buint m_fps;
				Buint m_ms_to_sleep;
				Buint m_time_last_processed;
			};

			std::vector<ProcInfo> m_proc_entity_list;
};

#endif 
