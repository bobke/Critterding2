#ifndef BE_ENTITY_CONSTRAINT_HINGE_H
#define BE_ENTITY_CONSTRAINT_HINGE_H

#include <vector>
#include "kernel/be_entity_core_types.h"
#include "LinearMath/btTransform.h"


class btHingeConstraint;


	class BConstraintHinge : public BEntity_float
	{
	public:
		// USING FLOATS ON LIMITS SO THAT HEADER CAN BE MOVED TO CPP
		BConstraintHinge() : m_hinge(0), m_input_sum(0.0f) { setProcessing(); };
// 		BConstraintHinge(btDynamicsWorld* ownerWorld, btRigidBody& bodyA, btRigidBody& bodyB, btTransform& localA, btTransform& localB, float limitA, float limitB);
		const char* class_id() const { return "Constraint_Hinge"; }
		virtual ~BConstraintHinge();

		void construct();
		void process();
		bool set( const Bstring& id, const Bbool& value );

		// void			motorate();
		float			getAngle();
		
		std::vector<bool*>		Inputs;
	// 	btTypedConstraint*	hinge;
		btHingeConstraint*	m_hinge;
		float			fullRange;
		float			diffFromZero;
		
		bool set( const Bfloat& value )
		{
			m_input_sum = m_input_sum + value;
			return true;
		}

	private:
		Bfloat			m_input_sum;
		Bfloat			m_direction;
		
		BEntity*		m_bidirectional;
		
		BEntity*		m_angle;
		float			m_fullRange;
		float			m_diffFromZero;

		bool			input1;
		bool			input2;
		
	// 	float			limitA;
	// 	float			limitB;
	};

	// TRANSFORM // FIXME A COPY TOO MUCH
		class BBulletTransform: public BEntity
		{
			public:
				BBulletTransform() {};
				const char* class_id() const { return "Bullet_Transform"; }
				virtual ~BBulletTransform() {};
				void construct();
				virtual bool apply( BEntity* e )
				{
					auto tr = dynamic_cast<BBulletTransform*>( e );
					if ( tr )
					{
						tr->m_transform = m_transform;
						return true;
					}

					float m_matrix[16];
					m_transform.getOpenGLMatrix( m_matrix );
					return e->set( reinterpret_cast<const char*>(m_matrix) );
				}
// 				virtual const char* get_string() { return reinterpret_cast<const char*>(m_transform); }
				
				bool set( const Bstring& id, const Bfloat& value );
				virtual Bfloat get_float( const Bstring& id );

// 				float m_matrix[16];
				btTransform m_transform;
			private:
// 				char m_value_chars[64];
		};


#endif
