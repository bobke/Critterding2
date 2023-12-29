#include "be_entity_raycastvehicle.h"
#include <iostream>
// #include "src/utils/bullet/BulletDynamics/Vehicle/btWheelInfo.h"

bRaycastVehicle::bRaycastVehicle( const btVehicleTuning& tuning,btRigidBody* chassis, btVehicleRaycaster* raycaster )
 : btRaycastVehicle( tuning, chassis, raycaster ), forwardWheelSumSide(0), touchingfrontwheels(0)
{
}

btScalar bRaycastVehicle::calcRollingFriction(btWheelContactPoint& contactPoint)
{
	const btVector3& contactPosWorld = contactPoint.m_frictionPositionWorld;

	btVector3 rel_pos1 = contactPosWorld - contactPoint.m_body0->getCenterOfMassPosition(); 
	btVector3 rel_pos2 = contactPosWorld - contactPoint.m_body1->getCenterOfMassPosition();
	btScalar maxImpulse  = contactPoint.m_maxImpulse;
	
	btVector3 vel = contactPoint.m_body0->getVelocityInLocalPoint(rel_pos1) - contactPoint.m_body1->getVelocityInLocalPoint(rel_pos2);
	btScalar vrel = contactPoint.m_frictionDirectionWorld.dot(vel);

	// calculate j that moves us to zero relative velocity
	btScalar j1 = -vrel * contactPoint.m_jacDiagABInv;
	btSetMin(j1, maxImpulse);
	btSetMax(j1, -maxImpulse);

	return j1;
}

