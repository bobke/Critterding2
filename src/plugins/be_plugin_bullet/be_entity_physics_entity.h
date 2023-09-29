#ifndef BE_ENTITY_PHYSICS_ENTITY_H_INCLUDED
#define BE_ENTITY_PHYSICS_ENTITY_H_INCLUDED

#include "kernel/be_plugin_interface.h"
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
			
	// 		virtual bool setProperty( const std::string& caller_name, BeSignalHistory& entity_history )
	// 		{
	// 			if ( caller_name == "reconstruct" )
	// 			{
	// 				if ( getPhysicsComponent() )
	// 				{
	// 					btTransform offset(getPhysicsComponent()->getBody()->getWorldTransform());
	// // 
	// 					if ( getBeParent() )
	// 						getBeParent()->onRemove(this);
	// 
	// 						setPhysicsComponent( getNewlyConstructedPhysicsComponent(offset) );
	// 	
	// 					if ( getBeParent() )
	// 						getBeParent()->onAdd(this);
	// 
	// 					getPhysicsComponent()->getMotionState()->setTransformEntity(get("transform", 1));
	// 					getPhysicsComponent()->getBody()->setGravity(m_gravity);
	// 				}
	// 				return true;
	// 			}
	// 			return false;
	// 		}

	// 				virtual bool set( const Bstring& id, const Buint& value );
	// 				virtual Buint get_uint( const Bstring& id );
	// 				virtual bool set( const Bstring& id, BEntity* value );
	// 				virtual BEntity* get_reference( const Bstring& id );
			
			
// 			virtual const bool getProperty_Bool(const std::string& caller_name) const;
			virtual Bbool get_bool( const Bstring& id );
// 			virtual bool setProperty( const std::string& caller_name, BeSignalHistory& entity_history, const bool value, const bool do_update=true );
			virtual bool set( const Bstring& id, const Bbool& value );

// 			virtual bool setProperty( const std::string& caller_name, BeSignalHistory& entity_history, const BETransform& value, const bool do_update=true );
// 			virtual const BETransform& getProperty_Transform(const std::string& caller_name) const;

// 			virtual const Bfloat getProperty_Float(const std::string& caller_name) const;
			virtual Bfloat get_float( const Bstring& id );

// 			virtual bool setProperty( const std::string& caller_name, BeSignalHistory& entity_history, const Bfloat value, const bool do_update=true );
			virtual bool set( const Bstring& id, const Bfloat& value );

// 			virtual const BEVector3& getProperty_Vector3(const std::string& caller_name) const;
// 			virtual bool setProperty( const std::string& caller_name, BeSignalHistory& entity_history, const BEVector3& value, const bool do_update=true );

// 			void setDrawCall( const unsigned int drawCall );

			
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
			typedef boost::shared_ptr<BPhysicsEntityMesh> ptr;

			void setGeometry( const boost::shared_ptr<BeGeometry>& geometry ) { m_geometry=geometry; }

			// virtual void process( const float timeDelta );

// 			virtual bool setProperty( const std::string& caller_name, BeSignalHistory& entity_history, const std::string& value, const bool do_update=true );

			virtual bool set( const Bstring& id, const char* value );
			
// 			virtual const std::string& getProperty_String(const std::string& caller_name) const;
// 			virtual Bstring* get_string( const Bstring& id );
			virtual const char* get_string( const Bstring& id );
		
			virtual Bbool onAddChild( BEntity* entity );
// 			virtual void onAddChild( BEntity* entity );
			virtual Bbool onRemoveChild( BEntity* entity );
// 			virtual void onRemoveChild( BEntity* entity );

// 			virtual const BEVector3& getProperty_Vector3(const std::string& caller_name) const;
// 			virtual bool setProperty( const std::string& caller_name, BeSignalHistory& entity_history, const BEVector3& value, const bool do_update=true );

	// 		// TRIGGER
	// 		virtual bool setProperty( const std::string& caller_name, BeSignalHistory& entity_history )
	// 		{
	// 			if ( caller_name == "reconstruct" )
	// 			{
	// 				return true;
	// 			}
	// 			return false;
	// 		}
		protected:
	// 		BEntity* m_filename;
			std::string m_filename_value;
