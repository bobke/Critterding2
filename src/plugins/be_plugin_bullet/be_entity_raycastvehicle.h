#ifndef BE_SERVER_ENTITY_CAR_H_INCLUDED
#define BE_SERVER_ENTITY_CAR_H_INCLUDED

#include "kernel/be_entity_interface.h"
#include "kernel/be_entity_core_types.h"
#include "plugins/be_plugin_bullet/btraycastvehicle.h"
#include "plugins/be_plugin_bullet/be_entity_physics_entity.h"

	struct BeWheelInfo
	{
		float offset;
		float radius;
		float axle_length;
		float axle_connection_height;
		float suspension_length;
	};

	class BeServerEntityPhysics_Vehicle : public BEntity
	{
		public:
			BeServerEntityPhysics_Vehicle();
			const char* class_id() const { return "SC_car"; }
			virtual ~BeServerEntityPhysics_Vehicle() {};

			virtual void construct();
			
			virtual BEntity* getProperty_Reference(const std::string& caller_name) const;
			// virtual bool setProperty( const std::string& caller_name, BeSignalHistory& entity_history, BEntity* value, const bool do_update=true );
			virtual bool set( const Bstring& id, BEntity* value );


			// BeServerEntityPhysics::ptr getChassis();
			BPhysicsEntity* getChassis();
			
			void setChassis(BEntity* entity);
			
			void process();

	// 			virtual void onUpdateDelayed()
	// 			{
	// 				if ( m_wheels )
	// 				{
	// 					auto wheel_it(m_wheels->children_begin());
	// 					wheel_it->second->getOutput()->commitDelayed();
	// 					wheel_it->second->setProperty(m_vehicle->getWheelInfo( 0 ).m_worldTransform);
	// 					++wheel_it;
	// 					wheel_it->second->getOutput()->commitDelayed();
	// 					wheel_it->second->setProperty(m_vehicle->getWheelInfo( 1 ).m_worldTransform);
	// 					++wheel_it;
	// 					wheel_it->second->getOutput()->commitDelayed();
	// 					wheel_it->second->setProperty(m_vehicle->getWheelInfo( 2 ).m_worldTransform);
	// 					++wheel_it;
	// 					wheel_it->second->getOutput()->commitDelayed();
	// 					wheel_it->second->setProperty(m_vehicle->getWheelInfo( 3 ).m_worldTransform);
	// 				}
	// 			}

			BEntity* m_wheels;
			boost::shared_ptr<bRaycastVehicle> m_vehicle;
			boost::shared_ptr<btDefaultVehicleRaycaster> m_vehicleRayCaster;
			void createWheelPair( unsigned int wheelpairindex, const BeWheelInfo& be_wheel_info );

		private:
			BEntity* m_chassis_reference;
			BPhysicsEntity* m_chassis;
	// 		BEntity* m_linearDamping;
	// 		BEntity* m_angularDamping;
			bRaycastVehicle::btVehicleTuning m_tuning;
	// 		BEntity* m_wheels;
			float	m_brakingsum;
			float	m_throttlesum;
			float	maxEngineForce;//this should be engine/velocity dependent
			float	maxBrakingForce;
			float	defaultBrakingForce;
			float	gVehicleSteering;
			float	m_prev_steering_sum;
			
			BEntity* m_brakingForce;
			BEntity* m_engineForce;
			BEntity* m_steering;
			BEntity* m_steering_sensitivity;
			BEntity* m_steering_state_left;
			BEntity* m_steering_state_right;
			BEntity* m_limit_steering_low;
			BEntity* m_limit_steering_high;
			// BEntity* m_steering_add;
			// BEntity* m_steering_subtract;
	};

	// class BeServerEntityPhysics_Vehicle_Wheel : public BEntity
	// {
	// 	public:
	// 		BeServerEntityPhysics_Vehicle_Wheel();
	// 		virtual ~BeServerEntityPhysics_Vehicle_Wheel() {};
	// 		typedef boost::shared_ptr<BeServerEntityPhysics_Vehicle_Wheel> ptr;
	// 
	// // 		virtual void onUpdateDelayed()
	// // 		{
	// // 			std::cout << "hi" << std::endl;
	// // 			const auto& end(m_children.end());
	// // 			for ( auto it=m_children.begin(); it != end; ++it )
	// // 				it->second->onUpdateDelayed();
	// // // 				m_last_send_time_ago = 0.0f;
	// // 			if ( m_output )
	// // 				m_output->commitDelayedExecute();
	// // 		}
	//     private:
	// };


#endif
 
