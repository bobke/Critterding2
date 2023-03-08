#include "kernel/be_entity_core_types.h"
#include "be_entity_physics_entity.h"
#include "physicsmodel_rigid.h"
#include "physicsmodel_rigid_trianglemesh.h"
#include "physicsmodel_rigid_convexmesh.h"
#include "physicsmodel_rigid_box.h"
#include "be_geometry.h"
#include "filesystem/be_filesystem.h"

		BPhysicsEntity::BPhysicsEntity()
		 : BEntity()
		 , m_drawCall(0)
		 , m_mass(0.0f)
		 , m_damping_linear(0.01f)
		 , m_damping_angular(0.01f)
		 , m_friction(1.0f)
		 , m_restitution(1.0f)
		 , m_scale(1.0f, 1.0f, 1.0f)
		 , m_gravity(0.0f, -9.81f, 0.0f)
		 , m_impulse(0.0f, 0.0f, 0.0f)
		 , m_angular_impulse(0.0f, 0.0f, 0.0f)
		 , m_wants_deactivation(true)
		 , m_disable_worldtransform(false)
		 , m_physics_component(0)
		{
			m_transform.setIdentity();
// 			// TRANSFORM
// 				m_transform = addChild( "transform", (new BEntity_Property_Transform()) );
			// UPDATE INTERVAL
// 				m_update_interval = addChild( "update_interval", (new BEntityFloat()) );
// 				m_update_interval->setProperty(1.0f/25);

// 						m_transform.setIdentity();

			// FIXME initialise

// 					// TRANSFORM
// 						BEntity* transform = addChild( "transform", (new BEntity_Property_Transform()) );
// 						BEntity* position = transform->addChild( "position", (new BEntity_Property_Vector3()) );
// 							position->addChild( "x", (new BEntity_Property_Float()) );
// 							position->addChild( "y", (new BEntity_Property_Float()) );
// 							position->addChild( "z", (new BEntity_Property_Float()) );
// 
// 						BEntity* rotation = transform->addChild( "rotation", (new BEntity_Property_Vector4()) );
// 							rotation->addChild( "x", (new BEntity_Property_Float()) );
// 							rotation->addChild( "y", (new BEntity_Property_Float()) );
// 							rotation->addChild( "z", (new BEntity_Property_Float()) );
// 							rotation->addChild( "w", (new BEntity_Property_Float()) )/*->setProperty(1.0f)*/;
// 
// 						BEntity* rotation_euler = transform->addChild( "rotation_euler", (new BEntity_Property_Vector3()) );
// 							rotation_euler->addChild( "x", (new BEntity_Property_Float()) );
// 							rotation_euler->addChild( "y", (new BEntity_Property_Float()) );
// 							rotation_euler->addChild( "z", (new BEntity_Property_Float()) );
// 
// 						m_transform.setIdentity();
// // 						transform->setProperty(m_transform);
// 
// 					// SCALE
// 						BEntity* scale = addChild( "scale", (new BEntity_Property_Vector3()) );
// 
// 							scale->addChild( "x", (new BEntity_Property_Float()) );
// 							scale->addChild( "y", (new BEntity_Property_Float()) );
// 							scale->addChild( "z", (new BEntity_Property_Float()) );
// 						
// 					// GRAVITY
// 						BEntity* gravity = addChild( "gravity", (new BEntity_Property_Vector3()) );
// 							gravity->addChild( "x", (new BEntity_Property_Float()) );
// 							gravity->addChild( "y", (new BEntity_Property_Float()) );
// 							gravity->addChild( "z", (new BEntity_Property_Float()) );
// 
// 					// DAMPING
// 						BEntity* t_damping_linear = addChild( "damping_linear", (new BEntity_Property_Float()) );
// 						BEntity* t_damping_angular = addChild( "damping_angular", (new BEntity_Property_Float()) );
// 
// 					// FRICTION
// 						addChild( "friction", (new BEntity_Property_Float()) );
// 
// 					// RESTITUTION
// 						addChild( "restitution", (new BEntity_Property_Float()) );
// 
// 					// WANTS_DEACTIVATION
// 						BEntity* wants_deactivation = addChild( "wants_deactivation", (new BEntity_Property_Bool()) );
// 
// 					// WEIGHT
// 						BEntity* weight = addChild( "weight", (new BEntity_Property_Float()) );
// // 						weight->setProperty(0.0f);

		};
		
		
		
		void BPhysicsEntity::reconstruct()
		{
			if ( getPhysicsComponent() )
			{
				BEntity* filename( getChild("filename", 1) );
				{
					
					if ( parent() )
						parent()->onRemoveChild(this);

				
						setPhysicsComponent( getNewlyConstructedPhysicsComponent() );
				}
			}
		}
		
		void BPhysicsEntity::construct() // FIME not BEntity::construct, name conflict, can be removed
		{
// 			std::cout << "construct" << std::endl;
			auto transform = addChild( "transform", new transformEmitter() );
// 			std::cout << "construct done" << std::endl;
			
// 			setPhysicsComponent( getNewlyConstructedPhysicsComponent() );
			

// 			getPhysicsComponent()->getMotionState()->setTransformEntity(get("transform", 1));

// 			getPhysicsComponent()->getBody()->setWorldTransform( m_transform );
// 			get("transform", 1)->setProperty(m_transform);
// 			// HACK LINK
// 			if ( m_mass > 0.0f )
// 			getPhysicsComponent()->getMotionState()->setTransformEntity(get("transform", 1));
		}
		
		
