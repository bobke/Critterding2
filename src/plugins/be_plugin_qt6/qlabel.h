#ifndef QLABEL_H_INCLUDED
#define QLABEL_H_INCLUDED

#include "kernel/be_entity_interface.h"
#include <QLabel>

	// QLABEL
		class BQLabel : public QLabel, public BEntity
		{
			public:
				BQLabel();
				virtual ~BQLabel() {};
				const char* class_id() const { return "QLabel"; }
// 				bool set( const Buint& value );
				bool set( const Bstring& id, const Buint& value );
				bool set( const Bstring& id, const char* value );
// 				bool set( const Bstring& value );
		};

	// QLABELDROPPABLE
		class BQLabelDroppable : public BQLabel
		{
			public:
				BQLabelDroppable();
				virtual ~BQLabelDroppable() {};
				const char* class_id() const { return "QLabelDroppable"; }
				virtual void dragEnterEvent(QDragEnterEvent *event);
				virtual void dragLeaveEvent(QDragLeaveEvent *event);
			    virtual void dropEvent(QDropEvent *event);
		};

#endif
