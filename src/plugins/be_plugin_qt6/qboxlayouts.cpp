#include "qboxlayouts.h"
#include "qrasterwindow.h"
#include "qmdiwindow.h"
// #include "kernel/be_plugin_base_entity_types.h"
#include <iostream>
#include <QWidget>

	// QVBOXLAYOUT
		BQVBoxLayout::BQVBoxLayout()
		: QVBoxLayout()
		{
			setSpacing(0);
// 			setMargin(0);
			setContentsMargins(0,0,0,0); // HACK
			setSizeConstraint(QLayout::SetMinimumSize);
			setAlignment(Qt::AlignTop | Qt::AlignLeft);
		}

		Bbool BQVBoxLayout::onAddChild( BEntity* entity )
		{ 
			// FIXME DO NOT CAST BUT SIMPLY CHECK TYPES, THEN CAST IF NEEDED
// 			std::cout << "BQVBoxLayout::onAddChild" << std::endl;

			QLayout* qlayout_entity = dynamic_cast<QLayout*>(entity);
			if ( qlayout_entity )
			{
// 				std::cout << "BQHBoxLayout::onAddChild : is QLayout" << std::endl;
				addLayout(qlayout_entity);
				setAlignment(qlayout_entity, Qt::AlignTop | Qt::AlignLeft);
				return true;
			}

			BQRasterWindow* window = dynamic_cast<BQRasterWindow*>(entity);
			if ( window )
			{
				QWidget *wrapper = QWidget::createWindowContainer(window);
				addWidget(wrapper, Qt::AlignTop | Qt::AlignLeft);
				return true;
			}

			QWidget* qwidget_entity = dynamic_cast<QWidget*>(entity);
			if ( qwidget_entity )
			{
// 				addWidget(qwidget_entity, Qt::AlignTop | Qt::AlignLeft);
				addWidget(qwidget_entity);

				// REDRAW HASTLE IN MDIWINDOW
				{
					qwidget_entity->show();
					// FIND MDI WINDOW
					BEntity* p = dynamic_cast<BEntity*>(this)->parent();
					bool found(false);
					while ( !found )
					{
						auto candidate = dynamic_cast<BQMdiWindow*>(p);
						if ( candidate )
						{
							found = true;
							candidate->adjustSize();
						}
						else
						{
							p = p->parent();
							if ( !p )
								break;
						}
					}
				}
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
		// NOTE: THIS SEEMS TO BE HANDLED AUTOMATICALLY, NO LEAKS
// 		Bbool BQVBoxLayout::onRemoveChild( BEntity* entity )
// 		{
// 			QLayout* qlayout_entity = dynamic_cast<QLayout*>(entity);
// 			if ( qlayout_entity )
// 			{
// 				removeItem(qlayout_entity);
// 				return true;
// 			}
// 			else
// 			{
// 				QWidget* qwidget_entity = dynamic_cast<QWidget*>(entity);
// 				if ( qwidget_entity )
// 				{
// 					removeWidget(qwidget_entity);
// // 						setSizeConstraint(QLayout::SetMinimumSize);
// // 						setAlignment(Qt::AlignTop);
// // 						setAlignment(Qt::AlignLeft);
// 					return true;
// 				}
// 			}
// 			return false;
// 		}
		
		
		

	// QHBOXLAYOUT
		BQHBoxLayout::BQHBoxLayout()
		: QHBoxLayout()
		{
			setSpacing(0);
// 			setMargin(0);
			setContentsMargins(0,0,0,0); // HACK
			setSizeConstraint(QLayout::SetMinimumSize);
			setAlignment(Qt::AlignTop | Qt::AlignLeft);
		}

		Bbool BQHBoxLayout::onAddChild( BEntity* entity )
		{ 
// 			std::cout << "BQHBoxLayout::onAddChild" << std::endl;

			QLayout* qlayout_entity = dynamic_cast<QLayout*>(entity);
			if ( qlayout_entity )
			{
// 				std::cout << "BQHBoxLayout::onAddChild : is QLayout" << std::endl;
				addLayout(qlayout_entity);
				setAlignment(qlayout_entity, Qt::AlignTop | Qt::AlignLeft);
				return true;
			}

			BQRasterWindow* window = dynamic_cast<BQRasterWindow*>(entity);
			if ( window )
			{
				QWidget *wrapper = QWidget::createWindowContainer(window);
				addWidget(wrapper, Qt::AlignTop | Qt::AlignLeft);
				return true;
			}

			QWidget* qwidget_entity = dynamic_cast<QWidget*>(entity);
			if ( qwidget_entity )
			{
// 				addWidget(qwidget_entity, Qt::AlignTop | Qt::AlignLeft);
				addWidget(qwidget_entity);

				// REDRAW HASTLE IN MDIWINDOW
				{
					qwidget_entity->show();
					// FIND MDI WINDOW
					BEntity* p = dynamic_cast<BEntity*>(this)->parent();
					bool found(false);
					while ( !found )
					{
						auto candidate = dynamic_cast<BQMdiWindow*>(p);
						if ( candidate )
						{
							found = true;
							candidate->adjustSize();
						}
						else
						{
							p = p->parent();
							if ( !p )
								break;
						}
					}
				}
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
		// NOTE: THIS SEEMS TO BE HANDLED AUTOMATICALLY, NO LEAKS
// 		Bbool BQHBoxLayout::onRemoveChild( BEntity* entity )
// 		{
// 			QLayout* qlayout_entity = dynamic_cast<QLayout*>(entity);
// 			if ( qlayout_entity )
// 			{
// 				removeItem(qlayout_entity);
// 				return true;
// 			}
// 			else
// 			{
// 				QWidget* qwidget_entity = dynamic_cast<QWidget*>(entity);
// 				if ( qwidget_entity )
// 				{
// 					removeWidget(qwidget_entity);
// // 						setSizeConstraint(QLayout::SetMinimumSize);
// // 						setAlignment(Qt::AlignTop);
// // 						setAlignment(Qt::AlignLeft);
// 					return true;
// 				}
// 			}
// 			return false;
// 		} 
