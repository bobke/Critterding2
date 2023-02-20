#include "qopenglwidget.h"
#include "qgraphicsscene.h"
#include "qgraphicsview.h"

		BQOpenGLWidget::BQOpenGLWidget()
		: QOpenGLWidget()
		{
// 			QSurfaceFormat format;
// 			format.setRedBufferSize(8);
// 			format.setGreenBufferSize(8);
// 			format.setBlueBufferSize(8);
// 			format.setAlphaBufferSize(8);
// 			format.setDepthBufferSize(16);
// 			format.setSamples(4);
// 			format.setStencilBufferSize(8);
// 			format.setSwapInterval(0);	// VSYNC
// // 			format.setSwapBehavior(QSurfaceFormat::TripleBuffer);
// 			format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
// // 			format.setSwapBehavior(QSurfaceFormat::SingleBuffer);
// 
// 			format.setProfile(QSurfaceFormat::CompatibilityProfile);  //CoreProfile
// // 			format.setProfile(QSurfaceFormat::CoreProfile);  //CoreProfile
// 			format.setVersion(4,5);
// // 			format.setVersion(2,2);
// 			
// // 			format.setDirectRendering(1);
// // 			format.setDoubleBuffer(1);
// // 			format.setAlpha(true);
// 
// 			setFormat(format);
	
			
			m_format.setProfile(QSurfaceFormat::CompatibilityProfile);  //CoreProfile
			m_format.setVersion(4,5);
// 			m_format.setProfile(QSurfaceFormat::CoreProfile);  //CoreProfile
// 			m_format.setVersion(2,2);

			m_format.setRedBufferSize(8);
			m_format.setGreenBufferSize(8);
			m_format.setBlueBufferSize(8);
			m_format.setAlphaBufferSize(8);
			m_format.setDepthBufferSize(16);
			m_format.setSamples(4);
			m_format.setStencilBufferSize(8);
// 			m_format.setSwapBehavior(QSurfaceFormat::TripleBuffer);
			m_format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
// 			m_format.setSwapBehavior(QSurfaceFormat::SingleBuffer);


			m_format.setSwapInterval(0);	// VSYNC
			

			setFormat(m_format);
			QSurfaceFormat::setDefaultFormat(m_format);
			
		}

		Bbool BQOpenGLWidget::onAddChild( BEntity* entity )
		{ 
			QGraphicsScene* scene = dynamic_cast<QGraphicsScene*>(entity);
			if ( scene )
			{
				scene->setParent(this);

				QGraphicsView* view = dynamic_cast<QGraphicsView*>(BEntity::parent());
				if ( view )
				{
					view->setScene(scene);
				}
				return true;
			}

			return false;
		}

