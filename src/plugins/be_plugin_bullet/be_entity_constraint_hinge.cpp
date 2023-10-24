#include "be_entity_constraint_hinge.h"
#include "be_entity_physics_entity.h"
#include "physicsmodel_rigid.h"
// #include "btBulletDynamicsCommon.h"
// #include "BulletSoftBody/btSoftRigidDynamicsWorld.h"

#include <iostream>


	// CONSTRUCT
	void BConstraintHinge::construct(  )
	{
		addChild( "limit_low", new BEntity_float() )->set( 0.0f );
		addChild( "limit_high", new BEntity_float() )->set( 0.72f );
		
		addChild( "softness", new BEntity_float() )->set( 0.001f );
		addChild( "biasfactor", new BEntity_float() )->set( 0.5f );
		addChild( "relaxationfactor", new BEntity_float() )->set( 0.5f );

		addChild( "localA", new BBulletTransform() );
		addChild( "localB", new BBulletTransform() );
		
		m_bidirectional = addChild( "bidirectional", new BEntity_bool() );
		m_bidirectional->set( false );

		m_angle = addChild( "angle", new BEntity_float() );

		// Calculate full and half range of hinge, HACK could be more efficient
			float smallestLimit = getChild( "limit_low", 1 )->get_float();

			if ( getChild( "limit_high", 1 )->get_float() < getChild( "limit_low", 1 )->get_float() )
				smallestLimit = getChild( "limit_high", 1 )->get_float();
		
			m_diffFromZero = 0.0f - smallestLimit;

			m_fullRange = 0.0f;
			if ( getChild( "limit_low", 1 )->get_float() > 0.0f )
				m_fullRange += getChild( "limit_low", 1 )->get_float();
			else
				m_fullRange += (getChild( "limit_low", 1 )->get_float() * -1.0f);
		
			if ( getChild( "limit_high", 1 )->get_float() > 0.0f )
				m_fullRange += getChild( "limit_high", 1 )->get_float();
			else
				m_fullRange += (getChild( "limit_high", 1 )->get_float() * -1.0f);		
	}

	// PROCESS
	void BConstraintHinge::process(  )
	{
		if ( m_hinge && m_input_sum != 0.0f )
		{
// 			std::cout << "input sum = " << m_input_sum << std::endl;
			
			// float max_input_sum = 0.38f; // FIXME MAKE OPTION
			float max_input_sum = 0.42f; // FIXME MAKE OPTION
			if ( m_input_sum > max_input_sum )
			{
				m_input_sum = max_input_sum;
			}
			else if ( m_input_sum < -max_input_sum )
			{
				m_input_sum = -max_input_sum;
			}
			
			m_direction = 0.025f;
			
			if ( m_bidirectional->get_bool() )
			{
				if ( m_input_sum < 0.0f )
				{
					m_direction = -m_direction;
					m_input_sum *= -1.0f;
				}
			}
			else // ONLY PERFORM NEGATIVE VALUES
			{
				if ( m_input_sum > 0.0f )
				{
					m_input_sum = 0.0f;
				}
			}
			
			if ( m_input_sum != 0.0f )
			{
				m_hinge->enableAngularMotor(true, m_direction, m_input_sum );  // 5000.0f
				m_input_sum = 0.0f;
			}
			
			// ANGLE
				// float percentAngle = (m_hinge->getHingeAngle() + m_diffFromZero) / m_fullRange;
				// if ( percentAngle > 1.0f )
				// 	percentAngle = 1.0f;
				// else if ( percentAngle < 0.0f )
				// 	percentAngle = 0.0f;
				// // FIXME INTO m_angle->set( percentAngle, true );
				// // where true sets commit=true every time, if value changes or not
				// m_angle->set( percentAngle );

				// if it's the same, force update to outputs
				if ( m_hinge->getHingeAngle() != 0.0f )
				{
					if ( !m_angle->set( m_hinge->getHingeAngle() ) )
					{
						m_angle->onUpdate();
					}
				}
		}
	}

	// WIRE UP THE HINGE
	bool BConstraintHinge::set( const Bstring& id, const Bbool& value )
	{
		if ( id == "create_hinge" )
		{
			BPhysicsEntity* bullet_bodyA = 0;
			BPhysicsEntity* bullet_bodyB = 0;
			BBulletTransform* transform_localA = 0;
			BBulletTransform* transform_localB = 0;
			
			// find reference to bodyA and bodyB
			auto bodyA = getChild( "bodyA", 1 );
			if ( bodyA )
			{
				auto ref = dynamic_cast<BEntity_reference*>( bodyA );
				bullet_bodyA = dynamic_cast<BPhysicsEntity*>( ref->get_reference() );
			}
			auto bodyB = getChild( "bodyB", 1 );
			if ( bodyB )
			{
				auto ref = dynamic_cast<BEntity_reference*>( bodyB );
				bullet_bodyB = dynamic_cast<BPhysicsEntity*>( ref->get_reference() );
			}
			
			if ( bullet_bodyA && bullet_bodyB )
			{
				auto BLocalA = getChild("localA", 1);
				auto BLocalB = getChild("localB", 1);
				transform_localA = dynamic_cast<BBulletTransform*>( BLocalA );
				transform_localB = dynamic_cast<BBulletTransform*>( BLocalB );
				
// 				std::cout << "createing hinge" << std::endl;
				m_hinge = new btHingeConstraint( *bullet_bodyA->getPhysicsComponent()->getBody(), *bullet_bodyB->getPhysicsComponent()->getBody(), transform_localA->m_transform, transform_localB->m_transform );
					
				// 	hinge->m_setting.m_impulseClamp = 30.f;
				// 	hinge->m_setting.m_tau = 0.1f;
						
				// setLimit (btScalar low, btScalar high, btScalar _softness=0.9f, btScalar _biasFactor=0.3f, btScalar _relaxationFactor=1.0f)
				m_hinge->setLimit( getChild( "limit_low", 1 )->get_float(), getChild( "limit_high", 1 )->get_float(), getChild( "softness", 1 )->get_float(), getChild( "biasfactor", 1 )->get_float(), getChild( "relaxationfactor", 1 )->get_float() );

				parent()->onAddChild( this );
				return true;
			}
			std::cout << "failed creating hinge, supply 2 bodies as references" << std::endl;
		}

		return false;
	}


