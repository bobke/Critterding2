#ifndef BE_ENTITY_CAMERA_H_INCLUDED
#define BE_ENTITY_CAMERA_H_INCLUDED

#include "be_entity_transform.h"
#include "kernel/be_entity_core_types.h"
#include "be_entity_graphics_model.h"

	class BCamera : public BEntity
	{
		public:
			BCamera();

			virtual ~BCamera() {};
			virtual void construct();
			virtual void process();

		private:
			btScalar m_modelview[16];
			glTransform m_gl_transform;
			btTransform m_pos_transform;
			btTransform m_inversable_ops;
			
			BEntity* m_s_elapsed;

			BEntity* m_transform;
			BEntity* m_fov_y;
			BEntity* m_aspect_ratio;
			BEntity* m_z_near;
			BEntity* m_z_far;
			
			BEntity* m_sensitivity_move;
			BEntity* m_sensitivity_look;
			
			
			BEntity* m_forward;
			BEntity* m_backward;
			BEntity* m_left;
			BEntity* m_right;
			BEntity* m_up;
			BEntity* m_down;

			BEntity* m_look_left;
			BEntity* m_look_right;
			BEntity* m_look_up;
			BEntity* m_look_down;
			BEntity* m_look_roll_left;
			BEntity* m_look_roll_right;
		
	};




#endif
 
