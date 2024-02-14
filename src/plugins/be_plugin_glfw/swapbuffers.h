#pragma once

#include "kernel/be_plugin_interface.h"
// #include "kernel/be_entity_macros.h"

	class BGLWindow;
	class GLSwapBuffers: public BEntity
	{
		public:
			GLSwapBuffers();
			const char* class_id() const { return "GLSwapBuffers"; }
			virtual ~GLSwapBuffers() {};
			void process();

			bool set( const Bstring& id, BEntity* value );
		private:
			BGLWindow* m_glwindow;
	}; 