void bRaycastVehicle::updateVehicle( btScalar step )
{
	int numWheel = getNumWheels();
	if ( numWheel==0 )
	{
		return;
	}

	for (int wheel(0); wheel < getNumWheels(); ++wheel)
	{
		updateWheelTransform(wheel,false);
	}

// 	m_forwardWS.resize(numWheel);
// 	m_axle.resize(numWheel);
// 	m_forwardImpulse.resize(numWheel);
// 	m_sideImpulse.resize(numWheel);
// 
// 	// reset forward & side impulses
// 		for ( unsigned int wheel(0); wheel < numWheel; ++wheel )
// 		{
// 			m_sideImpulse[wheel] = btScalar(0.);
// 			m_forwardImpulse[wheel] = btScalar(0.);
// 		}
	
// 	// CALCULATE km/h
		m_currentVehicleSpeedKmHour = btScalar(3.6) * getRigidBody()->getLinearVelocity().length();

		const btTransform& chassisTrans = getChassisWorldTransform();

		btVector3 forwardW (
			chassisTrans.getBasis()[0][m_indexForwardAxis],
			chassisTrans.getBasis()[1][m_indexForwardAxis],
			chassisTrans.getBasis()[2][m_indexForwardAxis]);

		if (forwardW.dot(getRigidBody()->getLinearVelocity()) < btScalar(0.))
			m_currentVehicleSpeedKmHour *= btScalar(-1.);

	// SIMULATE SUSPENSION
		for ( int wheel(0); wheel < numWheel; ++wheel )
			rayCast( m_wheelInfo[wheel]);

		updateSuspension(step);

	// APPLY SUSPENSION FORCES TO CHASSIS
		for ( int i(0); i < numWheel; ++i )
		{
			//apply suspension force
			btWheelInfo& wheel = m_wheelInfo[i];
			
			btScalar suspensionForce = wheel.m_wheelsSuspensionForce;
			
			if (suspensionForce > wheel.m_maxSuspensionForce)
			{
				suspensionForce = wheel.m_maxSuspensionForce;
			}
			btVector3 impulse = wheel.m_raycastInfo.m_contactNormalWS * suspensionForce * step;
			btVector3 relpos = wheel.m_raycastInfo.m_contactPointWS - getRigidBody()->getCenterOfMassPosition();
			
			getRigidBody()->applyImpulse(impulse, relpos);
		
		}

	// UPDATEFRICTION
		m_forwardWS.resize(numWheel);
		m_axle.resize(numWheel);
		m_forwardImpulse.resize(numWheel);
		m_sideImpulse.resize(numWheel);
		int numWheelsOnGround = 0;

		// reset forward & side impulses
		for ( int wheel(0); wheel < numWheel; ++wheel )
		{
			btWheelInfo& wheelInfo = m_wheelInfo[wheel];
			class btRigidBody* groundObject = (class btRigidBody*) wheelInfo.m_raycastInfo.m_groundObject;
			if (groundObject)
				numWheelsOnGround++;

			m_sideImpulse[wheel] = btScalar(0.);
			m_forwardImpulse[wheel] = btScalar(0.);
		}

		btScalar sideFrictionStiffness2 = btScalar(1.0);
		for ( int i(0); i < numWheel; ++i )
		{

			btWheelInfo& wheelInfo = m_wheelInfo[i];
				
			class btRigidBody* groundObject = (class btRigidBody*) wheelInfo.m_raycastInfo.m_groundObject;

			if (groundObject)
			{
				const btTransform& wheelTrans = getWheelTransformWS( i );

				btMatrix3x3 wheelBasis0 = wheelTrans.getBasis();
				m_axle[i] = btVector3(	
					wheelBasis0[0][m_indexRightAxis],
					wheelBasis0[1][m_indexRightAxis],
					wheelBasis0[2][m_indexRightAxis]);
				
				const btVector3& surfNormalWS = wheelInfo.m_raycastInfo.m_contactNormalWS;
				btScalar proj = m_axle[i].dot(surfNormalWS);
				m_axle[i] -= surfNormalWS * proj;
				m_axle[i] = m_axle[i].normalize();
				
				m_forwardWS[i] = surfNormalWS.cross(m_axle[i]);
				m_forwardWS[i].normalize();

			
				resolveSingleBilateral(*m_chassisBody, wheelInfo.m_raycastInfo.m_contactPointWS,
							*groundObject, wheelInfo.m_raycastInfo.m_contactPointWS,
							btScalar(0.), m_axle[i],m_sideImpulse[i],step);

				m_sideImpulse[i] *= sideFrictionStiffness2;
			}
		}

// 		bool sliding = false;
// 		{
// 			for (int wheel =0;wheel <getNumWheels();wheel++)
// 			{
// 				btWheelInfo& wheelInfo = m_wheelInfo[wheel];
// 				class btRigidBody* groundObject = (class btRigidBody*) wheelInfo.m_raycastInfo.m_groundObject;
// 
// 				btScalar	rollingFriction = 0.f;
// 
// 				if (groundObject)
// 				{
// 					if (wheelInfo.m_engineForce != 0.f)
// 					{
// 						rollingFriction = -wheelInfo.m_engineForce* step;
// 					} else
// 					{
// 						btScalar defaultRollingFrictionImpulse = 0.f;
// 						btScalar maxImpulse = wheelInfo.m_brake ? wheelInfo.m_brake : defaultRollingFrictionImpulse;
// 						btWheelContactPoint contactPt(m_chassisBody,groundObject,wheelInfo.m_raycastInfo.m_contactPointWS,m_forwardWS[wheel],maxImpulse);
// 						rollingFriction = calcRollingFriction(contactPt);
// 					}
// 				}
// 
// 				//switch between active rolling (throttle), braking and non-active rolling friction (no throttle/break)
// 				
// 
// 
// 
// 				m_forwardImpulse[wheel] = btScalar(0.);
// 				m_wheelInfo[wheel].m_skidInfo= btScalar(1.);
// 
// 				if (groundObject)
// 				{
// 					m_wheelInfo[wheel].m_skidInfo= btScalar(1.);
// 					
// 					btScalar maximp = wheelInfo.m_wheelsSuspensionForce * step * wheelInfo.m_frictionSlip;
// 					btScalar maximpSide = maximp;
// 
// 					btScalar maximpSquared = maximp * maximpSide;
// 				
// 
// 					m_forwardImpulse[wheel] = rollingFriction;//wheelInfo.m_engineForce* timeStep;
// 
// 					btScalar x = (m_forwardImpulse[wheel] ) * fwdFactor;
// 					btScalar y = (m_sideImpulse[wheel] ) * sideFactor;
// 					
// 					btScalar impulseSquared = (x*x + y*y);
// 
// 					if (impulseSquared > maximpSquared)
// 					{
// 						sliding = true;
// 						
// 						btScalar factor = maximp / btSqrt(impulseSquared);
// 						
// 						m_wheelInfo[wheel].m_skidInfo *= factor;
// 					}
// 				} 
// 
// 			}
// 		}
// 		if (sliding)
// 		{
// 			for (int wheel = 0;wheel < getNumWheels(); wheel++)
// 			{
// 				if (m_sideImpulse[wheel] != btScalar(0.))
// 				{
// 					if (m_wheelInfo[wheel].m_skidInfo< btScalar(1.))
// 					{
// 						m_forwardImpulse[wheel] *=	m_wheelInfo[wheel].m_skidInfo;
// 						m_sideImpulse[wheel] *= m_wheelInfo[wheel].m_skidInfo;
// 					}
// 				}
// 			}
// 		}		
// 
// 			for (int wheel = 0;wheel < getNumWheels(); wheel++)
// 			{
// 				if ( getSteeringValue(wheel) != 0.0f ) // FIXME -> hassteeringinfluence
// 				{
// 					forwardWheelSumSide += m_sideImpulse[wheel];
// 				}
// 			}
		
		
		forwardWheelSumSide = 0.f;
		touchingfrontwheels = 0.f;

// 		btScalar sideFactor(1.);
// 		btScalar fwdFactor(0.5);

		for ( int wheel=0; wheel < numWheel; wheel++ )
		{
			btWheelInfo& wheelInfo = m_wheelInfo[wheel];
			btRigidBody* groundObject = static_cast<btRigidBody*>(wheelInfo.m_raycastInfo.m_groundObject);

			// THROTTLE AND BRAKING
			btScalar rollingFriction = 0.f;

			// sliding & force feedback info
			if (groundObject)
			{
	// 			btScalar wantsspeed( wheelWantsRotation(wheelInfo, step) );
				if (wheelInfo.m_engineForce != 0.f)
					rollingFriction -= wheelInfo.m_engineForce * step;

				if (wheelInfo.m_brake != 0.f)
				{
					btWheelContactPoint contactPt(m_chassisBody,groundObject,wheelInfo.m_raycastInfo.m_contactPointWS,m_forwardWS[wheel], wheelInfo.m_brake*step );
					rollingFriction += calcRollingFriction(contactPt);
				}

				m_sideImpulse[wheel] *= groundObject->getFriction();
				m_forwardImpulse[wheel] = rollingFriction;
	// 			m_forwardImpulse[wheel] *= groundObject->getFriction();

				btScalar maximp = wheelInfo.m_wheelsSuspensionForce * step * wheelInfo.m_frictionSlip;// * groundObject->getFriction(); //  
				btScalar maximpSquared = maximp * maximp;

				btScalar x = rollingFriction;
				btScalar y = m_sideImpulse[wheel] * 0.5f;

				btScalar impulseSquared = (x*x) + (y*y);

				// sliding?
	// 				if (impulseSquared > maximpSquared/* || m_wheelspinInfo[wheel] > 0.001f */)
					{
	// 					m_wheelInfo[wheel].m_skidInfo = 1.0f;
						if (impulseSquared > maximpSquared )
						{
							btScalar newSkidinfo(maximp / btSqrt(impulseSquared));
							m_wheelInfo[wheel].m_skidInfo = 0.5f * (newSkidinfo + (m_wheelInfo[wheel].m_skidInfo));
						}
						else
						{
							m_wheelInfo[wheel].m_skidInfo = 0.5f * (1.0f + m_wheelInfo[wheel].m_skidInfo);
						}
	// 					std::cout << wheel << " : " << m_wheelInfo[wheel].m_skidInfo << std::endl;

					}
	// 				else
	// // 					m_wheelInfo[wheel].m_skidInfo = 1.0f;
	// 					m_wheelInfo[wheel].m_skidInfo = 0.25f * (3.0f + m_wheelInfo[wheel].m_skidInfo);
						
// 					m_wheelInfo[wheel].m_skidInfo /= m_wheelSpinFactors[wheel];
	// 				m_wheelInfo[wheel].m_skidInfo = 0.5f*(m_wheelInfo[wheel].m_skidInfo+1.0f);
						
						// apply skidinfo to impulses
		// 				if (m_sideImpulse[wheel] != btScalar(0.f))
							if (m_wheelInfo[wheel].m_skidInfo < btScalar(1.f))
							{
								if ( m_forwardImpulse[wheel] )
								{
									m_forwardImpulse[wheel] *= m_wheelInfo[wheel].m_skidInfo; //  * 0.5f
									m_sideImpulse[wheel] *= m_wheelInfo[wheel].m_skidInfo;
								}
								else
								{
									m_sideImpulse[wheel] *= m_wheelInfo[wheel].m_skidInfo;
								}
							}
						

// 					if ( wheelInfo.m_engineForce * step != 0.0f && m_wheelInfo[wheel].m_skidInfo != 1.0f )
// 					{
// 						m_wheelSpinFactors[wheel] = 0.5f * ((1.0f + (1.0f - m_wheelInfo[wheel].m_skidInfo))+m_wheelSpinFactors[wheel]);
// 					}
// 					else
// 					{
// 						m_wheelSpinFactors[wheel] = 0.5f * (1.0f+m_wheelSpinFactors[wheel]);
// 					}

// 					m_wheelSpinFactors[wheel] = sqrt(m_wheelSpinFactors[wheel]);
// 					m_wheelSpinFactors[wheel] = sqrt(m_wheelSpinFactors[wheel]);
	// 				m_wheelSpinFactors[wheel] = sqrt(m_wheelSpinFactors[wheel]);
					
// 					std::cout << wheel << " : " << m_wheelSpinFactors[wheel] <<  "   " << rollingFriction <<  std::endl;
	//				std::cout << wheel << " : " << m_wheelSpinFactors[wheel] * (1.0f+(fabs(rollingFriction/10))) <<  "   " << std::endl;

					if ( getSteeringValue(wheel) != 0.0f ) // FIXME -> hassteeringinfluence
					{
						forwardWheelSumSide += m_sideImpulse[wheel];
					}
			}

	// cerr << m_wheelInfo[wheel].m_skidInfo << endl;
		}


	// apply the impulses
	for ( int wheel = 0; wheel < numWheel; wheel++ )
	{
		btWheelInfo& wheelInfo = m_wheelInfo[wheel];

		btVector3 rel_pos = wheelInfo.m_raycastInfo.m_contactPointWS - m_chassisBody->getCenterOfMassPosition();

		if (m_forwardImpulse[wheel] != btScalar(0.))
			m_chassisBody->applyImpulse(m_forwardWS[wheel]*(m_forwardImpulse[wheel]),rel_pos);

		if ( m_sideImpulse[wheel] != btScalar(0.f) )
		{
			btRigidBody* groundObject = static_cast<btRigidBody*>(wheelInfo.m_raycastInfo.m_groundObject);
			btVector3 rel_pos2 = wheelInfo.m_raycastInfo.m_contactPointWS - groundObject->getCenterOfMassPosition();
			btVector3 sideImp = m_axle[wheel] * m_sideImpulse[wheel];

// 			btVector3 vChassisWorldUp = getRigidBody()->getCenterOfMassTransform().getBasis().getColumn(1);
// 			rel_pos -= vChassisWorldUp * (vChassisWorldUp.dot(rel_pos) * 0.002);
			rel_pos[m_indexUpAxis] *= wheelInfo.m_rollInfluence;

			m_chassisBody->applyImpulse(sideImp,rel_pos);

			//apply friction impulse on the ground
			groundObject->applyImpulse(-sideImp,rel_pos2);
		}
	}

	if ( touchingfrontwheels > 0 )
		forwardWheelSumSide /= touchingfrontwheels;

		// std::cout << "side: " << forwardWheelSumSide << std::endl;
// 		cerr << "forw: " << forwardWheelSumForw << endl << endl;

	// calculate wheel rotation
	for ( int i = 0; i < numWheel; i++ )
	{
		btWheelInfo& wheel = m_wheelInfo[i];
		btVector3 relpos = wheel.m_raycastInfo.m_hardPointWS - getRigidBody()->getCenterOfMassPosition();
		btVector3 vel = getRigidBody()->getVelocityInLocalPoint( relpos );

		if (wheel.m_raycastInfo.m_isInContact)
		{
			const btTransform&	chassisWorldTransform = getChassisWorldTransform();

			btVector3 fwd (
				chassisWorldTransform.getBasis()[0][m_indexForwardAxis],
				chassisWorldTransform.getBasis()[1][m_indexForwardAxis],
				chassisWorldTransform.getBasis()[2][m_indexForwardAxis]);

			btScalar proj = fwd.dot(wheel.m_raycastInfo.m_contactNormalWS);
			fwd -= wheel.m_raycastInfo.m_contactNormalWS * proj;

			btScalar proj2 = fwd.dot(vel);
			
			wheel.m_deltaRotation = (proj2 * step) / (wheel.m_wheelsRadius);
			wheel.m_rotation += wheel.m_deltaRotation;

		} else
		{
			wheel.m_rotation += wheel.m_deltaRotation;
		}
		
		wheel.m_deltaRotation *= btScalar(0.99);//damping of rotation when not in contact
	}
}

