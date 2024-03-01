#pragma once

#include "kernel/be_entity_core_types.h"
// #include "kernel/be_plugin_interface.h"
#include "kernel/be_entity_macros.h"
#include "kernel/be_lib_handler.h"

	class BImGuiContext: public BEntity
	{
		public:
			BImGuiContext() { setProcessing(); }
			const char* class_id() const { return "ImGuiContext"; }
			virtual ~BImGuiContext();

			void construct();
			void process();
			bool set( const Bstring& id, BEntity* value );
			
		private:
			BEntity* m_capture_keyboard;
			BEntity* m_capture_mouse;
	};

	class BImGuiWindow: public BEntity
	{
		public:
			BImGuiWindow() : m_tool_active(true) { setProcessing(); }
			const char* class_id() const { return "ImGuiWindow"; }
			virtual ~BImGuiWindow() {};

			virtual void construct();
			void process();
			virtual bool set( const Bstring& id, const char* value );
			virtual bool set( const Bstring& id, const Buint& value );
			virtual bool set( const Bstring& id, BEntity* value );


		private:
			BEntity* m_destroy_entity_on_close;
			float m_color[4];
			bool m_tool_active;
			std::string m_text;
			unsigned int m_width;
			unsigned int m_height;
	};

	class BImGuiWindow_end: public BEntity
	{
		public:
			BImGuiWindow_end() { setProcessing(); }
			const char* class_id() const { return "ImGuiWindow_end"; }
			virtual ~BImGuiWindow_end() {};
			void process();
	};	

	class BImGuiRender: public BEntity
	{
		public:
			BImGuiRender() { setProcessing(); }
			const char* class_id() const { return "ImGuiRender"; }
			virtual ~BImGuiRender() {};
			void process();
	};

	class BImGuiDemoWindow: public BEntity
	{
		public:
			BImGuiDemoWindow() { setProcessing(); }
			const char* class_id() const { return "ImGuiDemoWindow"; }
			virtual ~BImGuiDemoWindow() {};
			void process();
	};

	class BTranslate_QT_IMGUI: public BEntity
	{
		public:
			BTranslate_QT_IMGUI() : BEntity() {};
			virtual ~BTranslate_QT_IMGUI() {};

			virtual void construct();
			virtual const char* get_string( const Bstring& id );
		private:
			BClassTranslationMap m_imgui_translation_map;
	};