// 			BeFilesystem& m_filesystem;
// 			const boost::shared_ptr<BeGeometrySystem>& m_modelsystem;
			BEVector3 m_pre_scale;
			BEVector3 m_pre_position;
			BEVector3 m_pre_rotation;
			boost::shared_ptr<BeGeometry> m_geometry;
	};

	class BPhysicsEntityTriangleMesh : public BPhysicsEntityMesh
	{
		public:
			BPhysicsEntityTriangleMesh() : BPhysicsEntityMesh()
// 			BPhysicsEntityTriangleMesh(BeFilesystem& filesystem, const boost::shared_ptr<BeGeometrySystem>& modelsystem)
// 			: BPhysicsEntityMesh(filesystem, modelsystem)
			{
			}
			virtual ~BPhysicsEntityTriangleMesh(){};
			typedef boost::shared_ptr<BPhysicsEntityTriangleMesh> ptr;

	// 		// TRIGGER
	// 		virtual BeRigidBodyPtr getNewlyConstructedPhysicsComponent()
	// 		{
	// 			btScalar* const vertices = m_geometry->vertices.get();
	// 			unsigned int numVertices = m_geometry->getNumberVertices();
	// 			int* const indices = &m_geometry->elementArrayBuffer[0];
	// 			const BeGeometry::DrawCall& drawCall = m_geometry->m_drawCalls[m_drawCall];
	// 			return boost::shared_ptr<BodypartRigidTrianglemesh>( new BodypartRigidTrianglemesh((btVector3*)(vertices),numVertices,&indices[drawCall.m_first], drawCall.m_count, m_transform, m_mass, m_damping_linear, m_damping_angular) );
	// 		}

			virtual BeRigidBodyPtr getNewlyConstructedPhysicsComponent();
	};

	class BPhysicsEntityConvexMesh : public BPhysicsEntityMesh
	{
		public:
			BPhysicsEntityConvexMesh() : BPhysicsEntityMesh()
// 			BPhysicsEntityConvexMesh(BeFilesystem& filesystem, const boost::shared_ptr<BeGeometrySystem>& modelsystem)
// 			: BPhysicsEntityMesh(filesystem, modelsystem)
			{
			}
			virtual ~BPhysicsEntityConvexMesh(){};
			typedef boost::shared_ptr<BPhysicsEntityConvexMesh> ptr;

	// 		virtual bool setProperty( const std::string& caller_name, BeSignalHistory& entity_history, const std::string& value, const bool do_update=true )
	// 		{
	// 			if ( caller_name == "filename" ) // FIXME remove when has old filename
	// 			{
	// 				if ( !value.empty() && m_filename_value != value )
	// 				{
	// 					m_filename_value = value;
	// 					
	// 					BeServerPhysicsFactory factory;
	// 					factory.loadPhysicsMesh(this, m_filesystem, value, m_modelsystem, m_pre_scale, m_pre_position, m_pre_rotation, m_mass, m_damping_linear, m_damping_angular, "convex");
	// 
	// 					construct();
	// 
	// 					return true;
	// 				}
	// 			}
	// 			return false;
	// 		}

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

	// 			// TRANSFORM
	// 				BEntity* transform = addNew( "transform", BEntity*(new BEntity_Property_Transform()) );
	// 			// WEIGHT
	// 				BEntity* weight = addNew( "weight", BEntity*(new BEntity_Property_Float()) );
				
				
	// 			setPhysicsComponent( boost::shared_ptr<BodypartRigidBox>( new BodypartRigidBox(m_dimensions/2, t_transform, m_mass, m_damping_linear, m_damping_angular) ) );

	// 			m_mass= 1.0f;

// 				construct();
			}
			const char* class_id() const { return "PhysicsEntity_Cube"; }
			virtual ~BPhysicsEntityCube() {};
			virtual void construct();

			virtual BeRigidBodyPtr getNewlyConstructedPhysicsComponent();

			typedef boost::shared_ptr<BPhysicsEntityCube> ptr;
		private:
	};	
	
	
	
	
	
	
#endif
 
