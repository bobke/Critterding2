#pragma once

#include "kernel/be_plugin_interface.h"
#include "kernel/be_entity_macros.h"
#include <GLFW/glfw3.h>

	// SCENE
		class Scene: public BEntity
		{
			public:
				Scene() : BEntity() {};
				virtual ~Scene() {};
				
				virtual void construct();
		};
		
		class BGLWindow: public BEntity
		{
			public:
				enum ID
				{
					FULLSCREEN,
					VSYNC
				};
				
				BGLWindow();
				const char* class_id() const { return "GLWindow"; }
				virtual ~BGLWindow();

				virtual void construct();
				void process();
				virtual bool set( const Bstring& id, BEntity* value );
				virtual BEntity* get_reference( const Bstring& id );
				virtual bool set( const Bstring& id, const Bbool& value );
				virtual Bbool get_bool( const Bstring& id );

				GLFWwindow* m_window;
				GLFWmonitor* m_primary_monitor;
				BEntity* m_fullscreen;
				BEntity* m_vsync;
				BEntity* m_destroy_entity_on_close;
				BEntity* m_width;
				BEntity* m_height;
				BEntity* m_position_x;
				BEntity* m_position_y;
				BEntity* m_mouse_x;
				BEntity* m_mouse_y;
				
				bool m_isFullscreen;
				bool m_isVSync;
				
				int m_windowed_width;
				int m_windowed_height;
				int m_windowed_pos_x;
				int m_windowed_pos_y;
		};

	// SWAPBUFFERS
		class GLSwapBuffers: public BEntity
		{
			public:
				GLSwapBuffers()
				: BEntity()
				, m_glwindow(0)
				{
					setProcessing();
				}
				const char* class_id() const { return "GLSwapBuffers"; }
				virtual ~GLSwapBuffers() {};
				void process()
				{
					if ( m_glwindow )
					{
						glfwSwapBuffers( m_glwindow->m_window );
					}
				};

				bool set( const Bstring& id, BEntity* value )
				{
					if ( id == "set_glwindow" )
					{
						m_glwindow = dynamic_cast<BGLWindow*>( value );
						return true;
					}
					return false;
				}
			private:
				BGLWindow* m_glwindow;
		};



