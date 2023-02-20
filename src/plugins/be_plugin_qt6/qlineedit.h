#ifndef QLINEEDIT_H_INCLUDED
#define QLINEEDIT_H_INCLUDED

#include "kernel/be_entity_interface.h"
#include "kernel/be_entity_core_types.h"
#include <QLineEdit>

	// QLINEEDIT
		class BQLineEdit : public QLineEdit, public BEntity_uint
		{
			Q_OBJECT
			public:
				BQLineEdit();
				virtual ~BQLineEdit() {};
				const char* class_id() const { return "QLineEdit"; }
				bool set( BEntity* entity );
				bool set( const char* value );
				bool set( const Buint& value );
				bool set( const Bfloat& value );
				bool set( const Bdouble& value );
				bool set( const Bstring& id, const char* value );
				bool set( const Bstring& id, const Buint& value );
// 				bool set( const Bstring& id, const Bfloat& value );
// 				bool set( const Bstring& id, const Bdouble& value );
// // 				bool set( const Bstring& id, const Bbool& value );


			private Q_SLOTS:
				void onChange();
			private:
// 				Bfloat m_float; // HACK
				Buint m_width;
				Buint m_height;
				
		};

	// QLINEEDIT_INT
		class BQLineEdit_int : public QLineEdit, public BEntity_int
		{
			Q_OBJECT
			public:
				BQLineEdit_int();
				virtual ~BQLineEdit_int() {};
				const char* class_id() const { return "QLineEdit_int"; }
				bool set( BEntity* entity );
				bool set( const char* value );
// 				bool set( const Buint& value );
				bool set( const Bint& value );
				bool set( const Bstring& id, const Buint& value );
				bool set( const Bstring& id, const Bint& value );

			private Q_SLOTS:
				void onChange();
			private:
// 				Bfloat m_float; // HACK
				Buint m_width;
				Buint m_height;
		};

	// QLINEEDIT_FLOAT
		class BQLineEdit_float : public QLineEdit, public BEntity_float
		{
			Q_OBJECT
			public:
				BQLineEdit_float();
				virtual ~BQLineEdit_float() {};
				const char* class_id() const { return "QLineEdit_float"; }
				bool set( BEntity* entity );
				bool set( const char* value );
// 				bool set( const Buint& value );
				bool set( const Bfloat& value );
				bool set( const Bstring& id, const Buint& value );
				bool set( const Bstring& id, const Bfloat& value );

			private Q_SLOTS:
				void onChange();
			private:
// 				Bfloat m_float; // HACK
				Buint m_width;
				Buint m_height;
		};
		
	// QLINEEDIT_DOUBLE
		class BQLineEdit_double : public QLineEdit, public BEntity_double
		{
			Q_OBJECT
			public:
				BQLineEdit_double();
				virtual ~BQLineEdit_double() {};
				const char* class_id() const { return "QLineEdit_double"; }
				bool set( BEntity* entity );
				bool set( const char* value );
				bool set( const Bdouble& value );
				bool set( const Bstring& id, const Buint& value );
				bool set( const Bstring& id, const Bdouble& value );

			private Q_SLOTS:
				void onChange();
			private:
				Buint m_width;
				Buint m_height;
		};

	// QLINEEDIT_STRING
		class BQLineEdit_string : public QLineEdit, public BEntity_string
		{
			Q_OBJECT
			public:
				BQLineEdit_string();
				virtual ~BQLineEdit_string() {};
				const char* class_id() const { return "QLineEdit_string"; }
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
#endif