// btScalar bRaycastVehicle::wheelWantsRotation( const btWheelInfo& wheel, btScalar step )
// {
// 	btVector3 relpos = wheel.m_raycastInfo.m_hardPointWS - getRigidBody()->getCenterOfMassPosition();
// 	btVector3 vel = getRigidBody()->getVelocityInLocalPoint( relpos );
// 	
// 	// CHASSIS FORWARD VECTOR
// 	const btTransform&	chassisWorldTransform = getChassisWorldTransform();
// 	btVector3 fwd (
// 		chassisWorldTransform.getBasis()[0][m_indexForwardAxis],
// 		chassisWorldTransform.getBasis()[1][m_indexForwardAxis],
// 		chassisWorldTransform.getBasis()[2][m_indexForwardAxis]);
// 	// CHASSIS FORWARD VECTOR DOT RAYCAST CONTACTPOINT
// 	btScalar proj = fwd.dot(wheel.m_raycastInfo.m_contactNormalWS);
// 	// CHASSIS FORWARD VECTOR - RAYCAST CONTACTPOINT*PROJ
// 	btVector3 fwd2 = fwd - (wheel.m_raycastInfo.m_contactNormalWS * proj);
// 	// CHASSIS FORWARD VECTOR DOT VELOCITY
// 	btScalar proj2 = fwd2.dot(vel);
// 
// 	// DELTAROTATION = PROJ2 / WHEEL RADIUS
// 	return (proj2 * step) / wheel.m_wheelsRadius;
// }

