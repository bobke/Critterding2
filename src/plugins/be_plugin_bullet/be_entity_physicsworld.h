#ifndef BE_ENTITY_PHYSICSWORLD_H_INCLUDED
#define BE_ENTITY_PHYSICSWORLD_H_INCLUDED

#include "kernel/be_plugin_interface.h"

		class btDynamicsWorld;
		class btCollisionConfiguration;
		class btCollisionDispatcher;
		class btAxisSweep3;
		class btConstraintSolver;
		class btGhostPairCallback;
		class btBroadphasePair;
		class btDispatcherInfo;

		class BPhysicsWorld : public BEntity
		{
			public:
				BPhysicsWorld();
				const char* class_id() const { return "PhysicsWorld"; }
				virtual ~BPhysicsWorld();
				virtual void process();
				virtual void construct();
				Bbool onAddChild( BEntity* entity );
				Bbool onRemoveChild( BEntity* entity );
				static void CollisionNearOverride(btBroadphasePair& collisionPair, btCollisionDispatcher& dispatcher, const btDispatcherInfo& dispatchInfo);

				BEntity* m_collisions;
				
				btDynamicsWorld* m_physics_world;
				btCollisionConfiguration* m_collisionConfiguration;
				btCollisionDispatcher* m_dispatcher;
				btAxisSweep3* m_broadphase;
				btConstraintSolver* m_solver;
				btGhostPairCallback*  m_ghostPairCallback;
		};

#endif
 
