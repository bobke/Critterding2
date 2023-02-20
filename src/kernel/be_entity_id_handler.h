#ifndef BE_ENTITY_ID_HANDLER_H_INCLUDED
#define BE_ENTITY_ID_HANDLER_H_INCLUDED

#include "be_types.h"
// #include <map>
#include <map>

class B_ID_Handler
{
	public:
		B_ID_Handler();
		~B_ID_Handler() {};

		Buint64 pop_front();
		// Buint64 pop_front( const Bfloat totalTime );
		void processRecycle();
// 		void recycleID( const Buint64 t_id );
		void recycleID( const BEntity* t_id );
		void setEntityIDCounterOffset( const Buint64& offset );
		Buint64 lastID() { return m_id_counter; }

	private:
		Buint64 m_id_counter;
		Buint64 m_id_counter_offset;
		Buint64 m_grandTotalEntities;
		// Bfloat m_totalTime_lastRecycleCheck;
		// Bfloat m_totalTime_last;
		std::map<Buint64, Bbool> m_map;
		std::map<Buint64, Bfloat> m_delayed_map;
};

#endif