// btScalar bRaycastVehicle::customrayCast(btWheelInfo& wheel, unsigned int cwheel)
// {
// 	updateWheelTransformsWS( wheel,false);
// 
// 	btScalar depth = -1;
// 	
// 	btScalar raylen = wheel.getSuspensionRestLength()+wheel.m_wheelsRadius;
// 
// 	btVector3 rayvector = wheel.m_raycastInfo.m_wheelDirectionWS * (raylen);
// 	const btVector3& source = wheel.m_raycastInfo.m_hardPointWS;
// 	wheel.m_raycastInfo.m_contactPointWS = source + rayvector;
// 	const btVector3& target = wheel.m_raycastInfo.m_contactPointWS;
// 
// 	btScalar param = btScalar(0.);
// 	
// 	btVehicleRaycaster::btVehicleRaycasterResult	rayResults;
// 
// 	btAssert(m_vehicleRaycaster);
// 
// 	void* object = m_vehicleRaycaster->castRay(source,target,rayResults);
// 
// 	wheel.m_raycastInfo.m_groundObject = 0;
// 
// 	if (object)
// 	{
// 		param = rayResults.m_distFraction;
// 		depth = raylen * rayResults.m_distFraction;
// 
// 		wheel.m_raycastInfo.m_contactNormalWS = rayResults.m_hitNormalInWorld;
// 
// 		wheel.m_raycastInfo.m_isInContact = true;
// 		
// 		//wheel.m_raycastInfo.m_groundObject = &getFixedBody();///@todo for driving on dynamic/movable objects!;
// 		wheel.m_raycastInfo.m_groundObject = object;
// 
// 
// 		btScalar hitDistance = param*raylen;
// 		wheel.m_raycastInfo.m_suspensionLength = hitDistance - wheel.m_wheelsRadius;
// 		
// 		//clamp on max suspension travel
// 		btScalar  minSuspensionLength = wheel.getSuspensionRestLength() - wheel.m_maxSuspensionTravelCm*btScalar(0.01);
// 		btScalar maxSuspensionLength = wheel.getSuspensionRestLength() + wheel.m_maxSuspensionTravelCm*btScalar(0.01);
// 
// 		if (wheel.m_raycastInfo.m_suspensionLength < minSuspensionLength)
// 			wheel.m_raycastInfo.m_suspensionLength = minSuspensionLength;
// 
// 		if (wheel.m_raycastInfo.m_suspensionLength > maxSuspensionLength)
// 			wheel.m_raycastInfo.m_suspensionLength = maxSuspensionLength;
// 
// 		wheel.m_raycastInfo.m_contactPointWS = rayResults.m_hitPointInWorld;
// 
// 		btScalar denominator= wheel.m_raycastInfo.m_contactNormalWS.dot( wheel.m_raycastInfo.m_wheelDirectionWS );
// 
// 		btVector3 chassis_velocity_at_contactPoint;
// 		btVector3 relpos = wheel.m_raycastInfo.m_contactPointWS-getRigidBody()->getCenterOfMassPosition();
// 
// 		chassis_velocity_at_contactPoint = getRigidBody()->getVelocityInLocalPoint(relpos);
// 
// 		btScalar projVel = wheel.m_raycastInfo.m_contactNormalWS.dot( chassis_velocity_at_contactPoint );
// 
// 		if ( denominator >= btScalar(-0.1))
// 		{
// 			wheel.m_suspensionRelativeVelocity = btScalar(0.0);
// 			wheel.m_clippedInvContactDotSuspension = 10;
// 		}
// 		else
// 		{
// 			btScalar inv = btScalar(-1.) / denominator;
// 			wheel.m_suspensionRelativeVelocity = projVel * inv;
// 			wheel.m_clippedInvContactDotSuspension = inv;
// 		}
// 			
// 	}
// 	else
// 	{
// 		//put wheel info as in rest position
// 		wheel.m_raycastInfo.m_suspensionLength = wheel.getSuspensionRestLength();
// 		wheel.m_suspensionRelativeVelocity = btScalar(0.0);
// 		wheel.m_raycastInfo.m_contactNormalWS = -wheel.m_raycastInfo.m_wheelDirectionWS;
// // 		wheel.m_clippedInvContactDotSuspension = 10;
// 	}
// 
// 	return depth;
// }