// 		const bool BPhysicsEntity::getProperty_Bool(const std::string& id) const
		Bbool BPhysicsEntity::get_bool( const Bstring& id )
		{
			if ( id == "wants_deactivation" )
			{
				return m_wants_deactivation;
			}
			else if ( id == "disable_worldtransform" )
			{
				return m_disable_worldtransform;
			}
			return false;
		}
		
// 		bool BPhysicsEntity::setProperty( const std::string& id, BeSignalHistory& entity_history, const bool value, const bool do_update )
		bool BPhysicsEntity::set( const Bstring& id, const Bbool& value )
		{
// // 			std::cout << "BPhysicsEntity:bool: " << id << ":" << value << std::endl;
			if ( id == "wants_deactivation" )
			{
				if ( m_wants_deactivation != value )
				{
					m_wants_deactivation = value;
// 					std::cout << "m_wants_deactivation:" << m_wants_deactivation << std::endl;
// 					std::cout << " id:" << id() << std::endl;
					reconstruct();
// 						BeSignalHistory t_entity_history;
// 						setProperty("reconstruct", t_entity_history);
// 					std::cout << " m_wants_deactivation: done" << std::endl;
					return true;
				}
			}
// 			else if ( id == "disable_worldtransform" )
// 			{
// 				if ( m_disable_worldtransform != value )
// 				{
// 					m_disable_worldtransform = value;
// 					return true;
// 				}
// 			}
// 			return false;
		}

// 		bool BPhysicsEntity::setProperty( const std::string& id, BeSignalHistory& entity_history, const BETransform& value, const bool do_update )
// 		{
// // 			std::cout << "BPhysicsEntity:setProperty: " << name() << "  " << id() << "  " << id << ":" << std::endl;
// // 				std::cout << " " << "  p: x: " << value.getOrigin().x() << ", y: " << value.getOrigin().y() << ", z: " << value.getOrigin().z() << std::endl;
// // 				std::cout << " " << "  r: x: " << value.getRotation().x() << ", y: " << value.getRotation().y() << ", z: " << value.getRotation().z() << ", w: " << value.getRotation().w() << std::endl;
// // 			std::stringstream to_post;
// // 			to_post << "BPhysicsEntity::setProperty: type:" << BEntityTypeManager::Instance()->getEntityID(entityType()) << "'";
// // 			to_post << ", name:" << name() << "'";
// // 			value.postInvalid( to_post.str(), true );
// 
// 			if ( m_transform != value )
// 			{
// 				m_transform = value;
// 
// 				if ( !m_disable_worldtransform && getPhysicsComponent() )
// 				{
// // std::cout << "  entity set" << std::endl;
// // 					getPhysicsComponent()->getBody()->setWorldTransform( m_transform ); // FIXME NOW
// 					getPhysicsComponent()->setTransform( m_transform ); // FIXME NOW
// // std::cout << "  entity set done" << std::endl;
// 				}
// 				return true;
// 			}
// // 			else
// // 			{
// // 				std::cout << "NO MAN DOES NOT HAVE IT" << std::endl;
// // 				BEntity* submesh( get("submesh_1") );
// // 				if ( submesh )
// // 				{
// // 					submesh->setProperty( id, entity_history, value );
// // 				}
// // 			}
// 			return false;
// 		}
// 		const BETransform& BPhysicsEntity::getProperty_Transform(const std::string& id) const
// 		{
// // 			if ( getPhysicsComponent() )
// // 			{
// // 				std::stringstream to_post;
// // 				to_post << "BPhysicsEntity::getProperty_Transform(getPhysicsComponent()): type:" << BEntityTypeManager::Instance()->getEntityID(entityType()) << "'";
// // 				to_post << ", name:" << name() << "'";
// // 				BETransform t(getPhysicsComponent()->getTransform());
// // 				t.postInvalid( to_post.str(), true );
// // 
// // 				return getPhysicsComponent()->getTransform();
// // 			}
// // 			else
// // 			{
// // 				std::stringstream to_post;
// // 				to_post << "BPhysicsEntity::getProperty_Transform: type:" << BEntityTypeManager::Instance()->getEntityID(entityType()) << "'";
// // 				to_post << ", name:" << name() << "'";
// // 				m_transform.postInvalid( to_post.str(), true );
// 				return m_transform;
// // 			}
// 		}

