#ifndef QGRAPHICSVIEW_H_INCLUDED
#define QGRAPHICSVIEW_H_INCLUDED

#include <QGraphicsView>
#include "kernel/be_entity_interface.h"

#include <QOpenGLWidget>

	// QGRAPHICSVIEW
		class BQGraphicsView : public QGraphicsView, public BEntity
		{
			public:
				BQGraphicsView();
				virtual ~BQGraphicsView();
				const char* class_id() const { return "QGraphicsView"; }
				virtual Bbool onAddChild( BEntity* entity );
				virtual Bbool onRemoveChild( BEntity* entity );

				virtual void process();
			private:
// 				QSurfaceFormat m_format;
		};

#endif