void bRaycastVehicle::updateSuspension(btScalar deltaTime)
{
	(void)deltaTime;

	btScalar chassisMass = btScalar(1.) / m_chassisBody->getInvMass();

	for (int w_it=0; w_it<getNumWheels(); w_it++)
	{
		btWheelInfo &wheel_info = m_wheelInfo[w_it];
		
		if ( wheel_info.m_raycastInfo.m_isInContact )
		{
			btScalar force;
			//	Spring
			{
				btScalar susp_length = wheel_info.getSuspensionRestLength();
				btScalar current_length = wheel_info.m_raycastInfo.m_suspensionLength;

				btScalar length_diff = (susp_length - current_length);

				force = wheel_info.m_suspensionStiffness
					* length_diff * wheel_info.m_clippedInvContactDotSuspension;
			}
		
			// Damper
			{
				btScalar projected_rel_vel = wheel_info.m_suspensionRelativeVelocity;
				{
					btScalar	susp_damping;
					if ( projected_rel_vel < btScalar(0.0) )
					{
						susp_damping = wheel_info.m_wheelsDampingCompression;
					}
					else
					{
						susp_damping = wheel_info.m_wheelsDampingRelaxation;
					}
					force -= susp_damping * projected_rel_vel;
				}
			}

			// RESULT
			wheel_info.m_wheelsSuspensionForce = force * chassisMass;
			if (wheel_info.m_wheelsSuspensionForce < btScalar(0.))
			{
				wheel_info.m_wheelsSuspensionForce = btScalar(0.);
			}
		}
		else
		{
			wheel_info.m_wheelsSuspensionForce = btScalar(0.0);
		}
	}

}

