#ifndef QPEN_H_INCLUDED
#define QPEN_H_INCLUDED

#include <QPen>
#include "kernel/be_entity_interface.h"

		class BQPen : public QPen, public BEntity
		{
			public:
				BQPen();
				virtual ~BQPen() {};
				const char* class_id() const { return "QPen"; }
				
				void construct();
				bool set( const Bstring& id, const Buint& value );
			private:
				Buint m_r;
				Buint m_g;
				Buint m_b;
		};
 
#endif
 
