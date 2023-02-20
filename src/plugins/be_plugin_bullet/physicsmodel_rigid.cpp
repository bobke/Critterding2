// #include "be_server_entity_system.h"
#include "physicsmodel_rigid.h"
#include "be_entity_physics_entity.h"
#include "kernel/be_entity_core_types.h"

void BeRigidBody::generalSetup( const float weight, const btTransform& transform, const float linearDamping, const float angularDamping )
{
// 	if (weight != 0.f) // weight of non zero = dynamic
// 		m_motionState = boost::shared_ptr<BeEventDrivenMotionState>(new BeEventDrivenMotionState( transform ));
// 	
//     btVector3 localInertia(0,0,0);
// 	if (weight != 0.f) // weight of non zero = dynamic
// 		m_shape->calculateLocalInertia( weight, localInertia );
// 	
// // 	btVector3 localInertia2(0.0f,0.0f,0.0f);
// 	
// 	if (weight != 0.f) // weight of non zero = dynamic
// 	{
// 		m_body = boost::shared_ptr<btRigidBody>(new btRigidBody( btRigidBody::btRigidBodyConstructionInfo( weight, m_motionState.get(), m_shape.get(), localInertia )) );
// 	}
// 	else
// 	{
// 		m_body = boost::shared_ptr<btRigidBody>(new btRigidBody( btRigidBody::btRigidBodyConstructionInfo( weight, 0, m_shape.get(), localInertia )) );
// 	}
// 	m_body->setWorldTransform(transform);
		
// 	m_body->setDamping(linearDamping, angularDamping);
// 	m_body->setDeactivationTime(0.8f);
// 	m_body->setSleepingThresholds(1.6f, 2.5f);

	
// 	m_body->setDeactivationTime(0.0000f);
// 	m_body->setSleepingThresholds(0.4f, 0.4f);
	
// 	m_body->setActivationState(DISABLE_DEACTIVATION);
}

