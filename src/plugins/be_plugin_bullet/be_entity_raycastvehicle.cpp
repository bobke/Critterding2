#include "be_entity_raycastvehicle.h"
#include "be_entity_transform.h"

		BeServerEntityPhysics_Vehicle::BeServerEntityPhysics_Vehicle()
		 : m_brakingsum(0.0f)
		 , m_throttlesum(0.0f)
		 , gVehicleSteering(0.0f)
		 , m_prev_steering_sum(0.0f)
		 , m_wheels(0)
		{
			setProcessing();
		};

		void BeServerEntityPhysics_Vehicle::construct()
		{
// 			m_wheels = BEntity*(new BEntity());
// 			addChild( m_wheels );
// 			m_wheels->setName( "wheels" );

			// CALCULATE BRAKING AND THROTTLE HELPER SUMS
			for ( unsigned int i = 0; i < 1; i++ )
			{
				m_brakingsum += 100;
				m_throttlesum += 100;
			}

			// BRAKINGFORCE
			{
				m_brakingForce = addChild( "brakingForce", new BEntity_float() );

				// LIMITS
					m_brakingForce->addChild( "limit_low", new BEntity_float() )->set( 0.0f );
					m_brakingForce->addChild( "limit_high", new BEntity_float() )->set( 1.0f );
			}
			
			// ENGINEFORCE
			{
				m_engineForce = addChild( "engineForce", new BEntity_float() );

				// LIMITS
					m_engineForce->addChild( "limit_low", new BEntity_float() )->set( -1.0f );
					m_engineForce->addChild( "limit_high", new BEntity_float() )->set( 1.0f );
			}

			// STEERING
			{
				// STEERING VALUE
					m_steering = addChild( "steering", new BEntity_float() );
					
				// STATE LEFT
					m_steering_state_left = addChild( "steering_state_left", new BEntity_bool() );

				// STATE RIGHT
					m_steering_state_right = addChild( "steering_state_right", new BEntity_bool() );

				// SENSITIVITY
					m_steering_sensitivity = addChild( "steering_sensitivity", new BEntity_float() );
					m_steering_sensitivity->set( 0.4f );
				
				// MUTATORS
					// m_steering_add = m_steering->addChild( "+", new BEntity_float() );
					// m_steering_subtract = m_steering->addChild( "-", new BEntity_float() );
				
				// LIMITS
					m_limit_steering_low = m_steering->addChild( "limit_low", new BEntity_float() );
					m_limit_steering_low->set( -0.45f );
					m_limit_steering_high = m_steering->addChild( "limit_high", new BEntity_float() );
					m_limit_steering_high->set( 0.45f );
			}

// 			// LINEAR DAMPING
// 				m_linearDamping = new BEntity_float();
// 				m_linearDamping->setName( "linear_damping" );
// 				m_linearDamping->set( 0.05f );
// 				addChild( m_linearDamping );
// 			
// 			// ANGULAR DAMPING
// 				m_angularDamping = new BEntity_float();
// 				m_angularDamping->setName( "angular_damping" );
// 				m_angularDamping->set( 0.82f );
// 				addChild( m_angularDamping );
		}
		
		BEntity* BeServerEntityPhysics_Vehicle::getProperty_Reference(const std::string& caller_name) const
		{
			if ( caller_name == "chassis" )
				return m_chassis_reference;

			return 0;
		}
		
		bool BeServerEntityPhysics_Vehicle::set( const Bstring& id, BEntity* value )
		// bool BeServerEntityPhysics_Vehicle::set( const std::string& caller_name, BeSignalHistory& entity_history, BEntity* value, const bool do_update )
		{
			if ( id == "chassis" )
			{
				m_chassis_reference = value;
				setChassis(value);
				return true;
			}
			return false;
		}

		BPhysicsEntity* BeServerEntityPhysics_Vehicle::getChassis() { return m_chassis; }
		void BeServerEntityPhysics_Vehicle::setChassis(BEntity* entity)
		{
			BPhysicsEntity* physics_entity = dynamic_cast<BPhysicsEntity*>(entity);
			if ( physics_entity )
			{
				m_chassis = physics_entity;
				
// 				btVector3 localInertia(0.00000f,0.000001f,0.00000f);
// 					m_chassis->getPhysicsComponent()->getBody()->setMassProps( 1200.0f, localInertia );
// 					m_chassis->getPhysicsComponent()->getShape()->calculateLocalInertia( 1200, localInertia );
				
// 				m_chassis->getPhysicsComponent()->getBody()->setActivationState(DISABLE_DEACTIVATION);
// 				m_chassis->get("update_interval")->set(-1.0f);
// 				m_chassis->getPhysicsComponent()->getBody()->setDamping(m_linearDamping->get_float(), m_angularDamping->get_float());
// 				m_chassis->getPhysicsComponent()->getBody()->setRestitution( 0.0f );
// 				m_chassis->getPhysicsComponent()->getBody()->setFriction( 0.2f );

				
				
				m_vehicle = boost::shared_ptr<bRaycastVehicle>(new bRaycastVehicle(m_tuning,m_chassis->getPhysicsComponent()->getBody(),m_vehicleRayCaster.get()));
				m_vehicle->setCoordinateSystem(0,1,2); // rightIndex,upIndex,forwardIndex
				
				for ( unsigned int k(0); k < 2; ++k )
				{
					// REAR
					BeWheelInfo be_wheel_info;
					if ( k==0 )
					{
						be_wheel_info.offset = 1.36f;
						be_wheel_info.radius = 0.39f;
						be_wheel_info.axle_length = 0.78f;
						be_wheel_info.axle_connection_height = 0.55f;
						be_wheel_info.suspension_length = 0.22f;
					}
					// FRONT
					else if ( k==1 )
					{
						be_wheel_info.offset = -1.34f;
						be_wheel_info.radius = 0.39f;
						be_wheel_info.axle_length = 0.75f;
						be_wheel_info.axle_connection_height = 0.55f;
						be_wheel_info.suspension_length = 0.22f;
					}

					createWheelPair( k, be_wheel_info ); //carDef->getChassis().getWheelPairAttachments()[
				}

				m_vehicle->resetSuspension();
				for ( int i(0); i < m_vehicle->getNumWheels(); ++i )
				{
					//synchronize the wheels with the (interpolated) chassis worldtransform
					m_vehicle->updateWheelTransform(i,true);
				}

				m_wheels = m_chassis->getChild("wheels", 1);
			}

			parent()->onAddChild(this);
		}
		
		void BeServerEntityPhysics_Vehicle::process()
		{
			// FIXME 
			// auto timeDelta(0.01f);
			auto timeDelta(0.016667f);
			// float timeDelta( topParent()->getChild("sys", 1)->getChild("timer", 1)->getChild("s_elapsed", 1)->get_float() );

			if ( m_vehicle && timeDelta > 0.0f )
			{
// 				for ( unsigned int i(0); i < m_vehicle->getNumWheels(); ++i )
// 				{
// 					m_vehicle->updateWheelTransform(i,true);
// 					std::stringstream w;
// 					w << i;
// 					get("wheels")->get(w.str())->set(m_vehicle->getWheelInfo( i ).m_worldTransform, true);
// // 					if ( get("wheels")->get(w.str())->hasOutput() )
// // 						get("wheels")->get(w.str())->getOutput()->commitDelayedExecute();
// 				}
				// THROTTLE
				{
					const float engine(m_engineForce->get_float()*3000);
					for ( unsigned int i(0); i < 2; ++i )
					{
						float relativethrottleforce(0.0f);
						if ( i == 0 )
							relativethrottleforce = (engine / m_throttlesum) * 100;
// 						else if ( i == 1 )
// 							relativethrottleforce = (engine / m_throttlesum) * 0;

						m_vehicle->applyEngineForce(relativethrottleforce,(i*2));
						m_vehicle->applyEngineForce(relativethrottleforce,(i*2)+1);
					}
				}

				// BRAKING
				{
					const float braking(m_brakingForce->get_float()*5000);
					for ( unsigned int i(0); i < 2; ++i )
					{
						// BRAKING
						float relativebrakingforce(0.0f);
						if ( i == 0 )
							relativebrakingforce = (braking / m_brakingsum) * 43;
						else if ( i == 1 )
							relativebrakingforce = (braking / m_brakingsum) * 57;

						m_vehicle->setBrake(relativebrakingforce,(i*2));
						m_vehicle->setBrake(relativebrakingforce,(i*2)+1);
					}
				}

				// STEERING
				{
					// STEERING STATES
						const bool t_left = m_steering_state_left->get_bool();
						const bool t_right = m_steering_state_right->get_bool();
						float t_steering_add(0.0f);
						float t_steering_subtract(0.0f);

						if ( t_left )
						{
							t_steering_add = m_steering_sensitivity->get_float() * timeDelta;
						}
						if ( t_right )
						{
							t_steering_subtract = m_steering_sensitivity->get_float() * timeDelta;
						}
						
						if ( t_steering_add != t_steering_subtract )
						{
							if ( t_steering_add != 0.0f )
							{
								m_steering->set( m_steering->get_float() + t_steering_add );
							}
							if ( t_steering_subtract != 0.0f )
							{
								m_steering->set( m_steering->get_float() - t_steering_subtract );
							}

						}

					// STEERING CENTERING
						// if ( *setting_steering_autocenter )
						{
							if ( (!t_right && !t_left) || (t_left && m_vehicle->forwardWheelSumSide < 0) || (t_right && m_vehicle->forwardWheelSumSide > 0) )
							{
								const float maximumx = 90.0f; // bout max m_vehicle->forwardWheelSumSide
								const float x = (maximumx/2) + (m_vehicle->forwardWheelSumSide);
								// const float nx = 2.0f*(x-maximumx/2.0f)/maximumx;
								const float nx = 1.0f*(x-maximumx/2.0f)/maximumx;
								// m_steering_add->set( -nx * timeDelta ); // * fabs(nx)
								m_steering->set( m_steering->get_float() - (-nx * timeDelta) );
								
								
// 								m_prev_steering_sum = 0.25f * ( m_vehicle->forwardWheelSumSide + (m_prev_steering_sum*3) );
// 								m_steering_add->set( -0.025f * m_prev_steering_sum * timeDelta );
							}
						}

					// APPLY STEERING LIMITS
						if ( m_steering->get_float() <  m_limit_steering_low->get_float() )
						{
							m_steering->set( m_limit_steering_low->get_float() );
						}
						if ( m_steering->get_float() >  m_limit_steering_high->get_float() )
						{
							m_steering->set( m_limit_steering_high->get_float() );
						}
						
					// APPLY
						for ( unsigned int i(0); i < 2; ++i )
						{
							float influence(0.0f);

							if ( i == 1 )
								influence = 100.0f;

							if ( influence != 0 && influence <= 100.0f && influence >= -100.0f )
							{
								float factor(influence / 100);
								m_vehicle->setSteeringValue(m_steering->get_float()*factor,(i*2));
								m_vehicle->setSteeringValue(m_steering->get_float()*factor,(i*2)+1);
							}
						}
				}

				// DOWNFORCE
					const float downForceK(0.08f);
					btVector3 angle( -m_chassis->getPhysicsComponent()->getBody()->getWorldTransform().getBasis()[1].normalized() * fabs(m_vehicle->getCurrentSpeedKmHour()) * fabs(m_vehicle->getCurrentSpeedKmHour()) * timeDelta * downForceK ); //speed squared * downforce constant * down vector
					//std::cout << angle.getX() << " " << angle.getY() << " " << angle.getZ() << std::endl;
					//cout << angle.getY() << endl;
					//if ( angle.getY() < 0 )
					m_chassis->getPhysicsComponent()->getBody()->applyCentralImpulse ( angle );

				
				unsigned int count(0);
				if ( m_wheels )
				{
					for_all_children_of( m_wheels )
					{
						// auto wheel_it(m_wheels->children_begin());
						auto t = dynamic_cast<BBulletTransform*>( *child );
						if ( t )
						{
							// t->set( m_vehicle->getWheelInfo( count++ ).m_worldTransform );
							t->m_transform = m_vehicle->getWheelInfo( count++ ).m_worldTransform;
							t->onUpdate();
						}
					}
				}
			}
		}

		
		
		void BeServerEntityPhysics_Vehicle::createWheelPair( unsigned int wheelpairindex, const BeWheelInfo& be_wheel_info )
		{
			// WHEEL LEFT
// 			btVector3 wheelDirectionCS0(0,-1,0);
// 			btVector3 wheelAxleCS(-1,0,0);
			btVector3 wheelDirectionCS0(0,-1,0);
			btVector3 wheelAxleCS(-1,0,0);
			float connectionHeight = -be_wheel_info.axle_connection_height + be_wheel_info.radius;
			bool isFrontWheel=true; // need to test effect

			btVector3 connectionPointCS0;
			connectionPointCS0 = btVector3(
				-be_wheel_info.axle_length,
				// 			-chassisattachment.getHalfDimensions().x - wheel_left->getWidth(),
				connectionHeight,
				// 			-chassisattachment.getHalfDimensions().z + wheel_left->getRadius()
				be_wheel_info.offset
				);
			btWheelInfo& wheel = m_vehicle->addWheel(
				connectionPointCS0,
				wheelDirectionCS0,
				wheelAxleCS,
				be_wheel_info.suspension_length, // suspension height
				be_wheel_info.radius, // radius
				m_tuning,
				isFrontWheel
				);

			wheel.m_suspensionStiffness = 86.0f;
			wheel.m_wheelsDampingRelaxation = 0.09f;
			wheel.m_wheelsDampingCompression = 5.0f;
			wheel.m_rollInfluence = 0.05;
			wheel.m_maxSuspensionForce = 3000000;
			wheel.m_frictionSlip = 0.985;

			// WHEEL RIGHT
// 			connectionHeight = -be_wheel_info.axle_connection_height + be_wheel_info.radius;
			isFrontWheel=true; // need to test effect

			// 		btVector3 connectionPointCS0;
			connectionPointCS0 = btVector3(
				be_wheel_info.axle_length,
				// 			-chassisattachment.getHalfDimensions().x - wheel_right->getWidth(),
				connectionHeight,
				// 			-chassisattachment.getHalfDimensions().z + wheel_right->getRadius()
				be_wheel_info.offset
				);

			btWheelInfo& wheel2 = m_vehicle->addWheel(
				connectionPointCS0,
				wheelDirectionCS0,
				wheelAxleCS,
				be_wheel_info.suspension_length,
				be_wheel_info.radius,
				m_tuning,
				isFrontWheel
				);

			wheel2.m_suspensionStiffness = 86.0f;
			wheel2.m_wheelsDampingRelaxation = 0.09f;
			wheel2.m_wheelsDampingCompression = 5.0f;
			wheel2.m_rollInfluence = 0.05;
			wheel2.m_maxSuspensionForce = 3000000;
			wheel2.m_frictionSlip = 0.95;
			
		}
		
		
		// BeServerEntityPhysics_Vehicle_Wheel::BeServerEntityPhysics_Vehicle_Wheel()
		// : BEntity()
		// {
		// 	BEntity* t = BEntity*(new BEntity_Property_Transform());
		// 	addChild( t );
		// 	t->setName( "transform" );
		// };
		
