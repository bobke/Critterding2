#pragma once
#include "kernel/be_entity_interface.h"
#include "kernel/be_entity_core_types.h"
#include <QPlainTextEdit>

	// STRING
		class BQPlainTextEdit : public QPlainTextEdit, public BEntity_string
		{
			Q_OBJECT
			public:
				BQPlainTextEdit();
				virtual ~BQPlainTextEdit() {};
				const char* class_id() const { return "BQPlainTextEdit"; }
				bool set( const char* value );
// 				bool set( const Buint& value );
				bool set( const Bstring& id, const Buint& value );
				bool set( const Bstring& id, const char* value );
				// const char* get_string();

			private Q_SLOTS:
				void onChange();
			private:
				Buint m_width;
				Buint m_height;
		};		
