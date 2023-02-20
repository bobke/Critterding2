#ifndef BE_PARSER_H_INCLUDED
#define BE_PARSER_H_INCLUDED

#include "kernel/be_entity_interface.h"
#include <string>

	class btVector3;
	class btVector4;
	class btQuaternion;
	class btTransform;

	// namespace BeNetTypes
	// {
		class be_net_type_String
		{
			public:
				be_net_type_String();
				be_net_type_String(const char* const value);
				operator const char*() const;
			private:
				char m_value[128];
		};

		class be_net_type_Vector3
		{
			public:
				be_net_type_Vector3();
				be_net_type_Vector3(const be_net_type_Vector3& vector);
				be_net_type_Vector3(const btVector3& vector);
				be_net_type_Vector3(Bfloat x, Bfloat y, Bfloat z);
				operator btVector3() const;
				bool operator!=(const be_net_type_Vector3& rhs) const;
				bool operator==(const be_net_type_Vector3& rhs) const;
				be_net_type_Vector3 operator+=(const be_net_type_Vector3& rhs) const;
				be_net_type_Vector3 operator-=(const be_net_type_Vector3& rhs) const;
				
				virtual float x() const;
				virtual float y() const;
				virtual float z() const;
				void setX( const Bfloat value );
				void setY( const Bfloat value );
				void setZ( const Bfloat value );
			private:
				Bfloat m_x;
				Bfloat m_y;
				Bfloat m_z;
		};

		class be_net_type_Vector4
		{
			public:
				be_net_type_Vector4();
				be_net_type_Vector4(const be_net_type_Vector4& vector);
				be_net_type_Vector4(const btVector4 vector);
				be_net_type_Vector4(Bfloat x, Bfloat y, Bfloat z, Bfloat w);
				bool operator!=(const be_net_type_Vector4& rhs) const;
				bool operator==(const be_net_type_Vector4& rhs) const;
				virtual float x() const;
				virtual float y() const;
				virtual float z() const;
				virtual float w() const;
				virtual void setX( const Bfloat value );
				virtual void setY( const Bfloat value );
				virtual void setZ( const Bfloat value );
				virtual void setW( const Bfloat value );
			protected:
				Bfloat m_x;
				Bfloat m_y;
				Bfloat m_z;
				Bfloat m_w;
		};

		class be_net_type_Quaternion : public be_net_type_Vector4
		{
			public:
				
		// 		be_net_type_Quaternion() : be_net_type_Vector4( 0.0f, 0.0f, 0.0f, 1.0f ) {};
		// 		be_net_type_Quaternion(Bfloat x, Bfloat y, Bfloat z, Bfloat w) : be_net_type_Vector4( x, y, z, w ) { };
		// 		be_net_type_Quaternion(const btQuaternion& q);
		// 		be_net_type_Quaternion(const be_net_type_Quaternion& q);


				be_net_type_Quaternion();
				be_net_type_Quaternion(Bfloat x, Bfloat y, Bfloat z, Bfloat w);
				be_net_type_Quaternion(const btQuaternion& q);
				be_net_type_Quaternion( const be_net_type_Vector4& q);
				operator btQuaternion() const;
		};

		class be_net_type_Transform
		{
			public:
				be_net_type_Transform();
				be_net_type_Transform(const be_net_type_Transform& transform);
				be_net_type_Transform(const btTransform& transform);
				operator btTransform() const;
				bool operator!=(const be_net_type_Transform& rhs) const;

				const be_net_type_Vector3& getOrigin() const;
				const be_net_type_Vector3& getPosition() const;
				void setPosition( const be_net_type_Vector3& position );
				void setOrigin( const be_net_type_Vector3& position );

				const be_net_type_Quaternion& getRotation() const;
				void setRotation( const be_net_type_Quaternion& rotation );
				void setIdentity();
				
				bool isValid() const;
				void postInvalid( const std::string& header, const bool die ) const;

			private:
				be_net_type_Vector3 m_position;
				be_net_type_Quaternion m_rotation;
		};

	// }

	typedef be_net_type_String BEString;
	typedef be_net_type_Vector3 BEVector3;
	typedef be_net_type_Vector4 BEVector4;
	typedef be_net_type_Transform BETransform;
	typedef be_net_type_Quaternion BEQuaternion;
	
#endif
 