void bRaycastVehicle::resolveSingleBilateral(btRigidBody& body1, const btVector3& pos1,
                      btRigidBody& body2, const btVector3& pos2,
                      btScalar distance, const btVector3& normal,btScalar& impulse ,btScalar timeStep)
{
	(void)timeStep;
	(void)distance;


	btScalar normalLenSqr = normal.length2();
	btAssert(btFabs(normalLenSqr) < btScalar(1.1));
	if (normalLenSqr > btScalar(1.1))
	{
		impulse = btScalar(0.);
		return;
	}
	btVector3 rel_pos1 = pos1 - body1.getCenterOfMassPosition(); 
	btVector3 rel_pos2 = pos2 - body2.getCenterOfMassPosition();
	//this jacobian entry could be re-used for all iterations
	
	btVector3 vel1 = body1.getVelocityInLocalPoint(rel_pos1);
	btVector3 vel2 = body2.getVelocityInLocalPoint(rel_pos2);
	btVector3 vel = vel1 - vel2;
	

	   btJacobianEntry jac(body1.getCenterOfMassTransform().getBasis().transpose(),
		body2.getCenterOfMassTransform().getBasis().transpose(),
		rel_pos1,rel_pos2,normal,body1.getInvInertiaDiagLocal(),body1.getInvMass(),
		body2.getInvInertiaDiagLocal(),body2.getInvMass());

	btScalar jacDiagAB = jac.getDiagonal();
	btScalar jacDiagABInv = btScalar(1.) / jacDiagAB;
	
	  btScalar rel_vel = jac.getRelativeVelocity(
		body1.getLinearVelocity(),
		body1.getCenterOfMassTransform().getBasis().transpose() * body1.getAngularVelocity(),
		body2.getLinearVelocity(),
		body2.getCenterOfMassTransform().getBasis().transpose() * body2.getAngularVelocity()); 
// 	btScalar a;
// 	a=jacDiagABInv;


	rel_vel = normal.dot(vel);
	
	//todo: move this into proper structure
	btScalar contactDamping = btScalar(0.2);

#ifdef ONLY_USE_LINEAR_MASS
	btScalar massTerm = btScalar(1.) / (body1.getInvMass() + body2.getInvMass());
	impulse = - contactDamping * rel_vel * massTerm;
#else	
	btScalar velocityImpulse = -contactDamping * rel_vel * jacDiagABInv;
	impulse = velocityImpulse;
#endif
}

