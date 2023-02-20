#ifndef QGRAPHICSPROXYWIDGET_H_INCLUDED
#define QGRAPHICSPROXYWIDGET_H_INCLUDED

#include <QGraphicsProxyWidget>
#include "kernel/be_entity_interface.h"

		class BQGraphicsProxyWidget : public QGraphicsProxyWidget, public BEntity
		{
			public:
				BQGraphicsProxyWidget();
				virtual ~BQGraphicsProxyWidget();
				const char* class_id() const { return "QGraphicsProxyWidget"; }
				virtual Bbool onAddChild( BEntity* entity );
				virtual Bbool onRemoveChild( BEntity* entity );
		};

#endif

