#include "qmdiarea.h"
#include "qmdiwindow.h"
// #include "kernel/be_plugin_base_entity_types.h"
#include "kernel/be_lib_handler.h"
#include "qboxlayouts.h"

// #include <iostream>
// #include <QCloseEvent>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QRegularExpression>


	// QMDIAREA
		BQMdiArea::BQMdiArea()
		: QMdiArea()
		{
// 			setBaseSize(400, 500);  //HACK
// // 			setBackground(QColor(1,0,0,0));
// 			setAttribute(Qt::WA_OpaquePaintEvent);
// 			setWindowOpacity(0.9f);
// 			resize(400,400);
// 			setAcceptDrops(true);
			
			
//			setAutoFillBackground(false);
// 			setBackground(QColor(0,0,0,0));
// 			setAttribute(Qt::WA_OpaquePaintEvent);
			setWindowOpacity(1.0f);
			
		}

		Bbool BQMdiArea::onAddChild( BEntity* entity )
		{ 
			BQMdiWindow* subwindow = dynamic_cast<BQMdiWindow*>(entity);
			if ( subwindow )
			{
// 				setAlignment(qlayout_entity, Qt::AlignTop);
// 				setAlignment(qlayout_entity, Qt::AlignLeft);
// 				addLayout(qlayout_entity);
// 				std::cout << "BQMdiArea::onAddChild : BeQtMdiSubWindow" << std::endl;
				addSubWindow(subwindow);
// 				subwindow->resize(200,250);
				subwindow->show();
				return true;
			}

			QLayout* qlayout_entity = dynamic_cast<QLayout*>(entity);
			if ( qlayout_entity )
			{
// 				setAlignment(qlayout_entity, Qt::AlignTop);
// 				setAlignment(qlayout_entity, Qt::AlignLeft);
// 				addLayout(qlayout_entity);
				return true;

			}

// 			auto* qGraphicsView = dynamic_cast<QGraphicsView*>(entity);
// 			if ( qGraphicsView )
// 			{
// 				setViewport(qGraphicsView);
// 				return true;
// 			}

			QWidget* qwidget_entity = dynamic_cast<QWidget*>(entity);
			if ( qwidget_entity )
			{
// 					setAlignment(qwidget_entity, Qt::AlignTop);
// 					setAlignment(qwidget_entity, Qt::AlignLeft);
// 					addWidget(qwidget_entity);
				return true;
			}
// 			// if ( layout() )
// 			{
// 				QWidget* qwidget_entity = dynamic_cast<QWidget*>(entity.get());
// 				if ( qwidget_entity )
// 				{
// 					std::cout << "BeQtWindow::onAddChild : has layout" << std::endl;
// 					layout()->addWidget(qwidget_entity);
// 					qwidget_entity->show();
// 					showMinimized();
// 					showNormal();
// 					return true;
// 				}
// 			}
			return false;
		}	
		
		// FIXME onRemoveChild WITH removeSubWindow
		Bbool BQMdiArea::onRemoveChild( BEntity* entity )
		{ 
			auto subwindow = dynamic_cast<BQMdiWindow*>(entity);
			if ( subwindow )
			{
				removeSubWindow( subwindow );
				return true;
			}
// 
// // 			auto* qGraphicsView = dynamic_cast<QGraphicsView*>(entity);
// // 			if ( qGraphicsView )
// // 			{
// // // 				setViewport(0);
// // 				deleteLater();
// // 				return true;
// // 			}

			return false;
		}
		
		void BQMdiArea::dragEnterEvent(QDragEnterEvent *event)
		{
// 			std::cout << "drag event entered" << std::endl;
			if (event->mimeData()->hasText())
			{
				if (event->source() == this)
				{
					event->setDropAction(Qt::MoveAction);
					event->accept();
				}
				else
				{
// 					setStyleSheet("QMdiArea { background-color : white }");
// 					focusWidget();
// 					setBackground(QColor(1,0,0,0));
// 					setAttribute(Qt::WA_OpaquePaintEvent);
// 					setWindowOpacity(0.9f);
					setFrameStyle(1);
					setFrameRect(QRect(10, 10, 500, 300));
// 					repaint();

					event->acceptProposedAction();
				}
			}
			else
			{
				event->ignore();
			}
		}

		void BQMdiArea::dragLeaveEvent(QDragLeaveEvent *event)
		{
// 			std::cout << "drag event left" << std::endl;
			(void) event;
// 			setStyleSheet("QMdiArea { background-color : none }");
			setFrameStyle(0);
			event->ignore();
		}

		void BQMdiArea::dropEvent(QDropEvent *event)
		{
			if (event->mimeData()->hasText())
			{
				const QMimeData *mime = event->mimeData();
				QStringList pieces = mime->text().split(QRegularExpression("\\s+"), Qt::SplitBehaviorFlags::SkipEmptyParts);
// 				QPoint position = event->position().toPoint();
				QPoint hotSpot;

				QList<QByteArray> hotSpotPos = mime->data("application/x-hotspot").split(' ');
				if (hotSpotPos.size() == 2)
				{
					hotSpot.setX(hotSpotPos.first().toInt());
					hotSpot.setY(hotSpotPos.last().toInt());
				}

				foreach (QString piece, pieces)
				{
					addChild(piece.toStdString(), pluginManager()->create(this, piece.toStdString()));
				}

				if (event->source() == this) {
					event->setDropAction(Qt::MoveAction);
					event->accept();
				} else {
					event->acceptProposedAction();
				}
			}
			else
			{
				event->ignore();
			}
// 			setStyleSheet("QMdiArea { background-color : none }");
			setFrameStyle(0);
		}
