#pragma once

#include "kernel/be_entity_core_types.h"

	class BImGuiLabel: public BEntity_string
	{
		public:
			BImGuiLabel() { setProcessing(); }
			virtual ~BImGuiLabel() {};
			const char* class_id() const { return "ImGuiLabel"; }
			void process();
			bool set( const char* value );
			bool set( const Bstring& id, const char* value );
			bool set( const Bstring& id, const Buint& value );
			// char m_buf[2048];
		private:
			unsigned int m_width;
			unsigned int m_height;
	};
