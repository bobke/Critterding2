#pragma once

#include "kernel/be_entity_core_types.h"

	class BImGuiCheckBox: public BEntity_bool
	{
		public:
			BImGuiCheckBox();
			virtual ~BImGuiCheckBox() {};
			const char* class_id() const { return "ImGuiCheckBox"; }
			virtual bool set( const Bstring& id, const char* value );
			virtual bool set( const Bstring& id, const Buint& value );
			void process();

		private:
			std::string m_text;
			unsigned int m_width;
			unsigned int m_height;
	};

