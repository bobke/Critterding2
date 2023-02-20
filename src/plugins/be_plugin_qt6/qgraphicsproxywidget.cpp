#include "qgraphicsproxywidget.h"
// #include "qgraphicsscene.h"
// #include "qopenglwidget.h"
// #include <QOpenGLWidget>
#include <QWidget>

// #include <iostream>

	// QGRAPHICSVIEW
		BQGraphicsProxyWidget::BQGraphicsProxyWidget()
		: QGraphicsProxyWidget()
		{
			setCacheMode(QGraphicsItem::DeviceCoordinateCache);
// 			setCacheMode(QGraphicsItem::ItemCoordinateCache);
			setPos(0,0);
			show();

		}
		
		BQGraphicsProxyWidget::~BQGraphicsProxyWidget()
		{
// 			close();
// 			deleteLater();
		}

		Bbool BQGraphicsProxyWidget::onAddChild( BEntity* entity )
		{ 
			QWidget* qwidget_entity = dynamic_cast<QWidget*>(entity);
			if ( qwidget_entity )
			{
				setWidget(qwidget_entity);
				show();
				return true;
			}

			return false;
		}
	
		Bbool BQGraphicsProxyWidget::onRemoveChild( BEntity* entity )
		{ 
			QWidget* qwidget_entity = dynamic_cast<QWidget*>(entity);
			if ( qwidget_entity )
			{
				setWidget(NULL);
// 				addWidget(qwidget_entity, Qt::AlignTop | Qt::AlignLeft);
				return true;
			}

			return false;
		} 
