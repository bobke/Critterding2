#include "qgraphicsview.h"
#include "qgraphicsscene.h"
#include "qopenglwidget.h"
#include <QOpenGLWidget>
#include <iostream>
#include "kernel/be_timer.h"

// #include <iostream>

	// QGRAPHICSVIEW
		BQGraphicsView::BQGraphicsView()
		: QGraphicsView()
		{
			setProcessing();
			setStyleSheet( "QGraphicsView { border-style: none; padding: 0px; margin: 0px }" );
			setCacheMode(QGraphicsView::CacheNone);
			setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
			setOptimizationFlag(OptimizationFlag::IndirectPainting);
			setDragMode(QGraphicsView::ScrollHandDrag);
			// setOptimizationFlag(DontAdjustForAntialiasing);
		}
		
		BQGraphicsView::~BQGraphicsView()
		{
			close();
			deleteLater();
		}

		void BQGraphicsView::process()
		{
// 			std::cout << "view" << std::endl;
			
// 			static unsigned int t_diff(0);
// 			static unsigned int f_count(0);
// 			static BeTimer t;
// 			t.mark();
// 			if ( (t.getTotalMilliSeconds() - t_diff) > 20 )
// 				std::cout << "DIFF MODEL " << id() << " " << (t.getTotalMilliSeconds() - t_diff) << std::endl;
// 			t_diff = t.getTotalMilliSeconds();
			
			
			viewport()->update();
		}

		Bbool BQGraphicsView::onAddChild( BEntity* entity )
		{ 
			QOpenGLWidget* glwidget = dynamic_cast<QOpenGLWidget*>(entity);
			if ( glwidget )
			{
				setViewport(glwidget);
				show();
				return true;
			}

			BQGraphicsScene* scene = dynamic_cast<BQGraphicsScene*>(entity);
			if ( scene )
			{
				setScene(scene);
				show();
				return true;
			}

			return false;
		}
	
		Bbool BQGraphicsView::onRemoveChild( BEntity* entity )
		{ 
			BQGraphicsScene* scene = dynamic_cast<BQGraphicsScene*>(entity);
			if ( scene )
			{
				setViewport(NULL);
				setScene(NULL);
				return true;
			}
			return false;
		} 