// 		const Bfloat BPhysicsEntity::getProperty_Float(const std::string& id) const
		Bfloat BPhysicsEntity::get_float( const Bstring& id )
		{
			if ( id == "weight" )
				return m_mass;
			else if ( id == "damping_linear" )
				return m_damping_linear;
			else if ( id == "damping_angular" )
				return m_damping_angular;
			else if ( id == "friction" )
				return m_friction;
			else if ( id == "restitution" )
				return m_restitution;
			else if ( id == "scale_x" )
				return m_scale.x();
			else if ( id == "scale_y" )
				return m_scale.y();
			else if ( id == "scale_z" )
				return m_scale.z();
			return 0.0f;
		}

// 		void BPhysicsEntity::setDrawCall( const unsigned int drawCall )
// 		{
// 			m_drawCall = drawCall;
// 		}
		
		
		
		
		void BPhysicsEntity::setPhysicsComponent( BeRigidBody::ptr physics_component )
		{
// 				std::cout << "-------------------------------------------------------------" << std::endl;
// 				std::cout << "name: " << name() << std::endl;
// 				std::cout << "  id: " << id() << std::endl;
// 				std::cout << "  mass: " << m_mass << std::endl;
// 				std::cout << "  m_damping_linear: " << m_damping_linear << std::endl;
// 				std::cout << "  m_damping_angular: " << m_damping_angular << std::endl;
				
	// 			BETransform t( m_transform );
				m_physics_component = physics_component;
				btCollisionShape* shape(m_physics_component->getShape());

				if ( shape )
				{
				
					if (m_mass != 0.f) // weight of non zero = dynamic
						physics_component->setMotionState( boost::shared_ptr<BeEventDrivenMotionState>(new BeEventDrivenMotionState( m_transform )) );


// 					btVector3 localInertia(0,0,0);
// 					if (m_mass != 0.f) // weight of non zero = dynamic
					
				// 	btVector3 localInertia2(0.0f,0.0f,0.0f);
					
					if (m_mass != 0.f) // weight of non zero = dynamic
					{
// 						shape->calculateLocalInertia( m_mass, localInertia );
						m_physics_component->setBody( boost::shared_ptr<btRigidBody>(new btRigidBody( btRigidBody::btRigidBodyConstructionInfo( m_mass, physics_component->getMotionState().get(), shape, m_physics_component->m_localInertia )) ) );
					}
					else
					{
						m_physics_component->setBody( boost::shared_ptr<btRigidBody>(new btRigidBody( btRigidBody::btRigidBodyConstructionInfo( m_mass, 0, shape, m_physics_component->m_localInertia )) ) );
						m_physics_component->getBody()->setWorldTransform(m_transform);
					}

					btRigidBody* rigidBody(m_physics_component->getBody());

					if ( m_mass > 0.0f )
					{
						if ( m_wants_deactivation )
						{
							rigidBody->setDeactivationTime(0.8f);
							rigidBody->setSleepingThresholds(1.6f, 2.5f);
							rigidBody->setActivationState(WANTS_DEACTIVATION);
							rigidBody->activate();
						}
						else
							rigidBody->setActivationState(DISABLE_DEACTIVATION);
					}
					
					
		// 			if ( m_scale.x() != 0.0f && m_scale.y() != 0.0f && m_scale.z() != 0.0f )
		// 				physics_component->getShape()->setLocalScaling(m_scale);
					
					
					rigidBody->setFriction(m_friction);
					rigidBody->setRestitution(m_restitution);
					rigidBody->setDamping(m_damping_linear, m_damping_angular);

					rigidBody->setUserPointer(this);

					// do not insert them when the id is still 1
					if ( id() != 1 )
					{
						{
// 							if ( parent() )
								parent()->onAddChild(this);
							rigidBody->setGravity(m_gravity);
						}

						// DISABLED FOR NOW
// 						// HACK LINK
// 						if ( m_mass > 0.0f )
// 							getPhysicsComponent()->getMotionState()->setTransformEntity(get("transform", 1)/*.get()*/);

						if (m_mass != 0.f) // weight of non zero = dynamic
						{
							// TRANSFORM
// 								auto transform = addChild( "transform", new transformEmitter() );
								auto transform = getChild( "transform", 1 );
			// 					transform->setBuiltin();
								
							//	HACK LINK
								m_physics_component->getMotionState()->setTransformEntity(transform);
						}

					}
				}
				
				
		}

		
