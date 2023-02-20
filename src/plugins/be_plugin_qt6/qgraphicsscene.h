#ifndef QGRAPHICSSCENE_H_INCLUDED
#define QGRAPHICSSCENE_H_INCLUDED

#include "kernel/be_entity_interface.h"
#include <QGraphicsScene>

	// QGRAPHICSSCENEGL
		class BQGraphicsScene : public QGraphicsScene, public BEntity
		{
			public:
				BQGraphicsScene() : QGraphicsScene(), m_bg_entities(0) {};
				virtual ~BQGraphicsScene() { /*deleteLater();*/ };
				const char* class_id() const { return "QGraphicsScene"; }

				virtual void construct();
				virtual Bbool onAddChild( BEntity* entity );

				virtual void drawBackground(QPainter *painter, const QRectF &);
				virtual void drawForeground(QPainter *painter, const QRectF &);
			
			private:
				BEntity* m_bg_entities;
		};
 
#endif
