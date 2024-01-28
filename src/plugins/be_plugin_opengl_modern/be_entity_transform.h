#ifndef BE_ENTITY_TRANSFORM_H_INCLUDED
#define BE_ENTITY_TRANSFORM_H_INCLUDED

#include "kernel/be_entity_interface.h"
#include "LinearMath/btTransform.h"

	// CLASS 1
		class BTransform: public BEntity
		{
			public:
				BTransform();
				virtual ~BTransform() {};
// 				virtual void process();
// 				virtual void construct();
				const btTransform& getTransform() const;
				void setTransform( const btTransform& transform );
			private:
				btTransform m_tranform;
		};

#endif
 