// 		bool BPhysicsEntity::setProperty( const std::string& id, BeSignalHistory& entity_history, const Bfloat value, const bool do_update )
		bool BPhysicsEntity::set( const Bstring& id, const Bfloat& value )
		{
// 			std::cout << "BPhysicsEntity:Bfloat: " << id << ":" << value << std::endl;

			if ( id == "weight" )
			{
				if ( m_mass != value )
				{

					const Bfloat old_mass(m_mass);
					m_mass = value;
					if ( getPhysicsComponent() )
					{
						if ( m_mass == 0.0f || old_mass == 0.0f )
						{
							// std::cout << "  CHANGING MODELS: " << name() << " " << id() << "  weight: " << m_mass << std::endl;;
							reconstruct();
						}
						else
						{
							// std::cout << "  KEEPING MODELS: " << name() << " " << id() << "  weight: " << m_mass << std::endl;
							btVector3 localInertia(0,0,0);
							if (m_mass != 0.f) // weight of non zero = dynamic
							{
								getPhysicsComponent()->getShape()->calculateLocalInertia( m_mass, localInertia );
							}
							getPhysicsComponent()->getBody()->setMassProps(m_mass, localInertia);
						}
					}
					return true;
				}
			}
			else if ( id == "scale_x" )
			{
				if ( value != 0.0f && m_scale.x() != value )
				{
					m_scale.setX( value );
					getPhysicsComponent()->getShape()->setLocalScaling( m_scale );
					btVector3 localInertia(0,0,0);
					if (m_mass != 0.f) // weight of non zero = dynamic
					{
						getPhysicsComponent()->getShape()->calculateLocalInertia( m_mass, localInertia );
					}
					getPhysicsComponent()->getBody()->setMassProps(m_mass, localInertia);
					// if ( m_scale.x() != 0.0f && m_scale.y() != 0.0f && m_scale.z() != 0.0f )
					// reconstruct();

					return true;
				}
			}
			else if ( id == "scale_y" )
			{
				if ( value != 0.0f && m_scale.y() != value )
				{
					m_scale.setY( value );
					getPhysicsComponent()->getShape()->setLocalScaling( m_scale );
					btVector3 localInertia(0,0,0);
					if (m_mass != 0.f) // weight of non zero = dynamic
					{
						getPhysicsComponent()->getShape()->calculateLocalInertia( m_mass, localInertia );
					}
					getPhysicsComponent()->getBody()->setMassProps(m_mass, localInertia);
					// if ( m_scale.x() != 0.0f && m_scale.y() != 0.0f && m_scale.z() != 0.0f )
					// reconstruct();

					return true;
				}
			}
			else if ( value != 0.0f && id == "scale_z" )
			{
				if ( m_scale.z() != value )
				{
					m_scale.setZ( value );
					getPhysicsComponent()->getShape()->setLocalScaling( m_scale );
					btVector3 localInertia(0,0,0);
					if (m_mass != 0.f) // weight of non zero = dynamic
					{
						getPhysicsComponent()->getShape()->calculateLocalInertia( m_mass, localInertia );
					}
					getPhysicsComponent()->getBody()->setMassProps(m_mass, localInertia);
					// if ( m_scale.x() != 0.0f && m_scale.y() != 0.0f && m_scale.z() != 0.0f )
					// reconstruct();

					return true;
				}
			}

			else if ( id == "damping_linear" )
			{
				if ( m_damping_linear != value )
				{
					m_damping_linear = value;
					if ( getPhysicsComponent() )
					{
// 						reconstruct();
						getPhysicsComponent()->getBody()->setDamping(m_damping_linear, m_damping_angular);
					}
					return true;
				}
			}
			else if ( id == "damping_angular" )
			{
				if ( m_damping_angular != value )
				{
					m_damping_angular = value;
					if ( getPhysicsComponent() )
					{
// 						reconstruct();
						getPhysicsComponent()->getBody()->setDamping(m_damping_linear, m_damping_angular);
					}
					return true;
				}
			}
			else if ( id == "friction" )
			{
				if ( m_friction != value )
				{
					m_friction = value;
					if ( getPhysicsComponent() )
					{
// 						reconstruct();
						getPhysicsComponent()->getBody()->setFriction(m_friction);
					}
					return true;
				}
			}
			else if ( id == "restitution" )
			{
				if ( m_restitution != value )
				{
					m_restitution = value;
					if ( getPhysicsComponent() )
					{
// 						reconstruct();
						getPhysicsComponent()->getBody()->setRestitution(m_restitution);
					}
					return true;
				}
			}
			
			return false;
		}