// 	// MOVE THIS TO set(id, BEntity*)
// 	// "bodyA" and "bodyB" as id's
// 	// CREATE A BULLET TRANSFORM ENTITY FOR THIS
// 	BConstraintHinge::BConstraintHinge(btDynamicsWorld* ownerWorld, btRigidBody& bodyA, btRigidBody& bodyB, btTransform& localA, btTransform& localB, float limitA, float limitB)
// 	: BEntity_float()
// 	{
// 		input1 = false;
// 		input2 = false;
// 		// init constraint inputs
// 		Inputs.push_back(&input1); // 0: direction +
// 		Inputs.push_back(&input2); // 1: direction -
// 		
// 
// 		hinge = new btHingeConstraint( bodyA, bodyB, localA, localB );
// 		
// 	// 	hinge->m_setting.m_impulseClamp = 30.f;
// 	// 	hinge->m_setting.m_tau = 0.1f;
// 		
// 		// setLimit (btScalar low, btScalar high, btScalar _softness=0.9f, btScalar _biasFactor=0.3f, btScalar _relaxationFactor=1.0f)
// 		hinge->setLimit( limitA, limitB, 0.8f, 0.3f, 1.0f );
// 
// 		// Calculate full and half range of hinge, HACK could be more efficient
// 			btScalar smallestLimit = limitA;
// 			if ( limitB < limitA )
// 				smallestLimit = limitB;
// 
// 			m_diffFromZero = 0.0f - smallestLimit ;
// 			//cerr << "diff" << m_diffFromZero << endl;
// 
// 			m_fullRange = 0.0f;
// 			if ( limitA > 0.0f ) m_fullRange += limitA;
// 			else m_fullRange += (limitA * -1.0f);
// 			if ( limitB > 0.0f ) m_fullRange += limitB;
// 			else m_fullRange += (limitB * -1.0f);
// 
// 		hinge->setDbgDrawSize(2.0f);
// 	}

	float BConstraintHinge::getAngle()
	{
		float percentAngle = (m_hinge->getHingeAngle() + m_diffFromZero) / m_fullRange;
		if ( percentAngle > 1.0f )
			percentAngle = 1.0f;
		if ( percentAngle < 0.0f )
			percentAngle = 0.0f;

		return percentAngle;
	}

	// void BConstraintHinge::motorate()
	// {
	// 	float direction;
	// 	if ( input1 )
	// 		direction = 1.0f; // 10.0f
	// 	if ( input2 )
	// 		direction = -1.0f; // 10.0f
 // 
	// 	if ( direction != 0.0f )
	// 	{
	// 		m_hinge->enableAngularMotor(true, direction, 5.0f);  // 5000.0f
	// 	}
	// }

	BConstraintHinge::~BConstraintHinge()
	{
		if ( m_hinge )
			delete m_hinge;
	}



	void BBulletTransform::construct()
	{
// 		std::cout << "transformEmitter::construct()" << std::endl;
		m_transform.setIdentity();
		
		addChild("position_x", new BEntity_float_property());
		addChild("position_y", new BEntity_float_property());
		addChild("position_z", new BEntity_float_property());
// 		
// 		addChild("rotation_x", new BEntity_float_property());
// 		addChild("rotation_y", new BEntity_float_property());
// 		addChild("rotation_z", new BEntity_float_property());
// 		addChild("rotation_w", new BEntity_float_property());
// 		
		addChild("rotation_euler_x", new BEntity_float_property());
		addChild("rotation_euler_y", new BEntity_float_property());
		addChild("rotation_euler_z", new BEntity_float_property());
	}

	bool BBulletTransform::set( const Bstring& id, const Bfloat& value )
	{
		
		if ( id == "position_x" )
		{
			auto origin = m_transform.getOrigin();
			if ( origin.x() != value )
			{
				origin.setX( value );
				m_transform.setOrigin( origin );
				onUpdate();

				return true;
			}
		}
		else if ( id == "position_y" )
		{
			// get transform from parent BeRigidBody
			auto origin = m_transform.getOrigin();
			if ( origin.y() != value )
			{
				origin.setY( value );
				m_transform.setOrigin( origin );
				onUpdate();
				return true;
			}
		}
		else if ( id == "position_z" )
		{
			auto origin = m_transform.getOrigin();
			if ( origin.z() != value )
			{
				origin.setZ( value );
				m_transform.setOrigin( origin );
				onUpdate();
				return true;
			}
		}

		else if ( id == "move_x" )
		{
			if ( value != 0.0f )
			{
				m_transform = m_transform * btTransform( btQuaternion( 0.0f, 0.0f, 0.0f ), btVector3( value, 0.0f, 0.0f ) );
				onUpdate();
				return true;
			}
		}
		else if ( id == "move_y" )
		{
			if ( value != 0.0f )
			{
				m_transform = m_transform * btTransform( btQuaternion( 0.0f, 0.0f, 0.0f ), btVector3( 0.0f, value, 0.0f ) );
				onUpdate();
				return true;
			}
		}
		else if ( id == "move_z" )
		{
			if ( value != 0.0f )
			{
				m_transform = m_transform * btTransform( btQuaternion( 0.0f, 0.0f, 0.0f ), btVector3( 0.0f, 0.0f, value ) );
				onUpdate();
				return true;
			}
		}
		
		else if ( id == "rotation_euler_x" )
		{
			btScalar x, y, z;
			m_transform.getRotation().getEulerZYX( z, y, x );
			if ( x != value )
			{
				m_transform.getBasis().setEulerZYX( value, y, z );
				onUpdate();
				return true;
			}
		}
		else if ( id == "rotation_euler_y" )
		{
			btScalar x, y, z;
			m_transform.getRotation().getEulerZYX( z, y, x );
			if ( y != value )
			{
				m_transform.getBasis().setEulerZYX( x, value, z );
				onUpdate();
				return true;
			}
		}
		else if ( id == "rotation_euler_z" )
		{
			btScalar x, y, z;
			m_transform.getRotation().getEulerZYX( z, y, x );
			if ( z != value )
			{
				m_transform.getBasis().setEulerZYX( x, y, value );
				onUpdate();
				return true;
			}
		}
		else if ( id == "yaw" )
		{
			if ( value != 0 )
			{
				m_transform = m_transform * btTransform( btQuaternion( value, 0.0f, 0.0f ) );
				onUpdate();
				return true;
			}
		}
		else if ( id == "pitch" )
		{
			if ( value != 0 )
			{
				m_transform = m_transform * btTransform( btQuaternion( 0.0f, value, 0.0f ) );
				onUpdate();
				return true;
			}
		}
		else if ( id == "roll" )
		{
			if ( value != 0 )
			{
				m_transform = m_transform * btTransform( btQuaternion( 0.0f, 0.0f, value ) );
				onUpdate();
				return true;
			}
		}

		return false;
	}

	Bfloat BBulletTransform::get_float( const Bstring& id )
	{
		if ( id == "position_x" )
		{
			return m_transform.getOrigin().x();
		}
		else if ( id == "position_y" )
		{
			return m_transform.getOrigin().y();
		}
		else if ( id == "position_z" )
		{
			return m_transform.getOrigin().z();
		}
		else if ( id == "rotation_euler_x" )
		{
			btScalar x, y, z;
			m_transform.getRotation().getEulerZYX( z, y, x );
			return x;
		}
		else if ( id == "rotation_euler_y" )
		{
			btScalar x, y, z;
			m_transform.getRotation().getEulerZYX( z, y, x );
			return y;
		}
		else if ( id == "rotation_euler_z" )
		{
			btScalar x, y, z;
			m_transform.getRotation().getEulerZYX( z, y, x );
			return z;
		}
		return 0.0f;
	}
	
