#pragma once

#include "kernel/be_entity_core_types.h"

	class OpenGL_Setup: public BEntity
	{
		public:
			OpenGL_Setup();
			virtual ~OpenGL_Setup() {};
			void construct();
			void process();
			
		private:
			BEntity* m_glShadeModel_GL_SMOOTH;
			BEntity* m_glEnable_GL_MULTISAMPLE;
			BEntity* m_glEnable_GL_LINE_SMOOTH;
			BEntity* m_glEnable_GL_POLYGON_SMOOTH;
			BEntity* m_glEnable_GL_CULL_FACE_BACK;
			BEntity* m_glEnable_GL_CULL_FACE_FRONT;
			BEntity* m_glEnable_GL_DEPTH_TEST;
			BEntity* m_glEnable_GL_BLEND;
			BEntity* m_glEnable_GL_ALPHA_TEST;
			BEntity* m_glEnable_GL_NORMALIZE;
			
			BEntity* m_window_width;
			BEntity* m_window_height;
			
	};