// 		bool BPhysicsEntity::setProperty( const std::string& id, BeSignalHistory& entity_history, const BEVector3& value, const bool do_update )
// 		{
// // 			std::cout << "BPhysicsEntity:VECTOR3: " << id << ":" << value.x() << std::endl;
// 			if ( id == "scale" )
// 			{
// 				if ( m_scale != value )
// 				{
// // 					std::cout << "scale:" << m_scale.x() << std::endl;
// // 					std::cout << " id:" << id() << std::endl;
// 
// 					m_scale = value;
// 					
// 					if ( m_scale.x() != 0.0f && m_scale.y() != 0.0f && m_scale.z() != 0.0f )
// 						reconstruct();
// 					
// // 					std::cout << "  scale: done" << std::endl;
// 					return true;
// 				}
// 			}
// 			else if ( id == "gravity" )
// 			{
// 				if ( m_gravity != value )
// 				{
// 					m_gravity = value;
// 					if ( getPhysicsComponent() )
// 						reconstruct();
// // 						getPhysicsComponent()->getBody()->setGravity(m_gravity);
// 					return true;
// 				}
// 			}
// 			else if ( id == "impulse" )
// 			{
// 				if ( m_impulse != value )
// 				{
// 					m_impulse = value;
// 					return true;
// 				}
// 			}
// 			else if ( id == "angular_impulse" )
// 			{
// 				if ( m_angular_impulse != value )
// 				{
// 					m_angular_impulse = value;
// 					return true;
// 				}
// 			}
// 			return false;
// 		}









































		BPhysicsEntityMesh::BPhysicsEntityMesh()
// 		BPhysicsEntityMesh::BPhysicsEntityMesh(BeFilesystem& filesystem, const boost::shared_ptr<BeGeometrySystem>& modelsystem)
		 : BPhysicsEntity()
// 		 , m_filesystem(filesystem)
// 		 , m_modelsystem(modelsystem)
		 , m_pre_scale(1.0f, 1.0f, 1.0f)
		 , m_pre_position(0.0f, 0.0f, 0.0f)
		 , m_pre_rotation(0.0f, 0.0f, 0.0f)
		{
			// FILENAME PROPERTY
// 				m_filename = addNew( "filename", BEntity*(new BEntity_Property_String()) );

// 			// TRANSFORM
// 				BEntity* t = addNew( "transform", BEntity*(new BEntity_Property_Transform()) );
// 				getPhysicsComponent()->getMotionState()->setTransformEntity(t); // HACK
		}

