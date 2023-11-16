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
		 , m_mass(1.0f)
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
				if ( parent() )
					parent()->onRemoveChild(this);

				setPhysicsComponent( getNewlyConstructedPhysicsComponent() );
			}
		}

		void BPhysicsEntity::construct() // FIME not BEntity::construct, name conflict, can be removed
		{
			auto filename = addChild( "filename", new BEntity_string_property() );
			auto transform = addChild( "transform", new transformEmitter() );
		}

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

		bool BPhysicsEntity::set( const Bstring& id, const Bbool& value )
		{
			if ( id == "wants_deactivation" )
			{
				if ( m_wants_deactivation != value )
				{
					m_wants_deactivation = value;
					reconstruct();
					return true;
				}
			}
			return false;
		}

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

		void BPhysicsEntity::setPhysicsComponent( BeRigidBody::ptr physics_component )
		{
// 				std::cout << "-------------------------------------------------------------" << std::endl;
// 				std::cout << "name: " << name() << std::endl;
// 				std::cout << "  id: " << id() << std::endl;
// 				std::cout << "  mass: " << m_mass << std::endl;
// 				std::cout << "  m_damping_linear: " << m_damping_linear << std::endl;
// 				std::cout << "  m_damping_angular: " << m_damping_angular << std::endl;
				
			float position_x(0.0f);
			float position_y(0.0f);
			float position_z(0.0f);
			float rotation_euler_x(0.0f);
			float rotation_euler_y(0.0f);
			float rotation_euler_z(0.0f);
			if ( m_physics_component )
			{
				auto t = getChild("transform");
				if ( t )
				{
					auto x = t->getChild("position_x", 1);
					auto y = t->getChild("position_y", 1);
					auto z = t->getChild("position_z", 1);
					if ( x )
					{
						position_x = x->get_float();
					}
					if ( y )
					{
						position_y = y->get_float();
					}
					if ( z )
					{
						position_z = z->get_float();
					}
					auto r_x = t->getChild("rotation_euler_x", 1);
					auto r_y = t->getChild("rotation_euler_y", 1);
					auto r_z = t->getChild("rotation_euler_z", 1);
					if ( r_x )
					{
						rotation_euler_x = r_x->get_float();
					}
					if ( r_y )
					{
						rotation_euler_y = r_y->get_float();
					}
					if ( r_z )
					{
						rotation_euler_z = r_z->get_float();
					}
				}
			}
			
				
			
				m_physics_component = physics_component;
				btCollisionShape* shape(m_physics_component->getShape());

				if ( shape )
				{
				
					if (m_mass != 0.f) // weight of non zero = dynamic
						physics_component->setMotionState( boost::shared_ptr<BeEventDrivenMotionState>(new BeEventDrivenMotionState( m_transform )) );

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

					// if ( m_scale.x() != 0.0f && m_scale.y() != 0.0f && m_scale.z() != 0.0f )
					// 	physics_component->getShape()->setLocalScaling(m_scale);

					rigidBody->setFriction(m_friction);
					rigidBody->setRestitution(m_restitution);
					rigidBody->setDamping(m_damping_linear, m_damping_angular);

					rigidBody->setUserPointer(this);

					// do not insert them when the id is still 1
					if ( id() != 1 )
					{
						parent()->onAddChild(this);
						rigidBody->setGravity(m_gravity);

						// DISABLED FOR NOW
						// HACK LINK
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
				
			if ( m_physics_component )
			{
				auto t = getChild("transform");
				if ( t )
				{
					auto x = t->getChild("position_x", 1);
					auto y = t->getChild("position_y", 1);
					auto z = t->getChild("position_z", 1);
					if ( x )
					{
						x->set( position_x );
					}
					if ( y )
					{
						y->set( position_y );
					}
					if ( z )
					{
						z->set( position_z );
					}
					auto r_x = t->getChild("rotation_euler_x", 1);
					auto r_y = t->getChild("rotation_euler_y", 1);
					auto r_z = t->getChild("rotation_euler_z", 1);
					if ( r_x )
					{
						r_x->set( rotation_euler_x );
					}
					if ( r_y )
					{
						r_y->set( rotation_euler_y );
					}
					if ( r_z )
					{
						r_z->set( rotation_euler_z );
					}
				}
			}
				
		}

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



		BPhysicsEntityMesh::BPhysicsEntityMesh()
		 : BPhysicsEntity()
		 , m_pre_scale(1.0f, 1.0f, 1.0f)
		 , m_pre_position(0.0f, 0.0f, 0.0f)
		 , m_pre_rotation(0.0f, 0.0f, 0.0f)
		{
		}

		bool BPhysicsEntityMesh::set( const Bstring& id, const char* value )
		{
// 			std::cout << "BPhysicsEntity:string: " << id << ":" << value << std::endl;
			if ( id == "filename" ) // FIXME remove when has old filename
			{
// 				auto transform = addChild( "transform", new transformEmitter() );
				
				if ( !std::string(value).empty() && m_filename_value != value )
				{
					// std::cout << "HELLLOO" << std::endl;
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

					if ( getPhysicsComponent() )
					{
						// if ( m_mass == 0.0f )
						{
							// std::cout << "  CHANGING MODELS: " << name() << " " << id() << "  weight: " << m_mass << std::endl;;
							reconstruct();
						}
						// else
						// {
						// 	// std::cout << "  KEEPING MODELS: " << name() << " " << id() << "  weight: " << m_mass << std::endl;
						// 	btVector3 localInertia(0,0,0);
						// 	if (m_mass != 0.f) // weight of non zero = dynamic
						// 	{
						// 		getPhysicsComponent()->getShape()->calculateLocalInertia( m_mass, localInertia );
						// 	}
						// 	getPhysicsComponent()->getBody()->setMassProps(m_mass, localInertia);
						// }
						return true;
					}
					
					
					setPhysicsComponent( getNewlyConstructedPhysicsComponent() );

					return true;
				}
			}
			return false;
		}

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

