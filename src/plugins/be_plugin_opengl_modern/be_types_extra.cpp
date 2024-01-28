#include "be_types_extra.h"
	
#include "LinearMath/btTransform.h"
// make#include "LinearMath/btQuaternion.h"
// #include <sstream>
#include <cstring>
#include <iostream>

// be_net_type_String

	be_net_type_String::be_net_type_String() { memset( m_value, 0, sizeof(m_value) ); }
	be_net_type_String::be_net_type_String(const char* const value)
	{
		memset( m_value, 0, sizeof(m_value) );
		if(value)
		{
			size_t length=strlen(value);
			if(length>127)
			{
				length=127;
			}
			if(length>0)
			{
				memcpy( m_value, value, length );
			}
		}
	}
	be_net_type_String::operator const char*() const
	{
		return m_value;
	}


// // be_net_type_String
// 	be_net_type_String::operator std::string() const
// 	{
// // 		btVector3 v((float)m_x, (float)m_y, (float)m_z);
// 		return m_value;
// 	}
	
// be_net_type_Vector3
	be_net_type_Vector3::be_net_type_Vector3() : m_x(0.0f), m_y(0.0f), m_z(0.0f) {};
	be_net_type_Vector3::be_net_type_Vector3(const be_net_type_Vector3& vector) : m_x(vector.x()), m_y(vector.y()), m_z(vector.z()) { };
	be_net_type_Vector3::be_net_type_Vector3(Bfloat x, Bfloat y, Bfloat z) : m_x(x), m_y(y), m_z(z) { };

	float be_net_type_Vector3::x() const { return m_x; }
	float be_net_type_Vector3::y() const { return m_y; }
	float be_net_type_Vector3::z() const { return m_z; }
	void be_net_type_Vector3::setX( const Bfloat value ) { m_x=value; }
	void be_net_type_Vector3::setY( const Bfloat value ) { m_y=value; }
	void be_net_type_Vector3::setZ( const Bfloat value ) { m_z=value; }
	

	be_net_type_Vector3::be_net_type_Vector3(const btVector3& vector) : m_x(vector.getX()), m_y(vector.getY()), m_z(vector.getZ()) {};
	be_net_type_Vector3::operator btVector3() const
	{
		btVector3 v((float)m_x, (float)m_y, (float)m_z);
		return v;
	}
	bool be_net_type_Vector3::operator!=(const be_net_type_Vector3& rhs) const
	{
		if ( x() == rhs.x() )
			if ( y() == rhs.y() )
				if ( z() == rhs.z() )
					return false;
		return true;
	}
	bool be_net_type_Vector3::operator==(const be_net_type_Vector3& rhs) const
	{
		if ( x() == rhs.x() )
			if ( y() == rhs.y() )
				if ( z() == rhs.z() )
					return true;
		return false;
	}
	be_net_type_Vector3 be_net_type_Vector3::operator+=(const be_net_type_Vector3& rhs) const
	{
		return be_net_type_Vector3
		(
			  x() + rhs.x()
			, y() + rhs.y()
			, z() + rhs.z()
		);
	}
	be_net_type_Vector3 be_net_type_Vector3::operator-=(const be_net_type_Vector3& rhs) const
	{
		return be_net_type_Vector3
		(
			  x() - rhs.x()
			, y() - rhs.y()
			, z() - rhs.z()
		);
	}

// be_net_type_Vector4
		be_net_type_Vector4::be_net_type_Vector4() : m_x(0.0f), m_y(0.0f), m_z(0.0f), m_w(0.0f) {};
		be_net_type_Vector4::be_net_type_Vector4(const be_net_type_Vector4& vector) : m_x(vector.x()), m_y(vector.y()), m_z(vector.z()), m_w(vector.w()) { };
		be_net_type_Vector4::be_net_type_Vector4(Bfloat x, Bfloat y, Bfloat z, Bfloat w) : m_x(x), m_y(y), m_z(z), m_w(w) { };
		float be_net_type_Vector4::x() const { return m_x; }
		float be_net_type_Vector4::y() const { return m_y; }
		float be_net_type_Vector4::z() const { return m_z; }
		float be_net_type_Vector4::w() const { return m_w; }
		void be_net_type_Vector4::setX( const Bfloat value ) { m_x=value; }
		void be_net_type_Vector4::setY( const Bfloat value ) { m_y=value; }
		void be_net_type_Vector4::setZ( const Bfloat value ) { m_z=value; }
		void be_net_type_Vector4::setW( const Bfloat value ) { m_w=value; }

	be_net_type_Vector4::be_net_type_Vector4(const btVector4 vector) : m_x(vector.getX()), m_y(vector.getY()), m_z(vector.getZ()), m_w(vector.getW()) {};
	bool be_net_type_Vector4::operator!=(const be_net_type_Vector4& rhs) const
	{
		if ( x() == rhs.x() )
			if ( y() == rhs.y() )
				if ( z() == rhs.z() )
					if ( w() == rhs.w() )
						return false;
		return true;
	}
	bool be_net_type_Vector4::operator==(const be_net_type_Vector4& rhs) const
	{
		if ( x() == rhs.x() )
			if ( y() == rhs.y() )
				if ( z() == rhs.z() )
					if ( w() == rhs.w() )
						return true;
		return false;
	}


