#pragma once

#include "kernel/be_entity_interface.h"
#include "be_types_extra.h"
#include <boost/shared_ptr.hpp>

	class BeRigidBody;
	typedef boost::shared_ptr<BeRigidBody> BeRigidBodyPtr;


	class BPhysicsEntity : public BEntity
	{
		public:
			BPhysicsEntity();
			const char* class_id() const { return "PhysicsEntity"; }
			virtual ~BPhysicsEntity() { };

			BeRigidBodyPtr getPhysicsComponent() const { return m_physics_component; }

			void setPhysicsComponent( BeRigidBodyPtr physics_component );

			// TRIGGER
			virtual BeRigidBodyPtr getNewlyConstructedPhysicsComponent() { return BeRigidBodyPtr(); }

			virtual void reconstruct();
			virtual void construct();
			
			virtual Bbool get_bool( const Bstring& id );
			virtual bool set( const Bstring& id, const Bbool& value );
			virtual Bfloat get_float( const Bstring& id );
			virtual bool set( const Bstring& id, const Bfloat& value );
		private:
	// 		float m_last_send_time_ago;
			BeRigidBodyPtr m_physics_component;
		protected:
			unsigned int m_drawCall;
			BETransform m_transform;
			Bfloat m_mass;
			Bfloat m_damping_linear;
			Bfloat m_damping_angular;
			Bfloat m_friction;
			Bfloat m_restitution;
			BEVector3 m_scale;
			BEVector3 m_gravity;
			BEVector3 m_impulse;
			BEVector3 m_angular_impulse;
			bool m_wants_deactivation;
			bool m_disable_worldtransform;
	};

	
	
	class BeGeometrySystem;
	class BeGeometry;
	class BeFilesystem;

	class BPhysicsEntityMesh : public BPhysicsEntity
	{
		public:
			BPhysicsEntityMesh();
// 			BPhysicsEntityMesh(BeFilesystem& filesystem, const boost::shared_ptr<BeGeometrySystem>& modelsystem);
			virtual ~BPhysicsEntityMesh(){};

			virtual void construct();

			void setGeometry( const boost::shared_ptr<BeGeometry>& geometry ) { m_geometry=geometry; }

			virtual bool set( const Bstring& id, const char* value );

			virtual const char* get_string( const Bstring& id );
		
			virtual Bbool onAddChild( BEntity* entity );
			virtual Bbool onRemoveChild( BEntity* entity );
		protected:
			std::string m_filename_value;
			BEntity* m_pre_scale_x;
			BEntity* m_pre_scale_y;
			BEntity* m_pre_scale_z;
			BEntity* m_pre_position_x;
			BEntity* m_pre_position_y;
			BEntity* m_pre_position_z;
			BEntity* m_pre_rotation_x;
			BEntity* m_pre_rotation_y;
			BEntity* m_pre_rotation_z;
			boost::shared_ptr<BeGeometry> m_geometry;
	};

	class BPhysicsEntityTriangleMesh : public BPhysicsEntityMesh
	{
		public:
			BPhysicsEntityTriangleMesh() : BPhysicsEntityMesh() {};
			virtual ~BPhysicsEntityTriangleMesh(){};
			typedef boost::shared_ptr<BPhysicsEntityTriangleMesh> ptr;

			virtual BeRigidBodyPtr getNewlyConstructedPhysicsComponent();
	};

	class BPhysicsEntityConvexMesh : public BPhysicsEntityMesh
	{
		public:
			BPhysicsEntityConvexMesh() : BPhysicsEntityMesh() {};
			virtual ~BPhysicsEntityConvexMesh(){};
			typedef boost::shared_ptr<BPhysicsEntityConvexMesh> ptr;

			virtual BeRigidBodyPtr getNewlyConstructedPhysicsComponent();
	};

	class BPhysicsEntityCube : public BPhysicsEntity
	{
		public:
			BPhysicsEntityCube(/*const btVector3& dimensions, */)
			: BPhysicsEntity()
			{
	// 			m_damping_linear=0.05f;
	// 			m_damping_angular=0.85f;
	// 			btTransform t_transform;
	// 			t_transform.setIdentity();
	// 			m_mass = 10.0f;
			}
			const char* class_id() const { return "PhysicsEntity_Cube"; }
			virtual ~BPhysicsEntityCube() {};
			virtual void construct();

			virtual BeRigidBodyPtr getNewlyConstructedPhysicsComponent();

			typedef boost::shared_ptr<BPhysicsEntityCube> ptr;
		private:
	};	
	
	
	
	
	
