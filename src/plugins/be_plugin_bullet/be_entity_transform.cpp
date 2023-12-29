#include "be_entity_transform.h"
#include "kernel/be_entity_core_types.h"

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

	bool BBulletTransform::apply( BEntity* e )
	{
		auto tr = dynamic_cast<BBulletTransform*>( e );
		if ( tr )
		{
			tr->m_transform = m_transform;
			return true;
		}

		m_transform.getOpenGLMatrix( m_matrix );
		return e->set( reinterpret_cast<const char*>(m_matrix) );
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
	
 
