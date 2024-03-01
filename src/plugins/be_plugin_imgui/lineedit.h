#pragma once

#include "kernel/be_entity_core_types.h"

	class BImGuiLineEdit: public BEntity_string
	{
		public:
			BImGuiLineEdit() { setProcessing(); }
			virtual ~BImGuiLineEdit() {};
			const char* class_id() const { return "ImGuiLineEdit"; }
			void process();
			bool set( const char* value );
			bool set( const Bstring& id, const Buint& value );
			// char m_buf[2048];
		private:
			unsigned int m_width;
			unsigned int m_height;
	};

	class BImGuiLineEdit_uint: public BEntity_uint
	{
		public:
			BImGuiLineEdit_uint() : m_buf("") { setProcessing(); }
			virtual ~BImGuiLineEdit_uint() {};
			const char* class_id() const { return "ImGuiLineEdit_uint"; }
			void process();
			bool set( const Buint& value );
			bool set( const Bstring& id, const Buint& value );
			bool set( const Bint& value );
			char m_buf[12];
		private:
			unsigned int m_width;
			unsigned int m_height;
	};

	class BImGuiLineEdit_int: public BEntity_int
	{
		public:
			BImGuiLineEdit_int() : m_buf("") { setProcessing(); }
			virtual ~BImGuiLineEdit_int() {};
			const char* class_id() const { return "ImGuiLineEdit_int"; }
			void process();
			bool set( const Bint& value );
			bool set( const Bstring& id, const Buint& value );
			char m_buf[12];
		private:
			unsigned int m_width;
			unsigned int m_height;
	};
	
	class BImGuiLineEdit_float: public BEntity_float
	{
		public:
			BImGuiLineEdit_float() : m_buf("") { setProcessing(); }
			virtual ~BImGuiLineEdit_float() {};
			const char* class_id() const { return "ImGuiLineEdit_float"; }
			void process();
			bool set( const Bfloat& value );
			bool set( const Bstring& id, const Buint& value );
			char m_buf[12];
		private:
			unsigned int m_width;
			unsigned int m_height;
	};