void BeEventDrivenMotionState::setWorldTransform(const btTransform& centerOfMassWorldTrans)
{
	m_graphicsWorldTrans = centerOfMassWorldTrans * m_centerOfMassOffset;

	if ( m_entity_transform )
	{
		// DISABLED FOR NOW
// 			BeSignalHistory t_entity_history;
// 			m_entity_transform->getBeParent()->setProperty("disable_worldtransform", t_entity_history, true);
// 			m_entity_transform->setProperty(m_graphicsWorldTrans); //FIXME THIS FEEDS BACK INTO WORLD?
// 			m_entity_transform->getBeParent()->setProperty("disable_worldtransform", t_entity_history, false);
		
// 		m_entity_transform->set( reinterpret_cast<const char*>( m_matrix ) );

		m_graphicsWorldTrans.getOpenGLMatrix( m_buffer_value );
		if (
			   m_entity_transform->m_value[0] != m_buffer_value[0]
			|| m_entity_transform->m_value[1] != m_buffer_value[1]
			|| m_entity_transform->m_value[2] != m_buffer_value[2]
			|| m_entity_transform->m_value[3] != m_buffer_value[3]
			|| m_entity_transform->m_value[4] != m_buffer_value[4]
			|| m_entity_transform->m_value[5] != m_buffer_value[5]
			|| m_entity_transform->m_value[6] != m_buffer_value[6]
			|| m_entity_transform->m_value[7] != m_buffer_value[7]
			|| m_entity_transform->m_value[8] != m_buffer_value[8]
			|| m_entity_transform->m_value[9] != m_buffer_value[9]
			|| m_entity_transform->m_value[10] != m_buffer_value[10]
			|| m_entity_transform->m_value[11] != m_buffer_value[11]
			|| m_entity_transform->m_value[12] != m_buffer_value[12]
			|| m_entity_transform->m_value[13] != m_buffer_value[13]
			|| m_entity_transform->m_value[14] != m_buffer_value[14]
			|| m_entity_transform->m_value[15] != m_buffer_value[15]
		)
		{
			m_graphicsWorldTrans.getOpenGLMatrix( m_entity_transform->m_value );
			m_entity_transform->onUpdate();
		}
		//else
		//{
		//	std::cout << "skipping send" << std::endl;
		//}
		
		
// 		m_graphicsWorldTrans.getOpenGLMatrix( m_entity_transform->m_value );
// 		m_entity_transform->onUpdate();
		
// 					std::cout << "P ";
// 					std::cout << m_entity_transform->m_value[0] << " ";
// 					std::cout << m_entity_transform->m_value[1] << " ";
// 					std::cout << m_entity_transform->m_value[2] << " ";
// 					std::cout << m_entity_transform->m_value[3] << " ";
// 					std::cout << m_entity_transform->m_value[4] << " ";
// 					std::cout << m_entity_transform->m_value[5] << " ";
// 					std::cout << m_entity_transform->m_value[6] << " ";
// 					std::cout << std::endl;
		
		

	}
}

	void transformEmitter::construct()
	{
// 		std::cout << "transformEmitter::construct()" << std::endl;
		
		addChild("position_x", new BEntity_float_property());
		addChild("position_y", new BEntity_float_property());
		addChild("position_z", new BEntity_float_property());
		
// 		addChild("rotation_x", new BEntity_float_property());
// 		addChild("rotation_y", new BEntity_float_property());
// 		addChild("rotation_z", new BEntity_float_property());
// 		addChild("rotation_w", new BEntity_float_property());
		
		addChild("rotation_euler_x", new BEntity_float_property());
		addChild("rotation_euler_y", new BEntity_float_property());
		addChild("rotation_euler_z", new BEntity_float_property());
	}

	bool transformEmitter::set( const Bstring& id, const Bfloat& value )
	{
		
		if ( id == "position_x" )
		{
			// get transform from parent BeRigidBody
			auto rigidbody = dynamic_cast<BPhysicsEntity*>( parent() );
			if ( rigidbody )
			{
				auto parentChild_transform = rigidbody->getPhysicsComponent()->getTransform();
				auto origin = parentChild_transform.getOrigin();
				if ( origin.x() != value )
				{
					origin.setX( value );
					parentChild_transform.setOrigin( origin );
					
					rigidbody->getPhysicsComponent()->setTransform( parentChild_transform );
					parentChild_transform.getOpenGLMatrix( m_value );
					onUpdate();
					return true;
				}
			}
		}
		else if ( id == "position_y" )
		{
			// get transform from parent BeRigidBody
			auto rigidbody = dynamic_cast<BPhysicsEntity*>( parent() );
			if ( rigidbody )
			{
				auto parentChild_transform = rigidbody->getPhysicsComponent()->getTransform();
				auto origin = parentChild_transform.getOrigin();
				if ( origin.y() != value )
				{
					origin.setY( value );
					parentChild_transform.setOrigin( origin );
					
					rigidbody->getPhysicsComponent()->setTransform( parentChild_transform );
					parentChild_transform.getOpenGLMatrix( m_value );
					onUpdate();
					return true;
				}
			}
		}
		else if ( id == "position_z" )
		{
			// get transform from parent BeRigidBody
			auto rigidbody = dynamic_cast<BPhysicsEntity*>( parent() );
			if ( rigidbody )
			{
				auto parentChild_transform = rigidbody->getPhysicsComponent()->getTransform();
				auto origin = parentChild_transform.getOrigin();
				if ( origin.z() != value )
				{
					origin.setZ( value );
					parentChild_transform.setOrigin( origin );
					
					rigidbody->getPhysicsComponent()->setTransform( parentChild_transform );
					parentChild_transform.getOpenGLMatrix( m_value );
					onUpdate();
					return true;
				}
			}
		}
		
		else if ( id == "rotation_euler_x" )
		{
			// get transform from parent BeRigidBody
			auto rigidbody = dynamic_cast<BPhysicsEntity*>( parent() );
			if ( rigidbody )
			{
				auto parentChild_transform = rigidbody->getPhysicsComponent()->getTransform();
				btScalar x, y, z;
				parentChild_transform.getRotation().getEulerZYX( z, y, x );
				if ( x != value )
				{
					parentChild_transform.getBasis().setEulerZYX( value, y, z );
					rigidbody->getPhysicsComponent()->setTransform( parentChild_transform );
					parentChild_transform.getOpenGLMatrix( m_value );
					onUpdate();
					return true;
				}
			}
		}
		else if ( id == "rotation_euler_y" )
		{
			// get transform from parent BeRigidBody
			auto rigidbody = dynamic_cast<BPhysicsEntity*>( parent() );
			if ( rigidbody )
			{
				auto parentChild_transform = rigidbody->getPhysicsComponent()->getTransform();
				btScalar x, y, z;
				parentChild_transform.getRotation().getEulerZYX( z, y, x );
				if ( y != value )
				{
					parentChild_transform.getBasis().setEulerZYX( x, value, z );
					rigidbody->getPhysicsComponent()->setTransform( parentChild_transform );
					parentChild_transform.getOpenGLMatrix( m_value );
					onUpdate();
					return true;
				}
			}
		}
		else if ( id == "rotation_euler_z" )
		{
			// get transform from parent BeRigidBody
			auto rigidbody = dynamic_cast<BPhysicsEntity*>( parent() );
			if ( rigidbody )
			{
				auto parentChild_transform = rigidbody->getPhysicsComponent()->getTransform();
				btScalar x, y, z;
				parentChild_transform.getRotation().getEulerZYX( z, y, x );
				if ( z != value )
				{
					parentChild_transform.getBasis().setEulerZYX( x, y, value );
					rigidbody->getPhysicsComponent()->setTransform( parentChild_transform );
					parentChild_transform.getOpenGLMatrix( m_value );
					onUpdate();
					return true;
				}
			}
		}
		else if ( id == "scale_x" || id == "scale_y" || id == "scale_z" )
		{
			auto rigidbody = dynamic_cast<BPhysicsEntity*>( parent() );
			return rigidbody->set( id, value );
		}

		return false;
	}

	Bfloat transformEmitter::get_float( const Bstring& id )
	{
		if ( id == "position_x" )
		{
			// get transform from parent BeRigidBody
			auto rigidbody = dynamic_cast<BPhysicsEntity*>( parent() );
			if ( rigidbody )
			{
				auto parentChild_transform = rigidbody->getPhysicsComponent()->getTransform();
				return parentChild_transform.getOrigin().x();
			}
		}
		else if ( id == "position_y" )
		{
			// get transform from parent BeRigidBody
			auto rigidbody = dynamic_cast<BPhysicsEntity*>( parent() );
			if ( rigidbody )
			{
				auto parentChild_transform = rigidbody->getPhysicsComponent()->getTransform();
				return parentChild_transform.getOrigin().y();
			}
		}
		else if ( id == "position_z" )
		{
			// get transform from parent BeRigidBody
			auto rigidbody = dynamic_cast<BPhysicsEntity*>( parent() );
			if ( rigidbody )
			{
				auto parentChild_transform = rigidbody->getPhysicsComponent()->getTransform();
				return parentChild_transform.getOrigin().z();
			}
		}
		else if ( id == "rotation_euler_x" )
		{
			// get transform from parent BeRigidBody
			auto rigidbody = dynamic_cast<BPhysicsEntity*>( parent() );
			if ( rigidbody )
			{
				auto parentChild_transform = rigidbody->getPhysicsComponent()->getTransform();
				btScalar x, y, z;
				parentChild_transform.getRotation().getEulerZYX( z, y, x );
				return x;
			}
		}
		else if ( id == "rotation_euler_y" )
		{
			// get transform from parent BeRigidBody
			auto rigidbody = dynamic_cast<BPhysicsEntity*>( parent() );
			if ( rigidbody )
			{
				auto parentChild_transform = rigidbody->getPhysicsComponent()->getTransform();
				btScalar x, y, z;
				parentChild_transform.getRotation().getEulerZYX( z, y, x );
				return y;
			}
		}
		else if ( id == "rotation_euler_z" )
		{
			// get transform from parent BeRigidBody
			auto rigidbody = dynamic_cast<BPhysicsEntity*>( parent() );
			if ( rigidbody )
			{
				auto parentChild_transform = rigidbody->getPhysicsComponent()->getTransform();
				btScalar x, y, z;
				parentChild_transform.getRotation().getEulerZYX( z, y, x );
				return z;
			}
		}
		return 0.0f;
	}
