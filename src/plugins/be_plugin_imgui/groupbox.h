#pragma once

#include "kernel/be_entity_core_types.h"

	class BImGuiGroupBox: public BEntity
	{
		public:
			BImGuiGroupBox()
			: m_height(200)
			, m_width(450)
			{
				setProcessing();
			}
			virtual ~BImGuiGroupBox() {};
			const char* class_id() const { return "ImGuiGroupBox"; }
			void process();
			virtual bool set( const Bstring& id, const Buint& value );
			virtual bool set( const Bstring& id, const char* value );

		private:
			std::string m_text;
			unsigned int m_width;
			unsigned int m_height;
	};

	class BImGuiGroupBox_end: public BEntity
	{
		public:
			BImGuiGroupBox_end() { setProcessing(); }
			virtual ~BImGuiGroupBox_end() {};
			const char* class_id() const { return "ImGuiGroupBox_end"; }
			void process();
	};
