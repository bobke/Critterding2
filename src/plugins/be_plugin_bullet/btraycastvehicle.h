#ifndef BRAYCASTVEHICLE_H
#define BRAYCASTVEHICLE_H

#include "physicsmodel_rigid.h"
#include "BulletCollision/NarrowPhaseCollision/btRaycastCallback.h"
// #include "body/bodypart_rigid_box.h"

#include <vector>

struct btWheelContactPoint
{
	btRigidBody* m_body0;
	btRigidBody* m_body1;
	btVector3	m_frictionPositionWorld;
	btVector3	m_frictionDirectionWorld;
	btScalar	m_jacDiagABInv;
	btScalar	m_maxImpulse;


	btWheelContactPoint(btRigidBody* body0,btRigidBody* body1,const btVector3& frictionPosWorld,const btVector3& frictionDirectionWorld, btScalar maxImpulse)
		:m_body0(body0),
		m_body1(body1),
		m_frictionPositionWorld(frictionPosWorld),
		m_frictionDirectionWorld(frictionDirectionWorld),
		m_maxImpulse(maxImpulse)
	{
		btScalar denom0 = body0->computeImpulseDenominator(frictionPosWorld,frictionDirectionWorld);
		btScalar denom1 = body1->computeImpulseDenominator(frictionPosWorld,frictionDirectionWorld);
		btScalar	relaxation = 1.f;
		m_jacDiagABInv = relaxation/(denom0+denom1);
	}

};

class bRaycastVehicle : public btRaycastVehicle
{
	public:
		bRaycastVehicle( const btVehicleTuning& tuning,btRigidBody* chassis, btVehicleRaycaster* raycaster );
// 		~bRaycastVehicle();

		btScalar getSpeed() { return getCurrentSpeedKmHour(); }
		void setSpeed(btScalar currentVehicleSpeedKmHour) { m_currentVehicleSpeedKmHour=currentVehicleSpeedKmHour; } 

		btScalar calcRollingFriction(btWheelContactPoint& contactPoint);
		
// 		btScalar customrayCast(btWheelInfo& wheel, unsigned int cwheel);
		void updateVehicle(btScalar step);

		btScalar forwardWheelSumSide;
		btScalar touchingfrontwheels;

		//resolveSingleBilateral is an obsolete methods used for vehicle friction between two dynamic objects
		void resolveSingleBilateral(btRigidBody& body1, const btVector3& pos1,
				btRigidBody& body2, const btVector3& pos2,
				btScalar distance, const btVector3& normal,btScalar& impulse ,btScalar timeStep);		
		
		void updateSuspension(btScalar deltaTime);
		btWheelInfo&	addWheel( const btVector3& connectionPointCS0, const btVector3& wheelDirectionCS0,const btVector3& wheelAxleCS,btScalar suspensionRestLength,btScalar wheelRadius,const btVehicleTuning& tuning, bool isFrontWheel);

	private:
// 		btScalar wheelWantsRotation( const btWheelInfo& wheel, btScalar step );
		
// 		std::vector<float>	m_wheelspinInfo;
// 		std::vector<float>	m_wheelSpinFactors;
};

#endif