// 		bool BPhysicsEntityMesh::setProperty( const std::string& id, BeSignalHistory& entity_history, const std::string& value, const bool do_update )
		bool BPhysicsEntityMesh::set( const Bstring& id, const char* value )
		{
// 			std::cout << "BPhysicsEntity:string: " << id << ":" << value << std::endl;
			if ( id == "filename" ) // FIXME remove when has old filename
			{
// 				auto transform = addChild( "transform", new transformEmitter() );
				
				if ( !std::string(value).empty() && m_filename_value != value )
				{
					m_filename_value = value;

					btTransform geometry_transform;
					geometry_transform.setIdentity();
					geometry_transform.setOrigin( m_pre_position );
					geometry_transform.getBasis().setEulerZYX( m_pre_rotation.x(), m_pre_rotation.y(), m_pre_rotation.z() );
					
					BeGeometrySystem g;
					BeFilesystem fs;
					
					
					boost::shared_ptr<BeGeometry> geometry( g.load( fs, m_filename_value, m_pre_scale, geometry_transform ) );
					if ( geometry != 0 )
					{
						setGeometry(geometry);
					}
// 
// // 					BeServerPhysicsFactory factory;
// // 					factory.loadPhysicsMesh(this, m_filesystem, value, m_modelsystem, m_pre_scale, m_pre_position, m_pre_rotation, m_mass, m_damping_linear, m_damping_angular, "triangle");

					setPhysicsComponent( getNewlyConstructedPhysicsComponent() );
					
					// redo parent's onAddChild
// 					parent()->onAddChild(this);
// 					construct();

					return true;
				}
			}
			return false;
		}

// 		const std::string& BPhysicsEntityMesh::getProperty_String(const std::string& id) const
// 		Bstring* BPhysicsEntityMesh::get_string( const Bstring& id )
// 		{
// 			if ( id == "filename" )
// 				return &m_filename_value;
// 
// 			return 0;
// 		}
		const char* BPhysicsEntityMesh::get_string( const Bstring& id )
		{
			if ( id == "filename" )
				return m_filename_value.c_str();

			return "";
		}

		Bbool BPhysicsEntityMesh::onAddChild( BEntity* entity )
		{
// 			if ( getBeParent() )
			{
				return parent()->onAddChild(entity);
			}
		}

		Bbool BPhysicsEntityMesh::onRemoveChild( BEntity* entity )
		{
// 			if ( getBeParent() )
			{
				return parent()->onRemoveChild(entity);
			}
		}

