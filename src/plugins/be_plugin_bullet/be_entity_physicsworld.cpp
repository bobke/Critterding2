#include "be_entity_physicsworld.h"
#include "be_entity_physics_entity.h"
#include "physicsmodel_rigid.h"
#include "be_entity_constraint_hinge.h"
#include "be_entity_raycastvehicle.h"

// #include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#include "BulletSoftBody/btSoftRigidDynamicsWorld.h"
#include "BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h"

// #include "BulletCollision/BroadphaseCollision/btCollisionAlgorithm.h"
#include "BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "BulletCollision/BroadphaseCollision/btAxisSweep3.h"
// #include "BulletDynamics/ConstraintSolver/btConstraintSolver.h"
#include "BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h"
#include "BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h"

#include <iostream>

		BPhysicsWorld::BPhysicsWorld()
		: BEntity()
		{
			setProcessing();
// 			m_flags.m_has_processing = true;
			{
				m_collisionConfiguration = new btDefaultCollisionConfiguration;
				m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
	// 			if(settings->getCVar("body_selfcollisions") == 0)
				m_dispatcher->setNearCallback(&BPhysicsWorld::CollisionNearOverride);

				btVector3 worldAabbMin(-500,-500,-500);
				btVector3 worldAabbMax(500,500,500);
				m_broadphase = new btAxisSweep3 (worldAabbMin, worldAabbMax);
				m_ghostPairCallback = new btGhostPairCallback();
				m_broadphase->getOverlappingPairCache()->setInternalGhostPairCallback(m_ghostPairCallback);
				m_solver = new btSequentialImpulseConstraintSolver;

				m_physics_world = new btDiscreteDynamicsWorld(m_dispatcher,m_broadphase,m_solver,m_collisionConfiguration);
			// 	m_physics_world->setGravity( btVector3(0.0f, -50.0f, 0.0f) );
			// 	m_physics_world->getSolverInfo().m_solverMode = SOLVER_USE_WARMSTARTING | SOLVER_SIMD;
				m_physics_world->getSolverInfo().m_solverMode = SOLVER_USE_WARMSTARTING | SOLVER_SIMD | SOLVER_ENABLE_FRICTION_DIRECTION_CACHING;
				m_physics_world->getSolverInfo().m_numIterations = 8;
				
				
				m_physics_world->setDebugDrawer(0);
				btGImpactCollisionAlgorithm::registerAlgorithm(m_dispatcher);
// 				m_broadphase->getOverlappingPairCache()->setInternalGhostPairCallback( m_ghostPairCallback );
			}
			
// 			{
// 				m_collisionConfiguration = new btSoftBodyRigidBodyCollisionConfiguration();
// 				m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
// 				m_broadphase = new btAxisSweep3( btVector3(-100000,-100000,-100000),btVector3(100000,100000,100000));
// 				m_solver = new btSequentialImpulseConstraintSolver();
// 				m_ghostPairCallback = new btGhostPairCallback(),
// 				m_broadphase->getOverlappingPairCache()->setInternalGhostPairCallback( m_ghostPairCallback );
// // 				// debug drawer setup
// // 				physicsdebugrenderer.setDebugMode( btIDebugDraw::DBG_DrawWireframe + btIDebugDraw::DBG_DrawConstraints + btIDebugDraw::DBG_DrawConstraintLimits );
// 
// 				m_physics_world = new btSoftRigidDynamicsWorld( m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration );
// 				if( m_physics_world )
// 				{
// 					m_physics_world->getSolverInfo().m_solverMode = SOLVER_USE_WARMSTARTING | SOLVER_SIMD | SOLVER_ENABLE_FRICTION_DIRECTION_CACHING;
// 					m_physics_world->getSolverInfo().m_numIterations = 10;
// 					m_physics_world->setDebugDrawer(0);
// 					btGImpactCollisionAlgorithm::registerAlgorithm(m_dispatcher);
// 				}
// 			}

		}

		BPhysicsWorld::~BPhysicsWorld() {
			delete m_physics_world;
			delete m_solver;
			delete m_broadphase;
			delete m_ghostPairCallback;
			delete m_dispatcher;
			delete m_collisionConfiguration;
		}
		
		void BPhysicsWorld::construct()
		{
			// COLLISIONS
			m_collisions = addChild( "collisions", new BEntity() );
		}

		void BPhysicsWorld::CollisionNearOverride(btBroadphasePair& collisionPair, btCollisionDispatcher& dispatcher, const btDispatcherInfo& dispatchInfo)
		{
			btRigidBody* b1 = static_cast<btRigidBody*>(collisionPair.m_pProxy0->m_clientObject);
			btRigidBody* b2 = static_cast<btRigidBody*>(collisionPair.m_pProxy1->m_clientObject);
			auto e1 = static_cast<BEntity*>(b1->getUserPointer());
			auto e2 = static_cast<BEntity*>(b2->getUserPointer());

// 			std::cout << "Entity e1: " << e1->name() << " e2: " << e2->name() << std::endl;

			if(e1 == NULL || e2 == NULL)
			{
				//cout << "Not colliding." << endl;
				return;
			}
			else if( e1 == e2 )
			{
				//cout << "Not colliding." << endl;
				return;
			}
			
			if ( ( e1->name() == "bodypart_central" && e2->name() == "physics_entity_food" ) || ( e2->name() == "bodypart_central" && e1->name() == "physics_entity_food" ) )
			{
// 				std::cout << "Entity e1: " << e1->name() << " e2: " << e2->name() << std::endl;
				auto collision = e1->parent()->getChild( "collisions", 1 )->addChild( "collision", new BEntity() );
				auto collision_entity1 = collision->addChild( "entity1", new BEntity_reference() );
				collision_entity1->set( e1 );
				auto collision_entity2 = collision->addChild( "entity2", new BEntity_reference() );
				collision_entity2->set( e2 );
			}

			// cout << "Colliding." << endl;
			dispatcher.defaultNearCallback(collisionPair, dispatcher, dispatchInfo);
		}

		Bbool BPhysicsWorld::onAddChild( BEntity* entity )
		{
			
			auto physics_entity = dynamic_cast<BPhysicsEntity*>(entity);
			if ( physics_entity )
			{
				if ( physics_entity->getPhysicsComponent() )
				{
					m_physics_world->addRigidBody(physics_entity->getPhysicsComponent()->getBody());
					return true;
				}
				
			}
			
			auto physics_constraint_hinge = dynamic_cast<BConstraintHinge*>(entity);
			if ( physics_constraint_hinge )
			{
				// well it has to exist, and at this point it doesnt, it's handled in the constraint "create_hinge"
				if ( physics_constraint_hinge->m_hinge )
				{
					m_physics_world->addConstraint( physics_constraint_hinge->m_hinge, true ); // FIXME getHinge
				}
				return true;
			}

			auto vehicle = dynamic_cast<BeServerEntityPhysics_Vehicle*>(entity);
			if ( vehicle )
			{
				if ( vehicle->m_vehicle )
				{
					vehicle->m_vehicleRayCaster = boost::shared_ptr<btDefaultVehicleRaycaster>(new btDefaultVehicleRaycaster(m_physics_world));
					vehicle->m_vehicle->m_vehicleRaycaster = vehicle->m_vehicleRayCaster.get();
					m_physics_world->addVehicle(vehicle->m_vehicle.get());
					std::cout << "vehicle->m_vehicle added" << std::endl;
				}
				return true;
			}
			
			
// 			std::cout << "none added" << std::endl;
			return false;
		}

		Bbool BPhysicsWorld::onRemoveChild( BEntity* entity )
		{
			
			auto physics_entity = dynamic_cast<BPhysicsEntity*>(entity);
			if ( physics_entity )
			{
				if ( physics_entity->getPhysicsComponent() )
				{
					m_physics_world->removeRigidBody(physics_entity->getPhysicsComponent()->getBody());
					return true;
				}
				
			}
			
			auto physics_constraint_hinge = dynamic_cast<BConstraintHinge*>(entity);
			if ( physics_constraint_hinge )
			{
				if ( physics_constraint_hinge->m_hinge )
				{
					m_physics_world->removeConstraint( physics_constraint_hinge->m_hinge ); // FIXME getHinge
				}
				return true;
			}

			auto vehicle = dynamic_cast<BeServerEntityPhysics_Vehicle*>(entity);
			if ( vehicle )
			{
				if ( vehicle->m_vehicle )
				{
					m_physics_world->removeVehicle(vehicle->m_vehicle.get());
					std::cout << "vehicle->m_vehicle removed" << std::endl;
				}
				return true;
			}

			return false;
		}				
		
		void BPhysicsWorld::process()
		{
			// CLEAR COLLISIONS
// 			std::cout << "clear children" << std::endl;
			m_collisions->clearChildren();
			
// 			m_physics_world->stepSimulation(0.016667f, 3, 0.00833334f);
			m_physics_world->stepSimulation(0.016667f, 1, 0.016667f);
			
			
		}
		
 
