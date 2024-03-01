#pragma once

#include "kernel/be_entity_core_types.h"

	class BImGuiPushButton: public BEntity_trigger
	{
		public:
			BImGuiPushButton();
			virtual ~BImGuiPushButton() {};
			const char* class_id() const { return "ImGuiPushButton"; }
			virtual bool set( const Bstring& id, const char* value );
			virtual bool set( const Bstring& id, const Buint& value );
			void process();

		private:
			std::string m_text;
			unsigned int m_width;
			unsigned int m_height;
	};

