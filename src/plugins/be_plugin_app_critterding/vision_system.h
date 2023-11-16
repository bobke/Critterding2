#ifndef VISION_SYSTEM_H_INCLUDED
#define VISION_SYSTEM_H_INCLUDED

#include "kernel/be_entity_interface.h"
#include "plugins/be_plugin_bullet/physicsmodel_rigid.h"


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
			BEntity* m_drawEntities;
			btScalar m_drawingMatrix[16];
			unsigned int m_retinasperrow;
		
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
		
	};

#endif
 
