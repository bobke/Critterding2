#ifndef BE_RAYCAST_H
#define BE_RAYCAST_H

#include "kernel/be_entity_interface.h"
#include "btBulletDynamicsCommon.h"

class BRaycast : public BEntity
{
	public:
		BRaycast() {/* setProcessing(); */};
		~BRaycast() {};
		
		void construct();
		void process();

		// castResult cast(const btVector3& rayFrom, const btVector3& rayTo);

	private:
		btDynamicsWorld*	btDynWorld;
		
		BEntity* m_hit_entity;
		
		BEntity* m_source_x;
		BEntity* m_source_y;
		BEntity* m_source_z;
		BEntity* m_target_x;
		BEntity* m_target_y;
		BEntity* m_target_z;
};

#endif
