#ifndef PLUGIN_H_INCLUDED
#define PLUGIN_H_INCLUDED

#include "kernel/be_plugin_interface.h"
#include <SDL/SDL.h>
#include "kernel/be_entity_macros.h"

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
				BGLWindow();
				virtual ~BGLWindow();

				virtual void construct();
				void create(const std::string& title, const unsigned int t_width, const unsigned int t_height);

				//	Destroy window and OpenGL Context, close the Display
				virtual void process();

				void setTitle(const std::string& title);
				virtual bool set( const Bstring& id, BEntity* value );
				virtual BEntity* get_reference( const Bstring& id );

			private:
				//	Resize Window
				void resize();
				void toggleFs();
				unsigned int w_bpp;		// Bits Per Pixel. With XFree86, highest = 24
				int n_width;
				int n_height;
				int fs;
				const SDL_VideoInfo* vidInfo;
				SDL_Surface* m_surface;
				int vidFlags;
				bool hwaccel;
				int settingsfs;
				SDL_Event event;
				bool m_resized;
				bool m_resizable;
				BEntity* m_destroy_entity_on_close;

				BEntity* m_width;
				BEntity* m_height;
				BEntity* m_mouse_x;
				BEntity* m_mouse_y;
				
		};

	// SWAPBUFFERS
		ENTITY_SIMPLEST( SDL_SwapBuffers ) { SDL_GL_SwapBuffers(); } END
		// class SDL_SwapBuffers: public BEntity
		// {
		// 	public:
		// 		SDL_SwapBuffers() : BEntity() { setProcessing(); }
		// 		virtual ~SDL_SwapBuffers() {};
		// 		void process() { SDL_GL_SwapBuffers(); };
		// };

#endif
