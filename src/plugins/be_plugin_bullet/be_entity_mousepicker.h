#ifndef BE_ENTITY_MOUSEPICKER_H_INCLUDED
#define BE_ENTITY_MOUSEPICKER_H_INCLUDED

#include "kernel/be_entity_interface.h"
#include "btBulletDynamicsCommon.h"
#include <iostream>

	class BMousePicker : public BEntity
	{
		public:
			BMousePicker();
			~BMousePicker() {};
			void construct();
			void process();

			virtual bool set( const Bbool& value );
			bool removeGrabbedEntity( BEntity* to_remove );
		private:

			bool m_do_attach;
			
			// btVector3			direction;
			btPoint2PointConstraint* m_constraint;
			float m_picking_distance;

			btVector3 m_previous_rayFrom;
			btVector3 m_previous_rayDirection;

			BEntity* m_grabbed_entity;
			BEntity* m_source_x;
			BEntity* m_source_y;
			BEntity* m_source_z;
			BEntity* m_target_x;
			BEntity* m_target_y;
			BEntity* m_target_z;		
			
			
	};

#endif
