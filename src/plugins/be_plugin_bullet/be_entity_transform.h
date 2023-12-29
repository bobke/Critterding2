#pragma once

#include "kernel/be_entity_interface.h"
#include "LinearMath/btTransform.h"

	class BBulletTransform: public BEntity
	{
		public:
			BBulletTransform() {};
			const char* class_id() const { return "Bullet_Transform"; }
			virtual ~BBulletTransform() {};
			void construct();
			virtual bool apply( BEntity* e );

			bool set( const Bstring& id, const Bfloat& value );
			virtual Bfloat get_float( const Bstring& id );

			btTransform m_transform;
		private:
			float m_matrix[16];
	};


