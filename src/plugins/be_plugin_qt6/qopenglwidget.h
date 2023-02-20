#ifndef QOPENGLWIDGET_H_INCLUDED
#define QOPENGLWIDGET_H_INCLUDED

#include <QOpenGLWidget>
#include "kernel/be_entity_interface.h"

		class BQOpenGLWidget : public QOpenGLWidget, public BEntity
		{
			public:
				BQOpenGLWidget();
				virtual ~BQOpenGLWidget() { /*deleteLater();*/ };
				const char* class_id() const { return "QOpenGLWidget"; }
				virtual Bbool onAddChild( BEntity* entity );
				QSurfaceFormat m_format;
		};
 
#endif