btWheelInfo&	bRaycastVehicle::addWheel( const btVector3& connectionPointCS, const btVector3& wheelDirectionCS0,const btVector3& wheelAxleCS, btScalar suspensionRestLength, btScalar wheelRadius,const btVehicleTuning& tuning, bool isFrontWheel)
{

	btWheelInfoConstructionInfo ci;

	ci.m_chassisConnectionCS = connectionPointCS;
	ci.m_wheelDirectionCS = wheelDirectionCS0;
	ci.m_wheelAxleCS = wheelAxleCS;
	ci.m_suspensionRestLength = suspensionRestLength;
	ci.m_wheelRadius = wheelRadius;
	ci.m_suspensionStiffness = tuning.m_suspensionStiffness;
	ci.m_wheelsDampingCompression = tuning.m_suspensionCompression;
	ci.m_wheelsDampingRelaxation = tuning.m_suspensionDamping;
	ci.m_frictionSlip = tuning.m_frictionSlip;
	ci.m_bIsFrontWheel = isFrontWheel;
	ci.m_maxSuspensionTravelCm = tuning.m_maxSuspensionTravelCm;
	ci.m_maxSuspensionForce = tuning.m_maxSuspensionForce;

	m_wheelInfo.push_back( btWheelInfo(ci));
	
	btWheelInfo& wheel = m_wheelInfo[getNumWheels()-1];
	
	updateWheelTransformsWS( wheel , false );
	updateWheelTransform(getNumWheels()-1,false);
	return wheel;
}

