#ifndef QMDIAREA_H_INCLUDED
#define QMDIAREA_H_INCLUDED

#include "kernel/be_entity_interface.h"
#include <QMdiArea>

		class BQMdiArea : public QMdiArea, public BEntity
		{
			public:
				BQMdiArea();
				virtual ~BQMdiArea() {};
				const char* class_id() const { return "QMdiArea"; }
				virtual Bbool onAddChild( BEntity* entity );
				virtual Bbool onRemoveChild( BEntity* entity );
				virtual void dragEnterEvent(QDragEnterEvent *event);
				virtual void dragLeaveEvent(QDragLeaveEvent *event);
				virtual void dropEvent(QDropEvent *event);
		};

		
		
#endif