// be_net_type_Quaternion
		be_net_type_Quaternion::be_net_type_Quaternion() : be_net_type_Vector4( 0.0f, 0.0f, 0.0f, 1.0f ) {};
		be_net_type_Quaternion::be_net_type_Quaternion(Bfloat x, Bfloat y, Bfloat z, Bfloat w) : be_net_type_Vector4( x, y, z, w ) { };
		be_net_type_Quaternion::be_net_type_Quaternion( const be_net_type_Vector4& q) : be_net_type_Vector4( q ) { };

	be_net_type_Quaternion::be_net_type_Quaternion(const btQuaternion& q) : be_net_type_Vector4(q.x(), q.y(), q.z(), q.w()) { };
	be_net_type_Quaternion::operator btQuaternion() const
	{
		// FIXME DON'T THINK THIS IS NEEDED ANYMORE
		btTransform NEWtransform;
		NEWtransform.setIdentity();
		NEWtransform.setRotation( btQuaternion(m_x, m_y, m_z, m_w) );
		return NEWtransform.getRotation();
		
// 		btQuaternion q(m_x, m_y, m_z, m_w);
// 		return q;
	}

// be_net_type_Transform
		be_net_type_Transform::be_net_type_Transform() {};
		const be_net_type_Vector3& be_net_type_Transform::getOrigin() const { return m_position ; }
		const be_net_type_Vector3& be_net_type_Transform::getPosition() const { return m_position ; }
		void be_net_type_Transform::setPosition( const be_net_type_Vector3& position ) { m_position = position; }
		void be_net_type_Transform::setOrigin( const be_net_type_Vector3& position ) { m_position = position; }

		const be_net_type_Quaternion& be_net_type_Transform::getRotation() const { return m_rotation ; }
		void be_net_type_Transform::setRotation( const be_net_type_Quaternion& rotation ) { m_rotation = rotation; }

	be_net_type_Transform::be_net_type_Transform(const btTransform& transform)
	{
		setIdentity();
		m_position = transform.getOrigin();
		m_rotation = transform.getRotation();

// 		std::stringstream to_post;
// 		to_post << "be_net_type_Transform::be_net_type_Transform(const btTransform& transform)";
// 		postInvalid( to_post.str(), true );

// 		if ( !isValid() )
// 			setIdentity();
	}
	be_net_type_Transform::operator btTransform() const
	{
		btTransform t;
		t.setIdentity();
		t.setOrigin(m_position);
		t.setRotation(btQuaternion(m_rotation));
		
// 		std::stringstream to_post;
// 		to_post << "be_net_type_Transform::operator btTransform";
// 		postInvalid( to_post.str(), true );
		
		return t;
	}
	void be_net_type_Transform::setIdentity()
	{
		m_position = be_net_type_Vector3(0.0f, 0.0f, 0.0f);
		m_rotation = be_net_type_Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
	}
	bool be_net_type_Transform::operator!=(const be_net_type_Transform& rhs) const
	{
		if ( m_position == rhs.getOrigin() )
			if ( m_rotation == rhs.getRotation() )
				return false;
		return true;
	}
	
	be_net_type_Transform::be_net_type_Transform(const be_net_type_Transform& transform)
	{
		m_position = transform.getPosition();
		m_rotation = transform.getRotation();
	}

	
	bool be_net_type_Transform::isValid() const
	{
		if ( this != this )
			return false;
		return true;

// 			if (   m_position.x() != m_position.x()
// 				|| m_position.y() != m_position.y()
// 				|| m_position.z() != m_position.z()
// 			) return false;
// 
// 			if (   m_rotation.x() != m_rotation.x()
// 				|| m_rotation.y() != m_rotation.y()
// 				|| m_rotation.z() != m_rotation.z()
// 				|| m_rotation.w() != m_rotation.w()
// 			) return false;
// 
// 			return true;
	}
	
	void be_net_type_Transform::postInvalid( const std::string& header, const bool die ) const
	{
// 			std::cout << " testing: " << header << std::endl;
		if ( !isValid() )
		{
			std::cout << " " << header << ", x: " << getOrigin().x() << ", y: " << getOrigin().y() << ", z: " << getOrigin().z() << std::endl;
			std::cout << " " << header << ", x: " << getRotation().x() << ", y: " << getRotation().y() << ", z: " << getRotation().z() << ", w: " << getRotation().w() << std::endl;
			if ( die )
			{
// 					char* n = (char*)malloc(1);
// 					int a;
// 					memcpy(&n[0],&a,100000);
				exit(1);
			}
		}
	}
