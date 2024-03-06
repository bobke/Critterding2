#pragma once

#include "kernel/be_entity_interface.h"
#include "plugins/be_plugin_bullet/physicsmodel_rigid.h"
#include <glm/gtc/type_ptr.hpp>

	class BGraphicsModelSystem;

	class CdVisionSystem: public BEntity
	{
		public:
			CdVisionSystem() : BEntity() { setProcessing(); };
			virtual ~CdVisionSystem();
			const char* class_id() const { return "CdVisionSystem"; }

			virtual void construct();
			virtual void process();
			
			bool set ( const Bstring& id, BEntity* value );

		private:
			
			BEntity* m_critter_containers;

			void calcFramePos(unsigned int pos);
			unsigned char *retina;
			unsigned int fb;
			unsigned int color_tex;
			unsigned int depth_rb;
	
			btTransform m_turn_180;
			btTransform m_pos_transform;
			btScalar m_drawingMatrix[16];
			unsigned int m_retinasperrow;
			
			glm::mat4 m_ProjectionMatrixGLM;
			BEntity* m_skyDome;
		
		// Vision
			unsigned int m_critter_retinasize;
			
			unsigned int framePosX;
			unsigned int framePosY;
			unsigned int retinaColumnStart;
			unsigned int retinaRowStart;
			unsigned int retinaRowLength;
			unsigned int visionPosition;
			
			BEntity* m_print;
			BEntity* m_critter_sightrange;
			BEntity* m_e_scale_x;
			
			float m_buffer[16];
			btTransform m_ViewMatrix;
			glm::mat4 m_viewMatrix;
			glm::mat4 m_pvMatrix;
			
		
			unsigned int m_ProjectionViewMatrixID;
			
			BGraphicsModelSystem* m_graphics_model_system;
	};

