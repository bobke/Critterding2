#ifndef BE_ENTITY_CAMERA_H_INCLUDED
#define BE_ENTITY_CAMERA_H_INCLUDED

#include "plugins/be_plugin_bullet/be_entity_transform.h"
#include "kernel/be_entity_core_types.h"
#include "be_entity_graphics_model.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


	class BBulletTransform;

	class BCamera : public BEntity
	{
		public:
			BCamera();

			virtual ~BCamera() {};
			const char* class_id() const { return "Camera"; }
			virtual void construct();
			virtual void process();

			// const btVector3& getForwardVector() const { return m_transform.getBasis().getRow(2); }
			btVector3 getScreenDirection(const int win_x, const int win_y, const int mouse_x, const int mouse_y);

			BBulletTransform* m_transform;
			BBulletTransform* m_base_transform;

			// btTransform m_ProjectionMatrix;
			btTransform m_ViewMatrix;
			glm::mat4 m_ProjectionMatrixGLM;
			
			// btTransform m_ProjectionViewMatrix;
			// float m_projectionMatrix[16];
			float m_viewMatrix[16];
			// float m_prviewMatrix[16];
			// float m_projectionMatrixGLM[16];

		private:
			BEntity* m_active;
			
			BEntity* m_s_elapsed;

			// BEntity* m_transform;
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
	
			// GLuint m_ViewMatrixID;
			// GLuint m_ProjectionMatrixID;
			GLuint m_ProjectionViewMatrixID;

			BEntity* m_e_scale_x;
			
// 			void perspective( const float angleOfView, const float imageAspectRatio, const float n, const float f) 
// 			{ 
// 				float scale = tan(angleOfView * 0.5 * M_PI / 180) * n; 
// 				float r = imageAspectRatio * scale;
// 				float l = -r; 
// 				float t = scale;
// 				float b = -t; 
// 
// 				// set OpenGL perspective projection matrix
// 				m_projectionMatrix[0] = 2 * n / (r - l); 
// 				m_projectionMatrix[1] = 0; 
// 				m_projectionMatrix[2] = 0; 
// 				m_projectionMatrix[3] = 0; 
// 			
// 				m_projectionMatrix[4] = 0; 
// 				m_projectionMatrix[5] = 2 * n / (t - b); 
// 				m_projectionMatrix[6] = 0; 
// 				m_projectionMatrix[7] = 0; 
// 			
// 				m_projectionMatrix[8] = (r + l) / (r - l); 
// 				m_projectionMatrix[9] = (t + b) / (t - b); 
// 				m_projectionMatrix[10] = -(f + n) / (f - n); 
// 				m_projectionMatrix[11] = -1; 
// 			
// 				m_projectionMatrix[12] = 0; 
// 				m_projectionMatrix[13] = 0; 
// 				m_projectionMatrix[14] = -2 * f * n / (f - n); 
// 				m_projectionMatrix[15] = 0; 
// 				
// 				// m_ProjectionMatrix.setFromOpenGLMatrix( m_projectionMatrix );
// 				// std::cout << "!" << m_projectionMatrix[14] << std::endl;
// 			}

	};




#endif
 
