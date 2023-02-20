#include "qgraphicsscene.h"
// #include "kernel/be_lib_handler.h"
#include "qgraphicsproxywidget.h"

#include <QWidget>
#include <QPainter>
#include <GL/gl.h>

		void BQGraphicsScene::construct()
		{
// 			setItemIndexMethod(QGraphicsScene::NoIndex);
			// addRect(QRectF(0, 0, 100, 100), QPen(Qt::black), QBrush(Qt::green));
		}

		Bbool BQGraphicsScene::onAddChild( BEntity* entity )
		{ 
			QGraphicsProxyWidget* proxywidget = dynamic_cast<QGraphicsProxyWidget*>(entity);
			if ( proxywidget )
			{
				addItem(proxywidget);
				proxywidget->show();
				return true;
			}

			QWidget* widget = dynamic_cast<QWidget*>(entity);
			if ( widget )
			{
				addWidget(widget);
				widget->show();
				return true;
			}

			
			return false;
		}


		
		void BQGraphicsScene::drawBackground(QPainter *painter, const QRectF &)
		{
			// std::cout << "draw" << std::endl;

// 			painter->beginNativePainting();
// 				glFlush();
// 				glFinish();

// 			// RENDER MAIN CAMERA	
				glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
				
// 				BEntity* modelsystemchild = getChild(this, "GraphicsModelSystem", 1);
// 				// dynamic_cast it to BGraphicsModelSystem
// 				BGraphicsModelSystem* modelsystem = dynamic_cast<QBGraphicsModelSystem*>( modelsystemchild );
// 				if ( modelsystem )
// 					glUseProgram( m_effect->m_program.get()->handle() );
			

			// CHILDREN
				if ( m_bg_entities == 0 )
				{
					m_bg_entities = getChild("background", 1);
				}

				if ( m_bg_entities )
				{
					
					// MAKE IT ROTATE FIXME so yeah a transform entity and do this elsewhere
						
// 						f_count++;
// 
// 							QTransform tr;
// 							tr.reset();
// 							tr.setOrigin(btVector3(0.0f, -1.0f, -4.5f));
// 		// 					tr.getBasis().setEulerZYX( 0.0f, 0.0001f * t.getTotalMilliSeconds(), 0.0f );
// 							tr.getBasis().setEulerZYX( 0.0f, 0.001f * f_count, 0.0f );
// 							t_diff = t.getTotalMilliSeconds();
// 
// 						tr.getOpenGLMatrix( m_matrix );

					
					m_bg_entities->process_children();
				}
				
// 				glFlush();
// 				glFinish();
				

// 			painter->endNativePainting();
		}

		void BQGraphicsScene::drawForeground(QPainter *painter, const QRectF &)
		{
// 			painter->beginNativePainting();

// 			// CHILDREN	// NOT SURE THIS IS NEEDED
// 				BEntity* fg_entities = getChild(this, "foreground", 1);
// 				if ( fg_entities )
// 					fg_entities->process_children();

// 			painter->endNativePainting();
		}

// 		void BQGraphicsScene::drawForeground(QPainter *painter, const QRectF &)
// 		{
// 			painter->beginNativePainting();
// 
// 			// CHILDREN	// NOT SURE THIS IS NEEDED
// 				// if ( hasChildren() )
// 				// 	m_child_handler->process();
// 
// 			// clear
// 				glClearColor(1.0f, 1.0f, 1.0f, 0.0f );
// 				glClear(GL_COLOR_BUFFER_BIT);
// // 				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// 
// 				do_times(6)
// 				{
// 					int offset = dtc * 30 - 25;
// 				// Draw a Red 1x1 Square centered at origin
// 					glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
// 						glColor3f(0.0f, 0.0f, 1.0f); // Red
// 						glVertex2f(-10.5f+offset, -10.5f);    // x, y
// 						glVertex2f( 10.5f+offset, -10.5f);
// 						glVertex2f( 10.5f+offset,  10.5f);
// 						glVertex2f(-10.5f+offset,  10.5f);
// 					glEnd();
// 				}
// 				
// 			// Render now
// 				glFlush();
// 
// 			painter->endNativePainting();
// 		}