// 		bool BPhysicsEntityMesh::setProperty( const std::string& id, BeSignalHistory& entity_history, const BEVector3& value, const bool do_update )
// 		{
// // 			std::cout << "BPhysicsEntityMesh:VECTOR3: " << id << ":" << value.x() << std::endl;
// 			if ( id == "scale" )
// 			{
// 				if ( m_scale != value )
// 				{
// 					m_scale = value;
// // 					std::cout << "scale:" << m_scale.x() << std::endl;
// // 					std::cout << " id:" << id() << std::endl;
// 					if ( m_scale.x() != 0.0f && m_scale.y() != 0.0f && m_scale.z() != 0.0f )
// 						reconstruct();
// // 					std::cout << "scale: done" << std::endl;
// 					return true;
// 				}
// 			}
// 			else if ( id == "pre_scale" )
// 			{
// 				if ( m_pre_scale != value )
// 				{
// 					m_pre_scale = value;
// 					reconstruct();
// 					return true;
// 				}
// 			}
// 			else if ( id == "pre_position" )
// 			{
// 				if ( m_pre_position != value )
// 				{
// 					m_pre_position = value;
// 					reconstruct();
// 					return true;
// 				}
// 			}
// 			else if ( id == "pre_rotation" )
// 			{
// 				if ( m_pre_rotation != value )
// 				{
// 					m_pre_rotation = value;
// 					reconstruct();
// 					return true;
// 				}
// 			}
// 			else if ( id == "gravity" )
// 			{
// 				if ( m_gravity != value )
// 				{
// 					m_gravity = value;
// 					if ( getPhysicsComponent() )
// 						reconstruct();
// // 						getPhysicsComponent()->getBody()->setGravity(m_gravity);
// 					return true;
// 				}
// 			}
// 			else if ( id == "impulse" )
// 			{
// 				if ( m_impulse != value )
// 				{
// 					m_impulse = value;
// 					return true;
// 				}
// 			}
// 			else if ( id == "angular_impulse" )
// 			{
// 				if ( m_angular_impulse != value )
// 				{
// 					m_angular_impulse = value;
// 					return true;
// 				}
// 			}
// 			return false;
// 		}


		void BPhysicsEntityMesh::process( const float timeDelta )
		{
// 			m_last_send_time_ago += timeDelta;
			
			if ( getPhysicsComponent() )
			{
				if ( m_impulse != BEVector3(0.0f, 0.0f, 0.0f) )
				{
					// FIXME DISABLED FOR NOW
// 					btTransform t( getChild(this, "transform", 1)->getProperty_Transform() );
// 					getPhysicsComponent()->getBody()->applyCentralImpulse(t.getBasis() * m_impulse * timeDelta * 30);
						
				}
				
				if ( m_angular_impulse != BEVector3(0.0f, 0.0f, 0.0f) )
				{
					// FIXME DISABLED FOR NOW
// 					btTransform t( get("transform", 1)->getProperty_Transform() );
// 					btVector3 test = t.getBasis() * m_angular_impulse * timeDelta * 30;
// 					getPhysicsComponent()->getBody()->applyTorqueImpulse(test);
				}
			}
		};

		BeRigidBody::ptr BPhysicsEntityTriangleMesh::getNewlyConstructedPhysicsComponent()
		{
			
// 			btTransform t;
// 			t.setIdentity();
// 			std::cout << "mass : " << m_mass << std::endl;
// 			return boost::shared_ptr<BodypartRigidTrianglemesh>( new BodypartRigidTrianglemesh(m_geometry, t, m_mass, m_damping_linear, m_damping_angular) );

// 			std::stringstream to_post;
// 			to_post << "BPhysicsEntityTriangleMesh::getNewlyConstructedPhysicsComponent: type:" << BEntityTypeManager::Instance()->getEntityID(entityType()) << "'";
// 			to_post << ", name:" << name() << "'";
// 			m_transform.postInvalid( to_post.str(), true );



// 			btTransform geometry_transform;
// 			geometry_transform.setIdentity();
// 			geometry_transform.setOrigin( m_pre_position );
// 			geometry_transform.getBasis().setEulerZYX( m_pre_rotation.x(), m_pre_rotation.y(), m_pre_rotation.z() );
// 			boost::shared_ptr<BeGeometry> geometry( m_modelsystem->load( m_filesystem, m_filename_value, m_pre_scale, geometry_transform ) );
// 			if ( geometry != 0 )
// 			{
// 				setGeometry(geometry);
// 			}

			return boost::shared_ptr<BodypartRigidTrianglemesh>( new BodypartRigidTrianglemesh(m_geometry, m_transform, m_mass, m_damping_linear, m_damping_angular, m_scale) );
		}

		BeRigidBody::ptr BPhysicsEntityConvexMesh::getNewlyConstructedPhysicsComponent()
		{
// 			std::stringstream to_post;
// 			to_post << "BPhysicsEntityConvexMesh::getNewlyConstructedPhysicsComponent: type:" << BEntityTypeManager::Instance()->getEntityID(entityType()) << "'";
// 			to_post << ", name:" << name() << "'";
// 			m_transform.postInvalid( to_post.str(), true );
			
			
// 					btTransform geometry_transform;
// 					geometry_transform.setIdentity();
// 					geometry_transform.setOrigin( m_pre_position );
// 					geometry_transform.getBasis().setEulerZYX( m_pre_rotation.x(), m_pre_rotation.y(), m_pre_rotation.z() );
// 					boost::shared_ptr<BeGeometry> geometry( m_modelsystem->load( m_filesystem, m_filename_value, m_pre_scale, geometry_transform ) );
// 					if ( geometry != 0 )
// 					{
// 						setGeometry(geometry);
// 					}

			
			
			return boost::shared_ptr<BodypartRigidConvexmesh>( new BodypartRigidConvexmesh(m_geometry, m_transform, m_mass, m_damping_linear, m_damping_angular, m_scale) );
		}

		void BPhysicsEntityCube::construct() // FIME not BEntity::construct, name conflict, can be removed
		{
			addChild( "transform", new transformEmitter() );
// 			addChild( "_external_parent", new BEntity_reference() );
			setPhysicsComponent( getNewlyConstructedPhysicsComponent() );
		}

		BeRigidBody::ptr BPhysicsEntityCube::getNewlyConstructedPhysicsComponent()
		{
// 			std::cout << "Cube" << std::endl;
// 			std::stringstream to_post;
// 			to_post << "BPhysicsEntityCube::getNewlyConstructedPhysicsComponent: type:" << BEntityTypeManager::Instance()->getEntityID(entityType()) << "'";
// 			to_post << ", name:" << name() << "'";
// 			m_transform.postInvalid( to_post.str(), true );
			
			return boost::shared_ptr<BodypartRigidBox>( new BodypartRigidBox(m_scale*0.5f, m_transform, m_mass, m_damping_linear, m_damping_angular) );
		}