// btWheelInfo&	bRaycastVehicle::addWheel( const btVector3& connectionPointCS, const btVector3& wheelDirectionCS0,const btVector3& wheelAxleCS, btScalar suspensionRestLength, btScalar wheelRadius,const btVehicleTuning& tuning, bool isFrontWheel)
// {
// 																				std::cout << "a1" << std::endl;
// 	btWheelInfoConstructionInfo ci;
// 																				std::cout << "a2" << std::endl;
// 	ci.m_chassisConnectionCS = connectionPointCS;
// 																				std::cout << "a3" << std::endl;
// 	ci.m_wheelDirectionCS = wheelDirectionCS0;
// 																				std::cout << "a4" << std::endl;
// 	ci.m_wheelAxleCS = wheelAxleCS;
// 																				std::cout << "a5" << std::endl;
// 	ci.m_suspensionRestLength = suspensionRestLength;
// 																				std::cout << "a6" << std::endl;
// 	ci.m_wheelRadius = wheelRadius;
// 																				std::cout << "a7" << std::endl;
// 	ci.m_suspensionStiffness = tuning.m_suspensionStiffness;
// 																				std::cout << "a8" << std::endl;
// 	ci.m_wheelsDampingCompression = tuning.m_suspensionCompression;
// 																				std::cout << "a9" << std::endl;
// 	ci.m_wheelsDampingRelaxation = tuning.m_suspensionDamping;
// 																				std::cout << "a10" << std::endl;
// 	ci.m_frictionSlip = tuning.m_frictionSlip;
// 																				std::cout << "a11" << std::endl;
// 	ci.m_bIsFrontWheel = isFrontWheel;
// 																				std::cout << "a12" << std::endl;
// 	ci.m_maxSuspensionTravelCm = tuning.m_maxSuspensionTravelCm;
// 																				std::cout << "a13" << std::endl;
// 	ci.m_maxSuspensionForce = tuning.m_maxSuspensionForce;
// 																				std::cout << "a14" << std::endl;
// 	m_wheelInfo.push_back( btWheelInfo(ci));
// 																				std::cout << "a15" << std::endl;
// 	btWheelInfo& wheel = m_wheelInfo[getNumWheels()-1];
// 																				std::cout << "a16" << std::endl;
// 	updateWheelTransformsWS( wheel , false );
// 																				std::cout << "a17" << std::endl;
// 	updateWheelTransform(getNumWheels()-1,false);
// 																				std::cout << "a18" << std::endl;
// // 	m_wheelspinInfo.push_back(0.f);
// 	m_wheelSpinFactors.push_back(1.f);
// 																				std::cout << "a19" << std::endl;
// 	return wheel;
// }
