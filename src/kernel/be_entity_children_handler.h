#ifndef BE_ENTITY_CHILDREN_HANDLER_H_INCLUDED
#define BE_ENTITY_CHILDREN_HANDLER_H_INCLUDED

#include "be_types.h"
#include <unordered_map>
#include <thread>
#include <mutex>

class B_ID_Handler;
class BEntity_Plugin_Manager;

	class B_Children_Handler
	{
		public:
			B_Children_Handler();
			virtual ~B_Children_Handler();

		// PROCESSING
			public:
	// 			void process() const;
				void process_post() const;

		// CHILDREN
			public:
				bool addChild( BEntity* parent, BEntity* child );
				virtual bool removeChild( BEntity* parent, BEntity* entity );
				virtual bool removeChild( BEntity* parent, const BEntityVector::iterator& entity_iterator );

				Buint numChildren( const BEntity* entity );
				Buint numTotalChildren( const BEntity* entity );

				BEntityVector& children(const BEntity* entity);
				virtual void clearChildren(BEntity* parent); // FIXME FORMATTING
				void print( BEntity* entity, const Buint max_levels );
				void print_children( const BEntity* entity, const Buint level, const Buint max_levels );
			private:
				std::unordered_map<Buint, BEntityVector> m_children_map;

		// CHILD ID HANDLING
			public:
				Buint spawnId(); // FIXME MUST ALWAYS BE BIGGER THAN THE BIGGEST CHILD ID SO FAR
				void recycleID( BEntity* e );
				B_ID_Handler* m_id_handler;
			private:
				void setEntityIDCounterOffset( const Buint offset );
				
		// ADMIN APP SHORTCUT
				BEntity* m_admin_app_search_entity;
				BEntity* m_cmdbuffer;
				
		// MUTEX
			std::mutex m_mutex_children;
			std::mutex m_mutex;
		
	};

#endif
 
